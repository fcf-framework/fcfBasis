#include <iostream>
#include <array>
#include <type_traits>
#include <memory>
#include <chrono>

#include "../../libraries/fcfTest/test.hpp"

#include "../../../functions.hpp"
#include "../../../FunctionSignature.hpp"
#include "../../../convert.hpp"
#include "../../../Details/IndexableFunction/Storage.hpp"

bool enable_log = false;
namespace fcf {

  template<size_t StaticSize, typename Ty, bool CopyForMemory = true>
  class StaticVector {
    enum {
      STEP = StaticSize > 8 ? StaticSize : 8
    };
    public:
      StaticVector()
        : _sdata(0)
        , _cdata(StaticSize) {
        _pdata = &_adata[0];
      }

      StaticVector(size_t a_size) 
        : _sdata(0)
        , _cdata(StaticSize) {
        _pdata = &_adata[0];
        _reserve((int)(a_size / STEP) * STEP + STEP);
        _sdata = a_size;
      }


      StaticVector(size_t a_size, const Ty& a_fill)
        : _sdata(0)
        , _cdata(StaticSize) {
        _pdata = &_adata[0];
        _reserve((int)(a_size / STEP) * STEP + STEP);
        _sdata = a_size;
        std::fill(_pdata, _pdata + _sdata, a_fill);
      }

      Ty* get(){
        return _pdata;
      }

      const Ty* get() const{
        return _pdata;
      }

      size_t size() const{
        return _sdata;
      }

      bool empty() const{
        return !_sdata;
      }

      void clear(){
        _reserve(0);
      }

      void push_back(const Ty& a_value){
        if (_sdata == _cdata){
          _reserve(_cdata + STEP);
        }
        _pdata[_sdata++] = a_value;
      }

      StaticVector(const StaticVector& a_source){
        operator=(a_source);
      }

      StaticVector& operator=(const StaticVector& a_source){
        _sdata = a_source._sdata;
        if (a_source._sdata <= StaticSize) {
          std::copy(&a_source._pdata[0], &a_source._pdata[a_source._sdata], &_adata[0]);
          _mdata.reset();
          _pdata = &_adata[0];
          _cdata = StaticSize;
        } else if (CopyForMemory) {
          _mdata.reset(new Ty[a_source._cdata], [](Ty *p) { delete[] p; });
          std::copy(&a_source._pdata[0], &a_source._pdata[a_source._sdata], _mdata.get());
          _pdata = _mdata.get();
          _cdata = a_source._cdata;
        } else {
          _mdata = a_source._mdata;
          _pdata = _mdata.get();
          _cdata = a_source._cdata;
        }
        return *this;
      }

    private:
      void _reserve(size_t a_size){
        if (a_size > StaticSize) {
          std::shared_ptr<Ty> sp(new Ty[a_size], [](Ty *p) { delete[] p; });
          size_t size = std::min(_sdata, a_size);
          std::copy(_pdata, _pdata + size, sp.get());
          _mdata = sp;
          _pdata = _mdata.get();
          _sdata = size;
          _cdata = a_size;
        } else if (_sdata <= StaticSize) {
          _sdata = std::min(_sdata, a_size);
          _cdata = StaticSize;
        } else {
          size_t size = std::min(_sdata, a_size);
          std::copy(_pdata, _pdata + size, &_adata[0]);
          _sdata = a_size;
          _pdata = &_adata[0];
          _cdata = StaticSize;
          _mdata.reset();
        }
      }

      Ty                  _adata[StaticSize];
      Ty*                 _pdata;
      std::shared_ptr<Ty> _mdata;
      size_t              _cdata;
      size_t              _sdata;
  };

  enum ConversionMode{
    CM_NONE = 0,
    CM_RESOLVE = 1,
    CM_CONVERT = 2,
    CM_DYNAMIC_RESOLVE = 3,
  };

  struct Conversion {
    ConversionMode mode;
    unsigned int   type;
    unsigned int   index;
    void*          converter;
  };

  struct DynamicCall {
    bool                          complete;
    bool                          dynamicCaller;
    void*                         function;
    void*                         caller;
    StaticVector<8, Conversion>   conversions;
    std::string                   name;

    DynamicCall()
      : complete(false)
      , dynamicCaller(false)
      , function(0)
      , caller(0)
    {
    }
  };

