#ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALLER_BY_ARG_HPP___
#define ___FCF__BASIS__BITS__CALL__DETAILS__CALLER_BY_ARG_HPP___

#include <stddef.h>
#include <type_traits>
#include "../../../Template/PackageArgResolver.hpp"
#include "../../../Template/Sequence.hpp"
#include "../../../FunctionSignature.hpp"
#include "../../Specificator/DynamicIteratorInfo.hpp"
#include "../CallConversionMode.hpp"

namespace fcf {
  namespace Details {

    typedef StaticVector<void*, 8> CallerPtrArgsBuffer;
    
    template <size_t ArgSize>
    struct CallerByArgComplete;

    template <typename... TArgPack>
    struct CallerArgsResolver {

      CallerArgsResolver(){
        typedef std::tuple< TArgPack*... > tuple_type;
        tuple_type tuple;
        foreach(tuple, *this);
      }

      template <typename TTuple, typename TItem>
      void operator()(const TTuple& a_tuple, size_t a_index, const TItem* a_item){
        indexes[a_index] = Type<TItem>().index();
      }

      unsigned int indexes[sizeof...(TArgPack)];
    };

    template <size_t ArgSize>
    struct CallerListCall{
      public:
        static void call(const Call& a_procInfo, CallerPtrArgsBuffer& a_args){
          typedef typename Template::Sequence<0, ArgSize-1>::type sequence_type;
          _call(a_procInfo, a_args, sequence_type());
        }
      protected:
        template <int... SequencePack>
        static inline void _call(const Call& a_procInfo, CallerPtrArgsBuffer& a_args, Template::Sequence<0, SequencePack...> a_sequence){
          typedef void (*simple_function_type)(void*, const decltype(SequencePack)& ...);
          simple_function_type caller = (simple_function_type)a_procInfo.caller;
          caller(a_procInfo.function, *(int*)a_args[SequencePack]...);
        }
    };

    template <>
    struct CallerListCall<0>{
      public:
        static void call(const Call& a_procInfo, CallerPtrArgsBuffer& a_args){
          typedef void (*simple_function_type)(void*);
          simple_function_type caller = (simple_function_type)a_procInfo.caller;
          caller(a_procInfo.function);
        }
    };

    struct CallerListCallsImpl {
      typedef void(*function_type)(const Call& a_procInfo, CallerPtrArgsBuffer& a_args);
      typedef StaticVector<function_type, 8> buffer_type;

      CallerListCallsImpl() {
        functions.resize(buffer_type::static_capacity_value + 1);
        functions[0] = CallerListCall<0>::call;
        functions[1] = CallerListCall<1>::call;
        functions[2] = CallerListCall<2>::call;
        functions[3] = CallerListCall<3>::call;
        functions[4] = CallerListCall<4>::call;
        functions[5] = CallerListCall<5>::call;
        functions[6] = CallerListCall<6>::call;
        functions[7] = CallerListCall<7>::call;
        functions[8] = CallerListCall<8>::call;
      }

      inline void operator()(const Call& a_procInfo, CallerPtrArgsBuffer& a_args){
        functions[a_args.size()](a_procInfo, a_args);
      }

      buffer_type functions;
    };

    struct CallerListCalls {
      static inline void call(const Call& a_procInfo, CallerPtrArgsBuffer& a_args){
        static CallerListCallsImpl c;
        c(a_procInfo, a_args);
      }
    };



