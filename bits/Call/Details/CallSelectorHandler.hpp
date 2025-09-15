#ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_SELECTOR_HANDLER_HPP___
#define ___FCF__BASIS__BITS__CALL__DETAILS__CALL_SELECTOR_HANDLER_HPP___

#include <climits>
#include <algorithm>
#include "../../../foreach.hpp"
#include "../../../bits/Specificator/DynamicIteratorInfo.hpp"
#include "CallConversionNode.hpp"
#include "CallSelectorState.hpp"

namespace fcf {
  namespace Details {
    
    struct CallSelectorHandler {

      struct InputArgument {
        unsigned int                                        typeIndex;
        unsigned int                                        clearTypeIndex;
        RawDataSpecificator::function_type                  rawDataResolver;
        DynamicIteratorSpecificator::function_type          dynamicIteratorResolver;
        bool                                                invariantRawType;
        unsigned int                                        invariantIndex;
        void*                                               ptrArg;
        void*                                               ptrInvariantArg;
        const std::map<unsigned int, SpecificatorTypeInfo>* specificators;
        unsigned int                                        pairCounter;
        bool                                                ignoreConvertSeeker;
      };

      template <typename TTuple>
      void initialize() {
        TTuple tuple;
        inputArguments.resize(std::tuple_size<TTuple>::value);
        foreach(tuple, *this);
      }

      CallSelectorHandler(CallSelectorState& a_state)
        : state(a_state) {
      }

      StaticVector<InputArgument, 16> inputArguments;
      CallSelectorState&              state;