  namespace Details {
    namespace IndexableFunction {

      template <int IndexStop, int ... IndexPack>
      struct Sequence;

      template <int IndexStop>
      struct Sequence<IndexStop>{
        typedef Sequence<IndexStop> type;
      };

      template <int IndexStop, int StartIndex, int ... IndexPack>
      struct Sequence<IndexStop, StartIndex, IndexPack...> {
        typedef typename Sequence<IndexStop, StartIndex-1, StartIndex, IndexPack...>::type type;
      };

      template <int IndexStop, int ... IndexPack>
      struct Sequence<IndexStop, IndexStop, IndexPack...> {
        typedef Sequence<IndexStop, IndexStop, IndexPack...> type;
      };

      template <int IndexStop>
      struct Sequence<IndexStop, -1> {
        typedef Sequence<IndexStop> type;
      };

      template <int IndexStop>
      struct Sequence<IndexStop, IndexStop-1> {
        typedef Sequence<IndexStop> type;
      };

      struct ConversionNode {
        ConversionNode* prev;
        ConversionNode* next;
        Conversion      conversion;
      };

      template <int ArgIndex, int ArgSize, typename ... TArgPack>
      struct IndexableDynamicCallProcessor{
        template <typename TDynamicCallInfo, typename TArgTuple>
        void operator()(const TDynamicCallInfo& a_procInfo, unsigned int a_stateOffset, TArgTuple& a_argTuple){
          typedef typename std::remove_cv<typename std::remove_pointer<typename std::remove_cv<typename std::remove_reference<decltype(std::get<ArgIndex>(a_argTuple))>::type>::type>::type>::type arg_type;
          unsigned int currentType = BaseFunctionSignature::getSimpleType(Type<arg_type>().index());
          while (a_stateOffset < a_procInfo.conversions.size() && a_procInfo.conversions.get()[a_stateOffset].index == ArgIndex){
            if (a_procInfo.conversions.get()[a_stateOffset].mode == CM_RESOLVE) {
              arg_type& ref = (arg_type&)*std::get<ArgIndex>(a_argTuple);
              void* rawptr = (void*)Type<arg_type, RawDataSpecificator>()(&ref);
              currentType = a_procInfo.conversions.get()[a_stateOffset].type;
              std::get<ArgIndex>(a_argTuple) = (arg_type*)rawptr;
            } else if (a_procInfo.conversions.get()[a_stateOffset].mode == CM_CONVERT) {
              Variant arg(a_procInfo.conversions.get()[a_stateOffset].type, (const void*)std::get<ArgIndex>(a_argTuple), currentType, (ConvertOptions*)0, (ConvertFunction)a_procInfo.conversions.get()[a_stateOffset].converter);
              currentType = a_procInfo.conversions.get()[a_stateOffset].type;
              std::get<ArgIndex>(a_argTuple) = (arg_type*)arg.ptr();
              IndexableDynamicCallProcessor<ArgIndex, ArgSize, TArgPack...>()(a_procInfo, a_stateOffset + 1, a_argTuple);
              return;
            }
            ++a_stateOffset;
          }
          IndexableDynamicCallProcessor<ArgIndex + 1, ArgSize, TArgPack...>()(a_procInfo, a_stateOffset, a_argTuple);
        }
      };

      template <int ArgSize, typename ... TArgPack>
      struct IndexableDynamicCallProcessor<ArgSize, ArgSize, TArgPack...>{
        template <typename TDynamicCallInfo, typename TArgTuple>
        void operator()(const TDynamicCallInfo& a_procInfo, unsigned int a_stateOffset, TArgTuple& a_argTuple){
          typedef typename Sequence<0, ArgSize-1>::type sequence_type;
          _call(a_procInfo, a_stateOffset, a_argTuple, sequence_type());
        }

        private:
          template <typename TDynamicCallInfo, typename TArgTuple, int... SequencePack>
          void _call(const TDynamicCallInfo& a_procInfo, unsigned int a_stateOffset, TArgTuple& a_argTuple, Sequence<0, SequencePack...> a_sequence){
            typedef void (*simple_function_type)(void*, const typename std::remove_cv< typename std::remove_reference<TArgPack>::type >::type& ...);
            simple_function_type caller = (simple_function_type)a_procInfo.caller;
            caller(a_procInfo.function, *std::get<SequencePack>(a_argTuple)...);
          }
      };

