#ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALLER_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALLER_HPP___

#include <stddef.h>
#include <type_traits>
#include <map>
#include <memory>
#include "../../../PartConvert.hpp"
#include "../FunctionSignature.hpp"
#include "../../../PartException.hpp"
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
//
// Need to check whether invaiantIteration is always as set to a last item
//
//
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
          StaticVector<unsigned short, 8>         map;
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
            Caller::KeyNode ca{conversion.index, conversion.sourceIndex, (unsigned int)conversion.mode};
            auto insertIt = node->conversions.insert({ca, ConversionInfoNode()});
            ConversionInfoNode* typesConversion = &insertIt.first->second;
            typesConversion->conversion =  conversion;
            typesConversion->map        =  a_call.rargsMap;
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
        size_t                itemSize;
        unsigned int          typeIndex;
        unsigned int          beginArgIndex;
        unsigned int          currentIteratorConversionsEndIndex;
        const CallConversion* currentIteratorConversions[FCF_CALL_ITERATION_CONVERSION_BUFFER_SIZE];
        const CallConversion* conversion;
        void*                 leftBufferChildArg;
        void*                 rightBufferChildArg;
        void*                 beginBufferChildArg;
        void*                 endBufferChildArg;
        IterationState(Variant&& a_iterator, unsigned int a_beginArgIndex, unsigned int a_currentIteratorConversionsEndIndex, const CallConversion* a_conversion, void* /*a_ptrArg*/)
          : iterator(std::move(a_iterator))
          , itemSize(0)
          , typeIndex(0)
          , beginArgIndex(a_beginArgIndex)
          , currentIteratorConversionsEndIndex(a_currentIteratorConversionsEndIndex)
          , conversion(a_conversion)
        {
        }
        IterationState(unsigned int a_typeIndex, unsigned int a_beginArgIndex, unsigned int a_currentIteratorConversionsEndIndex, const CallConversion* a_conversion, void* a_ptrArg, void* a_endPtrArg, size_t a_itemSize)
          : itemSize(a_itemSize)
          , typeIndex(a_typeIndex)
          , beginArgIndex(a_beginArgIndex)
          , currentIteratorConversionsEndIndex(a_currentIteratorConversionsEndIndex)
          , conversion(a_conversion)
          , leftBufferChildArg(*(void**)a_ptrArg)
          , rightBufferChildArg(*(void**)a_endPtrArg)
          , beginBufferChildArg(*(void**)a_ptrArg)
          , endBufferChildArg(*(void**)a_endPtrArg)
        {
        }
        IterationState(){
        }
      };

      struct ConversionState {
        enum {
          BUFFER_CAPACITY = 16
        };
        ConversionState(const char* a_functionName)
          : functionName(a_functionName)
          , currentIteratorArgumentIndex(INT_MAX) {
        }
        const char*                                          functionName;
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
      inline void call(bool& a_complete, const char* a_functionName, CallGraph& a_graph, const TArgPack& ... a_argPack){
        CallArguments arguments(Nop(), a_argPack...);
        CallExecutor callExecutor;
        callWithArguments(callExecutor, a_complete, a_functionName, a_graph, arguments);
      }

      template <typename... TArgPack>
      inline Variant rcall(bool& a_complete, const char* a_functionName, CallGraph& a_graph, const TArgPack& ... a_argPack){
        CallArguments arguments(Nop(), a_argPack...);
        RCallExecutor callExecutor;
        callWithArguments(callExecutor, a_complete, a_functionName, a_graph, arguments);
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
      template <typename TCallExecutor>
      inline void callWithArguments(TCallExecutor& a_callExecutor, bool& a_complete, const char* a_functionName, CallGraph& a_graph, CallArguments& a_arguments){
        StaticVector<GraphPosition, 16> stack;

        ConversionState state(a_functionName);

        CallArgumentsExtended argumentsEx(a_arguments);

        CallGraph::ConversionsNode*            pnode     = &a_graph.conversions;
        const Call*                 pcall     = pnode->call.complete ? &pnode->call : 0;
        std::shared_ptr<CallGraph>* psubgraph = pnode->call.complete ? &pnode->graph : 0;
        while(!pcall){
          stack.push_back({pnode->conversions.begin(), pnode->conversions.end() });

          GraphPosition& position = stack.back();

          if (position.conversionBegin == position.conversionEnd){
            break;
          }

          argumentsEx.assignMap(&position.conversionBegin->second.map);

          bool isNotIterationMode = _conversion(position.conversionBegin->second.conversion, state, argumentsEx, -1);

          std::map<unsigned int, CallGraph::ConversionsNode>::iterator typeIt    = isNotIterationMode
                                              ? position.conversionBegin->second.types.find(argumentsEx.getTypeIndex(position.conversionBegin->first.argument) )
                                              : position.conversionBegin->second.types.begin();
          std::map<unsigned int, CallGraph::ConversionsNode>::iterator typeItEnd = position.conversionBegin->second.types.end();

          if (typeIt == typeItEnd){
            break;
          }

          pnode = &typeIt->second;

          if (pnode->call.complete){
            pcall     = &pnode->call;
            psubgraph = &pnode->graph;
            break;
          }

          ++position.conversionBegin;
        }

        if (pcall){
          a_complete = true;
          argumentsEx.prepare();
          _execution(a_callExecutor, state, *pcall, -1, argumentsEx.getCallArguments(), psubgraph);
        } else {
          a_complete = false;
        }
      }

      inline bool _isIteratorEnd(const IterationState& a_is){
        DynamicContainerAccessBase* iterator = (DynamicContainerAccessBase*)a_is.iterator.ptr();
        if (iterator) {
          return iterator->isEnd();
        } else {
          return a_is.beginBufferChildArg >= a_is.endBufferChildArg;
        }
      }

      inline void _iteratorInc(IterationState& a_is){
        DynamicContainerAccessBase* iterator = (DynamicContainerAccessBase*)a_is.iterator.ptr();
        if (iterator) {
          iterator->inc();
        } else {
          a_is.beginBufferChildArg = (char*)a_is.beginBufferChildArg + a_is.itemSize;
        }
      }

      inline void _applyIteration(IterationState& a_is,
                                  CallArguments& a_arguments) {
        DynamicContainerAccessBase* iterator = (DynamicContainerAccessBase*)a_is.iterator.ptr();
        if (iterator) {
          a_is.leftBufferChildArg = (void*)iterator->getValuePtr();
          a_is.rightBufferChildArg = (char*)a_is.leftBufferChildArg + iterator->getValueTypeInfo()->size;
          unsigned int typeIndex = iterator->getValueTypeIndex();
          typeIndex = TypeIndexConverter<>::addLevelPointer(typeIndex);
          a_arguments.setTypeIndex(a_is.beginArgIndex,   typeIndex);
          a_arguments.setTypeIndex(a_is.beginArgIndex+1, typeIndex);
        } else {
          a_is.leftBufferChildArg = a_is.beginBufferChildArg;
          a_is.rightBufferChildArg = (char*)a_is.leftBufferChildArg + a_is.itemSize;
        }
        a_arguments.setArgument(a_is.beginArgIndex, &a_is.leftBufferChildArg);
        a_arguments.setArgument(a_is.beginArgIndex+1, &a_is.rightBufferChildArg);
      }

      inline void _initIteration(IterationState& a_is,
                                 CallArguments& a_arguments) {
        if (a_is.conversion->mode == CCM_ITERATOR) {
          UniversalCall converter = (UniversalCall)a_is.conversion->converter;
          a_is.iterator           = converter(*(void**)a_arguments.getArgument(a_is.beginArgIndex), 0, 0);
        } else {
          a_is.beginBufferChildArg = a_arguments.getArgument(a_is.beginArgIndex);
          a_is.endBufferChildArg   = a_arguments.getArgument(a_is.beginArgIndex+1);
          a_is.itemSize            = a_arguments.getTypeInfo(a_is.beginArgIndex)->size;
        }
      }

      inline bool _executionIteration(
                                     bool*            a_isFirstCall,
                                     ConversionState& a_state,
                                     CallArguments&   a_arguments,
                                     bool&            a_dstIsInvariantMode
                                     ){
        size_t start = 0;

        while(true) {
          if (*a_isFirstCall) {
            *a_isFirstCall = false;
          } else { // if (*a_isFirstCall)
            start = a_state.iterations.size()-1;
            while(true) {
              _iteratorInc(a_state.iterations[start]);
              if (!_isIteratorEnd(a_state.iterations[start])){
                break;
              }
              if (!start) {
                return false;
              }
              --start;
            } // while(true)
          } // if (*a_isFirstCall) else

          bool   complete = true;
          size_t endIndex = a_state.iterations.size();
          size_t lastIndex = endIndex - 1;
          for(; start < endIndex; ++start) {
            IterationState& is = a_state.iterations[start];
            if (_isIteratorEnd(is)){
              if (!start) {
                return false;
              } else {
                complete = false;
                break;
              }
            }
            _applyIteration(is, a_arguments);
            if (is.currentIteratorConversionsEndIndex) {
              bool pairMode = false;
              for(size_t i = 0; i < is.currentIteratorConversionsEndIndex; ++i){
                if (is.currentIteratorConversions[i]->invariantIteration) {
                  a_dstIsInvariantMode = true;
                }
                _conversion(*is.currentIteratorConversions[i], a_state, a_arguments, INT_MAX, &pairMode);
              }
              if (!pairMode) {
                CallConversion cc;
                cc.mode        = CCM_SINGLE_PAIR_COPY;
                cc.type        = a_arguments.getTypeIndex(is.beginArgIndex);
                cc.index       = is.beginArgIndex;
                _conversion(cc, a_state, a_arguments, INT_MAX);
              }
            }

            if (start != lastIndex) {
              _initIteration(a_state.iterations[start+1], a_arguments);
            }
          } // for(; start < endIndex; ++start)

          if (complete) {
            return true;
          }
        } // while (true)
      }

      template <typename TCallExecutor>
      inline void _executionIterationMode(
                              TCallExecutor& a_callExecutor,
                              ConversionState& a_state,
                              const Call& a_callInfo,
                              int a_lastIterationArgumentIndex,
                              CallArguments& a_arguments,
                              std::shared_ptr<CallGraph>* a_graph = 0) {
        (void) a_callExecutor;
        (void) a_state;
        (void) a_callInfo;
        (void) a_lastIterationArgumentIndex;
        (void) a_arguments;
        (void) a_graph;

        bool firstCall = true;

        CallSeeker<void> seeker(callOptions);

        while(true) {
          CallArguments arguments(a_arguments);

          size_t argBufferSize = a_state.argBuffer.size();

          bool complete;
          bool invariantIteration = false;
          try {
            complete = !_executionIteration(&firstCall, a_state, arguments, invariantIteration);
            if (complete) {
              return;
            }
          } catch(const std::exception&){
            if (argBufferSize != a_state.argBuffer.size()){
              a_state.argBuffer.resize(argBufferSize);
            }
            if (callOptions && callOptions->flags & CO_ITERATION_SELECT_QUIET) {
              continue;
            } else {
              throw;
            }
          }

          if (complete) {
            if (argBufferSize != a_state.argBuffer.size()){
              a_state.argBuffer.resize(argBufferSize);
            }
            return;
          }

          if (a_graph && a_graph->get()) {
            callWithArguments(a_callExecutor, complete, a_callInfo.name.c_str(), *a_graph->get(), arguments);
          }

          if (complete) {
            if (argBufferSize != a_state.argBuffer.size()){
              a_state.argBuffer.resize(argBufferSize);
            }
            continue;
          }

          if (invariantIteration) {

            BaseFunctionSignature funcSignature(arguments.size());
            funcSignature.rcode = Type<void>().index();
            for(size_t i = 0; i < arguments.size(); ++i){
              funcSignature.pacodes[i] = arguments.getTypeIndex(i);
            }
            funcSignature.applySimpleCallSignature();

            Call subcallInfo;
            subcallInfo.complete = false;

            try {
              seeker(a_callInfo.name.c_str(), &funcSignature, 0, &subcallInfo, arguments.getCallArguments(), true);
              if (!subcallInfo.complete){
                throw std::bad_function_call();
              }
            } catch(const std::bad_function_call&){
              if (argBufferSize != a_state.argBuffer.size()){
                a_state.argBuffer.resize(argBufferSize);
              }
              if (callOptions && callOptions->flags & CO_ITERATION_SELECT_QUIET) {
                continue;
              } else {
                throw CallIterableNotFoundException(__FILE__, __LINE__, a_callInfo.name, a_arguments.getStringRepresentationTypes());
              }
            } catch(const std::exception&){
              if (argBufferSize != a_state.argBuffer.size()){
                a_state.argBuffer.resize(argBufferSize);
              }
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
            if (argBufferSize != a_state.argBuffer.size()){
              a_state.argBuffer.resize(argBufferSize);
            }
          } else { // if (invariantIteration) else
            a_callExecutor(a_callInfo, arguments.getArguments());
            if (argBufferSize != a_state.argBuffer.size()){
              a_state.argBuffer.resize(argBufferSize);
            }
          }
        } // while(true)
      }

      template <typename TCallExecutor>
      inline void _execution( TCallExecutor& a_callExecutor,
                              ConversionState& a_state,
                              const Call& a_callInfo,
                              int a_lastIterationArgumentIndex,
                              CallArguments& a_arguments,
                              std::shared_ptr<CallGraph>* a_graph = 0) {
        if (a_state.iterations.size()) {
          _executionIterationMode(a_callExecutor,
                                  a_state,
                                  a_callInfo,
                                  a_lastIterationArgumentIndex,
                                  a_arguments,
                                  a_graph);
        } else {
          a_callExecutor(a_callInfo, a_arguments.getArguments());
        }
      }


      template <typename TCallExecutor, typename ... TArgPack>
      inline void _call(TCallExecutor& a_callExecutor, const Call& a_callInfo, int a_lastIterationArgumentIndex, CallArguments& a_arguments){
        ConversionState state(a_callInfo.name.c_str());

        CallArgumentsExtended eargs(a_arguments, a_callInfo.rargsMap);

        const size_t conversionsSize = a_callInfo.conversions.size();
        for(size_t conversionIndex = 0; conversionIndex < conversionsSize; ++conversionIndex){
          _conversion(a_callInfo.conversions[conversionIndex], state, eargs, a_lastIterationArgumentIndex);
        }

        eargs.prepare();
        _execution(a_callExecutor, state, a_callInfo, a_lastIterationArgumentIndex, eargs.getCallArguments());
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
      inline bool _conversion(const CallConversion& a_cc, ConversionState& a_state, TCallArguments& a_arguments, int a_iteratorIndex = -1, bool* a_pairMode = 0){
        typedef int arg_type;
        if (a_iteratorIndex < (int)a_cc.index &&
            (
              a_state.currentIteratorArgumentIndex == (int)a_cc.index || (a_state.currentIteratorArgumentIndex+1) == (int)a_cc.index
            )
          ){
          if (a_state.iterations.back().currentIteratorConversionsEndIndex >= FCF_CALL_ITERATION_CONVERSION_BUFFER_SIZE){
            throw CallIterationConversionBufferOverflowException(__FILE__, __LINE__, a_state.functionName, a_arguments.getSourceCallArguments().getStringRepresentationTypes());
          }
          if (a_cc.mode == CCM_ITERATOR) {
            UniversalCall converter = (UniversalCall)a_cc.converter;
            a_state.iterations.push_back(IterationState(converter(a_arguments.getArgument(a_cc.index), 0, 0), a_cc.index, 0, &a_cc, 0));
          } else {
            a_state.iterations.back().currentIteratorConversions[a_state.iterations.back().currentIteratorConversionsEndIndex] = &a_cc;
            ++a_state.iterations.back().currentIteratorConversionsEndIndex;
          }
          return false;
        }
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
                throw CallArgumentBufferOverflowExException(__FILE__, __LINE__, a_state.functionName, a_arguments.getSourceCallArguments().getStringRepresentationTypes());
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
                throw CallArgumentBufferOverflowExException(__FILE__, __LINE__, a_state.functionName, a_arguments.getSourceCallArguments().getStringRepresentationTypes());
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
                throw CallArgumentBufferOverflowExException(__FILE__, __LINE__, a_state.functionName, a_arguments.getSourceCallArguments().getStringRepresentationTypes());
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

              fcf::Variant callResult = !!a_cc.converter ? ((UniversalCall)a_cc.converter)(aptr, 0, 0)
                                                         : *(Variant*)a_cc.values;

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
                  throw CallArgumentBufferOverflowExException(__FILE__, __LINE__, a_state.functionName, a_arguments.getSourceCallArguments().getStringRepresentationTypes());
                }
                a_state.argBuffer.resize(argBufferIndex+1);

                if (phae.placeHolderArgument-1 >= callResultsSize) {
                  throw CallSpecificatorArgumentCountException(__FILE__, __LINE__, a_cc.index+1, a_state.functionName, a_arguments.getSourceCallArguments().getStringRepresentationTypes());
                }

                a_state.argBuffer[argBufferIndex].set(phae.type, callResults[phae.placeHolderArgument-1].ptr(), callResults[phae.placeHolderArgument-1].getTypeIndex());

                a_arguments.setArgument(phae.argument, a_state.argBuffer[argBufferIndex].ptr());
                a_arguments.setTypeIndex(phae.argument, a_state.argBuffer[argBufferIndex].getTypeIndex());
              }
            }
            break;
          case CCM_FLAT_ITERATOR:
            {
              UniversalCall converter = (UniversalCall)a_cc.converter;
              void* ptrArgument = a_arguments.getArgument(a_cc.index);
              if ( fcf::TypeIndexConverter<>::isPointer( a_arguments.getTypeIndex(a_cc.index))) {
                ptrArgument = *(void**)ptrArgument;
              }
              Variant viterator = converter(ptrArgument, 0, 0);
              DynamicContainerAccessBase* iterator = (DynamicContainerAccessBase*)viterator.ptr();
              if (!iterator){
                throw CallIteratorGettingException(__FILE__, __LINE__, a_cc.index+1, a_state.functionName, a_arguments.getSourceCallArguments().getStringRepresentationTypes());
              }
              const size_t argBufferIndex = a_state.argBuffer.size();
              if ((argBufferIndex+2) >= ConversionState::BUFFER_CAPACITY){
                throw CallArgumentBufferOverflowExException(__FILE__, __LINE__, a_state.functionName, a_arguments.getSourceCallArguments().getStringRepresentationTypes());
              }

              unsigned int ptrTypeIndex = TypeIndexConverter<>::addLevelPointer( iterator->getValueTypeIndex() );
              a_state.argBuffer.push_back( Variant((int*)iterator->getValuePtr())  );
              a_arguments.setArgument(a_cc.index, a_state.argBuffer.back().ptr());
              a_arguments.setTypeIndex(a_cc.index, ptrTypeIndex);

              iterator->setEndPosition();

              a_state.argBuffer.push_back( Variant((int*)iterator->getValuePtr())  );
              if (a_pairMode != 0) {
                *a_pairMode = true;
              }
              a_arguments.setArgument(a_cc.index+1, a_state.argBuffer.back().ptr());
              a_arguments.setTypeIndex(a_cc.index+1, ptrTypeIndex);
            }
            break;
          case CCM_ITERATOR:
            {
              UniversalCall converter = (UniversalCall)a_cc.converter;
              void* originPtrArgument = a_arguments.getArgument(a_cc.index);
              void* ptrArgument = originPtrArgument;
              if ( fcf::TypeIndexConverter<>::isPointer( a_arguments.getTypeIndex(a_cc.index))) {
                ptrArgument = *(void**)ptrArgument;
              }
              a_state.iterations.push_back(IterationState(converter(ptrArgument, 0, 0), a_cc.index, 0, &a_cc, originPtrArgument));
              DynamicContainerAccessBase* iterator = (DynamicContainerAccessBase*)a_state.iterations.back().iterator.ptr();
              if (!iterator) {
                throw CallIteratorGettingException(__FILE__, __LINE__, a_cc.index+1, a_state.functionName, a_arguments.getSourceCallArguments().getStringRepresentationTypes());
              }
              a_state.currentIteratorArgumentIndex = a_cc.index;

              unsigned int ptrTypeIndex = TypeIndexConverter<>::addLevelPointer( iterator->getValueTypeIndex() );
              a_arguments.setTypeIndex(a_cc.index, ptrTypeIndex);
              a_arguments.setTypeIndex(a_cc.index+1, ptrTypeIndex);
            }
            break;
          case CCM_SEPARATE_PAIR:
            {
              const TypeInfo* itemTypeInfo = getTypeInfo(TypeIndexConverter<>::removeLevelPointer(a_cc.type));
              a_state.iterations.push_back(IterationState(a_cc.type, a_cc.index, 0, &a_cc, a_arguments.getArgument(a_cc.index), a_arguments.getArgument(a_cc.index+1), itemTypeInfo->size) );
              a_state.currentIteratorArgumentIndex = a_cc.index;
            }
            break;
          case CCM_SINGLE_PAIR_COPY:
            {
              const size_t argBufferIndex = a_state.argBuffer.size();
              if ((argBufferIndex+1) >= ConversionState::BUFFER_CAPACITY){
                throw CallArgumentBufferOverflowExException(__FILE__, __LINE__, a_state.functionName, a_arguments.getSourceCallArguments().getStringRepresentationTypes());
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
