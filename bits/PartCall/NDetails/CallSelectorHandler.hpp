#ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_SELECTOR_HANDLER_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_SELECTOR_HANDLER_HPP___

#include <climits>
#include <algorithm>
#include "../../../foreach.hpp"
#include "../../../bits/PartType/TypeIndexConverter.hpp"
#include "../../../bits/PartType/getTypeInfo.hpp"
#include "../../../bits/PartSpecificator/ContainerAccessSpecificator.hpp"
#include "CallConversionNode.hpp"
#include "CallSelectorState.hpp"

namespace fcf {
  namespace NDetails {

    struct CallSelectorHandler {

      struct InputArgument {
        unsigned int                                        typeIndex;
        unsigned int                                        clearTypeIndex;
        ResolveSpecificator::CallFunctionType               resolver;
        ResolveData                                         resolveData;
        UniversalCall                                       containerAccessResolver;
        void*                                               ptrArg;
        const std::map<unsigned int, SpecificatorInfo>*     specificators;
        const std::map<unsigned int, SpecificatorInfo>*     rawSpecificators;
        unsigned int                                        pairCounter;
        bool                                                ignoreConvertSeeker;
        bool                                                enablePtrSpecificators;
        InputArgument*                                      nextArgument;
      };

      FCF_FOREACH_METHOD_WRAPPER(ArgInitializerForeachWrapper, CallSelectorHandler, _argInit)