      struct DynamicCallProcessor{
        template <typename TDynamicCallInfo, typename... TArgPack>
        void operator()(const TDynamicCallInfo& a_procInfo, unsigned int a_stateOffset, const TArgPack&... a_argPack){
          typedef typename Sequence<0, sizeof...(a_argPack)>::type sequence_type;
          std::tuple<const typename std::remove_cv<typename std::remove_reference<TArgPack>::type>::type*...> tuple(&a_argPack...);
          IndexableDynamicCallProcessor<0, sizeof...(a_argPack), TArgPack...>()(a_procInfo, a_stateOffset, tuple);
        }
      };

      template <typename TTuple, typename TType, int Index>
      struct TupleElementReplacer {
        typedef typename Sequence<0, Index-1>::type                               left_sequence_type;
        typedef typename Sequence<Index+1, std::tuple_size<TTuple>::value >::type right_sequence_type;
        template<int... LeftSeqPack, int... RightSeqPack>
        auto gen(Sequence<0, LeftSeqPack...>, Sequence<Index+1, RightSeqPack...>) -> decltype(std::tuple<
              decltype(std::get<LeftSeqPack>(TTuple()))...,
              TType,
              decltype(std::get<RightSeqPack>(TTuple()))...
            >()) {
          return std::tuple<
              decltype(std::get<LeftSeqPack>(TTuple()))...,
              TType,
              decltype(std::get<RightSeqPack>(TTuple()))...
            >();
        }
        typedef decltype(gen(left_sequence_type(), right_sequence_type())) type;
      };

      template <typename TPtrTuple>
      struct InvariantArgSelectorData{
        const char*                                       name;
        DynamicCall*                                      result;
        fcf::Details::IndexableFunction::Groups::iterator groupIterator;
        BaseFunctionSignature&                            functionSignature;
        TPtrTuple&                                        tuple;
        bool                                              strictSource;
        bool                                              dynamicCaller;
      };

