#ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALLER_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALLER_HPP___

#include <stddef.h>
#include <type_traits>
#include <map>
#include <memory>
#include "../../../FunctionSignature.hpp"
#include "../../../bits/PartTypes/UniversalArguments.hpp"
#include "../../../bits/PartSpecificator/ContainerAccessSpecificator.hpp"
#include "../CallConversionMode.hpp"
#include "../CallOptions.hpp"
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
      typedef Variant (*rwrapper_type)(void*, void**);

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

      struct CallGraph;

      struct CallGraph {
        struct ConversionsNode;

        struct ConversionInfoNode {
          CallConversion                          conversion;
          std::map<unsigned int, ConversionsNode> types;
        };

        struct ConversionsNode {
          std::map<KeyNode, ConversionInfoNode> conversions;
          Call                                  call;
          std::shared_ptr<CallGraph>            graph;
        };

        void add(const Call& a_call){
          Caller::CallGraph::ConversionsNode* node = &conversions;
          Call* lastDstCall  = &conversions.call;
          for(const CallConversion& conversion : a_call.conversions){
            Caller::KeyNode ca{conversion.index, conversion.sourceIndex, conversion.mode};
            auto insertIt = node->conversions.insert({ca, ConversionInfoNode()});
            ConversionInfoNode* typesConversion = &insertIt.first->second;
            typesConversion->conversion =  conversion;
            auto insertTypeIt = typesConversion->types.insert({conversion.type, ConversionsNode()});
            lastDstCall = &insertTypeIt.first->second.call;
            node = &insertTypeIt.first->second;
          }
          *lastDstCall = a_call;
        }

        ConversionsNode  conversions;
      };

      struct CallExecutor {
        inline void operator()(const Call& a_callInfo, void** a_args){
          ((wrapper_type)a_callInfo.caller)(a_callInfo.function, a_args);
        }
        inline void result(){
        }
      };

      struct RCallExecutor {
        Variant value;

        inline void operator()(const Call& a_callInfo, void** a_args){
          value = ((rwrapper_type)a_callInfo.rcaller)(a_callInfo.function, a_args);
        }

        inline Variant& result(){
          return value;
        }
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
        std::map<KeyNode, CallGraph::ConversionInfoNode>::iterator             conversionBegin;
        std::map<KeyNode, CallGraph::ConversionInfoNode>::iterator             conversionEnd;
      };

      const CallOptions* callOptions;

      Caller()
        : callOptions(0) {
      }

      Caller(const CallOptions* a_callOptions)
        : callOptions(a_callOptions){
      }

      template <typename... TArgPack>
      inline void call(bool& a_complete, CallGraph& a_graph, const TArgPack& ... a_argPack){
        CallArguments arguments(Nop(), a_argPack...);
        CallArgumentsExtended argumentsEx(arguments);
        CallExecutor callExecutor;
        callWithArguments(callExecutor, a_complete, a_graph, argumentsEx);
      }

      template <typename... TArgPack>
      inline Variant rcall(bool& a_complete, CallGraph& a_graph, const TArgPack& ... a_argPack){
        CallArguments arguments(Nop(), a_argPack...);
        CallArgumentsExtended argumentsEx(arguments);
        RCallExecutor callExecutor;
        callWithArguments(callExecutor, a_complete, a_graph, argumentsEx);
        return callExecutor.result();
      }

      template <typename... TArgPack>
      inline void call(const Call& a_callInfo, const TArgPack& ... a_argPack){
        CallExecutor callExecutor;
        CallArguments arguments(Nop(), a_argPack...);
        _call(callExecutor, a_callInfo, -1, arguments);
      }

      template <typename... TArgPack>
      inline Variant rcall(const Call& a_callInfo, const TArgPack& ... a_argPack){
        RCallExecutor callExecutor;
        CallArguments arguments(Nop(), a_argPack...);
        _call(callExecutor, a_callInfo, -1, arguments);
        return callExecutor.result();
      }

    protected:
      template <typename TCallExecutor, typename... TArgPack>
      inline void callWithArguments(TCallExecutor& a_callExecutor, bool& a_complete, CallGraph& a_graph, CallArgumentsExtended& a_argumentsEx){
        StaticVector<GraphPosition, 16> stack;

        ConversionState state;

        CallGraph::ConversionsNode*            pnode     = &a_graph.conversions;
        const Call*                 pcall     = pnode->call.complete ? &pnode->call : 0;
        std::shared_ptr<CallGraph>* psubgraph = pnode->call.complete ? &pnode->graph : 0;
        while(!pcall){
          stack.push_back({pnode->conversions.begin(), pnode->conversions.end() });

          GraphPosition& position = stack.back();

          if (position.conversionBegin == position.conversionEnd){
            break;
          }

          bool isNotIterationMode = _conversion(position.conversionBegin->second.conversion, state, a_argumentsEx, -1);

          std::map<unsigned int, CallGraph::ConversionsNode>::iterator typeIt    = isNotIterationMode
                                              ? position.conversionBegin->second.types.find( a_argumentsEx.getTypeIndex(position.conversionBegin->first.argument) )
                                              : position.conversionBegin->second.types.begin();
          std::map<unsigned int, CallGraph::ConversionsNode>::iterator typeItEnd = position.conversionBegin->second.types.end();

          if (typeIt == typeItEnd){
            break;
          }

          pnode = &typeIt->second;

          if (pnode->call.complete){
            pcall     = &pnode->call;
            psubgraph = &pnode->graph;
          }

          ++position.conversionBegin;
        }

        if (pcall){
          a_complete = true;
          a_argumentsEx.prepare();
          _execution(a_callExecutor, state, *pcall, -1, a_argumentsEx.getCallArguments(), psubgraph);
        } else {
          a_complete = false;
        }
      }

      template <typename TCallExecutor>
      inline void _execution(
                              TCallExecutor& a_callExecutor,
                              ConversionState& a_state,
                              const Call& a_callInfo,
                              int a_lastIterationArgumentIndex,
                              CallArguments& a_arguments,
                              std::shared_ptr<CallGraph>* a_graph = 0) {
        (void)a_graph;

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
                  Call subcallInfo;
                  subcallInfo.complete = false;
                  CallSeeker<void> seeker;
                  CallArgumentsExtended arguments(a_arguments);

                  size_t argBufferSize = a_state.argBuffer.size();
                  try {
                    if (ist.currentIteratorConversionsEndIndex) {
                      for(unsigned int i = 0; i < ist.currentIteratorConversionsEndIndex; ++i) {
                        _conversion(*ist.currentIteratorConversions[i], a_state, arguments, INT_MAX);
                      }
                      CallConversion cc;
                      cc.mode        = CCM_SINGLE_PAIR_COPY;
                      cc.type        = arguments.getTypeIndex(ist.beginArgIndex);
                      cc.index       = ist.beginArgIndex;
                      _conversion(cc, a_state, arguments, INT_MAX);
                    }
                  } catch(const std::exception& e){
                    if (argBufferSize != a_state.argBuffer.size()){
                      a_state.argBuffer.resize(argBufferSize);
                    }
                    iterator->inc();
                    if (callOptions && callOptions->flags & CO_ITERATION_SELECT_QUIET) {
                      continue;
                    } else {
                      throw;
                    }
                  }

                  arguments.prepare();

                  bool callComplete = false;
                  if (a_graph && a_graph->get()) {
                    callWithArguments(a_callExecutor, callComplete, *a_graph->get(), arguments);
                  }

                  if (!callComplete) {
                    BaseFunctionSignature funcSignature(arguments.size());
                    funcSignature.rcode = Type<void>().index();
                    for(size_t i = 0; i < arguments.size(); ++i){
                      funcSignature.pacodes[i] = arguments.getTypeIndex(i);
                    }
                    funcSignature.applySimpleCallSignature();

                    try {
                      seeker(a_callInfo.name.c_str(), &funcSignature, 0, &subcallInfo, arguments.getCallArguments());
                      if (!subcallInfo.complete){
                        throw std::runtime_error("Iteratable function not found");
                      }
                    } catch(std::exception& e){
                      if (argBufferSize != a_state.argBuffer.size()){
                        a_state.argBuffer.resize(argBufferSize);
                      }
                      iterator->inc();
                      if (callOptions && callOptions->flags & CO_ITERATION_SELECT_QUIET) {
                        continue;
                      } else {
                        throw;
                      }
                    }

                    if (a_graph){
                      if (!a_graph->get()){
                        a_graph->reset(new CallGraph());
                      }
                      (*a_graph)->add(subcallInfo);
                    }
                    _call(a_callExecutor, subcallInfo,  std::max(a_lastIterationArgumentIndex, (int)a_state.iterations.back().currentIteratorConversions[0]->sourceIndex), arguments.getCallArguments());
                  }


                  if (argBufferSize != a_state.argBuffer.size()){
                    a_state.argBuffer.resize(argBufferSize);
                  }
                } else {
                  size_t argBufferSize = a_state.argBuffer.size();
                  try {
                    if (ist.currentIteratorConversionsEndIndex) {
                      for(unsigned int i = 0; i < ist.currentIteratorConversionsEndIndex; ++i) {
                        _conversion(*ist.currentIteratorConversions[i], a_state, a_arguments, INT_MAX);
                      }
                    }
                  } catch(std::exception&) {
                      if (argBufferSize != a_state.argBuffer.size()){
                        a_state.argBuffer.resize(argBufferSize);
                      }
                      iterator->inc();
                      if (callOptions && callOptions->flags & CO_ITERATION_SELECT_QUIET) {
                        continue;
                      } else {
                        throw;
                      }
                  }
                  a_arguments.prepare();
                  a_callExecutor(a_callInfo, a_arguments.getArguments());
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
                _iterationSeparatePair(
                            a_callExecutor,
                            a_state,
                            a_callInfo,
                            ist,
                            valueTypeIndex,
                            ptrSource,
                            (void*)((char*)ptrSource + valueTypeInfo->size),
                            a_arguments.getCallArguments(),
                            a_graph
                          );
                ptrSource = (char*)ptrSource + valueTypeInfo->size;
              }

            } // if (ist.iterator.ptr())
          }
        } else {
          a_arguments.prepare();
          a_callExecutor(a_callInfo, a_arguments.getArguments());
        }
      }

      template <typename TCallExecutor, typename ... TArgPack>
      inline void _call(TCallExecutor& a_callExecutor, const Call& a_callInfo, int a_lastIterationArgumentIndex, CallArguments& a_arguments){
        ConversionState state;

        CallArgumentsExtended eargs(a_arguments);

        const size_t conversionsSize = a_callInfo.conversions.size();
        for(size_t conversionIndex = 0; conversionIndex < conversionsSize; ++conversionIndex){
          _conversion(a_callInfo.conversions[conversionIndex], state, eargs, a_lastIterationArgumentIndex);
        }

        eargs.prepare();
        _execution(a_callExecutor, state, a_callInfo, a_lastIterationArgumentIndex, eargs.getCallArguments());
      }


      template <typename TCallExecutor, typename... TArgPack>
      inline void _iterationSeparatePair(
                                          TCallExecutor& a_callExecutor,
                                          ConversionState& a_state,
                                          const Call& a_callInfo,
                                          IterationState& a_ist,
                                          unsigned int /*a_valueTypeIndex*/,
                                          void* a_begin,
                                          void* a_end,
                                          CallArguments& a_arguments,
                                          std::shared_ptr<CallGraph>* a_graph = 0){
        CallArgumentsExtended arguments(a_arguments);
        arguments.setArgument(a_ist.beginArgIndex, &a_begin);
        arguments.setArgument(a_ist.endArgIndex, &a_end);

        if (a_ist.currentIteratorConversionsEndIndex && a_ist.currentIteratorConversions[a_ist.currentIteratorConversionsEndIndex-1]->invariantIteration ) {


          size_t argBufferSize = a_state.argBuffer.size();
          try {
            if (a_ist.currentIteratorConversionsEndIndex) {
              for(unsigned int i = 0; i < a_ist.currentIteratorConversionsEndIndex; ++i) {
                _conversion(*a_ist.currentIteratorConversions[i], a_state, arguments, INT_MAX);
              }
              CallConversion cc;
              cc.mode        = CCM_SINGLE_PAIR_COPY;
              cc.type        = arguments.getTypeIndex(a_ist.beginArgIndex);
              cc.index       = a_ist.beginArgIndex;
              _conversion(cc, a_state, arguments, INT_MAX);
            }
          } catch(std::exception&) {
              if (argBufferSize != a_state.argBuffer.size()){
                a_state.argBuffer.resize(argBufferSize);
              }
              if (callOptions && callOptions->flags & CO_ITERATION_SELECT_QUIET) {
                return;
              } else {
                throw;
              }
          }


          bool callComplete = false;
          if (a_graph && a_graph->get()) {
            callWithArguments(a_callExecutor, callComplete, *a_graph->get(), arguments);
          }

          if (!callComplete) {
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

            try {
              seeker(a_callInfo.name.c_str(), &funcSignature, 0, &subcallInfo, arguments.getCallArguments());
              if (!subcallInfo.complete){
                throw std::runtime_error("Iteratable function not found");
              }
            } catch(const std::exception& e){
              if (argBufferSize != a_state.argBuffer.size()){
                a_state.argBuffer.resize(argBufferSize);
              }
              if (callOptions && callOptions->flags & CO_ITERATION_SELECT_QUIET) {
                return;
              } else {
                throw;
              }
            }
            if (a_graph){
              if (!a_graph->get()){
                a_graph->reset(new CallGraph());
              }
              (*a_graph)->add(subcallInfo);
            }
            _call(a_callExecutor, subcallInfo, a_ist.currentIteratorConversions[0]->sourceIndex, arguments.getCallArguments());
          }

          if (argBufferSize != a_state.argBuffer.size()){
            a_state.argBuffer.resize(argBufferSize);
          }
        } else {
          size_t argBufferSize = a_state.argBuffer.size();

          try {
            if (a_ist.currentIteratorConversionsEndIndex) {
              for(unsigned int i = 0; i < a_ist.currentIteratorConversionsEndIndex; ++i) {
                _conversion(*a_ist.currentIteratorConversions[i], a_state, arguments, INT_MAX);
              }
            }
          } catch(const std::exception& e){
            if (argBufferSize != a_state.argBuffer.size()){
              a_state.argBuffer.resize(argBufferSize);
            }
            if (callOptions && callOptions->flags & CO_ITERATION_SELECT_QUIET) {
              return;
            } else {
              throw;
            }
          }

          arguments.prepare();
          a_callExecutor(a_callInfo, a_arguments.getArguments());
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
      inline bool _conversion(const CallConversion& a_cc, ConversionState& a_state, TCallArguments& a_arguments, int a_iteratorIndex = -1){
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
          return false;
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
          case CCM_PTR_CONVERT:
            {
              const size_t argBufferIndex = a_state.argBuffer.size();
              if ((argBufferIndex+1) >= ConversionState::BUFFER_CAPACITY){
                throw std::runtime_error("Argument buffer overflow");
              }
              unsigned int currentType = TypeIndexConverter<>::removeLevelPointer( a_arguments.getTypeIndex(a_cc.index) );
              unsigned int expectedType = TypeIndexConverter<>::removeLevelPointer(a_cc.type);
              a_state.argBuffer.push_back(::fcf::Variant(expectedType, *(const void**)a_arguments.getArgument(a_cc.index), currentType, (ConvertOptions*)0, (ConvertFunction)a_cc.converter));
              a_state.argBuffer.push_back(::fcf::Variant( (int*)a_state.argBuffer.back().ptr() ));
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
              a_arguments.setArgumentInfo(a_cc.index+1, a_arguments.getArgumentInfo(a_cc.index));
            }
            break;
          default:
            break;
        } // switch(a_cc.mode) end

        return true;
      }
    };
  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALLER_HPP___
