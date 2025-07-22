#ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALLER_BY_LIST_HPP___
#define ___FCF__BASIS__BITS__CALL__DETAILS__CALLER_BY_LIST_HPP___

#include <stddef.h>
#include <utility>
#include "../../../Template/Sequence.hpp"
#include "../../../FunctionSignature.hpp"
#include "../../Specificator/DynamicIteratorInfo.hpp"
#include "../CallConversionMode.hpp"

namespace fcf {
  namespace Details {

    template <int ArgIndex, int ArgSize, int MaxSize>
    struct CallerByList{
      template <typename TDynamicCallInfo, typename TArgs>
      void operator()(const TDynamicCallInfo& a_procInfo, unsigned int a_stateOffset, TArgs& a_args){
        typedef std::pair<void*, unsigned int> arg_type;
        while (a_stateOffset < a_procInfo.conversions.size() && a_procInfo.conversions[a_stateOffset].index == ArgIndex){
          if (a_procInfo.conversions[a_stateOffset].mode == CCM_RESOLVE) {
            int& ref = *(int*)a_args[ArgIndex].first;
            RawDataSpecificator::function_type converter = (RawDataSpecificator::function_type)a_procInfo.conversions[a_stateOffset].converter;
            void* rawptr = (void*)converter(&ref, 0, 0, 0);
            a_args[ArgIndex].first = (arg_type*)rawptr;
            a_args[ArgIndex].second = a_procInfo.conversions[a_stateOffset].type;
          } else if (a_procInfo.conversions[a_stateOffset].mode == CCM_CONVERT) {
            ::fcf::Variant arg(a_procInfo.conversions[a_stateOffset].type,
                        (const void*)a_args[ArgIndex].first,
                        a_args[ArgIndex].second,
                        (ConvertOptions*)0,
                        (ConvertFunction)a_procInfo.conversions[a_stateOffset].converter);
            a_args[ArgIndex].first = (arg_type*)arg.ptr();
            a_args[ArgIndex].second = a_procInfo.conversions[a_stateOffset].type;
            CallerByList<ArgIndex, ArgSize, MaxSize>()(a_procInfo, a_stateOffset + 1, a_args);
            return;
          } else if (a_procInfo.conversions[a_stateOffset].mode == CCM_FLAT_ITERATOR) {
            typedef bool (*converter_type)(void*, DynamicIteratorInfo*);
            converter_type converter = (converter_type)a_procInfo.conversions[a_stateOffset].converter;
            DynamicIteratorInfo dii;
            dii.flags = DIF_BEGIN | DIF_GET_VALUE | DIF_GET_TYPE;
            if (!converter(a_args[ArgIndex].first, &dii)){
              throw std::runtime_error("Failed to get left bound of argument");
            }
            unsigned int subtype = dii.type;
            void* left = dii.value;
            dii.flags = DIF_END | DIF_GET_VALUE;
            if (!converter(a_args[ArgIndex].first, &dii)){
              throw std::runtime_error("Failed to get left bound of argument");
            }
            void* right = dii.value;
            a_args.resize(ArgSize+1);
            std::memmove((void*)&a_args[ArgIndex+2], (void*)&a_args[ArgIndex+1], (ArgSize-(ArgIndex+1)) * sizeof(arg_type));
            a_args[ArgIndex].first = &left;
            a_args[ArgIndex].second = subtype;
            a_args[ArgIndex+1].first = &right;
            a_args[ArgIndex+1].second = subtype;
            CallerByList<ArgIndex, ArgSize+1, MaxSize>()(a_procInfo, a_stateOffset + 1, a_args);
            return;
          }
          ++a_stateOffset;
        }
        CallerByList<ArgIndex + 1, ArgSize, MaxSize>()(a_procInfo, a_stateOffset, a_args);
      }
    };

    template <int ArgSize, int MaxSize>
    struct CallerByList<ArgSize, ArgSize, MaxSize>{
      template <typename TDynamicCallInfo, typename TArgs>
      void operator()(const TDynamicCallInfo& a_procInfo, unsigned int a_stateOffset, TArgs& a_args){
        typedef typename Template::Sequence<0, ArgSize-1>::type sequence_type;
        _call(a_procInfo, a_stateOffset, a_args, sequence_type());
      }

      private:
        template <typename TDynamicCallInfo, typename TArgs, int... SequencePack>
        void _call(const TDynamicCallInfo& a_procInfo, unsigned int a_stateOffset, TArgs& a_args, Template::Sequence<0, SequencePack...> a_sequence){
          typedef void (*simple_function_type)(void*, decltype(SequencePack)& ...);
          simple_function_type caller = (simple_function_type)a_procInfo.caller;
          caller(a_procInfo.function, *(int*)a_args[SequencePack].first...);
        }
    };

    template <int ArgIndex, int MaxSize>
    struct CallerByList<ArgIndex, MaxSize, MaxSize>{
      template <typename TDynamicCallInfo, typename TArgs>
      void operator()(const TDynamicCallInfo& a_procInfo, unsigned int a_stateOffset, TArgs& a_args){
        throw std::runtime_error("Argument expansion limit exceeded");
      }
    };

  } // Details namespace
} // fcf namespace


#endif // #ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALLER_BY_LIST_HPP___