      template <int Index, int Size, typename TPtrTuple>
      struct InvariantArgSelector {
        inline void operator()(ConversionNode* a_node, InvariantArgSelectorData<TPtrTuple>& a_iasd, bool a_ignoreOrigin, bool a_dynamicCaller){
          unsigned int sourceTypeIndex       = a_iasd.functionSignature.pacodes[Index];
          unsigned int sourceSimpleTypeIndex = BaseFunctionSignature::getSimpleType(sourceTypeIndex);

          typedef
            typename std::remove_cv<
              typename std::remove_pointer<
                typename std::tuple_element<Index, TPtrTuple>::type
              >::type
            >::type current_arg_type;
          unsigned int originSourceSimpleTypeIndex = Type<current_arg_type>().index();

          bool invariantRawType = false;
          unsigned int invariantIndex = 0;
          if (originSourceSimpleTypeIndex == sourceSimpleTypeIndex) {
            Type<current_arg_type, RawDataSpecificator>()(std::get<Index>(a_iasd.tuple), &invariantIndex, &invariantRawType);
          } else {
            const fcf::Details::TypeInfo* ti = Details::typeStorage.get(sourceSimpleTypeIndex);
            if (ti && ti->rawDataResolver) {
              ti->rawDataResolver(std::get<Index>(a_iasd.tuple), &invariantIndex, &invariantRawType, 0);
            }
          }

          if (a_iasd.strictSource && invariantIndex) {
            ConversionNode curnode;
            curnode.prev = 0;
            curnode.next = 0;
            curnode.conversion.index = Index;
            curnode.conversion.type = invariantIndex;
            curnode.conversion.mode = CM_RESOLVE;
            if (a_node){
              a_node->next = &curnode;
              curnode.prev = a_node;
            }
            a_iasd.functionSignature.pacodes[Index] = a_iasd.functionSignature.getSimpleCallType(invariantIndex);
            InvariantArgSelector<Index, Size, TPtrTuple>()(&curnode, a_iasd, a_ignoreOrigin, a_dynamicCaller);
            a_iasd.functionSignature.pacodes[Index] = sourceTypeIndex;
            if (a_iasd.result->complete) {
              return;
            }
            if (a_node) {
              a_node->next = 0;
            }
          }

          InvariantArgSelector<Index + 1, Size, TPtrTuple>()(a_node, a_iasd, a_ignoreOrigin, a_dynamicCaller);
          if (a_iasd.result->complete) {
            return;
          }

          if (a_iasd.strictSource) {
            Details::IndexableFunction::CallersTree::iterator treeIt = a_iasd.groupIterator->second.callersTree.find(a_iasd.functionSignature.asize);
            if (treeIt != a_iasd.groupIterator->second.callersTree.end()){
              const Details::TypeInfo* ti =  Details::typeStorage.get(sourceSimpleTypeIndex);
              BaseFunctionSignature shortSign = a_iasd.functionSignature;
              for(size_t i = Index+1; i < shortSign.asize; ++i){
                shortSign.pacodes[i] = 0;
              }
              CallersMap::iterator rightIt = treeIt->second.lower_bound(shortSign);
              CallersMap::iterator leftIt = rightIt;
              if (rightIt != treeIt->second.end()) {
                if (leftIt != treeIt->second.end()) {
                  --leftIt;
                }

                // right side
                unsigned int rtypeIndex = rightIt->first.pacodes[Index];
                unsigned int rtypeSimpleIndex = BaseFunctionSignature::getSimpleType(rtypeIndex);
                ConvertFunction convertFunction = getConvertFunction(sourceSimpleTypeIndex, rtypeSimpleIndex, 0);
                if (convertFunction){
                  ConversionNode curnode;
                  curnode.prev = 0;
                  curnode.next = 0;
                  curnode.conversion.index = Index;
                  curnode.conversion.type = rtypeSimpleIndex;
                  curnode.conversion.mode = CM_CONVERT;
                  curnode.conversion.converter = (void*)convertFunction;
                  if (a_node){
                    a_node->next = &curnode;
                    curnode.prev = a_node;
                  }
                  a_iasd.functionSignature.pacodes[Index] = a_iasd.functionSignature.getSimpleCallType(rtypeIndex);
                  InvariantArgSelector<Index + 1, Size, TPtrTuple>()(&curnode, a_iasd, a_ignoreOrigin, a_dynamicCaller);
                  a_iasd.functionSignature.pacodes[Index] = sourceTypeIndex;
                  if (a_iasd.result->complete) {
                    return;
                  }
                  if (a_node) {
                    a_node->next = 0;
                  }
                }

                // left side
                if (leftIt != treeIt->second.end()) {
                  unsigned int rtypeIndex = leftIt->first.pacodes[Index];
                  unsigned int rtypeSimpleIndex = BaseFunctionSignature::getSimpleType(rtypeIndex);
                  ConvertFunction convertFunction = getConvertFunction(sourceSimpleTypeIndex, rtypeSimpleIndex, 0);
                  if (convertFunction){
                    ConversionNode curnode;
                    curnode.prev = 0;
                    curnode.next = 0;
                    curnode.conversion.index = Index;
                    curnode.conversion.type = rtypeSimpleIndex;
                    curnode.conversion.mode = CM_CONVERT;
                    curnode.conversion.converter = (void*)convertFunction;
                    if (a_node){
                      a_node->next = &curnode;
                      curnode.prev = a_node;
                    }
                    a_iasd.functionSignature.pacodes[Index] = a_iasd.functionSignature.getSimpleCallType(rtypeIndex);
                    InvariantArgSelector<Index + 1, Size, TPtrTuple>()(&curnode, a_iasd, a_ignoreOrigin, a_dynamicCaller);
                    a_iasd.functionSignature.pacodes[Index] = sourceTypeIndex;
                    if (a_iasd.result->complete) {
                      return;
                    }
                    if (a_node) {
                      a_node->next = 0;
                    }
                  }
                }

              } // if (leftIt != treeIt->second.end()) end
            } // if (treeIt != a_iasd.groupIterator->second.callersTree.end()) end
          } // if (a_iasd.strictSource) end

          if (!a_iasd.strictSource && invariantRawType) {
            ConversionNode curnode;
            curnode.prev = 0;
            curnode.next = 0;
            curnode.conversion.index = Index;
            curnode.conversion.type = 0;
            curnode.conversion.mode = CM_DYNAMIC_RESOLVE;
            curnode.conversion.converter = (void*)0;
            if (a_node){
              a_node->next = &curnode;
              curnode.prev = a_node;
            }

            unsigned int origTypeIndex = a_iasd.functionSignature.pacodes[Index];
            a_iasd.functionSignature.pacodes[Index] = 0;

            bool origDynamicCaller = a_iasd.dynamicCaller;
            a_iasd.dynamicCaller = true;

            InvariantArgSelector<Index + 1, Size, TPtrTuple>()(&curnode, a_iasd, a_ignoreOrigin, true);

            a_iasd.dynamicCaller = origDynamicCaller;
            a_iasd.functionSignature.pacodes[Index] = origTypeIndex;

            if (a_iasd.result->complete) {
              return;
            }
            if (a_node) {
              a_node->next = 0;
            }
          }
        } // method end
      };