    struct CallerByArgNewMode{
      template <typename TDynamicCallInfo, typename TBuffer, typename... TArgPack>
      inline void operator()(const TDynamicCallInfo& a_procInfo, TBuffer& a_args, const TArgPack& ... a_argPack){
        typedef int& ref_type;
        typedef int arg_type;

        static CallerArgsResolver<TArgPack...> callerArgsResolver;

        size_t       currentArgIndex = SIZE_MAX;
        unsigned int currentArgType  = 0;

        const size_t argBufferCapacity = sizeof...(a_argPack) * 3;
        StaticVector<fcf::Variant, sizeof...(a_argPack) * 3> argBuffer;

        _initArgs(a_procInfo, a_args, a_argPack...);

        for(size_t conversionIndex = 0; conversionIndex < a_procInfo.conversions.size(); ++conversionIndex){
          const CallConversion& cc = a_procInfo.conversions[conversionIndex];
          if (cc.mode == CCM_RESOLVE) {
            RawDataSpecificator::function_type converter = (RawDataSpecificator::function_type)cc.converter;
            arg_type& ref = *(arg_type*)a_args[cc.index];
            void* rawptr = (void*)converter(&ref,0,0,0);
            currentArgType = cc.type;
            a_args[cc.index] = rawptr;
          } else if (cc.mode == CCM_CONVERT) {
            if (currentArgIndex != cc.index)  {
              currentArgType = callerArgsResolver.indexes[cc.index];
              currentArgIndex = cc.index;
            }
            ::fcf::Variant arg(cc.type, (const void*)a_args[cc.index], currentArgType, (ConvertOptions*)0, (ConvertFunction)cc.converter);
            currentArgType = cc.type;
            a_args[cc.index] = (arg_type*)arg.ptr();
          } else if (cc.mode == CCM_PLACE_HOLDER) {
            const std::map<unsigned int, SpecificatorTypeInfo>& s = Details::typeStorage.get(cc.type)->specificators;
            const std::map<unsigned int, SpecificatorTypeInfo>::const_iterator si = s.find(cc.specificatorIndex);
            if (si == s.end()){
              throw std::runtime_error("Invalid specificator");
            }
            fcf::StaticVector<fcf::Variant, 4> vs;
            typedef void (*resolve_type)(int&, fcf::StaticVector<fcf::Variant, 4>&);
            resolve_type resolve = (resolve_type)si->second.resolve;
            int* aptr = (int*)a_args[cc.index];
            for(unsigned int i = 0; i < cc.pointerCounter; ++i){
              aptr = *(int**) aptr;
            }
            resolve(*aptr, vs);
            for(size_t i = 0; i < cc.placeHolders.size(); ++i){
              const ArgPlaceHolder::PlaceHolderArgEx& phae = cc.placeHolders[i];
              const size_t argBufferIndex = argBuffer.size();
              if (argBufferIndex >= argBufferCapacity){
                throw std::runtime_error("Argument buffer overflow");
              }
              argBuffer.resize(argBufferIndex+1);
              argBuffer[argBufferIndex].set(phae.type, vs[phae.placeHolderArgument-1].ptr(), vs[phae.placeHolderArgument-1].typeIndex());
              a_args[phae.argument] = argBuffer[argBufferIndex].ptr();
            }
          } else if (cc.mode == CCM_FLAT_ITERATOR) {
            typedef bool (*converter_type)(void*, DynamicIteratorInfo*);
            converter_type converter = (converter_type)cc.converter;
            DynamicIteratorInfo dii;
            dii.flags = DIF_BEGIN | DIF_GET_VALUE | DIF_GET_TYPE;
            if (!converter(a_args[cc.index], &dii)){
              throw std::runtime_error("Failed to get left bound of argument");
            }
            unsigned int subtype = dii.type;
            void* left = dii.value;
            dii.flags = DIF_END | DIF_GET_VALUE;
            if (!converter(a_args[cc.index], &dii)){
              throw std::runtime_error("Failed to get left bound of argument");
            }
            void* right = dii.value;
            a_args[cc.index] = &left;
            a_args[cc.index+1] = &right;
          }

        }
        
        CallerListCalls::call(a_procInfo, a_args);
      }


      template <typename TDynamicCallInfo, typename TBuffer>
      inline void _initArgs(const TDynamicCallInfo& a_procInfo, TBuffer& a_args) {
      }

      template <typename TDynamicCallInfo, typename TBuffer, typename TArg1>
      inline void _initArgs(const TDynamicCallInfo& a_procInfo, TBuffer& a_args,
                            const TArg1& a_arg1) {
        a_args[a_procInfo.argsMap[0]] = (void*)&a_arg1;
      }

      template <typename TDynamicCallInfo, typename TBuffer, typename TArg1, typename TArg2>
      inline void _initArgs(const TDynamicCallInfo& a_procInfo, TBuffer& a_args,
                            const TArg1& a_arg1, const TArg2& a_arg2) {
        a_args[a_procInfo.argsMap[0]] = (void*)&a_arg1;
        a_args[a_procInfo.argsMap[1]] = (void*)&a_arg2;
      }

