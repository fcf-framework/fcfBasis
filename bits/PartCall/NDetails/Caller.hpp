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
#include "CallPairArgumentNode.hpp"
#include "../CallSeeker.hpp"

#ifndef FCF_ITERATOR_CONVERSION_BUFFER_SIZE
  #define FCF_CALL_ITERATION_CONVERSION_BUFFER_SIZE 16
#endif

namespace fcf {
  namespace NDetails {

    struct Caller {

      typedef void (*wrapper_type)(void*, void**);

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


      struct IterationState {
        Variant               iterator;
        unsigned int          typeIndex;
        unsigned int          beginArgIndex;
        unsigned int          endArgIndex;
        unsigned int          currentIteratorConversionsEndIndex;
        const CallConversion* currentIteratorConversions[FCF_CALL_ITERATION_CONVERSION_BUFFER_SIZE];
        IterationState(Variant&& a_iterator, unsigned int a_beginArgIndex, unsigned int a_endArgIndex, unsigned int a_currentIteratorConversionsEndIndex)
          : iterator(std::move(a_iterator))
          , typeIndex(0)
          , beginArgIndex(a_beginArgIndex)
          , endArgIndex(a_endArgIndex)
          , currentIteratorConversionsEndIndex(a_currentIteratorConversionsEndIndex)
        {
        }
        IterationState(unsigned int a_typeIndex, unsigned int a_beginArgIndex, unsigned int a_endArgIndex, unsigned int a_currentIteratorConversionsEndIndex)
          : typeIndex(a_typeIndex)
          , beginArgIndex(a_beginArgIndex)
          , endArgIndex(a_endArgIndex)
          , currentIteratorConversionsEndIndex(a_currentIteratorConversionsEndIndex)
        {
        }
        IterationState(){
        }
      };

      struct ConversionState {
        enum {
          BUFFER_CAPACITY = 16
        };
        ConversionState()
          : currentIteratorArgumentIndex(INT_MAX) {
        }
        int                                                  currentIteratorArgumentIndex;
        StaticVector<fcf::Variant, BUFFER_CAPACITY>          argBuffer;
        StaticVector<IterationState>                         iterations;
      };

      struct GraphPosition {
        std::map<KeyNode, ConversionInfoNode>::const_iterator             conversionBegin;
        std::map<KeyNode, ConversionInfoNode>::const_iterator             conversionEnd;
      };

      template <typename... TArgPack>
      inline void call(bool& a_complete, const CallGraph& a_graph, const TArgPack& ... a_argPack){
        CallArguments arguments(Nop(), a_argPack...);
        CallArgumentsExtended argumentsEx(arguments);

        StaticVector<GraphPosition, 16> stack;

        ConversionState state;

        const ConversionsNode* pnode     = &a_graph.conversions;
        const Call*            pcall     = pnode->call.complete ? &pnode->call : 0;
        while(!pcall){
          stack.push_back({pnode->conversions.cbegin(), pnode->conversions.cend() });

          GraphPosition& position = stack.back();

          if (position.conversionBegin == position.conversionEnd){
            break;
          }

          _conversion(position.conversionBegin->second.conversion, state, argumentsEx, -1);

          std::map<unsigned int, ConversionsNode>::const_iterator typeIt    = position.conversionBegin->second.types.find( argumentsEx.getTypeIndex(position.conversionBegin->first.argument) );
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
          argumentsEx.prepare();
         ((wrapper_type)pcall->caller)(pcall->function, argumentsEx.getArguments());
        } else {
          a_complete = false;
        }
      }

      template <typename... TArgPack>
      inline void call(const Call& a_callInfo, const TArgPack& ... a_argPack){
        CallArguments arguments(Nop(), a_argPack...);
        _call(a_callInfo, -1, arguments);
      }

