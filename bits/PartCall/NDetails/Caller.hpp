#ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALLER_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALLER_HPP___

#include <stddef.h>
#include <type_traits>
#include <map>
#include "../../../FunctionSignature.hpp"
#include "../../../bits/PartTypes/UniversalArguments.hpp"
#include "../../../bits/PartSpecificator/ContainerAccessSpecificator.hpp"
#include "../CallConversionMode.hpp"
#include "CallArgsTypeIndexes.hpp"

namespace fcf {
  namespace NDetails {

    struct Caller {

      struct KeyNode{
        unsigned int argument;
        unsigned int sourceArgument;
        unsigned int conversion;
        bool operator<(const KeyNode& a_item) const{
          return argument < a_item.argument  ? true :
                 argument == a_item.argument ? ( sourceArgument < a_item.sourceArgument  ? true : 
                                                 sourceArgument == a_item.sourceArgument ? conversion < a_item.conversion :
                                                                                           false ) :
                                               false;
        }
      };

      struct TypeNode;

      struct ConversionsNode {
        std::map<KeyNode, TypeNode> conversions;
        Call                        call;
      };

      struct TypeNode{
        std::map<unsigned int, ConversionsNode> types;
      };

      struct CallGraph {
        ConversionsNode  conversions;
      };

      template <typename... TArgPack>
      inline void call(bool& a_complete, const CallGraph& a_graph, const TArgPack& ... a_argPack){
        void* inputArgs[sizeof...(a_argPack)];
        _initArgs<0>(inputArgs, a_argPack...);

        const size_t maxArgCount = sizeof...(TArgPack)*2 + 8;
        void* args[maxArgCount];

        StaticVector<
          std::pair<
            std::map<KeyNode, TypeNode>::const_iterator,
            std::map<KeyNode, TypeNode>::const_iterator
            >,
          16
          > stack;

        const ConversionsNode* pnode     = &a_graph.conversions;
        const Call*            pcall     = pnode->call.complete ? &pnode->call : 0;
        unsigned int           currentNumberArg = 0;
        while(!pcall){
          stack.push_back({pnode->conversions.cbegin(), pnode->conversions.cend()});
          std::map<KeyNode, TypeNode>::const_iterator& it = stack.back().first;
          std::map<KeyNode, TypeNode>::const_iterator& endIt = stack.back().second;

          if (it == endIt){
            break;
          }

          if (currentNumberArg != it->first.argument) {
            args[currentNumberArg] = inputArgs[it->first.sourceArgument];
            currentNumberArg = it->first.argument;
          }

          ++it;
        }

        if (pcall){
          a_complete = true;
        } else {
          a_complete = false;
        }
      }

      template <typename... TArgPack>
      inline void call(const Call& a_callInfo, const TArgPack& ... a_argPack){
        typedef int arg_type;

        const size_t maxArgCount = sizeof...(TArgPack)*2 + 8;

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

        unsigned int nextFlatArgumentIndex = UINT_MAX;
        unsigned int nextFlatArgumentType  = 0;

        const size_t conversionsSize = a_callInfo.conversions.size();
        for(size_t conversionIndex = 0; conversionIndex < conversionsSize; ++conversionIndex){
          const CallConversion& cc = a_callInfo.conversions[conversionIndex];
          switch(cc.mode) {
            case CCM_RESOLVE:
              {
                if (currentArgType == variantTypeIndex) {
                  Variant* variant = (Variant*)args[cc.index];
                  args[cc.index] = variant->ptr();
                  currentArgType = variant->getTypeIndex();
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
                  currentArgType = nextFlatArgumentIndex == cc.index
                                      ? nextFlatArgumentType 
                                      :  callerArgsResolver.indexes[cc.sourceIndex];
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
                int* aptr = (int*)args[cc.index];
                for(unsigned int i = 0; i < cc.pointerCounter; ++i){
                  aptr = *(int**) aptr;
                }

                UniversalCall call = (UniversalCall)cc.converter;
                fcf::Variant callResult = call(aptr, 0, 0);

                Variant* callResults;
                size_t   callResultsSize;
                if (callResult.getTypeIndex() == Type<UniversalArguments>().index()){
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

                  argBuffer[argBufferIndex].set(phae.type, callResults[phae.placeHolderArgument-1].ptr(), callResults[phae.placeHolderArgument-1].getTypeIndex());
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

                nextFlatArgumentIndex = cc.index+1;
                nextFlatArgumentType  = iterator->getValueTypeIndex();
              }
              break;
            default:
              break;
          } // switch(cc.mode) end
        } // for(size_t conversionIndex = 0; conversionIndex < a_callInfo.conversions.size(); ++conversionIndex) end
        {
          typedef void (*wrapper_type)(void*, void**);
          ((wrapper_type)a_callInfo.caller)(a_callInfo.function, args);
        }
      }

      template <size_t Index, typename TBuffer, typename TFirstArg, typename ...TArgPack>
      inline void _initArgs(const Call& a_callInfo, TBuffer& a_args, const TFirstArg& a_firstArg, const TArgPack&... a_argPack) {
        a_args[a_callInfo.argsMap[Index]] = (void*)&a_firstArg;
        _initArgs<Index+1>(a_callInfo, a_args, a_argPack...);
      }

      template <size_t Index, typename TBuffer>
      inline void _initArgs(const Call& /*a_callInfo*/, TBuffer& /*a_args*/) {
      }

      template <size_t Index, typename TBuffer, typename TFirstArg, typename ...TArgPack>
      inline void _initArgs(TBuffer& a_args, const TFirstArg& a_firstArg, const TArgPack&... a_argPack) {
        a_args[Index] = (void*)&a_firstArg;
        _initArgs<Index+1>(a_args, a_argPack...);
      }

      template <size_t Index, typename TBuffer>
      inline void _initArgs(TBuffer& /*a_args*/) {
      }

    };
  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALLER_HPP___