      template <typename TDynamicCallInfo, typename TBuffer, typename TArg1, typename TArg2, typename TArg3>
      inline void _initArgs(const TDynamicCallInfo& a_procInfo, TBuffer& a_args,
                            const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3) {
        a_args[a_procInfo.argsMap[0]] = (void*)&a_arg1;
        a_args[a_procInfo.argsMap[1]] = (void*)&a_arg2;
        a_args[a_procInfo.argsMap[2]] = (void*)&a_arg3;
      }

      template <typename TDynamicCallInfo, typename TBuffer, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
      inline void _initArgs(const TDynamicCallInfo& a_procInfo, TBuffer& a_args,
                            const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3, const TArg4& a_arg4) {
        a_args[a_procInfo.argsMap[0]] = (void*)&a_arg1;
        a_args[a_procInfo.argsMap[1]] = (void*)&a_arg2;
        a_args[a_procInfo.argsMap[2]] = (void*)&a_arg3;
        a_args[a_procInfo.argsMap[3]] = (void*)&a_arg4;
      }

      template <typename TDynamicCallInfo, typename TBuffer, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
      inline void _initArgs(const TDynamicCallInfo& a_procInfo, TBuffer& a_args,
                            const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3, const TArg4& a_arg4, const TArg5& a_arg5) {
        a_args[a_procInfo.argsMap[0]] = (void*)&a_arg1;
        a_args[a_procInfo.argsMap[1]] = (void*)&a_arg2;
        a_args[a_procInfo.argsMap[2]] = (void*)&a_arg3;
        a_args[a_procInfo.argsMap[3]] = (void*)&a_arg4;
        a_args[a_procInfo.argsMap[4]] = (void*)&a_arg5;
      }


      template <typename TDynamicCallInfo, typename TBuffer, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6>
      inline void _initArgs(const TDynamicCallInfo& a_procInfo, TBuffer& a_args,
                            const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3, const TArg4& a_arg4, const TArg5& a_arg5,
                            const TArg6& a_arg6) {
        a_args[a_procInfo.argsMap[0]] = (void*)&a_arg1;
        a_args[a_procInfo.argsMap[1]] = (void*)&a_arg2;
        a_args[a_procInfo.argsMap[2]] = (void*)&a_arg3;
        a_args[a_procInfo.argsMap[3]] = (void*)&a_arg4;
        a_args[a_procInfo.argsMap[4]] = (void*)&a_arg5;
        a_args[a_procInfo.argsMap[5]] = (void*)&a_arg6;
      }

      template <typename TDynamicCallInfo, typename TBuffer, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7>
      inline void _initArgs(const TDynamicCallInfo& a_procInfo, TBuffer& a_args,
                            const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3, const TArg4& a_arg4, const TArg5& a_arg5,
                            const TArg6& a_arg6, const TArg7& a_arg7) {
        a_args[a_procInfo.argsMap[0]] = (void*)&a_arg1;
        a_args[a_procInfo.argsMap[1]] = (void*)&a_arg2;
        a_args[a_procInfo.argsMap[2]] = (void*)&a_arg3;
        a_args[a_procInfo.argsMap[3]] = (void*)&a_arg4;
        a_args[a_procInfo.argsMap[4]] = (void*)&a_arg5;
        a_args[a_procInfo.argsMap[5]] = (void*)&a_arg6;
        a_args[a_procInfo.argsMap[6]] = (void*)&a_arg7;
      }

      template <typename TDynamicCallInfo, typename TBuffer, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8>
      inline void _initArgs(const TDynamicCallInfo& a_procInfo, TBuffer& a_args,
                            const TArg1& a_arg1, const TArg2& a_arg2, const TArg3& a_arg3, const TArg4& a_arg4, const TArg5& a_arg5,
                            const TArg6& a_arg6, const TArg7& a_arg7, const TArg8& a_arg8) {
        a_args[a_procInfo.argsMap[0]] = (void*)&a_arg1;
        a_args[a_procInfo.argsMap[1]] = (void*)&a_arg2;
        a_args[a_procInfo.argsMap[2]] = (void*)&a_arg3;
        a_args[a_procInfo.argsMap[3]] = (void*)&a_arg4;
        a_args[a_procInfo.argsMap[4]] = (void*)&a_arg5;
        a_args[a_procInfo.argsMap[5]] = (void*)&a_arg6;
        a_args[a_procInfo.argsMap[6]] = (void*)&a_arg7;
        a_args[a_procInfo.argsMap[7]] = (void*)&a_arg8;
      }
    };

