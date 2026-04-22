#ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_SELECTOR_HANDLER_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_SELECTOR_HANDLER_HPP___

#include <climits>
#include <algorithm>
#include "../../../PartForeach.hpp"
#include "../../../PartConvert.hpp"
#include "../../../bits/PartType/TypeIndexConverter.hpp"
#include "../../../bits/PartType/getTypeInfo.hpp"
#include "../../../bits/PartSpecificator/ContainerAccessSpecificator.hpp"
#include "../../../bits/PartMetaType/MetaTypeRemoveDeepConst.hpp"
#include "CallConversionNode.hpp"
#include "CallSelectorState.hpp"
#include "CallPairArgumentNode.hpp"
#include "CallArguments.hpp"

namespace fcf {
  namespace NDetails {

    struct CallSelectorHandler {

      struct InputArgument {
        unsigned int                                        typeIndex;
        unsigned int                                        clearTypeIndex;
        ResolveSpecificator::CallFunctionType               resolver;
        ResolveData                                         resolveData;
        UniversalCall                                       containerAccessResolver;
        UniversalCall                                       ptrContainerAccessResolver;
        void*                                               ptrArg;
        const std::map<unsigned int, SpecificatorInfo>*     specificators;
        const std::map<unsigned int, SpecificatorInfo>*     rawSpecificators;
        unsigned int                                        pairCounter;
        bool                                                ignoreConvertSeeker;
        bool                                                enablePtrSpecificators;
        bool                                                singleStepIteration;
        InputArgument*                                      nextArgument;
      };


      void initialize(CallArguments& a_callArguments) {
        inputArguments.resize(a_callArguments.size());
        for(size_t i = 0; i < a_callArguments.size(); ++i) {
          const TypeInfo* ti = a_callArguments.getTypeInfo(i);
          InputArgument& ia          = inputArguments[i];
          ia.ptrArg                  = state.strictSource ? (void*)a_callArguments.getArgument(i) : (void*)0;
          ia.typeIndex               = ti->index;
          ia.clearTypeIndex          = TypeIndexConverter<>::getDataIndex(ti->index);
          ia.resolver                = ti->resolver;
          ia.containerAccessResolver = ti->template getSpecificator<ContainerAccessSpecificator>(0);
          ia.specificators           = &ti->specificators;
          ia.pairCounter             = 0;
          ia.enablePtrSpecificators  = false;
          ia.rawSpecificators        = 0;
          ia.nextArgument            = 0;
          ia.singleStepIteration     = false;
          if (ia.resolver) {
            ia.resolveData = ia.resolver(ia.ptrArg);
          } else {
            ia.resolveData.data      = 0;
            ia.resolveData.typeIndex = 0;
            ia.resolveData.invariant = false;
          }
        }
      }

      CallSelectorHandler(CallSelectorState& a_state)
        : state(a_state) {
      }

      StaticVector<InputArgument, 16> inputArguments;
      CallSelectorState&              state;