      template <int Size, typename TPtrTuple>
      struct InvariantArgSelector<Size, Size, TPtrTuple >{
        inline void operator()(ConversionNode* a_node, InvariantArgSelectorData<TPtrTuple>& a_iasd, bool a_ignoreOrigin, bool a_dynamicCaller){
          if (a_ignoreOrigin && !a_node) {
            return;
          }

          if (!a_iasd.dynamicCaller) {
            fcf::Details::IndexableFunction::Callers::iterator callerInfoIt =
              a_iasd.groupIterator->second.callers.find(a_iasd.functionSignature);
            if (callerInfoIt == a_iasd.groupIterator->second.callers.end()) {
              return;
            }

            a_iasd.result->complete = true;
            a_iasd.result->caller   = callerInfoIt->second.caller;
            a_iasd.result->function = Details::IndexableFunction::getStorage().functions[callerInfoIt->second.index].function;

          } else {
            Details::IndexableFunction::CallersTree::iterator treeIt = a_iasd.groupIterator->second.callersTree.find(a_iasd.functionSignature.asize);
            if (treeIt != a_iasd.groupIterator->second.callersTree.end()) {
              Details::IndexableFunction::CallersMap::const_iterator it = treeIt->second.begin();
              for(; it != treeIt->second.end(); ++it) {
                unsigned int argIndex = 0;
                for(; argIndex < a_iasd.functionSignature.asize; ++argIndex){
                  if (
                       a_iasd.functionSignature.pacodes[argIndex] != 0 &&
                       a_iasd.functionSignature.pacodes[argIndex] != it->first.pacodes[argIndex]
                     ){
                    break;
                  }
                }
                if (argIndex == a_iasd.functionSignature.asize) {
                  break;
                }
              }
              if (it != treeIt->second.end()){
                a_iasd.result->complete = true;
                a_iasd.result->dynamicCaller = true;
                a_iasd.result->name = a_iasd.name;
              }
            }
          }

          if (a_iasd.result->complete) {
            if (a_node) {
              ConversionNode* begNode = a_node;
              while(begNode->prev){
                begNode = begNode->prev;
              }
              while(begNode){
                if (begNode->conversion.mode != CM_NONE) {
                  a_iasd.result->conversions.push_back(begNode->conversion);
                }
                begNode = begNode->next;
              }
            }
          }

        }
      };


    } // namespace Details
  } // namespace IndexableFunction

  template <typename TRes, typename... TArgPack>
  class DynamicCallSeeker {
    protected:

      struct State {
        typedef StaticVector<8, Conversion, false> conversions_type;

        bool             init;
        conversions_type conversions;
        bool             strictSource;
      };

    public:
      template <typename... TCurrentArgPack>
      void operator()(const char* a_functionName, DynamicCall* a_result, const TCurrentArgPack&... a_argPack){
        State state;
        state.init = true;
        state.strictSource = !!sizeof...(TCurrentArgPack);
        this->call(a_functionName, a_result, state, a_argPack...);
      }