    template <size_t ArgSize, size_t BufferIndex, size_t SourceIndex, bool InitArg = true, bool InitNextArg = true>
    struct CallerByArg{
      template <typename TDynamicCallInfo, typename TBuffer, typename... TArgPack>
      inline void operator()(const TDynamicCallInfo& a_procInfo, TBuffer& a_args, unsigned int a_currentType, size_t a_stateOffset, const TArgPack& ... a_argPack){
        typedef decltype(Template::PackageArgResolver<SourceIndex, true, int*>()(a_argPack...)) ref_arg_type;
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
        if (ArgSize == BufferIndex && a_stateOffset >= a_procInfo.conversions.size()) {
          CallerByArgComplete<ArgSize>()(a_procInfo, a_args, currentType, a_stateOffset, a_argPack...);
          return;
        }

        if (InitArg && a_procInfo.conversions[a_stateOffset].mode != CCM_SKIP) {
          a_args[BufferIndex] = Template::PackageArgResolver<SourceIndex, true, int*>()((void*)&a_argPack...);
        } else {
          currentType = a_currentType;
        }
        while (a_stateOffset < a_procInfo.conversions.size() && a_procInfo.conversions[a_stateOffset].index == BufferIndex) {
          if (a_procInfo.conversions[a_stateOffset].mode == CCM_RESOLVE) {
            RawDataSpecificator::function_type converter = (RawDataSpecificator::function_type)a_procInfo.conversions[a_stateOffset].converter;
            arg_type& ref = *(arg_type*)a_args[BufferIndex];
            void* rawptr = (void*)converter(&ref,0,0,0);
            currentType = a_procInfo.conversions[a_stateOffset].type;
            a_args[BufferIndex] = (arg_type*)rawptr;
          } else if (a_procInfo.conversions[a_stateOffset].mode == CCM_CONVERT) {
            ::fcf::Variant arg(a_procInfo.conversions[a_stateOffset].type, (const void*)a_args[BufferIndex], currentType, (ConvertOptions*)0, (ConvertFunction)a_procInfo.conversions[a_stateOffset].converter);
            currentType = a_procInfo.conversions[a_stateOffset].type;
            a_args[BufferIndex] = (arg_type*)arg.ptr();
            CallerByArg<ArgSize, BufferIndex, SourceIndex, false, InitNextArg>()(a_procInfo, a_args, currentType, a_stateOffset + 1, a_argPack...);
            return;
          } else if (a_procInfo.conversions[a_stateOffset].mode == CCM_PLACE_HOLDER) {
            const std::map<unsigned int, SpecificatorTypeInfo>& s = Details::typeStorage.get(a_procInfo.conversions[a_stateOffset].type)->specificators;
            const std::map<unsigned int, SpecificatorTypeInfo>::const_iterator si = s.find(a_procInfo.conversions[a_stateOffset].specificatorIndex);
            if (si == s.end()){
              throw std::runtime_error("Invalid specificator");
            }
            fcf::StaticVector<fcf::Variant, 4> vs;
            typedef void (*resolve_type)(int&, fcf::StaticVector<fcf::Variant, 4>&);
            resolve_type resolve = (resolve_type)si->second.resolve;
            int* aptr = (int*)a_args[BufferIndex];
            for(unsigned int i = 0; i < a_procInfo.conversions[a_stateOffset].pointerCounter; ++i){
              aptr = *(int**) aptr;
            }
            resolve(*aptr, vs);
            for(size_t i = 0; i < a_procInfo.conversions[a_stateOffset].placeHolders.size(); ++i){
              const ArgPlaceHolder::PlaceHolderArgEx& phae = a_procInfo.conversions[a_stateOffset].placeHolders[i];
              if (vs[phae.placeHolderArgument-1].typeIndex() != phae.type) {
                std::cout << "TYPE: " << Details::typeStorage.get(phae.type)->name << std::endl;;
                vs[phae.placeHolderArgument-1].set(phae.type, vs[phae.placeHolderArgument-1].ptr(), vs[phae.placeHolderArgument-1].typeIndex());
              }
              a_args[phae.argument] = vs[phae.placeHolderArgument-1].ptr();
            }
            CallerByArg<ArgSize, BufferIndex, SourceIndex, false, InitNextArg>()(a_procInfo, a_args, currentType, a_stateOffset + 1, a_argPack...);
            return;
          } else if (a_procInfo.conversions[a_stateOffset].mode == CCM_SKIP) {
            CallerByArg<ArgSize+1, BufferIndex+1, SourceIndex, InitNextArg>()(a_procInfo, a_args, currentType, a_stateOffset+1, a_argPack...);
            return;
          } else if (a_procInfo.conversions[a_stateOffset].mode == CCM_FLAT_ITERATOR) {
            typedef bool (*converter_type)(void*, DynamicIteratorInfo*);
            converter_type converter = (converter_type)a_procInfo.conversions[a_stateOffset].converter;
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
            //a_args.resize(ArgSize+1);
            a_args[BufferIndex+1] = &right;
            CallerByArg<ArgSize+1, BufferIndex, SourceIndex, false, false>()(a_procInfo, a_args, subtype, a_stateOffset + 1, a_argPack...);
            return;
          }
          ++a_stateOffset;
        }
        CallerByArg<ArgSize, BufferIndex+1, InitNextArg ? SourceIndex+1 : SourceIndex, InitNextArg>()(a_procInfo, a_args, currentType, a_stateOffset, a_argPack...);
      }
    };