      void operator()(CallConversionNode* a_node, InputArgument* a_currentInputArgument, unsigned int a_inputArgumentIndex, unsigned int a_argumentIndex, bool a_dynamicCaller){
        unsigned int sourceTypeIndex       = state.ptrFunctionSignature->pacodes[a_argumentIndex];
        InputArgument* currentInputArgument = a_currentInputArgument ? a_currentInputArgument : &inputArguments[a_inputArgumentIndex];

        size_t originPlaceHolderVecSize = state.placeHolderVec.size();

        const size_t curSpecNodesMaxSize = 8;
        size_t curSpecNodesSize = 0;
        CallConversionNode curSpecNodes[curSpecNodesMaxSize];

        if (a_argumentIndex < state.placeHolderSpecificators->size()) {
          for(size_t i = 0; i < (*state.placeHolderSpecificators)[a_argumentIndex].size(); ++i){
            unsigned int specificatorTypeIndex = (*state.placeHolderSpecificators)[a_argumentIndex][i];
            const fcf::Details::TypeInfo* clearTypeInfo = Details::typeStorage.get(currentInputArgument->clearTypeIndex);
            std::map<unsigned int, SpecificatorTypeInfo>::const_iterator specificatorIt = currentInputArgument->specificators->find(specificatorTypeIndex);
            if (specificatorIt == currentInputArgument->specificators->cend()) {
              continue;
            }
            if (curSpecNodesSize == curSpecNodesMaxSize){
              throw std::runtime_error("Overflow specificator vector size");
            }

            CallConversionNode& curnode = curSpecNodes[curSpecNodesSize];
            ++curSpecNodesSize;
            curnode.prev = 0;
            curnode.next = 0;
            curnode.conversion.index = a_argumentIndex;
            curnode.conversion.specificatorIndex = specificatorTypeIndex;
            curnode.conversion.pointerCounter    = typeIndexIsSinglePointer(currentInputArgument->typeIndex) ? 1 :
                                                   typeIndexIsDoublePointer(currentInputArgument->typeIndex) ? 2 :
                                                                                                               0;
            curnode.conversion.type = currentInputArgument->clearTypeIndex;
            curnode.conversion.mode = CCM_PLACE_HOLDER;
            curnode.conversion.converter = (void*)specificatorIt->second.resolve;
            curnode.conversion.converterArgCount = specificatorIt->second.argc;
            if (a_node) {
              a_node->next = &curnode;
              curnode.prev = a_node;
            }
            state.placeHolderVec.push_back(specificatorTypeIndex);
          }
        }

        _processingNextArg(a_node, currentInputArgument, a_inputArgumentIndex, a_argumentIndex, a_dynamicCaller);
         if (state.result->complete) {
          return;
        }

        if (state.strictSource && currentInputArgument->invariantIndex && !currentInputArgument->pairCounter) {
          CallConversionNode curnode;
          curnode.prev = 0;
          curnode.next = 0;
          curnode.conversion.index = a_argumentIndex;
          curnode.conversion.type = currentInputArgument->invariantIndex;
          curnode.conversion.mode = CCM_RESOLVE;
          curnode.conversion.converter = (void*)currentInputArgument->rawDataResolver;
          if (a_node) {
            a_node->next = &curnode;
            curnode.prev = a_node;
          }
          state.ptrFunctionSignature->pacodes[a_argumentIndex] = state.ptrFunctionSignature->getSimpleCallType(currentInputArgument->invariantIndex);

          InputArgument nextTypeInputArgument;
          _fillCurrentInputArgument(nextTypeInputArgument, currentInputArgument->invariantIndex, currentInputArgument->ptrInvariantArg);
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

        if (state.strictSource && !currentInputArgument->pairCounter && !currentInputArgument->ignoreConvertSeeker) {
          Details::IndexableFunction::CallFunctionsByArgNumber::iterator treeIt = state.groupIterator->second.callersTree.find(state.ptrFunctionSignature->asize);
          if (treeIt != state.groupIterator->second.callersTree.end()){
            const Details::TypeInfo* ti =  Details::typeStorage.get(currentInputArgument->clearTypeIndex);
            BaseFunctionSignature shortSign = *state.ptrFunctionSignature;
            for(size_t i = a_argumentIndex + 1; i < shortSign.asize; ++i){
              shortSign.pacodes[i] = 0;
            }
            ::fcf::Details::IndexableFunction::CallFunctionsMap::iterator rightIt = treeIt->second.lower_bound(shortSign);
            ::fcf::Details::IndexableFunction::CallFunctionsMap::iterator leftIt = rightIt;
            if (rightIt != treeIt->second.end()) {
              if (leftIt != treeIt->second.end()) {
                --leftIt;
              }

              // right side
              unsigned int rtypeIndex = rightIt->first.pacodes[a_argumentIndex];
              unsigned int rtypeSimpleIndex = BaseFunctionSignature::getSimpleType(rtypeIndex);
              ConvertFunction convertFunction = getConvertFunction(rtypeSimpleIndex, currentInputArgument->clearTypeIndex, 0);
              if (convertFunction){
                CallConversionNode curnode;
                curnode.prev = 0;
                curnode.next = 0;
                curnode.conversion.index = a_argumentIndex;
                curnode.conversion.type = rtypeSimpleIndex;
                curnode.conversion.mode = CCM_CONVERT;
                curnode.conversion.converter = (void*)convertFunction;
                if (a_node){
                  a_node->next = &curnode;
                  curnode.prev = a_node;
                }
                state.ptrFunctionSignature->pacodes[a_argumentIndex] = state.ptrFunctionSignature->getSimpleCallType(rtypeIndex);

                InputArgument nextTypeInputArgument;
                _createCurrentInputArgument(nextTypeInputArgument, *currentInputArgument, rtypeSimpleIndex, 0);
                nextTypeInputArgument.ignoreConvertSeeker = true;

                (*this)(&curnode, &nextTypeInputArgument, a_inputArgumentIndex, a_argumentIndex, a_dynamicCaller);
                state.ptrFunctionSignature->pacodes[a_argumentIndex] = sourceTypeIndex;
                if (state.result->complete) {
                  return;
                }
                if (a_node) {
                  a_node->next = 0;
                }
              }

              // left side
              if (leftIt != treeIt->second.end()) {
                unsigned int rtypeIndex = leftIt->first.pacodes[a_argumentIndex];
                unsigned int rtypeSimpleIndex = BaseFunctionSignature::getSimpleType(rtypeIndex);
                ConvertFunction convertFunction = getConvertFunction(rtypeSimpleIndex, currentInputArgument->clearTypeIndex, 0);
                if (convertFunction){
                  CallConversionNode curnode;
                  curnode.prev = 0;
                  curnode.next = 0;
                  curnode.conversion.index = a_argumentIndex;
                  curnode.conversion.type = rtypeSimpleIndex;
                  curnode.conversion.mode = CCM_CONVERT;
                  curnode.conversion.converter = (void*)convertFunction;
                  if (a_node){
                    a_node->next = &curnode;
                    curnode.prev = a_node;
                  }
                  state.ptrFunctionSignature->pacodes[a_argumentIndex] = state.ptrFunctionSignature->getSimpleCallType(rtypeIndex);

                  InputArgument nextTypeInputArgument;
                  _createCurrentInputArgument(nextTypeInputArgument, *currentInputArgument, rtypeSimpleIndex, 0);
                  nextTypeInputArgument.ignoreConvertSeeker = true;

                  (*this)(&curnode, &nextTypeInputArgument, a_inputArgumentIndex, a_argumentIndex, a_dynamicCaller);
                  state.ptrFunctionSignature->pacodes[a_argumentIndex] = sourceTypeIndex;
                  if (state.result->complete) {
                    return;
                  }
                  if (a_node) {
                    a_node->next = 0;
                  }
                }
              }
            } // if (leftIt != treeIt->second.end()) end
          } // if (treeIt != state.groupIterator->second.callersTree.end()) end
        } // if (a_iasd.strictSource) end

        if (!state.strictSource && currentInputArgument->invariantRawType && !currentInputArgument->pairCounter) {
          CallConversionNode curnode;
          curnode.prev = 0;
          curnode.next = 0;
          curnode.conversion.index = a_argumentIndex;
          curnode.conversion.type = 0;
          curnode.conversion.mode = CCM_DYNAMIC_RESOLVE;
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

        if (currentInputArgument->dynamicIteratorResolver && !currentInputArgument->pairCounter) {
          DynamicIteratorInfo dii;
          dii.flags = DIF_INFO | DIF_GET_FLAT | DIF_GET_TYPE;
          currentInputArgument->dynamicIteratorResolver(0, &dii);
          if (dii.flat) {
            BaseFunctionSignature* ptrOriginFunctionSignature = state.ptrFunctionSignature;
            BaseFunctionSignature ofs = *state.ptrFunctionSignature;
            BaseFunctionSignature fs = BaseFunctionSignature(state.ptrFunctionSignature->asize + 1);
            fs.rcode = ofs.rcode;
            std::copy(&state.ptrFunctionSignature->pacodes[0],
                      &state.ptrFunctionSignature->pacodes[a_argumentIndex],
                      &fs.pacodes[0]
                      );

            unsigned int ptrTypeIndex = dii.type;
            if (ptrTypeIndex & (8 << (24 + 1)) ) {
              ptrTypeIndex |= (16 << (24 + 1));
            } else {
              ptrTypeIndex |= (8 << (24 + 1));
            }
            fs.pacodes[a_argumentIndex] = state.ptrFunctionSignature->getSimpleCallType(ptrTypeIndex);
            fs.pacodes[a_argumentIndex+1] = state.ptrFunctionSignature->getSimpleCallType(ptrTypeIndex);

            std::copy(&state.ptrFunctionSignature->pacodes[a_argumentIndex+1],
                      &state.ptrFunctionSignature->pacodes[state.ptrFunctionSignature->asize],
                      &fs.pacodes[a_argumentIndex+2]
                      );

            CallConversionNode curnode;
            curnode.prev = 0;
            curnode.next = 0;
            curnode.conversion.index     = a_argumentIndex;
            curnode.conversion.type      = ptrTypeIndex;
            curnode.conversion.mode      = CCM_FLAT_ITERATOR;
            curnode.conversion.converter = (void*)currentInputArgument->dynamicIteratorResolver;
            if (a_node) {
              a_node->next = &curnode;
              curnode.prev = a_node;
            }

            _fillCurrentInputArgument(*currentInputArgument, ptrTypeIndex, 0);
            currentInputArgument->pairCounter = 1;

            state.ptrFunctionSignature = &fs;

            (*this)(&curnode, currentInputArgument, a_inputArgumentIndex, a_argumentIndex, a_dynamicCaller);

            state.ptrFunctionSignature = ptrOriginFunctionSignature;

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

      static ArgPlaceHolder::PlaceHolderArg* _getNextPlaceHolder(fcf::Details::IndexableFunction::CallFunctionInfo* pCall, int a_currentArgNumber){
        ArgPlaceHolder::PlaceHolderArg* result = 0;
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
            if (ca > a_currentArgNumber && ca < minValue) {
              minValue = ca;
              result = &pCall->placeHolder[phsi].placeHolders[phai];
            }
          }
        }
        return result;
      }

      void _createCurrentInputArgument(InputArgument& a_destinationInputArgument, InputArgument& a_sourceInputArgument, unsigned int a_type, void* a_ptrArg) {
        _fillCurrentInputArgument(a_destinationInputArgument, a_type, a_ptrArg);
        a_destinationInputArgument.pairCounter = a_sourceInputArgument.pairCounter;
        a_destinationInputArgument.ignoreConvertSeeker = a_sourceInputArgument.ignoreConvertSeeker;
      }

      void _fillCurrentInputArgument(InputArgument& a_inputArgument, unsigned int a_type, void* a_ptrArg){
        a_inputArgument.ptrArg                  = a_ptrArg;
        a_inputArgument.typeIndex               = a_type;
        a_inputArgument.clearTypeIndex          = typeIndexToClearTypeIndex(a_type);
        const fcf::Details::TypeInfo* typeInfo  = Details::typeStorage.get(a_inputArgument.clearTypeIndex);
        a_inputArgument.rawDataResolver         = typeInfo->rawDataResolver;
        a_inputArgument.dynamicIteratorResolver = typeInfo->dynamicIteratorResolver;
        a_inputArgument.specificators           = &typeInfo->specificators;
        a_inputArgument.invariantIndex          = false;
        a_inputArgument.ignoreConvertSeeker     = false;
        a_inputArgument.invariantRawType        = 0;
        if (a_inputArgument.rawDataResolver) {
          a_inputArgument.ptrInvariantArg = a_inputArgument.rawDataResolver(a_inputArgument.ptrArg, &a_inputArgument.invariantIndex, &a_inputArgument.invariantRawType, 0);
        } else {
          a_inputArgument.ptrInvariantArg = 0;
        }
      }

      inline void _processingNextArg(CallConversionNode* a_node, InputArgument* a_currentInputArgument, unsigned int a_inputArgumentIndex, unsigned int a_argumentIndex, bool a_dynamicCaller){
        if (a_currentInputArgument->pairCounter) {
          a_argumentIndex      += 2;
          a_inputArgumentIndex += 1;
        } else {
          a_inputArgumentIndex += 1;
          a_argumentIndex      += 1;
        }

        if (a_inputArgumentIndex >= inputArguments.size()) {
          _complete(a_node, a_dynamicCaller);
          return;
        }

        (*this)(a_node, 0, a_inputArgumentIndex, a_argumentIndex, a_dynamicCaller);
      }

      void _complete(CallConversionNode* a_node, bool a_dynamicCaller) {
        fcf::Details::IndexableFunction::CallFunctionInfo* pCall = 0;
        if (!state.dynamicCaller) {
          std::pair<fcf::Details::IndexableFunction::CallFunctions::iterator, fcf::Details::IndexableFunction::CallFunctions::iterator> range =
              state.groupIterator->second.callers.equal_range(*state.ptrFunctionSignature);
          for(; range.first != range.second; ++range.first) {
            size_t i = 0;
            for(; i < range.first->second.placeHolder.size(); ++i) {
              const unsigned int specificatorIndex = range.first->second.placeHolder[i].specificatorIndex;
              size_t j = 0;
              for(; j < state.placeHolderVec.size(); ++j) {
                if (specificatorIndex == state.placeHolderVec[j]){
                  break;
                }
              }
              if (j != state.placeHolderVec.size()) {
                break;
              }
            }
            if (i != range.first->second.placeHolder.size() || range.first->second.placeHolder.size() == 0) {
              break;
            }
          }
          if (range.first == range.second) {
            return;
          }
          pCall = &range.first->second;
          state.result->complete = true;
          state.result->caller   = (void*)range.first->second.lcaller;
          state.result->function = Details::IndexableFunction::getStorage().functions[range.first->second.index].function;
          state.result->argCount = range.first->second.callerSignature.asize;
        } else {
          Details::IndexableFunction::CallFunctionsByArgNumber::iterator treeIt = state.groupIterator->second.callersTree.find(state.ptrFunctionSignature->asize);
          if (treeIt != state.groupIterator->second.callersTree.end()) {
            ::fcf::Details::IndexableFunction::CallFunctionsMap::const_iterator it = treeIt->second.begin();
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
            }
          }
        }

        if (state.result->complete) {
          if (!state.dynamicCaller) {
            state.result->argsMap.resize(state.result->argCount);
          } else {
            state.result->argsMap.clear();
          }
          unsigned int argMapIndex = 0;
          unsigned int argMapCounter = 0;
          if (a_node) {
            unsigned int phaoffset = 0;
            CallConversionNode* begNode = a_node;
            while(begNode->prev){
              begNode = begNode->prev;
            }
            ArgPlaceHolder::PlaceHolderArg* pha = pCall ? _getNextPlaceHolder(pCall, -1) : 0;
            while(begNode){
              bool ignore = begNode->conversion.mode == CCM_NONE;
              if (pCall) {
                while (pha && pha->argument <= (begNode->conversion.index + phaoffset) ) {
                  CallConversion cc;
                  cc.mode = CCM_SKIP;
                  cc.index = pha->argument;
                  state.result->conversions.push_back(cc);
                  pha = _getNextPlaceHolder(pCall, pha->argument);
                  ++phaoffset;
                  ++argMapCounter;
                }
                if (begNode->conversion.mode == CCM_PLACE_HOLDER) {
                  std::vector<ArgPlaceHolder::SignatureData>::iterator it =
                    std::find_if(pCall->placeHolder.begin(), pCall->placeHolder.end(), [begNode](ArgPlaceHolder::SignatureData& a_itm){
                      return a_itm.specificatorIndex == begNode->conversion.specificatorIndex;
                    });
                  if (it == pCall->placeHolder.end()){
                    ignore = true;
                  } else {
                    for(auto ph : it->placeHolders) {
                      ArgPlaceHolder::PlaceHolderArgEx phe;
                      phe.argument = ph.argument;
                      phe.placeHolderArgument = ph.placeHolderArgument;
                      phe.type = pCall->callerSignature.pacodes[ph.argument];
                      begNode->conversion.placeHolders.push_back(phe);
                    }
                  }
                }
              }
              if (!ignore) {
                if (!state.dynamicCaller) {
                  for(; argMapIndex <= begNode->conversion.index;){
                    if (argMapIndex >= state.result->argsMap.size()){
                      throw std::runtime_error("Logic_error");
                    }
                    state.result->argsMap[argMapIndex] = argMapCounter;
                    ++argMapIndex;
                    ++argMapCounter;
                    if (begNode->conversion.mode == CCM_FLAT_ITERATOR) {
                      ++argMapCounter;
                    }
                  }
                }
                begNode->conversion.index += phaoffset;
                state.result->conversions.push_back(begNode->conversion);
              }
              begNode = begNode->next;
            }

            while (pha) {
              CallConversion cc;
              cc.mode = CCM_SKIP;
              cc.index = pha->argument;
              state.result->conversions.push_back(cc);
              pha = _getNextPlaceHolder(pCall, pha->argument);
              ++phaoffset;
            }
          } // if (a_node) end

          if (!state.dynamicCaller) {
            for(; argMapIndex < state.result->argsMap.size(); ++argMapIndex){
              state.result->argsMap[argMapIndex] = argMapCounter;
              ++argMapCounter;
            }
          }

        }
  
      }


      template <typename TContainer, typename TItem>
      void operator()(TContainer& a_container, size_t a_index, const TItem& a_item){
        typedef
          typename std::remove_cv<
            typename std::remove_pointer<
              typename std::remove_pointer<
                TItem
              >::type
            >::type
          >::type current_arg_type;

        InputArgument& ia = inputArguments[a_index];
        ia.ptrArg                  = state.strictSource ? (current_arg_type*) (*state.arguments)[a_index] : (current_arg_type*)0;
        ia.typeIndex               = Type<current_arg_type>().index();
        ia.clearTypeIndex          = typeIndexToClearTypeIndex(Type<current_arg_type>().index());
        ia.rawDataResolver         = Type<current_arg_type>().rawDataResolver();
        ia.dynamicIteratorResolver = Type<current_arg_type>().dynamicIteratorResolver();
        ia.specificators           = &Type<current_arg_type>().specificators();
        ia.invariantIndex          = false;
        ia.invariantRawType        = 0;
        ia.pairCounter             = 0;
        if (ia.rawDataResolver) {
          ia.ptrInvariantArg = ia.rawDataResolver(ia.ptrArg, &ia.invariantIndex, &ia.invariantRawType, 0);
        } else {
          ia.ptrInvariantArg = 0;
        }
      }
    };
    
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_SELECTOR_HANDLER_HPP___