      template <typename TTuple>
      void initialize() {
        TTuple tuple;
        inputArguments.resize(std::tuple_size<TTuple>::value);
        foreach(tuple, ArgInitializerForeachWrapper(this));
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
              throw std::runtime_error("Overflow specificator vector size");
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
            curnode.conversion.converter = (void*)specificatorIt->second.universalCall;
            if (a_node) {
              a_node->next = &curnode;
              curnode.prev = a_node;
            }
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

        if (state.strictSource && currentInputArgument->resolveData.typeIndex && !currentInputArgument->pairCounter) {
          CallConversionNode curnode;
          curnode.prev = 0;
          curnode.next = 0;
          curnode.conversion.index = a_argumentIndex;
          curnode.conversion.sourceIndex = a_inputArgumentIndex;
          curnode.conversion.type = currentInputArgument->resolveData.typeIndex;
          curnode.conversion.mode = CCM_RESOLVE;
          curnode.conversion.converter = (void*)currentInputArgument->resolver;
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
          CallStorageSelectionFunctionsByArgNumber::iterator treeIt = state.groupIterator->second.callersTree.find(state.ptrFunctionSignature->asize);
          if (treeIt != state.groupIterator->second.callersTree.end()){
            BaseFunctionSignature shortSign = *state.ptrFunctionSignature;
            for(size_t i = a_argumentIndex + 1; i < shortSign.asize; ++i){
              shortSign.pacodes[i] = 0;
            }
            CallStorageSelectionFunctionsMap::iterator rightIt = treeIt->second.lower_bound(shortSign);
            CallStorageSelectionFunctionsMap::iterator leftIt = rightIt;
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
                curnode.conversion.sourceIndex = a_inputArgumentIndex;
                curnode.conversion.type = rtypeSimpleIndex;
                curnode.conversion.mode = CCM_CONVERT;
                curnode.conversion.converter = (void*)convertFunction;
                if (a_node){
                  a_node->next = &curnode;
                  curnode.prev = a_node;
                }
                state.ptrFunctionSignature->pacodes[a_argumentIndex] = state.ptrFunctionSignature->getSimpleCallType(rtypeIndex);

                InputArgument nextTypeInputArgument;
                _createCurrentInputArgument(nextTypeInputArgument, *currentInputArgument, rtypeSimpleIndex, 0, currentInputArgument->enablePtrSpecificators);
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
                  curnode.conversion.sourceIndex = a_inputArgumentIndex;
                  curnode.conversion.type = rtypeSimpleIndex;
                  curnode.conversion.mode = CCM_CONVERT;
                  curnode.conversion.converter = (void*)convertFunction;
                  if (a_node){
                    a_node->next = &curnode;
                    curnode.prev = a_node;
                  }
                  state.ptrFunctionSignature->pacodes[a_argumentIndex] = state.ptrFunctionSignature->getSimpleCallType(rtypeIndex);

                  InputArgument nextTypeInputArgument;
                  _createCurrentInputArgument(nextTypeInputArgument, *currentInputArgument, rtypeSimpleIndex, 0, currentInputArgument->enablePtrSpecificators);
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

        if (!state.strictSource && currentInputArgument->resolveData.invariant && !currentInputArgument->pairCounter) {
          CallConversionNode curnode;
          curnode.prev = 0;
          curnode.next = 0;
          curnode.conversion.index = a_argumentIndex;
          curnode.conversion.sourceIndex = a_inputArgumentIndex;
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

        if (currentInputArgument->containerAccessResolver && !currentInputArgument->pairCounter) {
          Variant viterator = currentInputArgument->containerAccessResolver(0, 0, 0);
          DynamicContainerAccessBase* iterator = (DynamicContainerAccessBase*)viterator.ptr();
          if (iterator) {
            if (iterator->isFlatContainer()) {
              BaseFunctionSignature* ptrOriginFunctionSignature = state.ptrFunctionSignature;
              BaseFunctionSignature ofs = *state.ptrFunctionSignature;
              BaseFunctionSignature fs = BaseFunctionSignature(state.ptrFunctionSignature->asize + 1);
              fs.rcode = ofs.rcode;
              std::copy(&state.ptrFunctionSignature->pacodes[0],
                        &state.ptrFunctionSignature->pacodes[a_argumentIndex],
                        &fs.pacodes[0]
                        );

              unsigned int ptrTypeIndex = iterator->getValueTypeIndex();
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
              curnode.conversion.index        = a_argumentIndex;
              curnode.conversion.sourceIndex  = a_inputArgumentIndex;
              curnode.conversion.type         = ptrTypeIndex;
              curnode.conversion.mode         = CCM_FLAT_ITERATOR;
              curnode.conversion.converter    = (void*)currentInputArgument->containerAccessResolver;
              if (a_node) {
                a_node->next = &curnode;
                curnode.prev = a_node;
              }

              _fillCurrentInputArgument(*currentInputArgument, ptrTypeIndex, 0, true);
              currentInputArgument->pairCounter = 1;

              InputArgument nextArgument(*currentInputArgument);
              currentInputArgument->nextArgument = &nextArgument;

              state.ptrFunctionSignature = &fs;

              (*this)(&curnode, currentInputArgument, a_inputArgumentIndex, a_argumentIndex, a_dynamicCaller);

              state.ptrFunctionSignature = ptrOriginFunctionSignature;

              if (state.result->complete) {
                return;
              }
            }
          }
        }

        if (a_node) {
          a_node->next = 0;
        }
        state.placeHolderVec.resize(originPlaceHolderVecSize);
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
      }

      void _fillCurrentInputArgument(InputArgument& a_inputArgument, unsigned int a_type, void* a_ptrArg, bool a_enablePtrSpecificators){
        a_inputArgument.ptrArg                  = a_ptrArg;
        a_inputArgument.typeIndex               = a_type;
        //a_inputArgument.clearTypeIndex          = TypeIndexConverter<>::getRawIndex(a_type);
        a_inputArgument.clearTypeIndex          = TypeIndexConverter<>::getDataIndex(a_type);
        const fcf::TypeInfo* typeInfo           = typeStorage.get(a_inputArgument.clearTypeIndex);
        a_inputArgument.resolver                = typeInfo->resolver;
        a_inputArgument.containerAccessResolver = typeInfo->getSpecificator<ContainerAccessSpecificator>();
        a_inputArgument.specificators           = &typeInfo->specificators;
        a_inputArgument.ignoreConvertSeeker     = false;
        a_inputArgument.enablePtrSpecificators  = a_enablePtrSpecificators;
        a_inputArgument.nextArgument            = 0;

        if (a_enablePtrSpecificators && TypeIndexConverter<>::isPointer(a_type)) {
          unsigned int rawTypeIndex     =  TypeIndexConverter<>::getRawIndex(a_type);
          const fcf::TypeInfo* typeInfo = getTypeInfo(rawTypeIndex);
          a_inputArgument.rawSpecificators = &typeInfo->specificators;
        } else {
          a_inputArgument.rawSpecificators = 0;
        }

        if (a_inputArgument.resolver) {
          a_inputArgument.resolveData = a_inputArgument.resolver(a_inputArgument.ptrArg);
        } else {
          a_inputArgument.resolveData.data      = 0;
          a_inputArgument.resolveData.typeIndex = 0;
          a_inputArgument.resolveData.invariant = false;
        }
      }

      inline void _processingNextArg(CallConversionNode* a_node, InputArgument* a_currentInputArgument, unsigned int a_inputArgumentIndex, unsigned int a_argumentIndex, bool a_dynamicCaller){
        if (a_currentInputArgument->pairCounter && a_currentInputArgument->nextArgument) {
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
        CallStorageSelectionFunctionInfo* pCall = 0;
        if (!state.dynamicCaller) {
          std::pair<CallStorageSelectionFunctions::iterator, CallStorageSelectionFunctions::iterator> range =
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
          state.result->function = getCallStorage().functions[range.first->second.index].function;
          state.result->argCount = range.first->second.callerSignature.asize;
        } else {
          CallStorageSelectionFunctionsByArgNumber::iterator treeIt = state.groupIterator->second.callersTree.find(state.ptrFunctionSignature->asize);
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
            CallConversionNode* begNode = a_node;
            while(begNode->prev){
              begNode = begNode->prev;
            }

            unsigned int phmapIndex = 0;
            unsigned int phmapOffset = 0;
            unsigned int phmapArgCounter = 0;
                                           // Index as called function argument
                                           // Value as input argument
            StaticVector<unsigned int, 16> phmap(state.result->argCount, 0);
            for(size_t i = 0; i < pCall->placeHolder.size(); ++i) {
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
                  throw std::runtime_error("Invalid logic into CallSelectorHandler (complete step filling flags)");
                }
                if (phmap[phmapIndex] == UINT_MAX){               // if PLACE HOLDER insertion
                  ++phmapOffset;
                  ++node->conversion.index;
                  ++phmapIndex;
                } else if (phmap[phmapIndex] == (UINT_MAX - 1)) { // if CCM_FLAT_ITERATOR insertion
                  ++phmapIndex;
                } else {
                  if (phmapIndex != node->conversion.index) {     // if insertion without converter
                    CallConversion conversion;
                    conversion.index        = phmapIndex;
                    conversion.sourceIndex  = phmapArgCounter;
                    conversion.type         = 0;
                    conversion.mode         = CCM_SKIP;
                    conversion.converter    = 0;
                    state.result->conversions.push_back(conversion);
                  }
                  phmap[phmapIndex] = phmapArgCounter;
                  ++phmapArgCounter;
                  ++phmapIndex;
                }
              }

              if (node->conversion.mode == CCM_FLAT_ITERATOR) {
                if (phmap[phmapIndex] == UINT_MAX){
                  throw std::runtime_error("Invalid logic into CallSelectorHandler (Placeholder overflow (pos1))");
                }
                if (phmapIndex >= phmap.size()){
                  throw std::runtime_error("Invalid logic into CallSelectorHandler (Placeholder overflow (pos2))");
                }
                phmap[phmapIndex] = (UINT_MAX - 1);
              } else if (node->conversion.mode == CCM_PLACE_HOLDER) {
                std::vector<::fcf::CallPlaceHolderInfo>::iterator it =
                  std::find_if(pCall->placeHolder.begin(), pCall->placeHolder.end(), [node](::fcf::CallPlaceHolderInfo& a_itm){
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
                  throw std::runtime_error("Invalid logic into CallSelectorHandler (argument map overflow)");
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

      protected:
        template <typename TContainer, typename TItem>
        void _argInit(TContainer& /*a_container*/, size_t a_index, const TItem& /*a_item*/){
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
          //ia.clearTypeIndex          = TypeIndexConverter<>::getRawIndex(Type<current_arg_type>().index());
          ia.clearTypeIndex          = TypeIndexConverter<>::getDataIndex(Type<current_arg_type>().index());
          ia.resolver                = Type<current_arg_type>().getTypeInfo()->resolver;
          ia.containerAccessResolver = Type<current_arg_type>().getTypeInfo()->template getSpecificator<ContainerAccessSpecificator>();
          ia.specificators           = &Type<current_arg_type>().specificators();
          ia.pairCounter             = 0;
          ia.enablePtrSpecificators  = false;
          ia.rawSpecificators        = 0;
          ia.nextArgument            = 0;
          if (ia.resolver) {
            ia.resolveData = ia.resolver(ia.ptrArg);
          } else {
            ia.resolveData.data      = 0;
            ia.resolveData.typeIndex = 0;
            ia.resolveData.invariant = false;
          }
        }
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_SELECTOR_HANDLER_HPP___