      void operator()(CallConversionNode* a_node, InputArgument* a_currentInputArgument, unsigned int a_inputArgumentIndex, unsigned int a_argumentIndex, bool a_dynamicCaller){
        InputArgument* currentInputArgument = a_currentInputArgument ? a_currentInputArgument : &inputArguments[a_inputArgumentIndex];

        size_t originPlaceHolderVecSize = state.placeHolderVec.size();

        const size_t curSpecNodesMaxSize = 8;
        size_t curSpecNodesSize = 0;
        CallConversionNode curSpecNodes[curSpecNodesMaxSize];

        if (a_argumentIndex < state.placeHolderSpecificators->size()) {
          for(size_t i = 0; i < (*state.placeHolderSpecificators)[a_argumentIndex].size(); ++i){
            unsigned int specificatorTypeIndex = (*state.placeHolderSpecificators)[a_argumentIndex][i];
            std::map<unsigned int, SpecificatorInfo>::const_iterator specificatorIt = currentInputArgument->specificators->find(specificatorTypeIndex);
            int pointerCounter = 0;
            if (specificatorIt == currentInputArgument->specificators->cend()) {
              if (currentInputArgument->rawSpecificators){
                pointerCounter = 1;
                specificatorIt = currentInputArgument->rawSpecificators->find(specificatorTypeIndex);
                if (specificatorIt == currentInputArgument->rawSpecificators->cend()){
                  continue;
                }
              } else {
                continue;
              }
            }
            if (curSpecNodesSize == curSpecNodesMaxSize){
              throw CallPlaceholderBufferOverflowException(__FILE__, __LINE__, state.name, convert<std::string>(state.functionSignature));
            }

            CallConversionNode& curnode = curSpecNodes[curSpecNodesSize];
            ++curSpecNodesSize;
            curnode.prev = 0;
            curnode.next = 0;
            curnode.conversion.index = a_argumentIndex;
            curnode.conversion.sourceIndex = a_inputArgumentIndex;
            curnode.conversion.specificatorIndex = specificatorTypeIndex;
            curnode.conversion.pointerCounter    = pointerCounter;
            curnode.conversion.type = currentInputArgument->clearTypeIndex;
            curnode.conversion.mode = CCM_PLACE_HOLDER;
            curnode.conversion.invariantIteration = false;
            curnode.conversion.converter = (void*)specificatorIt->second.universalCall;
            if (a_node) {
              a_node->next = &curnode;
              curnode.prev = a_node;
            }
            a_node = &curnode;
            CallSelectorState::PlaceHolderSource phs;
            phs.specificatorIndex = specificatorTypeIndex;
            phs.argumentNumber = a_argumentIndex;
            state.placeHolderVec.push_back(phs);
          }
        }

        _processingNextArg(a_node, currentInputArgument, a_inputArgumentIndex, a_argumentIndex, a_dynamicCaller);
        if (state.result->complete) {
          return;
        }

        if (state.strictSource && currentInputArgument->resolveData.typeIndex) {
          CallConversionNode curnode;
          curnode.prev = 0;
          curnode.next = 0;
          curnode.conversion.index              = a_argumentIndex;
          curnode.conversion.sourceIndex        = a_inputArgumentIndex;
          curnode.conversion.type               = currentInputArgument->resolveData.typeIndex;
          curnode.conversion.mode               = CCM_RESOLVE;
          curnode.conversion.invariantIteration = currentInputArgument->pairCounter && currentInputArgument->resolveData.invariant;
          curnode.conversion.converter          = (void*)currentInputArgument->resolver;
          if (a_node) {
            a_node->next = &curnode;
            curnode.prev = a_node;
          }
          state.ptrFunctionSignature->pacodes[a_argumentIndex] = state.ptrFunctionSignature->getSimpleCallType(currentInputArgument->resolveData.typeIndex);

          InputArgument nextTypeInputArgument;
          _fillCurrentInputArgument(nextTypeInputArgument, currentInputArgument->resolveData.typeIndex, currentInputArgument->resolveData.data, currentInputArgument->enablePtrSpecificators);
          nextTypeInputArgument.pairCounter = currentInputArgument->pairCounter;

          (*this)(&curnode, &nextTypeInputArgument, a_inputArgumentIndex, a_argumentIndex, a_dynamicCaller);

          state.ptrFunctionSignature->pacodes[a_argumentIndex] = currentInputArgument->typeIndex;
          if (state.result->complete) {
            return;
          }

          if (a_node) {
            a_node->next = 0;
          }
        }

        if (state.strictSource && !currentInputArgument->ignoreConvertSeeker) {
          _convertOperation(false, currentInputArgument->clearTypeIndex, a_node, currentInputArgument, a_inputArgumentIndex, a_argumentIndex, a_dynamicCaller);
          if (state.result->complete) {
            return;
          }
          if (
              TypeIndexConverter<>::isSinglePointer(currentInputArgument->typeIndex) &&
              state.groupIterator->second.argumentOptions[a_argumentIndex] & CAO_CONVERT_POINTER
             ) {
            unsigned unptrTypeIndex = TypeIndexConverter<>::removeLevelPointer(currentInputArgument->clearTypeIndex);
            state.requiredArgumentsFlags.push_back({a_argumentIndex, CAO_CONVERT_POINTER});
            _convertOperation(true, unptrTypeIndex, a_node, currentInputArgument, a_inputArgumentIndex, a_argumentIndex, a_dynamicCaller);
            if (state.result->complete) {
              return;
            }
            state.requiredArgumentsFlags.pop_back();
          }
        } // if (state.strictSource && !currentInputArgument->ignoreConvertSeeker) end

        if ( state.strictSource &&
             a_argumentIndex < state.groupIterator->second.argumentOptions.size() &&
             (state.groupIterator->second.argumentOptions[a_argumentIndex] & (CAO_RESOLVE_POINTER | CAO_PAIR_ITERATION_POINTER)) &&
             TypeIndexConverter<>::isSinglePointer(currentInputArgument->typeIndex)
           ){
          unsigned int typeIndex = TypeIndexConverter<>::getUnpointerSingleIndex(currentInputArgument->typeIndex);
          const TypeInfo* typeInfo = ::fcf::getTypeInfo(typeIndex);
          ResolveSpecificator::CallType resolver = typeInfo->resolver;
          void* ptr = currentInputArgument->ptrArg ? (void*)*(int**)currentInputArgument->ptrArg : 0;
          if (resolver) {
            ResolveData rd  = resolver(ptr);

            int* stubValuePtr = 0;
            if (!rd.typeIndex || !rd.data) {
              rd.typeIndex = Type<int*>().index();
              rd.data = &stubValuePtr;
            }

            unsigned int ptrTypeIndex = TypeIndexConverter<>::getSinglePointerIndex( rd.typeIndex );

            CallConversionNode curnode;
            curnode.prev = 0;
            curnode.next = 0;
            curnode.conversion.index              = a_argumentIndex;
            curnode.conversion.sourceIndex        = a_inputArgumentIndex;
            curnode.conversion.type               = ptrTypeIndex;
            curnode.conversion.mode               = CCM_POINTER_RESOLVE;
            curnode.conversion.invariantIteration = true;
            curnode.conversion.converter          = (void*)resolver;
            if (a_node) {
              a_node->next = &curnode;
              curnode.prev = a_node;
            }

            state.ptrFunctionSignature->pacodes[a_argumentIndex] = state.ptrFunctionSignature->getSimpleCallType(ptrTypeIndex);

            void* ptrData = &rd.data;
            InputArgument newInputArgument;
            _createCurrentInputArgument(newInputArgument, *currentInputArgument, ptrTypeIndex, &ptrData, currentInputArgument->enablePtrSpecificators);

            state.ptrResolveVector.push_back(a_argumentIndex);

            InputArgument nextInputArgument;
            if (newInputArgument.pairCounter) {
              nextInputArgument = newInputArgument;
              newInputArgument.nextArgument = &nextInputArgument;
            }

            bool lastInvariantIteration = state.invariantIteration;
            if (newInputArgument.pairCounter && !newInputArgument.singleStepIteration){
              state.invariantIteration |= rd.invariant;
            }

            (*this)(&curnode, &newInputArgument, a_inputArgumentIndex, a_argumentIndex, a_dynamicCaller);

            state.invariantIteration = lastInvariantIteration;
            state.ptrResolveVector.pop_back();


            state.ptrFunctionSignature->pacodes[a_argumentIndex] = currentInputArgument->typeIndex;
            if (state.result->complete) {
              return;
            }

            if (a_node) {
              a_node->next = 0;
            }
          }
        }

        if (!state.strictSource && currentInputArgument->resolveData.invariant && !currentInputArgument->pairCounter) {
          CallConversionNode curnode;
          curnode.prev = 0;
          curnode.next = 0;
          curnode.conversion.index = a_argumentIndex;
          curnode.conversion.sourceIndex = a_inputArgumentIndex;
          curnode.conversion.type = 0;
          curnode.conversion.mode = CCM_DYNAMIC_RESOLVE;
          curnode.conversion.invariantIteration = false;
          curnode.conversion.converter = (void*)0;
          if (a_node){
            a_node->next = &curnode;
            curnode.prev = a_node;
          }

          unsigned int origTypeIndex = state.ptrFunctionSignature->pacodes[a_argumentIndex];
          state.ptrFunctionSignature->pacodes[a_argumentIndex] = 0;

          bool origDynamicCaller = state.dynamicCaller;
          state.dynamicCaller = true;

          _processingNextArg(&curnode, currentInputArgument, a_inputArgumentIndex, a_argumentIndex, a_dynamicCaller);

          state.dynamicCaller = origDynamicCaller;
          state.ptrFunctionSignature->pacodes[a_argumentIndex] = origTypeIndex;

          if (state.result->complete) {
            return;
          }
          if (a_node) {
            a_node->next = 0;
          }
        }

        if (
            (
              currentInputArgument->containerAccessResolver &&
              state.groupIterator->second.argumentOptions[a_argumentIndex] & CAO_PAIR_ITERATION_POINTER
            )
            ||
            (
              TypeIndexConverter<>::isSinglePointer(currentInputArgument->typeIndex) &&
              currentInputArgument->ptrContainerAccessResolver &&
              state.groupIterator->second.argumentOptions[a_argumentIndex] & CAO_RESOLVE_POINTER
            )
          ) {
          Variant viterator = currentInputArgument->containerAccessResolver ? currentInputArgument->containerAccessResolver(0, 0, 0)
                                                                            : currentInputArgument->ptrContainerAccessResolver(0, 0, 0); 
          DynamicContainerAccessBase* iterator = (DynamicContainerAccessBase*)viterator.ptr();
          if (iterator) {
            unsigned int ptrTypeIndex = iterator->getValueTypeIndex();
            if (ptrTypeIndex & (8 << (24 + 1)) ) {
              ptrTypeIndex |= (16 << (24 + 1));
            } else {
              ptrTypeIndex |= (8 << (24 + 1));
            }

            BaseFunctionSignature* ptrOriginFunctionSignature = state.ptrFunctionSignature;
            BaseFunctionSignature  fs;
            unsigned int originArgumentTypeIndex = state.ptrFunctionSignature->pacodes[a_argumentIndex];

            if (!TypeIndexConverter<>::isSinglePointer(currentInputArgument->typeIndex)) {
              fs = BaseFunctionSignature(state.ptrFunctionSignature->asize + 1);
              fs.rcode = ptrOriginFunctionSignature->rcode;
              std::copy(&state.ptrFunctionSignature->pacodes[0],
                        &state.ptrFunctionSignature->pacodes[a_argumentIndex],
                        &fs.pacodes[0]
                        );

              fs.pacodes[a_argumentIndex]   = state.ptrFunctionSignature->getSimpleCallType(ptrTypeIndex);
              fs.pacodes[a_argumentIndex+1] = state.ptrFunctionSignature->getSimpleCallType(ptrTypeIndex);

              std::copy(&state.ptrFunctionSignature->pacodes[a_argumentIndex+1],
                        &state.ptrFunctionSignature->pacodes[state.ptrFunctionSignature->asize],
                        &fs.pacodes[a_argumentIndex+2]
                        );
              state.ptrFunctionSignature = &fs;
            } else {
              state.ptrFunctionSignature->pacodes[a_argumentIndex]   = state.ptrFunctionSignature->getSimpleCallType(ptrTypeIndex);
              state.ptrFunctionSignature->pacodes[a_argumentIndex+1] = state.ptrFunctionSignature->getSimpleCallType(ptrTypeIndex);
            }

            CallConversionNode curnode;
            curnode.prev = 0;
            curnode.next = 0;
            curnode.conversion.index              = a_argumentIndex;
            curnode.conversion.sourceIndex        = a_inputArgumentIndex;
            curnode.conversion.type               = ptrTypeIndex;
            if (iterator->isFlatContainer()) {
              curnode.conversion.mode = CCM_FLAT_ITERATOR;
            } else {
              state.requiredArgumentsFlags.push_back({a_argumentIndex, CAO_PAIR_SEGMENTATION});
              curnode.conversion.mode = CCM_ITERATOR;
            }
            curnode.conversion.invariantIteration = false;
            curnode.conversion.converter          = currentInputArgument->containerAccessResolver ? (void*)currentInputArgument->containerAccessResolver
                                                                                                  : (void*)currentInputArgument->ptrContainerAccessResolver;
            if (a_node) {
              a_node->next = &curnode;
              curnode.prev = a_node;
            }

            void* leftValue = 0;
            _fillCurrentInputArgument(*currentInputArgument, ptrTypeIndex, &leftValue, true);
            currentInputArgument->pairCounter = 1;

            InputArgument nextArgument(*currentInputArgument);
            void* rightValue = 0;
            nextArgument.ptrArg = &rightValue;
            currentInputArgument->nextArgument = &nextArgument;


            state.requiredArgumentsFlags.push_back({a_argumentIndex, CAO_PAIR_ITERATION_POINTER});

            (*this)(&curnode, currentInputArgument, a_inputArgumentIndex, a_argumentIndex, a_dynamicCaller);

            if (state.ptrFunctionSignature != ptrOriginFunctionSignature) {
              state.ptrFunctionSignature = ptrOriginFunctionSignature;
            } else {
              state.ptrFunctionSignature->pacodes[a_argumentIndex] = originArgumentTypeIndex;
              state.ptrFunctionSignature->pacodes[a_argumentIndex+1] = originArgumentTypeIndex;
            }

            if (state.result->complete) {
              return;
            }
          }
        }

        if (a_node) {
          a_node->next = 0;
        }
        state.placeHolderVec.resize(originPlaceHolderVecSize);
      }