    protected:
       inline void _execution(ConversionState& a_state,
                             const Call& a_callInfo, 
                             int a_lastIterationArgumentIndex,
                             CallArguments& a_arguments) {

        if (a_state.iterations.size() && (!a_state.iterations.back().currentIteratorConversionsEndIndex 
             || (a_lastIterationArgumentIndex < (int)a_state.iterations.back().currentIteratorConversions[0]->sourceIndex) )){
          for(size_t i = 0; i < a_state.iterations.size(); ++i){
            IterationState& ist = a_state.iterations[i];
            if (ist.iterator.ptr()) {

              DynamicContainerAccessBase* iterator = (DynamicContainerAccessBase*)ist.iterator.ptr();
              while(!iterator->isEnd()){
                void* begin = (void*)iterator->getValuePtr();
                void* end = (char*)begin + iterator->getValueTypeInfo()->size;
                a_arguments.setArgument(ist.beginArgIndex, &begin);
                a_arguments.setArgument(ist.endArgIndex, &end);
                a_arguments.setTypeIndex(ist.beginArgIndex, TypeIndexConverter<>::addLevelPointer(iterator->getValueTypeInfo()->index));
                a_arguments.setTypeIndex(ist.endArgIndex, TypeIndexConverter<>::addLevelPointer(iterator->getValueTypeInfo()->index));

                if (ist.currentIteratorConversionsEndIndex && ist.currentIteratorConversions[ist.currentIteratorConversionsEndIndex-1]->invariantIteration ) {
                  BaseFunctionSignature funcSignature(a_arguments.size());
                  funcSignature.rcode = Type<void>().index();
                  for(size_t i = 0; i < a_arguments.size(); ++i){
                    funcSignature.pacodes[i] = a_arguments.getTypeIndex(i);
                  }
                  funcSignature.applySimpleCallSignature();

                  Call subcallInfo;
                  subcallInfo.complete = false;
                  CallSeeker<void> seeker;
                  CallArguments arguments(a_arguments);
                  seeker(a_callInfo.name.c_str(), &funcSignature, 0, &subcallInfo, arguments);
                  if (!subcallInfo.complete){
                    throw std::runtime_error("Iteratable function not found");
                  }
                  _call(subcallInfo,  std::max(a_lastIterationArgumentIndex, (int)a_state.iterations.back().currentIteratorConversions[0]->sourceIndex), arguments);
                } else {
                  size_t argBufferSize = a_state.argBuffer.size();
                  if (ist.currentIteratorConversionsEndIndex) {
                    for(unsigned int i = 0; i < ist.currentIteratorConversionsEndIndex; ++i) {
                      _conversion(*ist.currentIteratorConversions[i], a_state, a_arguments, INT_MAX);
                    }
                  }
                  a_arguments.prepare();
                  ((wrapper_type)a_callInfo.caller)(a_callInfo.function, a_arguments.getArguments());
                  if (argBufferSize != a_state.argBuffer.size()){
                    a_state.argBuffer.resize(argBufferSize);
                  }
                }
                iterator->inc();
              }
            } else { // if (ist.iterator.ptr()) 
              a_arguments.prepare();
              void* ptrSource               = *(void**)a_arguments.getArgument(ist.beginArgIndex);
              void* endSource               = *(void**)a_arguments.getArgument(ist.endArgIndex);
              unsigned int valueTypeIndex   = TypeIndexConverter<>::removeLevelPointer(ist.typeIndex);
              const TypeInfo* valueTypeInfo = fcf::getTypeInfo(valueTypeIndex);
              while(ptrSource < endSource) {
                _iterationSeparatePair(a_state,
                           a_callInfo,
                           ist,
                           valueTypeIndex,
                           ptrSource, 
                           (void*)((char*)ptrSource + valueTypeInfo->size),
                           a_arguments.getCallArguments());
                ptrSource = (char*)ptrSource + valueTypeInfo->size;
              }

            } // if (ist.iterator.ptr())
          }
        } else {
          a_arguments.prepare();
          ((wrapper_type)a_callInfo.caller)(a_callInfo.function, a_arguments.getArguments());
        }
      }