    protected:
      template <typename... TCurrentArgPack>
      void call(const char* a_functionName, DynamicCall* a_result, State& a_state, const TCurrentArgPack&... a_argPack){
        fcf::Details::IndexableFunction::Groups::iterator groupIt = fcf::Details::IndexableFunction::getStorage().groups.find(a_functionName);
        if (groupIt == Details::IndexableFunction::getStorage().groups.end()) {
          throw std::runtime_error("Function not found.");
        }

        FunctionSignature<TRes (TArgPack...)> functionSignature;
        functionSignature.applySimpleCallSignature();

        if (a_state.init) {
          a_state.init = false;
          a_result->complete = false;
          a_result->dynamicCaller = false;
          a_result->caller = 0;
          a_result->function = 0;
          a_result->conversions.clear();
        }

        fcf::Details::IndexableFunction::Callers::iterator callerInfoIt =
          groupIt->second.callers.find(functionSignature);

        typedef std::tuple<const typename std::remove_cv< typename std::remove_reference<TArgPack>::type >::type *...> ptr_tuple_type;
        ptr_tuple_type ptr_tuple(&a_argPack...);
        Details::IndexableFunction::InvariantArgSelectorData<ptr_tuple_type> iasd = {a_functionName, a_result, groupIt, functionSignature, ptr_tuple, a_state.strictSource};
        {
          typedef Details::IndexableFunction::InvariantArgSelector<sizeof...(a_argPack), sizeof...(a_argPack), ptr_tuple_type> selector_type;
          selector_type()(0, iasd, false, false);
          if (iasd.result->caller){
            return;
          }
        }
        {
          typedef Details::IndexableFunction::InvariantArgSelector<0, sizeof...(TArgPack), ptr_tuple_type> selector_type;
          selector_type()(0, iasd, true, false);
        }

        if (!a_result->complete) {
          throw std::runtime_error("Function not found. No signature found.");
        }
      }
  };


  template <typename... TArgPack>
  void dynamicCall(const char* a_functionName, const TArgPack& ... a_argPack) {
    fcf::DynamicCall dc;
    fcf::DynamicCallSeeker<void, TArgPack...>()("random", &dc, a_argPack...);
    Details::IndexableFunction::DynamicCallProcessor()(dc, 0, a_argPack...);
  }

  template <typename... TArgPack>
  void dynamicCall(const DynamicCall* a_dc, const TArgPack& ... a_argPack) {
    if (a_dc->dynamicCaller) {
      dynamicCall(a_dc->name.c_str(), a_argPack...);
    } else {
      Details::IndexableFunction::DynamicCallProcessor()(*a_dc, 0, a_argPack...);
    }
  }

} // namespace fcf

void deepIndexNearestCaller(){
  std::cout << "Start deepIndexNearestCaller..." << std::endl; 

  {
    int arr[10];
    std::fill(std::begin(arr), std::end(arr), 99);
    fcf::Variant v((short)10);
    fcf::dynamicCall("random", &arr[0], &arr[10], 0, v);
    for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
      FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
    }
  }
  {
    int arr[10];
    std::fill(std::begin(arr), std::end(arr), 99);
    fcf::Variant v((long long)10);
    fcf::dynamicCall("random", &arr[0], &arr[10], 0, v);
    for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
      FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
    }
  }
  {
    int arr[10];
    std::fill(std::begin(arr), std::end(arr), 99);
    fcf::Variant v(std::string("10"));
    fcf::dynamicCall("random", &arr[0], &arr[10], 0, v);
    for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
      FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
    }
  }
  {
    int arr[10];
    std::fill(std::begin(arr), std::end(arr), 99);
    fcf::Variant v(std::string("10"));
    fcf::DynamicCall dc;
    fcf::DynamicCallSeeker<void, int*, int*, int, fcf::Variant>()("random", &dc);
    fcf::dynamicCall(&dc, &arr[0], &arr[10], 0, v);
    for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
      FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
    }
  }

}