      void _convertOperation(bool a_isPointerMode, unsigned int a_clearTypeIndex, CallConversionNode* a_node, InputArgument* a_currentInputArgument, unsigned int a_inputArgumentIndex, unsigned int a_argumentIndex, bool a_dynamicCaller){
        unsigned int sourceTypeIndex       = state.ptrFunctionSignature->pacodes[a_argumentIndex];
        CallStorageSelectionFunctionsByArgNumber::const_iterator treeIt = state.groupIterator->second.callersTree.find(state.ptrFunctionSignature->asize);
        if (treeIt != state.groupIterator->second.callersTree.end()){
          BaseFunctionSignature shortSign = *state.ptrFunctionSignature;
          for(size_t i = a_argumentIndex + 1; i < shortSign.asize; ++i){
            shortSign.pacodes[i] = 0;
          }
          CallStorageSelectionFunctionsMap::const_iterator rightIt = treeIt->second.lower_bound(shortSign);
          CallStorageSelectionFunctionsMap::const_iterator leftIt = rightIt;

          bool isIgnorePointer = Type<char*>().index() == a_clearTypeIndex;

          if (rightIt != treeIt->second.end()) {
            // right side
            unsigned int rtypeIndex       = rightIt->first.pacodes[a_argumentIndex];
            unsigned int rtypeSimpleIndex = BaseFunctionSignature::getSimpleType(rtypeIndex);
            unsigned int converTypeIndex  = a_isPointerMode ? TypeIndexConverter<>::removeLevelPointer(rtypeSimpleIndex) : rtypeSimpleIndex;
            ConvertFunction convertFunction = getConvertFunction(converTypeIndex, a_clearTypeIndex, 0);
            if (convertFunction) {
              bool popReqArgFlag = false;
              bool ignore = false;

              if (!isIgnorePointer && TypeIndexConverter<>::isSinglePointer(a_clearTypeIndex)) {
                if (state.groupIterator->second.argumentOptions[a_argumentIndex] & CAO_RESOLVE_POINTER){
                  state.requiredArgumentsFlags.push_back({a_argumentIndex, CAO_RESOLVE_POINTER});
                  popReqArgFlag = true;
                } else {
                  ignore = true;
                }
              }

              if (!ignore) {
                CallConversionNode curnode;
                curnode.prev = 0;
                curnode.next = 0;
                curnode.conversion.index = a_argumentIndex;
                curnode.conversion.sourceIndex = a_inputArgumentIndex;
                curnode.conversion.type = rtypeSimpleIndex;
                curnode.conversion.mode = a_isPointerMode ? CCM_PTR_CONVERT : CCM_CONVERT;
                curnode.conversion.invariantIteration = true;
                curnode.conversion.converter = (void*)convertFunction;
                if (a_node){
                  a_node->next = &curnode;
                  curnode.prev = a_node;
                }
                state.ptrFunctionSignature->pacodes[a_argumentIndex] = state.ptrFunctionSignature->getSimpleCallType(rtypeIndex);

                InputArgument nextTypeInputArgument;
                _createCurrentInputArgument(nextTypeInputArgument, *a_currentInputArgument, rtypeSimpleIndex, 0, a_currentInputArgument->enablePtrSpecificators);
                nextTypeInputArgument.ignoreConvertSeeker = true;

                (*this)(&curnode, &nextTypeInputArgument, a_inputArgumentIndex, a_argumentIndex, a_dynamicCaller);
                state.ptrFunctionSignature->pacodes[a_argumentIndex] = sourceTypeIndex;
                if (state.result->complete) {
                  return;
                }
                if (a_node) {
                  a_node->next = 0;
                }
                if (popReqArgFlag){
                  state.requiredArgumentsFlags.pop_back();
                }
              }
            }
          }

          // left side
          if (leftIt != treeIt->second.begin()) {
            --leftIt;
            unsigned int rtypeIndex = leftIt->first.pacodes[a_argumentIndex];
            unsigned int rtypeSimpleIndex = BaseFunctionSignature::getSimpleType(rtypeIndex);
            unsigned int converTypeIndex  = a_isPointerMode ? TypeIndexConverter<>::removeLevelPointer(rtypeSimpleIndex) : rtypeSimpleIndex;
            ConvertFunction convertFunction = getConvertFunction(converTypeIndex, a_clearTypeIndex, 0);
            if (convertFunction){
              bool popReqArgFlag = false;
              bool ignore = false;

              if (!isIgnorePointer && TypeIndexConverter<>::isSinglePointer(a_clearTypeIndex)) {
                if (state.groupIterator->second.argumentOptions[a_argumentIndex] & CAO_RESOLVE_POINTER){
                  state.requiredArgumentsFlags.push_back({a_argumentIndex, CAO_RESOLVE_POINTER});
                  popReqArgFlag = true;
                } else {
                  ignore = true;
                }
              }

              if (!ignore) {
                CallConversionNode curnode;
                curnode.prev = 0;
                curnode.next = 0;
                curnode.conversion.index = a_argumentIndex;
                curnode.conversion.sourceIndex = a_inputArgumentIndex;
                curnode.conversion.type = rtypeSimpleIndex;
                curnode.conversion.mode = a_isPointerMode ? CCM_PTR_CONVERT : CCM_CONVERT;
                curnode.conversion.invariantIteration = true;
                curnode.conversion.converter = (void*)convertFunction;
                if (a_node){
                  a_node->next = &curnode;
                  curnode.prev = a_node;
                }
                state.ptrFunctionSignature->pacodes[a_argumentIndex] = state.ptrFunctionSignature->getSimpleCallType(rtypeIndex);

                InputArgument nextTypeInputArgument;
                _createCurrentInputArgument(nextTypeInputArgument, *a_currentInputArgument, rtypeSimpleIndex, 0, a_currentInputArgument->enablePtrSpecificators);
                nextTypeInputArgument.ignoreConvertSeeker = true;

                (*this)(&curnode, &nextTypeInputArgument, a_inputArgumentIndex, a_argumentIndex, a_dynamicCaller);
                state.ptrFunctionSignature->pacodes[a_argumentIndex] = sourceTypeIndex;
                if (state.result->complete) {
                  return;
                }
                if (a_node) {
                  a_node->next = 0;
                }
                if (popReqArgFlag){
                  state.requiredArgumentsFlags.pop_back();
                }
              }
            }
          } // if (leftIt != treeIt->second.end()) end
        } // if (treeIt != state.groupIterator->second.callersTree.end()) end
      }