      template <typename ... TArgPack>
      inline void _call(const Call& a_callInfo, int a_lastIterationArgumentIndex, CallArguments& a_arguments){
        ConversionState state;

        CallArgumentsExtended eargs(a_arguments);

        const size_t conversionsSize = a_callInfo.conversions.size();
        for(size_t conversionIndex = 0; conversionIndex < conversionsSize; ++conversionIndex){
          _conversion(a_callInfo.conversions[conversionIndex], state, eargs, a_lastIterationArgumentIndex);
        }

        eargs.prepare();
        _execution(state, a_callInfo, a_lastIterationArgumentIndex, eargs.getCallArguments());
      }


      template <typename... TArgPack>
      inline void _iterationSeparatePair( ConversionState& a_state, 
                                          const Call& a_callInfo, 
                                          IterationState& a_ist, 
                                          unsigned int /*a_valueTypeIndex*/, 
                                          void* a_begin, 
                                          void* a_end, 
                                          CallArguments& a_arguments){
        CallArguments arguments(a_arguments);
        arguments.setArgument(a_ist.beginArgIndex, &a_begin);
        arguments.setArgument(a_ist.endArgIndex, &a_end);

        if (a_ist.currentIteratorConversionsEndIndex && a_ist.currentIteratorConversions[a_ist.currentIteratorConversionsEndIndex-1]->invariantIteration ) {
          BaseFunctionSignature funcSignature(arguments.size());
          funcSignature.rcode = Type<void>().index();
          for(size_t i = 0; i < arguments.size(); ++i){
            funcSignature.pacodes[i] = arguments.getTypeIndex(i);
          }
          funcSignature.applySimpleCallSignature();

          Call subcallInfo;
          subcallInfo.complete = false;
          CallSeeker<void> seeker;
          arguments.prepare();
          seeker(a_callInfo.name.c_str(), &funcSignature, 0, &subcallInfo, arguments.getCallArguments());
          if (!subcallInfo.complete){
            throw std::runtime_error("Iteratable function not found");
          }
          _call(subcallInfo, a_ist.currentIteratorConversions[0]->sourceIndex, arguments.getCallArguments());
        } else {
          size_t argBufferSize = a_state.argBuffer.size();
          if (a_ist.currentIteratorConversionsEndIndex) {
            for(unsigned int i = 0; i < a_ist.currentIteratorConversionsEndIndex; ++i) {
              _conversion(*a_ist.currentIteratorConversions[i], a_state, arguments, INT_MAX);
            }
          }
          arguments.prepare();
          ((wrapper_type)a_callInfo.caller)(a_callInfo.function, a_arguments.getArguments());
          if (argBufferSize != a_state.argBuffer.size()){
            a_state.argBuffer.resize(argBufferSize);
          }
        }
      }

      FCF_FOREACH_METHOD_WRAPPER(FunctionSugnatureInitializer, Caller, _fillFunctionSignature);
      template <typename TTuple, typename Ty>
      void _fillFunctionSignature(const TTuple&, size_t a_tupleIndex, const Ty&, size_t* a_currentIndex, CallPairArgumentNode** a_ppnode, BaseFunctionSignature* a_functionSignature){
        if (*a_ppnode && (*a_ppnode)->index == a_tupleIndex){
          a_functionSignature->pacodes[*a_currentIndex]   = (*a_ppnode)->typeInfo->index;
          a_functionSignature->pacodes[++*a_currentIndex] = (*a_ppnode)->typeInfo->index;
          *a_ppnode = (*a_ppnode)->next;
        } else {
          a_functionSignature->pacodes[*a_currentIndex] = Type<Ty>().index();
        }
        ++*a_currentIndex;
      }

