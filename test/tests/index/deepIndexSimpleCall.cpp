#include <iostream>
#include <array>
#include <type_traits>
#include <memory>
#include <chrono>

#include "../../libraries/fcfTest/test.hpp"

#include "../../../functions.hpp"
#include "../../../FunctionSignature.hpp"
#include "../../../convert.hpp"
#include "../../../bits/Specificator/DynamicIteratorFlags.hpp"
#include "../../../bits/Specificator/DynamicIteratorInfo.hpp"
#include "../../../DynamicIterator.hpp"
#include "../../../Details/IndexableFunction/Storage.hpp"

bool enable_log = false;
namespace fcf {

  template <typename Ty>
  class Foreach;

  namespace Details {
    namespace Basis {
      template <typename TTuple, int Index, int Size>
      class TupleForeach{
        public:
          template <typename TFunctor>
          void operator()(TTuple& a_container, TFunctor& a_functor){
            a_functor(a_container, Index, std::get<Index>(a_container));
            TupleForeach<TTuple, Index+1, Size>()(a_container, a_functor);
          }
      };
      template <typename TTuple, int Size>
      class TupleForeach<TTuple, Size, Size>{
        public:
          template <typename TFunctor>
          void operator()(TTuple& a_container, TFunctor& a_functor){
          }
      };
    }
  }

  template <typename... TPack>
  class Foreach< std::tuple<TPack...> >{
    public:
      typedef std::tuple<TPack...> container_type;
      template <typename TFunctor>
      void operator()(container_type& a_container, TFunctor& a_functor){
        Details::Basis::TupleForeach<container_type, 0, sizeof...(TPack)>()(a_container, a_functor);
      }
  };

  template <typename TContainer, typename TFunctor>
  void foreach(TContainer& a_container, TFunctor& a_functor){
    Foreach<TContainer>()(a_container, a_functor);
  }

  template <size_t Index, bool Unsafe = false, typename TUnsafe = Nop>
  struct ArgGetter{
    template <typename TArg1, typename... TArgPack>
    inline auto operator()(TArg1 a_arg, TArgPack... a_argPack) -> decltype( ArgGetter<Index-1, Unsafe, TUnsafe>()(a_argPack...) ) {
      return ArgGetter<Index-1, Unsafe, TUnsafe>()(a_argPack...);
    }
  };

  template <size_t Index, typename TUnsafe>
  struct ArgGetter<Index, true, TUnsafe>{
    template <typename TArg1, typename... TArgPack>
    inline auto operator()(TArg1 a_arg, TArgPack... a_argPack) -> decltype( ArgGetter<Index-1, true, TUnsafe>()(a_argPack...) ) {
      return ArgGetter<Index-1, true, TUnsafe>()(a_argPack...);
    }
    inline TUnsafe operator()() {
      return TUnsafe();
    }
  };

  template <typename TUnsafe>
  struct ArgGetter<0, false, TUnsafe> {
    template <typename TArg1, typename... TArgPack>
    inline TArg1 operator()(TArg1 a_arg, TArgPack... a_argPack) {
      return a_arg;
    }
  };


  template <typename TUnsafe>
  struct ArgGetter<0, true, TUnsafe> {
    template <typename TArg1, typename... TArgPack>
    inline TArg1 operator()(TArg1 a_arg, TArgPack... a_argPack) {
      return a_arg;
    }
    inline TUnsafe operator()() {
      return TUnsafe();
    }
  };

  namespace Details {
    namespace Basis {

      template <typename Ty = Nop, typename... TPack>
      class StaticVariantCopyArgs {
        public:
          template <typename TPtrDest>
          void operator()(TPtrDest* a_dst, Ty a_arg1, TPack... a_pack){
            *a_dst = a_arg1;
            StaticVariantCopyArgs<TPack...>()(++a_dst, a_pack...);
          }
      };

      template <typename Ty>
      class StaticVariantCopyArgs<Ty> {
        public:
          template <typename TPtrDest>
          void operator()(TPtrDest* a_dst, Ty a_arg1){
            *a_dst = a_arg1;
          }
      };
    }
  }
  
  
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

      template <typename... TPack>
      StaticVector(TPack... a_pack) 
        : _sdata(0)
        , _cdata(StaticSize) {
        _pdata = &_adata[0];
        _reserve((int)(sizeof...(TPack) / STEP) * STEP + STEP);
        _sdata = sizeof...(TPack);
        Details::Basis::StaticVariantCopyArgs<TPack...>()(_pdata, a_pack...);
      }