      static ::fcf::CallPlaceHolderArg* _getNextPlaceHolder(CallStorageSelectionFunctionInfo* pCall, int a_currentArgNumber){
        ::fcf::CallPlaceHolderArg* result = 0;
        unsigned int minValue = UINT_MAX;
        bool         exit = false;
        for(size_t phsi  = 0; phsi < pCall->placeHolder.size() && !exit; ++phsi){
          for(size_t phai  = 0; phai < pCall->placeHolder[phsi].placeHolders.size(); ++phai){
            int ca = pCall->placeHolder[phsi].placeHolders[phai].argument;
            if (ca == a_currentArgNumber + 1) {
              minValue = ca;
              result = &pCall->placeHolder[phsi].placeHolders[phai];
              exit = true;
              break;
            }
            if (ca > a_currentArgNumber && (unsigned int)ca < minValue) {
              minValue = ca;
              result = &pCall->placeHolder[phsi].placeHolders[phai];
            }
          }
        }
        return result;
      }



      void _createCurrentInputArgument(InputArgument& a_destinationInputArgument, InputArgument& a_sourceInputArgument, unsigned int a_type, void* a_ptrArg, bool a_enablePtrSpecificators) {
        _fillCurrentInputArgument(a_destinationInputArgument, a_type, a_ptrArg, a_enablePtrSpecificators);
        a_destinationInputArgument.pairCounter = a_sourceInputArgument.pairCounter;
        a_destinationInputArgument.ignoreConvertSeeker = a_sourceInputArgument.ignoreConvertSeeker;
        a_destinationInputArgument.nextArgument = a_sourceInputArgument.nextArgument;
        a_destinationInputArgument.singleStepIteration = a_sourceInputArgument.singleStepIteration;
      }



