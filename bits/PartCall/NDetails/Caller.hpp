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

      struct ConversionInfoNode;

      struct ConversionsNode {
        std::map<KeyNode, ConversionInfoNode> conversions;
        Call                                  call;
      };

      struct ConversionInfoNode {
        CallConversion                          conversion;
        std::map<unsigned int, ConversionsNode> types;
      };

      struct CallGraph {
        ConversionsNode  conversions;
      };


      template <typename... TArgPack>
      struct ConversionState {
        ConversionState()
          : nextFlatArgumentIndex(UINT_MAX)
          , nextFlatArgumentType(0)
          , currentArgIndex(SIZE_MAX)
          , currentArgType(0)
          , maxArgCount(sizeof...(TArgPack)*2 + 8)
          , argBufferCapacity(sizeof...(TArgPack) * 10){
        }
        unsigned int nextFlatArgumentIndex;
        unsigned int nextFlatArgumentType;
        size_t       currentArgIndex;
        unsigned int currentArgType;
        static const CallArgsTypeIndexes<TArgPack...> callerArgsResolver;
        const size_t maxArgCount;
        void*        args[sizeof...(TArgPack)*2 + 8];
        const size_t argBufferCapacity;
        StaticVector<fcf::Variant, sizeof...(TArgPack) * 10> argBuffer;
      };

      struct GraphPosition {
        std::map<KeyNode, ConversionInfoNode>::const_iterator             conversionBegin;
        std::map<KeyNode, ConversionInfoNode>::const_iterator             conversionEnd;
      };

      template <typename... TArgPack>
      inline void call(bool& a_complete, const CallGraph& a_graph, const TArgPack& ... a_argPack){
        typedef void (*wrapper_type)(void*, void**);
        void* inputArgs[sizeof...(a_argPack)];
        _initArgs<0>(inputArgs, a_argPack...);

        StaticVector<GraphPosition, 16> stack;

        ConversionState<TArgPack...> state;

        const ConversionsNode* pnode     = &a_graph.conversions;
        const Call*            pcall     = pnode->call.complete ? &pnode->call : 0;
        while(!pcall){
          stack.push_back({pnode->conversions.cbegin(), pnode->conversions.cend() });

          GraphPosition& position = stack.back();

          if (position.conversionBegin == position.conversionEnd){
            break;
          }

          if (state.currentArgIndex != position.conversionBegin->first.argument) {
            state.args[position.conversionBegin->first.argument] = inputArgs[position.conversionBegin->first.sourceArgument];
            state.currentArgIndex = position.conversionBegin->first.argument;
            state.currentArgType  = state.nextFlatArgumentIndex == state.currentArgIndex 
                                      ? state.nextFlatArgumentType 
                                      : ConversionState<TArgPack...>::callerArgsResolver.indexes[position.conversionBegin->first.sourceArgument];
          }

          _processConversion(position.conversionBegin->second.conversion, state);

          std::map<unsigned int, ConversionsNode>::const_iterator typeIt    = position.conversionBegin->second.types.find(state.currentArgType);
          std::map<unsigned int, ConversionsNode>::const_iterator typeItEnd = position.conversionBegin->second.types.cend();

          if (typeIt == typeItEnd){
            break;
          }

          pnode = &typeIt->second;

          if (pnode->call.complete){
            pcall = &pnode->call;
          }

          ++position.conversionBegin;
        }

        if (pcall){
          a_complete = true;
         ((wrapper_type)pcall->caller)(pcall->function, state.args);
        } else {
          a_complete = false;
        }
      }

      template <typename... TArgPack>
      inline void call(const Call& a_callInfo, const TArgPack& ... a_argPack){
        typedef void (*wrapper_type)(void*, void**);
        ConversionState<TArgPack...> state;

        if (a_callInfo.argCount > state.maxArgCount){
          throw std::runtime_error("Argument buffer overflow");
        }
        _initArgs<0>(a_callInfo, state.args, a_argPack...);

        const size_t conversionsSize = a_callInfo.conversions.size();
        for(size_t conversionIndex = 0; conversionIndex < conversionsSize; ++conversionIndex){
          _processConversion(a_callInfo.conversions[conversionIndex], state);
        }

        ((wrapper_type)a_callInfo.caller)(a_callInfo.function, state.args);
      }

    protected:

      template <typename... TArgPack>
      inline void _processConversion(const CallConversion& a_cc, ConversionState<TArgPack...>& a_state){
        typedef int arg_type;
        switch(a_cc.mode) {
          case CCM_RESOLVE:
            {
              ResolveSpecificator::CallFunctionType converter = (ResolveSpecificator::CallFunctionType)a_cc.converter;
              a_state.args[a_cc.index] = converter((arg_type*)a_state.args[a_cc.index]).data;
              a_state.currentArgType = a_cc.type;
            }
            break;
          case CCM_CONVERT:
            {
              if (a_state.currentArgIndex != a_cc.index)  {
                a_state.currentArgType = a_state.nextFlatArgumentIndex == a_cc.index
                                    ? a_state.nextFlatArgumentType
                                    : ConversionState<TArgPack...>::callerArgsResolver.indexes[a_cc.sourceIndex];
                a_state.currentArgIndex = a_cc.index;
              }
              const size_t argBufferIndex = a_state.argBuffer.size();
              if ((argBufferIndex) >= a_state.argBufferCapacity){
                throw std::runtime_error("Argument buffer overflow");
              }
              a_state.argBuffer.push_back(::fcf::Variant(a_cc.type, (const void*)a_state.args[a_cc.index], a_state.currentArgType, (ConvertOptions*)0, (ConvertFunction)a_cc.converter));
              a_state.currentArgType = a_cc.type;
              a_state.args[a_cc.index] = (arg_type*)a_state.argBuffer[a_state.argBuffer.size()-1].ptr();
            }
            break;
          case CCM_PLACE_HOLDER:
            {
              int* aptr = (int*)a_state.args[a_cc.index];
              for(unsigned int i = 0; i < a_cc.pointerCounter; ++i){
                aptr = *(int**) aptr;
              }

              UniversalCall call = (UniversalCall)a_cc.converter;
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

              for(size_t i = 0; i < a_cc.placeHolders.size(); ++i){
                const CallPlaceHolderArgEx& phae = a_cc.placeHolders[i];
                const size_t argBufferIndex = a_state.argBuffer.size();
                if (argBufferIndex >= a_state.argBufferCapacity){
                  throw std::runtime_error("Argument buffer overflow");
                }
                a_state.argBuffer.resize(argBufferIndex+1);

                if (phae.placeHolderArgument-1 >= callResultsSize) {
                  throw std::runtime_error("The function of the specificator returned an insufficient number of arguments");
                }

                a_state.argBuffer[argBufferIndex].set(phae.type, callResults[phae.placeHolderArgument-1].ptr(), callResults[phae.placeHolderArgument-1].getTypeIndex());
                a_state.args[phae.argument] = a_state.argBuffer[argBufferIndex].ptr();
              }
            }
            break;
          case CCM_FLAT_ITERATOR:
            {
              UniversalCall converter = (UniversalCall)a_cc.converter;
              Variant viterator = converter(a_state.args[a_cc.index], 0, 0);
              DynamicContainerAccessBase* iterator = (DynamicContainerAccessBase*)viterator.ptr();
              if (!iterator){
                throw std::runtime_error("Failed to get left bound of argument");
              }
              const size_t argBufferIndex = a_state.argBuffer.size();
              if ((argBufferIndex+1) >= a_state.argBufferCapacity){
                throw std::runtime_error("Argument buffer overflow");
              }

              a_state.argBuffer.push_back( Variant((int*)iterator->getValuePtr())  );
              a_state.args[a_cc.index] = a_state.argBuffer[a_state.argBuffer.size()-1].ptr();

              iterator->setEndPosition();

              a_state.argBuffer.push_back( Variant((int*)iterator->getValuePtr())  );
              a_state.args[a_cc.index+1] = a_state.argBuffer[a_state.argBuffer.size()-1].ptr();

              a_state.nextFlatArgumentIndex = a_cc.index+1;
              a_state.nextFlatArgumentType  = iterator->getValueTypeIndex();
              a_state.currentArgType        = a_cc.type;
            }
            break;
          default:
            break;
        } // switch(a_cc.mode) end
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


    template <typename... TArgPack>
    const CallArgsTypeIndexes<TArgPack...> Caller::ConversionState<TArgPack...>::callerArgsResolver;

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALLER_HPP___