void deepIndexSimpleCaller(){
  std::cout << "Start deepIndexSimpleCaller..." << std::endl; 
  {
    bool except = false;
    try {
      fcf::DynamicCall dc;
      fcf::DynamicCallSeeker<void, int*, int*, int, bool>()("random", &dc);
    } catch(...) {
      except = true;
    }
    FCF_TEST(except == true);
  }
  {
    fcf::DynamicCall dc;
    fcf::DynamicCallSeeker<void, int*, int*, int, int>()("random", &dc);
    int arr[10];
    std::fill(std::begin(arr), std::end(arr), 99);
    fcf::dynamicCall(&dc, &arr[0], &arr[10], 0, 10);
    for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
      FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
    }
  }
  {
    fcf::Variant variant((int)10);
    fcf::DynamicCall dc;
    fcf::DynamicCallSeeker<void, int*, int*, int, const fcf::Variant>()("random", &dc, (int*)0, (int*)0, (int)0, variant);
    int arr[10];
    std::fill(std::begin(arr), std::end(arr), 99);
    fcf::dynamicCall(&dc, &arr[0], &arr[10], 0, variant);
    for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
      FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
    }
  }
  {
    fcf::Variant variant((int)10);
    fcf::DynamicCall dc;
    fcf::DynamicCallSeeker<void, int*, int*, int, const fcf::Variant&>()("random", &dc, (int*)0, (int*)0, (int)0, variant);
    int arr[10];
    std::fill(std::begin(arr), std::end(arr), 99);
    fcf::dynamicCall(&dc, &arr[0], &arr[10], 0, variant);
    for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
      FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
    }
  }
  {
    int arr[10];
    std::fill(std::begin(arr), std::end(arr), 99);
    fcf::dynamicCall("random", &arr[0], &arr[10], 0, 10);
    for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
      FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
    }
  }
  enable_log = true;
  std::cout <<  "Start test" << std::endl;
  {
    int arr[10];
    std::fill(std::begin(arr), std::end(arr), 99);
    fcf::Variant v((int)10);
    fcf::dynamicCall("random", &arr[0], &arr[10], 0, v);
    for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
      FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
    }
  }
  enable_log = false;
  std::cout <<  "End test" << std::endl;
  
  //duration test
  {
    unsigned long long defaultSize = 100000;
    unsigned long long defaultSizeForDetect = defaultSize * 100;
    unsigned long long defaultDuration = 0;
    {
      int arr[10];
      std::fill(std::begin(arr), std::end(arr), 99);
      size_t size = defaultSizeForDetect;
      auto start = std::chrono::high_resolution_clock::now();
      for(size_t i = 0; i < size; ++i) {
        fcf::random(&arr[0], &arr[10], 0, 10);
      }
      auto end = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
      defaultDuration = duration / size;
      for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
        FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
      }
    }
    {
      int arr[10];
      std::fill(std::begin(arr), std::end(arr), 99);
      fcf::Variant v((int)10);

      size_t size = defaultSize;
      auto start = std::chrono::high_resolution_clock::now();
      for(size_t i = 0; i < size; ++i) {
        fcf::dynamicCall("random", &arr[0], &arr[10], 0, 10);
      }
      auto end = std::chrono::high_resolution_clock::now();
      unsigned long long duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
      unsigned long long rduration = duration / size;
      rduration = rduration < defaultDuration ? 0 : rduration - defaultDuration;
      std::cout << "(int*, int*, int, int)     [Find, Call] : " << rduration << "nsec" << std::endl;

      for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
        FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
      }
    }
    {
      int arr[10];
      std::fill(std::begin(arr), std::end(arr), 99);
      fcf::Variant v((int)10);

      size_t size = defaultSize;
      auto start = std::chrono::high_resolution_clock::now();
      for(size_t i = 0; i < size; ++i) {
        fcf::dynamicCall("random", &arr[0], &arr[10], 0, v);
      }
      auto end = std::chrono::high_resolution_clock::now();
      unsigned long long duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
      unsigned long long rduration = duration / size;
      rduration = rduration < defaultDuration ? 0 : rduration - defaultDuration;
      std::cout << "(int*, int*, int, variant) [Find, Call] : " << rduration << "nsec" << std::endl;

      for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
        FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
      }
    }

    {
      int arr[10];
      std::fill(std::begin(arr), std::end(arr), 99);
      fcf::Variant v((int)10);

      fcf::DynamicCall dc;
      fcf::DynamicCallSeeker<void, int*, int*, int, const fcf::Variant>()("random", &dc, (int*)0, (int*)0, (int)0, v);

      size_t size = defaultSize;
      auto start = std::chrono::high_resolution_clock::now();
      for(size_t i = 0; i < size; ++i) {
        fcf::dynamicCall(&dc, &arr[0], &arr[10], 0, v);
      }
      auto end = std::chrono::high_resolution_clock::now();
      unsigned long long duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
      unsigned long long rduration = duration / size;
      rduration = rduration < defaultDuration ? 0 : rduration - defaultDuration;
      std::cout << "(int*, int*, int, variant) [Call]       : " << rduration << "nsec" << std::endl;
      for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
        FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
      }
    }
  }

}