      void _fillCurrentInputArgument(InputArgument& a_inputArgument, unsigned int a_type, void* a_ptrArg, bool a_enablePtrSpecificators, bool a_singleStepIteration = false){
        a_inputArgument.ptrArg                  = a_ptrArg;
        a_inputArgument.typeIndex               = a_type;
        //a_inputArgument.clearTypeIndex          = TypeIndexConverter<>::getRawIndex(a_type);
        a_inputArgument.clearTypeIndex          = TypeIndexConverter<>::getDataIndex(a_type);
        const fcf::TypeInfo* typeInfo           = typeStorage.get(a_inputArgument.clearTypeIndex);
        a_inputArgument.resolver                = typeInfo->resolver;
        a_inputArgument.containerAccessResolver = typeInfo->getSpecificator<ContainerAccessSpecificator>(0);
        a_inputArgument.specificators           = &typeInfo->specificators;
        a_inputArgument.ignoreConvertSeeker     = false;
        a_inputArgument.enablePtrSpecificators  = a_enablePtrSpecificators;
        a_inputArgument.nextArgument            = 0;
        a_inputArgument.singleStepIteration     = a_singleStepIteration;

        if (a_enablePtrSpecificators && TypeIndexConverter<>::isPointer(a_type)) {
          unsigned int rawTypeIndex     =  TypeIndexConverter<>::getRawIndex(a_type);
          const fcf::TypeInfo* typeInfo = getTypeInfo(rawTypeIndex);
          a_inputArgument.rawSpecificators = &typeInfo->specificators;
          a_inputArgument.ptrContainerAccessResolver = typeInfo->getSpecificator<ContainerAccessSpecificator>(0);
        } else {
          a_inputArgument.rawSpecificators = 0;
          a_inputArgument.ptrContainerAccessResolver = 0;
        }

        if (a_inputArgument.resolver) {
          a_inputArgument.resolveData = a_inputArgument.resolver(a_inputArgument.ptrArg);
        } else {
          a_inputArgument.resolveData.data      = 0;
          a_inputArgument.resolveData.typeIndex = 0;
          a_inputArgument.resolveData.invariant = false;
        }
      }



