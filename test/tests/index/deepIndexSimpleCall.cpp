#include <iostream>
#include <array>
#include <type_traits>
#include <memory>
#include <chrono>

#include "../../libraries/fcfTest/test.hpp"

#include "../../../functions.hpp"
#include "../../../FunctionSignature.hpp"
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
  };

  struct Conversion {
    ConversionMode mode;
    unsigned int   type;
    unsigned int   index;
  };

  struct DynamicCall {
    void*                         function;
    void*                         caller;
    StaticVector<8, Conversion>   conversions;
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
          while (a_stateOffset < a_procInfo.conversions.size() && a_procInfo.conversions.get()[a_stateOffset].index == ArgIndex){
            if (a_procInfo.conversions.get()[a_stateOffset].mode == CM_RESOLVE) {
              arg_type& ref = (arg_type&)*std::get<ArgIndex>(a_argTuple);
              void* rawptr = Type<arg_type, RawDataSpecificator>().resolve(ref);
              std::get<ArgIndex>(a_argTuple) = (arg_type*)rawptr;
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
        DynamicCall*                                      result;
        fcf::Details::IndexableFunction::Groups::iterator groupIterator;
        BaseFunctionSignature&                            functionSignature;
        TPtrTuple&                                        tuple;
      };

      template <int Index, int Size, typename TPtrTuple>
      struct InvariantArgSelector {
        inline void operator()(ConversionNode* a_node, InvariantArgSelectorData<TPtrTuple>& a_iasd){
          unsigned int sourceTypeIndex = a_iasd.functionSignature.pacodes[Index];

          typedef
            typename std::remove_cv<
              typename std::remove_pointer<
                typename std::tuple_element<Index, TPtrTuple>::type
              >::type
            >::type current_arg_type;

          if (!a_iasd.result->caller) {
            unsigned int invariantIndex = Type<current_arg_type, RawDataSpecificator>().type( std::get<Index>(a_iasd.tuple) );
            if (invariantIndex) {
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
              InvariantArgSelector<Index + 1, Size, TPtrTuple>()(&curnode, a_iasd);
            }
          }

          if (!a_iasd.result->caller) {
            if (a_node) {
              a_node->next = 0;
            }
            InvariantArgSelector<Index + 1, Size, TPtrTuple>()(a_node, a_iasd);
          }

         a_iasd.functionSignature.pacodes[Index] = sourceTypeIndex;
        }
      };

      template <int Size, typename TPtrTuple>
      struct InvariantArgSelector<Size, Size, TPtrTuple >{
        inline void operator()(ConversionNode* a_node, InvariantArgSelectorData<TPtrTuple>& a_iasd, bool a_ignoreOrigin = true){
          if (a_ignoreOrigin && !a_node) {
            return;
          }

          fcf::Details::IndexableFunction::Callers::iterator callerInfoIt =
            a_iasd.groupIterator->second.callers.find(a_iasd.functionSignature);
          if (callerInfoIt == a_iasd.groupIterator->second.callers.end()) {
            return;
          }

          a_iasd.result->caller   = callerInfoIt->second.caller;
          a_iasd.result->function = Details::IndexableFunction::getStorage().functions[callerInfoIt->second.index].function;

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
      };

    public:
      template <typename... TCurrentArgPack>
      void operator()(const char* a_functionName, DynamicCall* a_result, const TCurrentArgPack&... a_argPack){
        State state;
        state.init = true;
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
          a_result->caller = 0;
          a_result->function = 0;
          a_result->conversions.clear();
        }

        fcf::Details::IndexableFunction::Callers::iterator callerInfoIt =
          groupIt->second.callers.find(functionSignature);

        typedef std::tuple<const typename std::remove_cv< typename std::remove_reference<TArgPack>::type >::type *...> ptr_tuple_type;
        ptr_tuple_type ptr_tuple(&a_argPack...);
        Details::IndexableFunction::InvariantArgSelectorData<ptr_tuple_type> iasd = {a_result, groupIt, functionSignature, ptr_tuple};
        {
          typedef Details::IndexableFunction::InvariantArgSelector<sizeof...(a_argPack), sizeof...(a_argPack), ptr_tuple_type> selector_type;
          selector_type()(0, iasd, false);
          if (iasd.result->caller){
            return;
          }
        }
        {
          typedef Details::IndexableFunction::InvariantArgSelector<0, sizeof...(TArgPack), ptr_tuple_type> selector_type;
          selector_type()(0, iasd);
        }

        if (!a_result->caller) {
          throw std::runtime_error("Function not found. No signature found.");
        }
      }
  };

  template <typename... TArgPack>
  void dynamicCall(const DynamicCall* a_dc, const TArgPack& ... a_argPack) {
    Details::IndexableFunction::DynamicCallProcessor()(*a_dc, 0, a_argPack...);
  }


  template <typename... TArgPack>
  void dynamicCall(const char* a_functionName, const TArgPack& ... a_argPack) {
    fcf::DynamicCall dc;
    fcf::DynamicCallSeeker<void, TArgPack...>()("random", &dc, a_argPack...);
    Details::IndexableFunction::DynamicCallProcessor()(dc, 0, a_argPack...);
  }

} // namespace fcf

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
    unsigned long long defaultSize = 10000000;
    unsigned long long defaultDuration = 0;
    {
      int arr[10];
      std::fill(std::begin(arr), std::end(arr), 99);
      size_t size = defaultSize;
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