    template <size_t ArgSize>
    struct CallerByArgComplete{
      public:
        template <typename TDynamicCallInfo, typename TBuffer, typename... TArgPack>
        inline void operator()(const TDynamicCallInfo& a_procInfo, TBuffer& a_args, size_t a_stateOffset, const TArgPack& ... a_argPack){
          typedef typename Template::Sequence<0, ArgSize-1>::type sequence_type;
          _call(a_procInfo, a_args, sequence_type());
        }
      protected:
        template <typename TDynamicCallInfo, typename TBuffer, int... SequencePack>
        inline void _call(const TDynamicCallInfo& a_procInfo, TBuffer& a_args, Template::Sequence<0, SequencePack...> a_sequence){
          typedef void (*simple_function_type)(void*, const decltype(SequencePack)& ...);
          simple_function_type caller = (simple_function_type)a_procInfo.caller;
          caller(a_procInfo.function, *(int*)a_args[SequencePack]...);
        }
    };

    template <size_t SourceIndex, bool InitArg, bool InitNextArg>
    struct CallerByArg<8, 8, SourceIndex, InitArg, InitNextArg>{
      template <typename TDynamicCallInfo, typename TBuffer, typename... TArgPack>
      inline void operator()(const TDynamicCallInfo& a_procInfo, TBuffer& a_args, size_t a_stateOffset, const TArgPack& ... a_argPack){
      }
    };

    template <size_t BufferIndex, size_t SourceIndex, bool InitArg, bool InitNextArg>
    struct CallerByArg<8, BufferIndex, SourceIndex, InitArg, InitNextArg>{
      template <typename TDynamicCallInfo, typename TBuffer, typename... TArgPack>
      inline void operator()(const TDynamicCallInfo& a_procInfo, TBuffer& a_args, size_t a_stateOffset, const TArgPack& ... a_argPack){
      }
    };

    template <size_t ArgSize, size_t SourceIndex, bool InitArg, bool InitNextArg>
    struct CallerByArg<ArgSize, 8, SourceIndex, InitArg, InitNextArg>{
      template <typename TDynamicCallInfo, typename TBuffer, typename... TArgPack>
      inline void operator()(const TDynamicCallInfo& a_procInfo, TBuffer& a_args, size_t a_stateOffset, const TArgPack& ... a_argPack){
      }
    };

  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__CALL__CALLER_BY_ARG_HPP___