      inline void _processingNextArg(CallConversionNode* a_node, InputArgument* a_currentInputArgument, unsigned int a_inputArgumentIndex, unsigned int a_argumentIndex, bool a_dynamicCaller, bool a_isIterationMode = false){

        bool isSinglePair = false;

        if (!a_isIterationMode &&
            !a_currentInputArgument->singleStepIteration &&
            !a_currentInputArgument->pairCounter &&
            state.groupIterator->second.argumentOptions[a_argumentIndex] & CAO_PAIR_ITERATION_POINTER &&
            a_inputArgumentIndex+1 < inputArguments.size() &&
            inputArguments[a_inputArgumentIndex].clearTypeIndex == inputArguments[a_inputArgumentIndex+1].clearTypeIndex &&
            TypeIndexConverter<>::isPointer(inputArguments[a_inputArgumentIndex].typeIndex)
          ) {

          if (a_inputArgumentIndex + 1 < inputArguments.size()) {
            if (inputArguments[a_inputArgumentIndex].ptrArg) {
              if (inputArguments[a_inputArgumentIndex].clearTypeIndex == inputArguments[a_inputArgumentIndex+1].clearTypeIndex &&
                  TypeIndexConverter<>::isPointer(inputArguments[a_inputArgumentIndex].typeIndex)
                  ) {
                unsigned int    tix = TypeIndexConverter<>::removeLevelPointer(inputArguments[a_inputArgumentIndex].typeIndex);
                const TypeInfo* ti  = getTypeInfo(tix);
                void* nextPtr = *((char**)inputArguments[a_inputArgumentIndex].ptrArg) + ti->size;
                isSinglePair = nextPtr == *((void**)inputArguments[a_inputArgumentIndex+1].ptrArg);
              }
            }
          }

          CallConversionNode pairNode;
          pairNode.prev = 0;
          pairNode.next = 0;
          pairNode.conversion.index = a_argumentIndex;
          pairNode.conversion.sourceIndex = a_inputArgumentIndex;
          pairNode.conversion.type = inputArguments[a_inputArgumentIndex].typeIndex;
          pairNode.conversion.mode = !isSinglePair ? CCM_SEPARATE_PAIR : CCM_SINGLE_PAIR;
          pairNode.conversion.invariantIteration = false;
          pairNode.conversion.converter = (void*)0;

          bool restoreNode = false;
          CallConversionNode* node = a_node;
          if (node && node->conversion.index == a_argumentIndex){
              bool enableSeparate = isSinglePair;
              CallConversionNode* cnode = node;
              while (true) {
                if ((cnode->conversion.mode == CCM_RESOLVE || cnode->conversion.mode == CCM_POINTER_RESOLVE || cnode->conversion.mode == CCM_CONVERT || cnode->conversion.mode == CCM_PTR_CONVERT ) && cnode->conversion.invariantIteration){
                  enableSeparate = true;
                }

                if (!cnode->prev){
                  break;
                }

                if (cnode->prev->conversion.index != a_argumentIndex){
                  break;
                }

                cnode = cnode->prev;
              }
              if (enableSeparate) {
                CallConversionNode* prevNode = cnode->prev;

                pairNode.prev = prevNode;
                pairNode.next = cnode;

                cnode->prev = &pairNode;

                if (prevNode) {
                  prevNode->next = &pairNode;
                }

                restoreNode = true;
              }
          } else if (node && isSinglePair) {
            node->next = &pairNode;
            pairNode.prev = node;
            node = &pairNode;
            restoreNode = true;
          } else if (isSinglePair) {
            node = &pairNode;
            restoreNode = true;
          }

          CallConversionNode fillPairNode;
          fillPairNode.prev = 0;
          fillPairNode.next = 0;
          fillPairNode.conversion.index = a_argumentIndex;
          fillPairNode.conversion.sourceIndex = a_inputArgumentIndex;
          fillPairNode.conversion.type = a_currentInputArgument->typeIndex;
          fillPairNode.conversion.mode = CCM_SINGLE_PAIR_COPY;
          fillPairNode.conversion.invariantIteration = false;
          fillPairNode.conversion.converter = (void*)0;

          if (isSinglePair) {
            node->next = &fillPairNode;
            fillPairNode.prev = node;
            node = &fillPairNode;
          }

         _processingNextArg(node, a_currentInputArgument, a_inputArgumentIndex, a_argumentIndex, a_dynamicCaller, true);

          if (state.result->complete) {
            return;
          }
          if (isSinglePair){
            node = node->prev;
            node->next = 0;
          }
          if (restoreNode){
            if (pairNode.prev){
              pairNode.prev->next = pairNode.next;
            }
            if (pairNode.next){
              pairNode.next->prev = pairNode.prev;
            }
          }
        }

        if (a_currentInputArgument->singleStepIteration ||
            (a_currentInputArgument->pairCounter && a_currentInputArgument->nextArgument) ||
            a_isIterationMode ) {
          //const TypeInfo* ti = ::fcf::getTypeInfo(a_currentInputArgument->clearTypeIndex);
          unsigned int lastTypeIndex = state.ptrFunctionSignature->pacodes[a_argumentIndex+1];
          state.ptrFunctionSignature->pacodes[a_argumentIndex+1] = state.ptrFunctionSignature->pacodes[a_argumentIndex];
          a_inputArgumentIndex += a_currentInputArgument->singleStepIteration || a_isIterationMode ? 2 : 1;
          a_argumentIndex      += 2;

          if (a_inputArgumentIndex >= inputArguments.size()) {
            _complete(a_node, a_dynamicCaller);
            if (!state.result->complete) {
              state.ptrFunctionSignature->pacodes[a_argumentIndex-1] = lastTypeIndex;
            }
            return;
          }

          (*this)(a_node, 0, a_inputArgumentIndex, a_argumentIndex, a_dynamicCaller);
          if (!state.result->complete) {
            state.ptrFunctionSignature->pacodes[a_argumentIndex-1] = lastTypeIndex;
          }
          return;
        } else if (a_currentInputArgument->pairCounter && a_currentInputArgument->nextArgument) {
          a_argumentIndex      += 1;
        } else {
          a_inputArgumentIndex += 1;
          a_argumentIndex      += 1;
        }

        if (a_inputArgumentIndex >= inputArguments.size()) {
          _complete(a_node, a_dynamicCaller);
          return;
        }

        (*this)(a_node, a_currentInputArgument->nextArgument, a_inputArgumentIndex, a_argumentIndex, a_dynamicCaller);
      }

