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
    
    template <size_t ArgSize>
    struct CallerByArgComplete;


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
        if (ArgSize == BufferIndex && a_stateOffset >= a_args.size()) {
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
            std::cout << "LEFT: " << left << std::endl;
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
          test<simple_function_type>();
          caller(a_procInfo.function, *(int*)a_args[SequencePack]...);
        }
        template <typename Ty>
        inline void test() {
          int i =0;
          ++i;
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
