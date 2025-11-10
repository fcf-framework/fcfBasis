#ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALLER_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALLER_HPP___

#include <stddef.h>
#include <type_traits>
#include "../../../FunctionSignature.hpp"
#include "../../../bits/PartTypes/UniversalArguments.hpp"
#include "../../../bits/PartSpecificator/ContainerAccessSpecificator.hpp"
#include "../CallConversionMode.hpp"
#include "CallArgsTypeIndexes.hpp"

namespace fcf::NDetails {

  struct Caller {
    template <typename... TArgPack>
    inline void operator()(const Call& a_callInfo, const TArgPack& ... a_argPack){
      typedef int& ref_type;
      typedef int arg_type;

      const size_t maxArgCount = 10;

      if (a_callInfo.argCount > maxArgCount){
        throw std::runtime_error("Argument buffer overflow");
      }
      void* args[maxArgCount];

      static const unsigned int variantTypeIndex = Type<Variant>().index();
      static const CallArgsTypeIndexes<TArgPack...> callerArgsResolver;

      size_t       currentArgIndex = SIZE_MAX;
      unsigned int currentArgType  = 0;

      const size_t argBufferCapacity = sizeof...(a_argPack) * 10;
      StaticVector<fcf::Variant, sizeof...(a_argPack) * 10> argBuffer;

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
                ResolveSpecificator::CallFunctionType converter = (ResolveSpecificator::CallFunctionType)cc.converter;
                args[cc.index] = converter((arg_type*)args[cc.index]).data;
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
              const size_t argBufferIndex = argBuffer.size();
              if ((argBufferIndex) >= argBufferCapacity){
                throw std::runtime_error("Argument buffer overflow");
              }
              argBuffer.push_back(::fcf::Variant(cc.type, (const void*)args[cc.index], currentArgType, (ConvertOptions*)0, (ConvertFunction)cc.converter));
              currentArgType = cc.type;
              args[cc.index] = (arg_type*)argBuffer[argBuffer.size()-1].ptr();
            }
            break;
          case CCM_PLACE_HOLDER:
            {
              const std::map<unsigned int, SpecificatorInfo>& s = typeStorage.get(cc.type)->specificators;
              const std::map<unsigned int, SpecificatorInfo>::const_iterator si = s.find(cc.specificatorIndex);
              if (si == s.end()){
                throw std::runtime_error("Invalid specificator");
              }

              int* aptr = (int*)args[cc.index];
              for(unsigned int i = 0; i < cc.pointerCounter; ++i){
                aptr = *(int**) aptr;
              }

              UniversalCall call = (UniversalCall)si->second.universalCall;
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
              const size_t argBufferIndex = argBuffer.size();
              if ((argBufferIndex+1) >= argBufferCapacity){
                throw std::runtime_error("Argument buffer overflow");
              }

              argBuffer.push_back( Variant((int*)iterator->getValuePtr())  );
              args[cc.index] = argBuffer[argBuffer.size()-1].ptr();

              iterator->setEndPosition();

              argBuffer.push_back( Variant((int*)iterator->getValuePtr())  );
              args[cc.index+1] = argBuffer[argBuffer.size()-1].ptr();
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

} // fcf::NDetails namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALLER_HPP___