      template <typename TCallArguments>
      inline void _conversion(const CallConversion& a_cc, ConversionState& a_state, TCallArguments& a_arguments, int a_iteratorIndex = -1){
        typedef int arg_type;
        if (a_iteratorIndex < (int)a_cc.index &&
            (
              a_state.currentIteratorArgumentIndex == (int)a_cc.index || (a_state.currentIteratorArgumentIndex+1) == (int)a_cc.index
            )
          ){
          if (a_state.iterations.back().currentIteratorConversionsEndIndex >= FCF_CALL_ITERATION_CONVERSION_BUFFER_SIZE){
            throw std::runtime_error("Iteration conversion buffer overflow (FCF_CALL_ITERATION_CONVERSION_BUFFER_SIZE macro)");
          }
          a_state.iterations.back().currentIteratorConversions[a_state.iterations.back().currentIteratorConversionsEndIndex] = &a_cc;
          ++a_state.iterations.back().currentIteratorConversionsEndIndex;
          return;
        }
        a_arguments.prepare(a_cc.index);
        switch(a_cc.mode) {
          case CCM_RESOLVE:
            {
              ResolveSpecificator::CallFunctionType converter = (ResolveSpecificator::CallFunctionType)a_cc.converter;
              ResolveData rd = converter((arg_type*)a_arguments.getArgument(a_cc.index));
              a_arguments.setArgument(a_cc.index, rd.data);
              a_arguments.setTypeIndex(a_cc.index, rd.typeIndex);
            }
            break;
          case CCM_POINTER_RESOLVE:
            {
              ResolveSpecificator::CallFunctionType converter = (ResolveSpecificator::CallFunctionType)a_cc.converter;
              ResolveData rd = converter(*(arg_type**)a_arguments.getArgument(a_cc.index));
              const size_t argBufferIndex = a_state.argBuffer.size();
              if ((argBufferIndex) >= ConversionState::BUFFER_CAPACITY){
                throw std::runtime_error("Argument buffer overflow");
              }
              a_state.argBuffer.push_back(::fcf::Variant((arg_type*)rd.data));
              a_arguments.setArgument(a_cc.index, a_state.argBuffer.back().ptr());
              a_arguments.setTypeIndex(a_cc.index, TypeIndexConverter<>::addLevelPointer(rd.typeIndex));
            }
            break;
          case CCM_CONVERT:
            {
              const size_t argBufferIndex = a_state.argBuffer.size();
              if ((argBufferIndex) >= ConversionState::BUFFER_CAPACITY){
                throw std::runtime_error("Argument buffer overflow");
              }
              a_state.argBuffer.push_back(::fcf::Variant(a_cc.type, (const void*)a_arguments.getArgument(a_cc.index), a_arguments.getTypeIndex(a_cc.index), (ConvertOptions*)0, (ConvertFunction)a_cc.converter));
              a_arguments.setArgument(a_cc.index, a_state.argBuffer.back().ptr());
              a_arguments.setTypeIndex(a_cc.index, a_cc.type);
            }
            break;
          case CCM_PLACE_HOLDER:
            {
              int* aptr = (int*)a_arguments.getArgument(a_cc.index);
              for(unsigned int i = 0; i < a_cc.pointerCounter; ++i){
                aptr = *(int**) aptr;
              }

              UniversalCall call = (UniversalCall)a_cc.converter;
              fcf::Variant callResult = call(aptr, 0, 0);

              Variant* callResults;
              size_t   callResultsSize;
              if (callResult.getTypeIndex() == Type<UniversalArguments>().index()){
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
                if (argBufferIndex >= ConversionState::BUFFER_CAPACITY){
                  throw std::runtime_error("Argument buffer overflow");
                }
                a_state.argBuffer.resize(argBufferIndex+1);

                if (phae.placeHolderArgument-1 >= callResultsSize) {
                  throw std::runtime_error("The function of the specificator returned an insufficient number of arguments");
                }

                a_state.argBuffer[argBufferIndex].set(phae.type, callResults[phae.placeHolderArgument-1].ptr(), callResults[phae.placeHolderArgument-1].getTypeIndex());

                a_arguments.extend(phae.argument);
                a_arguments.setArgument(phae.argument, a_state.argBuffer[argBufferIndex].ptr());
                a_arguments.setTypeIndex(phae.argument, a_state.argBuffer[argBufferIndex].getTypeIndex());
              }
            }
            break;
          case CCM_FLAT_ITERATOR:
            {
              UniversalCall converter = (UniversalCall)a_cc.converter;
              Variant viterator = converter(a_arguments.getArgument(a_cc.index), 0, 0);
              DynamicContainerAccessBase* iterator = (DynamicContainerAccessBase*)viterator.ptr();
              if (!iterator){
                throw std::runtime_error("Failed to get left bound of argument");
              }
              const size_t argBufferIndex = a_state.argBuffer.size();
              if ((argBufferIndex+2) >= ConversionState::BUFFER_CAPACITY){
                throw std::runtime_error("Argument buffer overflow");
              }

              unsigned int ptrTypeIndex = TypeIndexConverter<>::addLevelPointer( iterator->getValueTypeIndex() );
              a_state.argBuffer.push_back( Variant((int*)iterator->getValuePtr())  );
              a_arguments.setArgument(a_cc.index, a_state.argBuffer.back().ptr());
              a_arguments.setTypeIndex(a_cc.index, ptrTypeIndex);

              iterator->setEndPosition();

              a_state.argBuffer.push_back( Variant((int*)iterator->getValuePtr())  );
              a_arguments.extend(a_cc.index+1);
              a_arguments.setArgument(a_cc.index+1, a_state.argBuffer.back().ptr());
              a_arguments.setTypeIndex(a_cc.index+1, ptrTypeIndex);
            }
            break;
          case CCM_ITERATOR:
            {
              UniversalCall converter = (UniversalCall)a_cc.converter;
              a_state.iterations.push_back(IterationState(converter(a_arguments.getArgument(a_cc.index), 0, 0), a_cc.index, a_cc.index+1, 0));
              DynamicContainerAccessBase* iterator = (DynamicContainerAccessBase*)a_state.iterations.back().iterator.ptr();
              if (!iterator){
                throw std::runtime_error("Failed to get left bound of argument");
              }
              a_state.currentIteratorArgumentIndex = a_cc.index;

              unsigned int ptrTypeIndex = TypeIndexConverter<>::addLevelPointer( iterator->getValueTypeIndex() );
              a_arguments.setTypeIndex(a_cc.index, ptrTypeIndex);
              a_arguments.extend(a_cc.index+1);
              a_arguments.setTypeIndex(a_cc.index+1, ptrTypeIndex);
            }
            break;
          case CCM_SEPARATE_PAIR:
            {
              a_state.iterations.push_back(IterationState(a_cc.type, a_cc.index, a_cc.index+1, 0));
              a_state.currentIteratorArgumentIndex = a_cc.index;
            }
            break;
          case CCM_SINGLE_PAIR_COPY:
            {
              const size_t argBufferIndex = a_state.argBuffer.size();
              if ((argBufferIndex+1) >= ConversionState::BUFFER_CAPACITY){
                throw std::runtime_error("Argument buffer overflow");
              }

              const TypeInfo* ti = fcf::getTypeInfo( TypeIndexConverter<>::removeLevelPointer(a_cc.type) );
              void* ptr = (*(char**)a_arguments.getArgument(a_cc.index)) + ti->size;
              a_state.argBuffer.push_back( Variant((int*)ptr)  );
              a_arguments.setArgument(a_cc.index+1, a_state.argBuffer.back().ptr());
            }
            break;
          default:
            break;
        } // switch(a_cc.mode) end
      }


    };



  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALLER_HPP___
