#ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALLER_HPP___
#define ___FCF__BASIS__BITS__CALL__DETAILS__CALLER_HPP___

#include <stddef.h>
#include <type_traits>
#include "../../../Template/Sequence.hpp"
#include "../../../FunctionSignature.hpp"
#include "../../../bits/PartTypes/UniversalArguments.hpp"
#include "../../Specificator/DynamicIteratorInfo.hpp"
#include "../CallConversionMode.hpp"
#include "../../PartSpecificator/ContainerAccessSpecificator.hpp"
#include "CallArgsTypeIndexes.hpp"

namespace fcf {
  namespace Details {

    struct Caller {
      template <typename... TArgPack>
      inline void operator()(const Call& a_callInfo, const TArgPack& ... a_argPack){
        typedef int& ref_type;
        typedef int arg_type;

        void* args[sizeof...(TArgPack)];

        static const unsigned int variantTypeIndex = Type<Variant>().index();
        static const CallArgsTypeIndexes<TArgPack...> callerArgsResolver;

        size_t       currentArgIndex = SIZE_MAX;
        unsigned int currentArgType  = 0;

        const size_t argBufferCapacity = sizeof...(a_argPack) * 3;
        StaticVector<fcf::Variant, sizeof...(a_argPack) * 3> argBuffer;

        _initArgs<0>(a_callInfo, args, a_argPack...);

        const size_t conversionsSize = a_callInfo.conversions.size();
        for(size_t conversionIndex = 0; conversionIndex < conversionsSize; ++conversionIndex){
          const CallConversion& cc = a_callInfo.conversions[conversionIndex];
          switch(cc.mode) {
            case CCM_RESOLVE:
              {
                if (currentArgType == variantTypeIndex) {
                  Variant* variant = (Variant*)args[cc.index];
                  args[cc.index] = variant->ptr();
                  currentArgType = variant->typeIndex();
                } else {
                  RawDataSpecificator::function_type converter = (RawDataSpecificator::function_type)cc.converter;
                  args[cc.index] = (void*)converter((arg_type*)args[cc.index],0,0,0);
                  currentArgType = cc.type;
                }
              }
              break;
            case CCM_CONVERT:
              {
                if (currentArgIndex != cc.index)  {
                  currentArgType = callerArgsResolver.indexes[cc.index];
                  currentArgIndex = cc.index;
                }
                ::fcf::Variant arg(cc.type, (const void*)args[cc.index], currentArgType, (ConvertOptions*)0, (ConvertFunction)cc.converter);
                currentArgType = cc.type;
                args[cc.index] = (arg_type*)arg.ptr();
              }
              break;
            case CCM_PLACE_HOLDER:
              {
                const std::map<unsigned int, SpecificatorTypeInfo>& s = Details::typeStorage.get(cc.type)->specificators;
                const std::map<unsigned int, SpecificatorTypeInfo>::const_iterator si = s.find(cc.specificatorIndex);
                if (si == s.end()){
                  throw std::runtime_error("Invalid specificator");
                }

                int* aptr = (int*)args[cc.index];
                for(unsigned int i = 0; i < cc.pointerCounter; ++i){
                  aptr = *(int**) aptr;
                }

                UniversalCall call = (UniversalCall)si->second.resolve;
                fcf::Variant callResult = call(aptr, 0, 0);

                Variant* callResults;
                size_t   callResultsSize;
                if (callResult.typeIndex() == Type<UniversalArguments>().index()){
                  callResult = call(aptr, 0, 0);
                  UniversalArguments& ua = *(UniversalArguments*)callResult.ptr();
                  callResults = &ua[0];
                  callResultsSize = ua.size();
                } else {
                  callResults = &callResult;
                  callResultsSize = 1;
                }

                for(size_t i = 0; i < cc.placeHolders.size(); ++i){
                  const CallPlaceHolderArgEx& phae = cc.placeHolders[i];
                  const size_t argBufferIndex = argBuffer.size();
                  if (argBufferIndex >= argBufferCapacity){
                    throw std::runtime_error("Argument buffer overflow");
                  }
                  argBuffer.resize(argBufferIndex+1);

                  if (phae.placeHolderArgument-1 >= callResultsSize) {
                    throw std::runtime_error("The function of the specificator returned an insufficient number of arguments");
                  }

                  argBuffer[argBufferIndex].set(phae.type, callResults[phae.placeHolderArgument-1].ptr(), callResults[phae.placeHolderArgument-1].typeIndex());
                  args[phae.argument] = argBuffer[argBufferIndex].ptr();
                }
              }
              break;
            case CCM_FLAT_ITERATOR:
              {
                UniversalCall converter = (UniversalCall)cc.converter;
                Variant viterator = converter(args[cc.index], 0, 0);
                DynamicContainerAccessBase* iterator = (DynamicContainerAccessBase*)viterator.ptr();
                if (!iterator){
                  throw std::runtime_error("Failed to get left bound of argument");
                }
                unsigned int subtype = iterator->getValueTypeIndex();
                void* left = iterator->getValuePtr();
                iterator->setEndPosition();
                void* right = iterator->getValuePtr();
                args[cc.index] = &left;
                args[cc.index+1] = &right;
              }
              break;
          } // switch(cc.mode) end
        } // for(size_t conversionIndex = 0; conversionIndex < a_callInfo.conversions.size(); ++conversionIndex) end
        {
          typedef void (*wrapper_type)(void*, void**);
          ((wrapper_type)a_callInfo.caller)(a_callInfo.function, args);
        }
      }

      template <size_t Index, typename TDynamicCallInfo, typename TBuffer, typename TFirstArg, typename ...TArgPack>
      inline void _initArgs(const TDynamicCallInfo& a_callInfo, TBuffer& a_args, const TFirstArg& a_firstArg, const TArgPack&... a_argPack) {
        a_args[a_callInfo.argsMap[Index]] = (void*)&a_firstArg;
        _initArgs<Index+1>(a_callInfo, a_args, a_argPack...);
      }

      template <size_t Index, typename TDynamicCallInfo, typename TBuffer>
      inline void _initArgs(const TDynamicCallInfo& a_callInfo, TBuffer& a_args) {
      }

    };
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__CALL__CALLER_HPP___