      Ty& operator[](size_t a_index){
        return _pdata[a_index];
      }

      const Ty& operator[](size_t a_index) const{
        return _pdata[a_index];
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

      void resize(size_t a_size) {
        if (_cdata < a_size) {
          _reserve((int)(a_size / STEP) * STEP + STEP);
        }
        _sdata = a_size;
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
    CM_FLAT_ITERATOR = 4,
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
        template <typename TDynamicCallInfo, typename TArgs>
        void operator()(const TDynamicCallInfo& a_procInfo, unsigned int a_stateOffset, TArgs& a_args){
          typedef typename std::remove_cv<
                    typename std::remove_pointer<
                      typename std::remove_cv<
                        typename std::remove_reference<
                          decltype(std::get<ArgIndex>( std::tuple<TArgPack*...>() ))
                        >::type
                      >::type
                    >::type
                  >::type arg_type;
          unsigned int currentType = BaseFunctionSignature::getSimpleType(Type<arg_type>().index());
          while (a_stateOffset < a_procInfo.conversions.size() && a_procInfo.conversions.get()[a_stateOffset].index == ArgIndex){
            if (a_procInfo.conversions.get()[a_stateOffset].mode == CM_RESOLVE) {
              arg_type& ref = *(arg_type*)a_args[ArgIndex];
              void* rawptr = (void*)Type<arg_type, RawDataSpecificator>()(&ref);
              currentType = a_procInfo.conversions.get()[a_stateOffset].type;
              a_args[ArgIndex] = (arg_type*)rawptr;
            } else if (a_procInfo.conversions.get()[a_stateOffset].mode == CM_CONVERT) {
              Variant arg(a_procInfo.conversions.get()[a_stateOffset].type, (const void*)a_args[ArgIndex], currentType, (ConvertOptions*)0, (ConvertFunction)a_procInfo.conversions.get()[a_stateOffset].converter);
              currentType = a_procInfo.conversions.get()[a_stateOffset].type;
              a_args[ArgIndex] = (arg_type*)arg.ptr();
              IndexableDynamicCallProcessor<ArgIndex, ArgSize, TArgPack...>()(a_procInfo, a_stateOffset + 1, a_args);
              return;
            }
            ++a_stateOffset;
          }
          IndexableDynamicCallProcessor<ArgIndex + 1, ArgSize, TArgPack...>()(a_procInfo, a_stateOffset, a_args);
        }
      };

      template <int ArgSize, typename ... TArgPack>
      struct IndexableDynamicCallProcessor<ArgSize, ArgSize, TArgPack...>{
        template <typename TDynamicCallInfo, typename TArgs>
        void operator()(const TDynamicCallInfo& a_procInfo, unsigned int a_stateOffset, TArgs& a_args){
          typedef typename Sequence<0, ArgSize-1>::type sequence_type;
          _call(a_procInfo, a_stateOffset, a_args, sequence_type());
        }

        private:
          template <typename TDynamicCallInfo, typename TArgs, int... SequencePack>
          void _call(const TDynamicCallInfo& a_procInfo, unsigned int a_stateOffset, TArgs& a_args, Sequence<0, SequencePack...> a_sequence){
            typedef void (*simple_function_type)(void*, const typename std::remove_cv< typename std::remove_reference<TArgPack>::type >::type& ...);
            simple_function_type caller = (simple_function_type)a_procInfo.caller;
            caller(a_procInfo.function, *(const typename std::remove_cv< typename std::remove_reference<TArgPack>::type >::type*)a_args[SequencePack]...);
          }
      };

      template <size_t ArgSize, size_t BufferIndex, size_t SourceIndex, bool InitArg = true, bool InitNextArg = true>
      struct IndexableDynamicCallProcessor2{
        template <typename TDynamicCallInfo, typename TBuffer, typename... TArgPack>
        inline void operator()(const TDynamicCallInfo& a_procInfo, TBuffer& a_args, unsigned int a_currentType, size_t a_stateOffset, const TArgPack& ... a_argPack){
          typedef decltype(ArgGetter<SourceIndex, true, int*>()(a_argPack...)) ref_arg_type;
          typedef typename std::remove_cv<
                    typename std::remove_pointer<
                      typename std::remove_cv<
                        typename std::remove_reference<
                          ref_arg_type
                        >::type
                      >::type
                    >::type
                  >::type arg_type;
          unsigned int currentType = BaseFunctionSignature::getSimpleType(Type<arg_type>().index());
          if (InitArg) {
            a_args[BufferIndex] = ArgGetter<SourceIndex, true, int*>()((void*)&a_argPack...);
          } else {
            currentType = a_currentType;
          }
          while (a_stateOffset < a_procInfo.conversions.size() && a_procInfo.conversions.get()[a_stateOffset].index == BufferIndex) {
            if (a_procInfo.conversions.get()[a_stateOffset].mode == CM_RESOLVE) {
              arg_type& ref = *(arg_type*)a_args[BufferIndex];
              void* rawptr = (void*)Type<arg_type, RawDataSpecificator>()(&ref);
              currentType = a_procInfo.conversions.get()[a_stateOffset].type;
              a_args[BufferIndex] = (arg_type*)rawptr;
            } else if (a_procInfo.conversions.get()[a_stateOffset].mode == CM_CONVERT) {
              Variant arg(a_procInfo.conversions.get()[a_stateOffset].type, (const void*)a_args[BufferIndex], currentType, (ConvertOptions*)0, (ConvertFunction)a_procInfo.conversions.get()[a_stateOffset].converter);
              currentType = a_procInfo.conversions.get()[a_stateOffset].type;
              a_args[BufferIndex] = (arg_type*)arg.ptr();
              IndexableDynamicCallProcessor2<ArgSize, BufferIndex, SourceIndex, false, InitNextArg>()(a_procInfo, a_args, currentType, a_stateOffset + 1, a_argPack...);
              return;
            } else if (a_procInfo.conversions.get()[a_stateOffset].mode == CM_FLAT_ITERATOR) {
              typedef bool (*converter_type)(void*, DynamicIteratorInfo*);
              converter_type converter = (converter_type)a_procInfo.conversions.get()[a_stateOffset].converter;
              DynamicIteratorInfo dii;
              dii.flags = DIF_BEGIN | DIF_GET_VALUE | DIF_GET_TYPE;
              if (!converter(a_args[BufferIndex], &dii)){
                throw std::runtime_error("Failed to get left bound of argument");
              }
              unsigned int subtype = dii.type;
              void* left = dii.value;
              dii.flags = DIF_END | DIF_GET_VALUE;
              if (!converter(a_args[BufferIndex], &dii)){
                throw std::runtime_error("Failed to get left bound of argument");
              }
              void* right = dii.value;
              a_args[BufferIndex] = &left;
              a_args.resize(ArgSize+1);
              a_args[BufferIndex+1] = &right;
              IndexableDynamicCallProcessor2<ArgSize+1, BufferIndex, SourceIndex, false, false>()(a_procInfo, a_args, subtype, a_stateOffset + 1, a_argPack...);
              return;
            }
            ++a_stateOffset;
          }
          IndexableDynamicCallProcessor2<ArgSize, BufferIndex+1, InitNextArg ? SourceIndex+1 : SourceIndex, InitNextArg>()(a_procInfo, a_args, currentType, a_stateOffset, a_argPack...);
        }
      };

      template <size_t ArgSize, size_t SourceIndex, bool InitArg, bool InitNextArg>
      struct IndexableDynamicCallProcessor2<ArgSize, ArgSize, SourceIndex, InitArg, InitNextArg>{
        public:
          template <typename TDynamicCallInfo, typename TBuffer, typename... TArgPack>
          inline void operator()(const TDynamicCallInfo& a_procInfo, TBuffer& a_args, size_t a_stateOffset, const TArgPack& ... a_argPack){
            typedef typename Sequence<0, ArgSize-1>::type sequence_type;
            _call(a_procInfo, a_args, sequence_type());
          }
        protected:
          template <typename TDynamicCallInfo, typename TBuffer, int... SequencePack>
          inline void _call(const TDynamicCallInfo& a_procInfo, TBuffer& a_args, Sequence<0, SequencePack...> a_sequence){
            typedef void (*simple_function_type)(void*, const decltype(SequencePack)& ...);
            simple_function_type caller = (simple_function_type)a_procInfo.caller;
            caller(a_procInfo.function, *(int*)a_args[SequencePack]...);
          }
      };

      template <size_t SourceIndex, size_t BufferIndex, bool InitArg, bool InitNextArg>
      struct IndexableDynamicCallProcessor2<8, BufferIndex, SourceIndex, InitArg, InitNextArg>{
        template <typename TDynamicCallInfo, typename TBuffer, typename... TArgPack>
        inline void operator()(const TDynamicCallInfo& a_procInfo, TBuffer& a_args, size_t a_stateOffset, const TArgPack& ... a_argPack){
        }
      };

      struct DynamicCallProcessor{
        template <typename TDynamicCallInfo, typename... TArgPack>
        void operator()(const TDynamicCallInfo& a_procInfo, unsigned int a_stateOffset, const TArgPack&... a_argPack){
          StaticVector<sizeof...(TArgPack)*2, void*> args(sizeof...(TArgPack));
          IndexableDynamicCallProcessor2<sizeof...(TArgPack), 0, 0>()(a_procInfo, args, 0, 0, a_argPack...);
          //StaticVector<sizeof...(TArgPack)*2, void*> args{ (void*)&a_argPack... };
          //IndexableDynamicCallProcessor<0, sizeof...(TArgPack), TArgPack...>()(a_procInfo, 0, args);
        }
      };

      template <typename TTuple, typename TType, int Index>
      struct TupleElementReplace {
        typedef typename Sequence<0, Index-1>::type                                   left_sequence_type;
        typedef typename Sequence<Index+1, std::tuple_size<TTuple>::value - 1 >::type right_sequence_type;
        template<int... LeftSeqPack, int... RightSeqPack>
        static auto gen(Sequence<0, LeftSeqPack...>, Sequence<Index+1, RightSeqPack...>) -> decltype(std::tuple<
              typename std::remove_reference< decltype(std::get<LeftSeqPack>(TTuple())) >::type...,
              TType,
              typename std::remove_reference< decltype(std::get<RightSeqPack>(TTuple())) >::type...
            >()) {
          return std::tuple<
              typename std::remove_reference< decltype(std::get<LeftSeqPack>(TTuple())) >::type...,
              TType,
              typename std::remove_reference< decltype(std::get<RightSeqPack>(TTuple())) >::type...
            >();
        }
        typedef decltype(gen(left_sequence_type(), right_sequence_type())) type;
      };

      template <typename TTuple, typename TType>
      struct TupleElementReplace<TTuple, TType, 0> {
        typedef typename Sequence<1, std::tuple_size<TTuple>::value - 1 >::type right_sequence_type;
        template<int... LeftSeqPack, int... RightSeqPack>
        static auto gen(Sequence<1, RightSeqPack...>) -> decltype(std::tuple<
              TType,
              typename std::remove_reference< decltype(std::get<RightSeqPack>(TTuple())) >::type...
            >()) {
          return std::tuple<
              TType,
              typename std::remove_reference< decltype(std::get<RightSeqPack>(TTuple())) >::type...
            >();
        }
        typedef decltype(gen(right_sequence_type())) type;
      };


      template <typename TTuple, size_t TupleSize, typename TType, int Index>
      struct TupleElementInsertImpl {
        typedef typename Sequence<0, Index-1>::type                                 left_sequence_type;
        typedef typename Sequence<Index, std::tuple_size<TTuple>::value - 1 >::type right_sequence_type;
        template<int... LeftSeqPack, int... RightSeqPack>
        static auto gen(Sequence<0, LeftSeqPack...>, Sequence<Index, RightSeqPack...>) -> decltype(std::tuple<
              typename std::remove_reference< decltype(std::get<LeftSeqPack>(TTuple())) >::type...,
              TType,
              typename std::remove_reference< decltype(std::get<RightSeqPack>(TTuple())) >::type...
            >()) {
          return std::tuple<
              typename std::remove_reference< decltype(std::get<LeftSeqPack>(TTuple())) >::type...,
              TType,
              typename std::remove_reference< decltype(std::get<RightSeqPack>(TTuple())) >::type...
            >();
        }
        typedef decltype(gen(left_sequence_type(), right_sequence_type())) type;
      };

      template <typename TTuple, size_t TupleSize, typename TType>
      struct TupleElementInsertImpl<TTuple, TupleSize, TType, 0> {
        typedef typename Sequence<0, std::tuple_size<TTuple>::value - 1 >::type right_sequence_type;
        template<int... RightSeqPack>
        static auto gen(Sequence<0, RightSeqPack...>) -> decltype(std::tuple<
              TType,
              typename std::remove_reference< decltype(std::get<RightSeqPack>(TTuple())) >::type...
            >()) {
          return std::tuple<
              TType,
              typename std::remove_reference< decltype(std::get<RightSeqPack>(TTuple())) >::type...
            >();
        }
        typedef decltype(gen(right_sequence_type())) type;
      };


      template <typename TTuple, typename TType>
      struct TupleElementInsertImpl<TTuple, 0, TType, 0> {
        typedef std::tuple<TType> type;
      };

      template <typename TTuple, typename TType, int Index>
      struct TupleElementInsert {
        typedef typename TupleElementInsertImpl<TTuple, std::tuple_size<TTuple>::value, TType, Index>::type type;
      };



      struct InvariantArgSelectorData{
        const char*                                       name;
        DynamicCall*                                      result;
        fcf::Details::IndexableFunction::Groups::iterator groupIterator;
        BaseFunctionSignature&                            functionSignature;
        StaticVector<8, void*>*                           arguments;
        bool                                              strictSource;
        bool                                              dynamicCaller;
      };

      template <int Index, int Size, typename TPtrTuple>
      struct InvariantArgSelector {
        inline void operator()(ConversionNode* a_node, InvariantArgSelectorData& a_iasd, bool a_ignoreOrigin, bool a_dynamicCaller){
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
          DynamicIteratorSpecificator::function_type dynamicIteratorResolver = 0;
          unsigned int invariantIndex = 0;
          void* aptr = a_iasd.strictSource ? (void*) (*a_iasd.arguments)[Index] : (void*)0;
          if (originSourceSimpleTypeIndex == sourceSimpleTypeIndex) {
            Type<current_arg_type, RawDataSpecificator>()((current_arg_type*)aptr, &invariantIndex, &invariantRawType);
            dynamicIteratorResolver = Type<current_arg_type>().dynamicIteratorResolver();
          } else {
            const fcf::Details::TypeInfo* ti = Details::typeStorage.get(sourceSimpleTypeIndex);
            if (ti) {
              if (ti->rawDataResolver) {
                ti->rawDataResolver(aptr, &invariantIndex, &invariantRawType, 0);
              }
              dynamicIteratorResolver = ti->dynamicIteratorResolver;
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

          if (dynamicIteratorResolver) {
            DynamicIteratorInfo dii;
            dii.flags = DIF_INFO | DIF_GET_FLAT | DIF_GET_TYPE;
            dynamicIteratorResolver(0, &dii);
            if (dii.flat) {
              typedef Nop* pnop_type;
              typedef typename TupleElementReplace<TPtrTuple, pnop_type, Index>::type rep_tuple_type;
              typedef typename TupleElementInsert<rep_tuple_type, pnop_type, Index>::type pair_tuple_type;

              BaseFunctionSignature ofs = a_iasd.functionSignature;
              BaseFunctionSignature fs = BaseFunctionSignature(a_iasd.functionSignature.asize + 1);
              fs.rcode = ofs.rcode;
              std::copy(&a_iasd.functionSignature.pacodes[0],
                        &a_iasd.functionSignature.pacodes[Index],
                        &fs.pacodes[0]
                        );

              unsigned int ptrTypeIndex = dii.type;
              if (ptrTypeIndex & (8 << (24 + 1)) ) {
                ptrTypeIndex |= (16 << (24 + 1));
              } else {
                ptrTypeIndex |= (8 << (24 + 1));
              }
              fs.pacodes[Index] = a_iasd.functionSignature.getSimpleCallType(ptrTypeIndex);
              fs.pacodes[Index+1] = a_iasd.functionSignature.getSimpleCallType(ptrTypeIndex);

              std::copy(&a_iasd.functionSignature.pacodes[Index+1],
                        &a_iasd.functionSignature.pacodes[a_iasd.functionSignature.asize],
                        &fs.pacodes[Index+2]
                        );

              ConversionNode curnode;
              curnode.prev = 0;
              curnode.next = 0;
              curnode.conversion.index     = Index;
              curnode.conversion.type      = ptrTypeIndex;
              curnode.conversion.mode      = CM_FLAT_ITERATOR;
              curnode.conversion.converter = (void*)dynamicIteratorResolver;
              if (a_node){
                a_node->next = &curnode;
                curnode.prev = a_node;
              }

              StaticVector<8, void*> arguments((size_t)Size+1);
              if (a_iasd.strictSource) {
                std::copy(&(*a_iasd.arguments)[0], &(*a_iasd.arguments)[Index], &arguments[0]);
                arguments[Index] = 0;
                arguments[Index+1] = 0;
                std::copy(&(*a_iasd.arguments)[Index+1], &(*a_iasd.arguments)[Size], &arguments[Index+2]);
              } else {
                std::fill(&arguments[0], &arguments[Size+1], (void*)0);
              }
              InvariantArgSelectorData repiasd
                   = { a_iasd.name, a_iasd.result, a_iasd.groupIterator, fs, &arguments, a_iasd.strictSource};
              InvariantArgSelector<Index+2, Size+1, pair_tuple_type>()(&curnode, repiasd, a_ignoreOrigin, a_dynamicCaller);
            }
          }
        } // method end
      };

      template <int Size, typename TPtrTuple>
      struct InvariantArgSelector<Size, Size, TPtrTuple >{
        inline void operator()(ConversionNode* a_node, InvariantArgSelectorData& a_iasd, bool a_ignoreOrigin, bool a_dynamicCaller){
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
        StaticVector<8, void*> arguments = {(void*)&a_argPack...};
        Details::IndexableFunction::InvariantArgSelectorData iasd = {a_functionName, a_result, groupIt, functionSignature, &arguments, a_state.strictSource};
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

void deepIndexContainerCaller(){
  std::cout << "Start deepIndexContainerCaller..." << std::endl; 
  {
    std::vector<int> vec(10);
    fcf::DynamicCall dc;
    fcf::DynamicCallSeeker<void, std::vector<int>, int, int>()("random", &dc, vec, (int)0, (int)0);
    fcf::dynamicCall(&dc, vec, (int)0, (int)10);
    for(size_t i = 0; i < vec.size(); ++i){
      FCF_TEST((vec[i] >= 0 && vec[i] <= 9), i, vec[i]);
    }
  }
}

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
    unsigned long long defaultSize = 1000000;
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


struct TupleTestFunc{
  std::string result;
  template <typename Tuple, typename TIndex, typename TValue>
  void operator()(Tuple& a_tuple, TIndex a_index, TValue& a_value){
    if (!result.empty()){
      result += "|";
    }
    result += fcf::Type<TValue>().name();
  }
};


void tupleTest() {
  std::cout << "Start tupleTest..." << std::endl;

  // insert test
  {
    typedef std::tuple<> ttype;
    typedef typename fcf::Details::IndexableFunction::TupleElementInsert<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float", ttf.result);
  }
  {
    typedef std::tuple<char> ttype;
    typedef typename fcf::Details::IndexableFunction::TupleElementInsert<ttype, float, 1>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|float", ttf.result);
  }
  {
    typedef std::tuple<char> ttype;
    typedef typename fcf::Details::IndexableFunction::TupleElementInsert<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float|char", ttf.result);
  }
  {
    typedef std::tuple<char, short> ttype;
    typedef typename fcf::Details::IndexableFunction::TupleElementInsert<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float|char|short", ttf.result);
  }
  {
    typedef std::tuple<char, short> ttype;
    typedef typename fcf::Details::IndexableFunction::TupleElementInsert<ttype, float, 1>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|float|short", ttf.result);
  }
  {
    typedef std::tuple<char, short> ttype;
    typedef typename fcf::Details::IndexableFunction::TupleElementInsert<ttype, float, 2>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|short|float", ttf.result);
  }

  // replace test
  {
    typedef std::tuple<char> ttype;
    typedef typename fcf::Details::IndexableFunction::TupleElementReplace<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float", ttf.result)
  }
  {
    typedef std::tuple<char, short> ttype;
    typedef typename fcf::Details::IndexableFunction::TupleElementReplace<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float|short", ttf.result)
  }
  {
    typedef std::tuple<char, short> ttype;
    typedef typename fcf::Details::IndexableFunction::TupleElementReplace<ttype, float, 1>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|float", ttf.result)
  }

  {
    typedef std::tuple<char, short, int> ttype;
    typedef typename fcf::Details::IndexableFunction::TupleElementReplace<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float|short|int", ttf.result)
  }
  {
    typedef std::tuple<char, short, int> ttype;
    typedef typename fcf::Details::IndexableFunction::TupleElementReplace<ttype, float, 1>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|float|int", ttf.result)
  }
  {
    typedef std::tuple<char, short, int> ttype;
    typedef typename fcf::Details::IndexableFunction::TupleElementReplace<ttype, float, 2>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|short|float", ttf.result)
  }
}