      void _complete(CallConversionNode* a_node, bool /*a_dynamicCaller*/) {
        const CallStorageSelectionFunctionInfo* pCall = 0;

        if (!state.dynamicCaller && state.invariantIteration) {
          state.result->complete = true;
          state.result->caller   = 0;
          state.result->rcaller   = 0;
          state.result->function = 0;
          state.result->argCount = state.groupIterator->second.maxArgumentCount;
          state.result->name = state.name;
        } else if (!state.dynamicCaller) {
          std::pair<CallStorageSelectionFunctions::const_iterator, CallStorageSelectionFunctions::const_iterator> range =
              state.groupIterator->second.callers.equal_range(*state.ptrFunctionSignature);
          for(; range.first != range.second; ++range.first) {
            bool found = true;
            for(size_t i = 0; i < range.first->second.placeHolder.size(); ++i) {
              const unsigned int specificatorIndex = range.first->second.placeHolder[i].specificatorIndex;
              const unsigned int placeHolderSourceArgIndex = range.first->second.placeHolder[i].argSourceIndex-1;
              bool subFound = false;
              for(size_t j = 0; j < state.placeHolderVec.size(); ++j) {
                if (specificatorIndex == state.placeHolderVec[j].specificatorIndex) {
                  if (placeHolderSourceArgIndex == state.placeHolderVec[j].argumentNumber){
                    subFound = true;
                    break;
                  }
                }
              }

              if (subFound) {
                const CallStorageFunctionInfo* functionInfo = &state.storage->functions[range.first->second.index];
                for(size_t resolveIndex = 0; resolveIndex <  state.ptrResolveVector.size(); ++resolveIndex){
                  unsigned int resolveArgumentIndex = state.ptrResolveVector[resolveIndex];
                  std::map<unsigned int, unsigned int>::const_iterator it    = functionInfo->argumentOptions.find(resolveArgumentIndex);
                  std::map<unsigned int, unsigned int>::const_iterator itEnd = functionInfo->argumentOptions.cend();
                  if (it == itEnd || !(it->second & CAO_RESOLVE_POINTER) ){
                    subFound = false;
                  }
                }
                for(size_t reqIndex = 0; reqIndex <  state.requiredArgumentsFlags.size(); ++reqIndex){
                  unsigned int reqArgIndex = state.requiredArgumentsFlags[reqIndex].first;
                  unsigned int reqArgFlags = state.requiredArgumentsFlags[reqIndex].second;
                  std::map<unsigned int, unsigned int>::const_iterator it    = functionInfo->argumentOptions.find(reqArgIndex);
                  std::map<unsigned int, unsigned int>::const_iterator itEnd = functionInfo->argumentOptions.cend();
                  unsigned currentMask = it->second & reqArgFlags;
                  if (it == itEnd || currentMask != reqArgFlags){
                    subFound = false;
                  }
                }
              }

              if (!subFound) {
                found = false;
              }
            }
            if (found) {
              break;
            }
          }
          if (range.first == range.second) {
            return;
          }
          pCall = &range.first->second;
          state.result->complete = true;
          state.result->caller   = (void*)range.first->second.lcaller;
          state.result->rcaller  = (void*)range.first->second.rcaller;
          state.result->function = state.storage->functions[range.first->second.index].function;
          state.result->argCount = range.first->second.callerSignature.asize;
          state.result->name = state.name;
          if (state.resultFunctionSignature){
            *state.resultFunctionSignature = *state.ptrFunctionSignature;
          }
        } else {
          CallStorageSelectionFunctionsByArgNumber::const_iterator treeIt = state.groupIterator->second.callersTree.find(state.ptrFunctionSignature->asize);
          if (treeIt != state.groupIterator->second.callersTree.end()) {
            CallStorageSelectionFunctionsMap::const_iterator it = treeIt->second.begin();
            for(; it != treeIt->second.end(); ++it) {
              unsigned int argIndex = 0;
              for(; argIndex < state.ptrFunctionSignature->asize; ++argIndex){
                if (
                     state.ptrFunctionSignature->pacodes[argIndex] != 0 &&
                     state.ptrFunctionSignature->pacodes[argIndex] != it->first.pacodes[argIndex]
                   ){
                  break;
                }
              }
              if (argIndex == state.ptrFunctionSignature->asize) {
                break;
              }
            }
            if (it != treeIt->second.end()){
              state.result->complete = true;
              state.result->dynamicCaller = true;
              state.result->name = state.name;
              return;
            }
          }
        }

        if (state.result->complete) {
          state.result->argsMap.resize(state.functionSignature.asize);
          if (a_node) {
            unsigned int currentPHIndex = UINT_MAX;
            unsigned int currentIIIndex = UINT_MAX;
            CallConversionNode* begNode = a_node;

            CallConversion* lastIterationConvertion = 0;

            unsigned int singleIterationLastIndex = UINT_MAX;
            while(begNode->prev){
              if (begNode->conversion.mode == CCM_SINGLE_PAIR_COPY){
                singleIterationLastIndex = begNode->conversion.index;
              }
              if (
                    (
                      begNode->conversion.mode == CCM_RESOLVE || 
                      begNode->conversion.mode == CCM_POINTER_RESOLVE || 
                      begNode->conversion.mode == CCM_CONVERT || 
                      begNode->conversion.mode == CCM_PTR_CONVERT
                    ) &&
                    begNode->conversion.invariantIteration &&
                    singleIterationLastIndex != begNode->conversion.index
                  ){
                begNode->next = 0;
                currentPHIndex = begNode->conversion.index;
                currentIIIndex = begNode->conversion.index;
              }

              if (begNode->conversion.mode == CCM_PLACE_HOLDER){
                currentPHIndex = begNode->conversion.index;
              } else if ( begNode->conversion.mode == CCM_FLAT_ITERATOR && 
                          (
                            currentPHIndex == begNode->conversion.index ||
                            (
                              lastIterationConvertion && lastIterationConvertion->index == begNode->conversion.index
                            )
                          ) 
                        ) {
                begNode->conversion.mode = CCM_ITERATOR;
                state.requiredArgumentsFlags.push_back({begNode->conversion.index, CAO_PAIR_SEGMENTATION});
              }

              if ((begNode->conversion.mode == CCM_FLAT_ITERATOR) || (begNode->conversion.mode == CCM_ITERATOR)){
                lastIterationConvertion = &begNode->conversion;
              }

              if (begNode->conversion.mode == CCM_ITERATOR && currentIIIndex == begNode->conversion.index) {
                begNode->prev = 0;
              }
              begNode = begNode->prev;
            }
            if (begNode->conversion.mode == CCM_FLAT_ITERATOR &&
                (
                  currentPHIndex == begNode->conversion.index ||
                  (
                    lastIterationConvertion && lastIterationConvertion->index == begNode->conversion.index
                  )
                )
              ){
              begNode->conversion.mode = CCM_ITERATOR;
              state.requiredArgumentsFlags.push_back({begNode->conversion.index, CAO_PAIR_SEGMENTATION});
            }

            unsigned int phmapIndex = 0;
            unsigned int phmapOffset = 0;
            unsigned int phmapArgCounter = 0;
                                           // Index as called function argument
                                           // Value as input argument
            StaticVector<unsigned int, 16> phmap(state.result->argCount, 0);
            for(size_t i = 0; pCall && i < pCall->placeHolder.size(); ++i) {
              for(const CallPlaceHolderArg& pha : pCall->placeHolder[i].placeHolders){
                phmap[pha.argument] = UINT_MAX;
              }
            }


            CallConversionNode* node = begNode;


            while(node){
              bool ignore = false;

              node->conversion.index += phmapOffset;
              while(phmapIndex <= node->conversion.index){
                if (phmapIndex >= phmap.size()){
                  throw LogicException(__FILE__, __LINE__, "into CallSelectorHandler (complete step filling flags)");
                }
                if (phmap[phmapIndex] == UINT_MAX){               // if PLACE HOLDER insertion
                  ++phmapOffset;
                  ++node->conversion.index;
                  ++phmapIndex;
                } else if (phmap[phmapIndex] == (UINT_MAX - 1)) { // if CCM_FLAT_ITERATOR insertion
                  ++phmapIndex;
                } else {
                  /*
                  if (phmapIndex != node->conversion.index) {     // if insertion without converter
                    CallConversion conversion;
                    conversion.index        = phmapIndex;
                    conversion.sourceIndex  = phmapArgCounter;
                    conversion.type         = 0;
                    conversion.mode         = CCM_SKIP;
                    conversion.invariantIteration = false;
                    conversion.converter    = 0;
                    state.result->conversions.push_back(conversion);
                  }
                  */
                  phmap[phmapIndex] = phmapArgCounter;
                  ++phmapArgCounter;
                  ++phmapIndex;
                }
              }

              if (node->conversion.mode == CCM_FLAT_ITERATOR || node->conversion.mode == CCM_ITERATOR) {
                if (phmap[phmapIndex] == UINT_MAX){
                  throw LogicException(__FILE__, __LINE__, "into CallSelectorHandler (Placeholder overflow)");
                }
                if (phmapIndex >= phmap.size()){
                  throw LogicException(__FILE__, __LINE__, "into CallSelectorHandler (Placeholder overflow)");
                }
                phmap[phmapIndex] = (UINT_MAX - 1);
              } else if (node->conversion.mode == CCM_PLACE_HOLDER && pCall) {
                std::vector<::fcf::CallPlaceHolderInfo>::const_iterator it =
                  std::find_if(pCall->placeHolder.begin(), pCall->placeHolder.end(), [node](const ::fcf::CallPlaceHolderInfo& a_itm){
                    return a_itm.specificatorIndex == node->conversion.specificatorIndex &&
                           ((unsigned int)a_itm.argSourceIndex - 1) == node->conversion.index;
                  });
                if (it != pCall->placeHolder.end()) {
                  for(auto ph : it->placeHolders) {
                    ::fcf::CallPlaceHolderArgEx phe;
                    phe.argument = ph.argument;
                    phe.placeHolderArgument = ph.placeHolderArgument;
                    phe.type = pCall->callerSignature.pacodes[ph.argument];
                    node->conversion.placeHolders.push_back(phe);
                  }
                } else {
                  ignore = true;
                }
              }
              if (!ignore) {
                state.result->conversions.push_back(node->conversion);
              }
              node = node->next;
            }

            unsigned int srcArgCounter = 0;
            for(unsigned int i = 0; i < phmap.size(); ++i){
              if (phmap[i] < (UINT_MAX - 1)) {
                if (srcArgCounter >= state.result->argsMap.size()){
                  if (state.invariantIteration) {
                    break;
                  } else {
                    throw LogicException(__FILE__, __LINE__, "into CallSelectorHandler (argument map overflow)");
                  }
                }
                state.result->argsMap[srcArgCounter] = i;
                ++srcArgCounter;
              }
            }
          } else { // if (a_node) else
            for(unsigned int i = 0; i < state.result->argsMap.size(); ++i){
              state.result->argsMap[i] = i;
            }
          } // if (a_node) end
        }

      }

    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_SELECTOR_HANDLER_HPP___
