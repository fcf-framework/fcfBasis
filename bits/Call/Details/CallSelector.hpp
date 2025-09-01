#ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_SELECTOR_HPP___
#define ___FCF__BASIS__BITS__CALL__DETAILS__CALL_SELECTOR_HPP___

#include <algorithm>
#include <climits>
#include "../../../Template/TupleReplace.hpp"
#include "../../../Template/TupleInsert.hpp"
#include "../../../bits/Specificator/DynamicIteratorInfo.hpp"
#include "CallConversionNode.hpp"
#include "CallSelectorState.hpp"

namespace fcf {
  namespace Details {

    template <int Index, int Size, typename TPtrTuple, bool IgnoreIterator = false, unsigned int MaxCount = 0>
    struct CallSelector {
      inline void operator()(CallConversionNode* a_node, CallSelectorState& a_iasd, bool a_ignoreOrigin, bool a_dynamicCaller){
        unsigned int sourceTypeIndex       = a_iasd.functionSignature.pacodes[Index];
        unsigned int sourceSimpleTypeIndex = BaseFunctionSignature::getSimpleType(sourceTypeIndex);

        typedef
          typename std::remove_cv<
            typename std::remove_pointer<
              typename std::tuple_element<Index, TPtrTuple>::type
            >::type
          >::type current_arg_type;
        unsigned int originSourceSimpleTypeIndex = Type<current_arg_type>().index();

        bool invariantRawType = false;
        RawDataSpecificator::function_type rawDataResolver = 0;
        DynamicIteratorSpecificator::function_type dynamicIteratorResolver = 0;
        unsigned int invariantIndex = 0;
        void* aptr = a_iasd.strictSource ? (void*) (*a_iasd.arguments)[Index] : (void*)0;
        const std::map<unsigned int, SpecificatorTypeInfo>* specificators;
        if (originSourceSimpleTypeIndex == sourceSimpleTypeIndex) {
          rawDataResolver = Type<current_arg_type>().rawDataResolver();
          if (rawDataResolver) {
            rawDataResolver((current_arg_type*)aptr, &invariantIndex, &invariantRawType, 0);
          }
          dynamicIteratorResolver = Type<current_arg_type>().dynamicIteratorResolver();
        } else {
          const fcf::Details::TypeInfo* ti = Details::typeStorage.get(sourceSimpleTypeIndex);
          if (ti) {
            if (ti->rawDataResolver) {
              rawDataResolver = ti->rawDataResolver;
              rawDataResolver(aptr, &invariantIndex, &invariantRawType, 0);
            }
            dynamicIteratorResolver = ti->dynamicIteratorResolver;
          }
        }
        unsigned int clearTypeIndex = sourceSimpleTypeIndex & ~((8 << (24 + 1)) | (16 << (24 + 1)));
        const fcf::Details::TypeInfo* cti = Details::typeStorage.get(clearTypeIndex);
        if (cti) {
          specificators = &cti->specificators;
        }

        const size_t curSpecNodesMaxSize = 8;
        size_t curSpecNodesSize = 0;
        size_t placeHolderVecSize = a_iasd.placeHolderVec.size();
        CallConversionNode curSpecNodes[curSpecNodesMaxSize];
        if (Index < a_iasd.placeHolderSpecificators->size()) {
          for(size_t i = 0; i < (*a_iasd.placeHolderSpecificators)[Index].size(); ++i){
            unsigned int specificatorTypeIndex = (*a_iasd.placeHolderSpecificators)[Index][i];
            unsigned int sourceSimpleClearTypeIndex = sourceSimpleTypeIndex & ~((8 << (24 + 1)) | (16 << (24 + 1)));
            const fcf::Details::TypeInfo* ti = Details::typeStorage.get(sourceSimpleClearTypeIndex);
            std::map<unsigned int, SpecificatorTypeInfo>::const_iterator specificatorIt = specificators->find(specificatorTypeIndex);
            if (specificatorIt == specificators->cend()) {
              continue;
            }
            if (curSpecNodesSize == curSpecNodesMaxSize){
              throw std::runtime_error("Overflow specificator vector size");
            }
            CallConversionNode& curnode = curSpecNodes[curSpecNodesSize];
            ++curSpecNodesSize;
            curnode.prev = 0;
            curnode.next = 0;
            curnode.conversion.index = Index;
            curnode.conversion.specificatorIndex = specificatorTypeIndex;
            curnode.conversion.pointerCounter    = sourceSimpleTypeIndex & (8 << (24 + 1))  ? 1 :
                                                   sourceSimpleTypeIndex & (16 << (24 + 1)) ? 2 :
                                                                                              0;
            std::cout << "curnode.conversion.pointerCounter: " << curnode.conversion.pointerCounter << "; specificatorTypeIndex: " << std::hex << specificatorTypeIndex << std::dec<< std::endl;
            curnode.conversion.type = sourceSimpleClearTypeIndex;
            curnode.conversion.mode = CCM_PLACE_HOLDER;
            curnode.conversion.converter = (void*)specificatorIt->second.resolve;
            curnode.conversion.converterArgCount = specificatorIt->second.argc;
            if (a_node) {
              a_node->next = &curnode;
              curnode.prev = a_node;
            }
            a_iasd.placeHolderVec.push_back(specificatorTypeIndex);
          }
        }

        if (a_iasd.strictSource && invariantIndex) {
          CallConversionNode curnode;
          curnode.prev = 0;
          curnode.next = 0;
          curnode.conversion.index = Index;
          curnode.conversion.type = invariantIndex;
          curnode.conversion.mode = CCM_RESOLVE;
          curnode.conversion.converter = (void*)rawDataResolver;
          if (a_node){
            a_node->next = &curnode;
            curnode.prev = a_node;
          }
          a_iasd.functionSignature.pacodes[Index] = a_iasd.functionSignature.getSimpleCallType(invariantIndex);
          CallSelector<Index, Size, TPtrTuple, false, MaxCount + 1>()(&curnode, a_iasd, a_ignoreOrigin, a_dynamicCaller);
          a_iasd.functionSignature.pacodes[Index] = sourceTypeIndex;
          if (a_iasd.result->complete) {
            return;
          }
          if (a_node) {
            a_node->next = 0;
          }
        }

        CallSelector<Index + 1, Size, TPtrTuple, false, MaxCount + 1>()(a_node, a_iasd, a_ignoreOrigin, a_dynamicCaller);
        if (a_iasd.result->complete) {
          return;
        }

        if (a_iasd.strictSource) {
          Details::IndexableFunction::CallFunctionsByArgNumber::iterator treeIt = a_iasd.groupIterator->second.callersTree.find(a_iasd.functionSignature.asize);
          if (treeIt != a_iasd.groupIterator->second.callersTree.end()){
            const Details::TypeInfo* ti =  Details::typeStorage.get(sourceSimpleTypeIndex);
            BaseFunctionSignature shortSign = a_iasd.functionSignature;
            for(size_t i = Index+1; i < shortSign.asize; ++i){
              shortSign.pacodes[i] = 0;
            }
            ::fcf::Details::IndexableFunction::CallFunctionsMap::iterator rightIt = treeIt->second.lower_bound(shortSign);
            ::fcf::Details::IndexableFunction::CallFunctionsMap::iterator leftIt = rightIt;
            if (rightIt != treeIt->second.end()) {
              if (leftIt != treeIt->second.end()) {
                --leftIt;
              }

              // right side
              unsigned int rtypeIndex = rightIt->first.pacodes[Index];
              unsigned int rtypeSimpleIndex = BaseFunctionSignature::getSimpleType(rtypeIndex);
              ConvertFunction convertFunction = getConvertFunction(sourceSimpleTypeIndex, rtypeSimpleIndex, 0);
              if (convertFunction){
                CallConversionNode curnode;
                curnode.prev = 0;
                curnode.next = 0;
                curnode.conversion.index = Index;
                curnode.conversion.type = rtypeSimpleIndex;
                curnode.conversion.mode = CCM_CONVERT;
                curnode.conversion.converter = (void*)convertFunction;
                if (a_node){
                  a_node->next = &curnode;
                  curnode.prev = a_node;
                }
                a_iasd.functionSignature.pacodes[Index] = a_iasd.functionSignature.getSimpleCallType(rtypeIndex);
                CallSelector<Index + 1, Size, TPtrTuple, false, MaxCount + 1>()(&curnode, a_iasd, a_ignoreOrigin, a_dynamicCaller);
                a_iasd.functionSignature.pacodes[Index] = sourceTypeIndex;
                if (a_iasd.result->complete) {
                  return;
                }
                if (a_node) {
                  a_node->next = 0;
                }
              }

              // left side
              if (leftIt != treeIt->second.end()) {
                unsigned int rtypeIndex = leftIt->first.pacodes[Index];
                unsigned int rtypeSimpleIndex = BaseFunctionSignature::getSimpleType(rtypeIndex);
                ConvertFunction convertFunction = getConvertFunction(sourceSimpleTypeIndex, rtypeSimpleIndex, 0);
                if (convertFunction){
                  CallConversionNode curnode;
                  curnode.prev = 0;
                  curnode.next = 0;
                  curnode.conversion.index = Index;
                  curnode.conversion.type = rtypeSimpleIndex;
                  curnode.conversion.mode = CCM_CONVERT;
                  curnode.conversion.converter = (void*)convertFunction;
                  if (a_node){
                    a_node->next = &curnode;
                    curnode.prev = a_node;
                  }
                  a_iasd.functionSignature.pacodes[Index] = a_iasd.functionSignature.getSimpleCallType(rtypeIndex);
                  CallSelector<Index + 1, Size, TPtrTuple, false, MaxCount + 1>()(&curnode, a_iasd, a_ignoreOrigin, a_dynamicCaller);
                  a_iasd.functionSignature.pacodes[Index] = sourceTypeIndex;
                  if (a_iasd.result->complete) {
                    return;
                  }
                  if (a_node) {
                    a_node->next = 0;
                  }
                }
              }
            } // if (leftIt != treeIt->second.end()) end
          } // if (treeIt != a_iasd.groupIterator->second.callersTree.end()) end
        } // if (a_iasd.strictSource) end

        if (!a_iasd.strictSource && invariantRawType) {
          CallConversionNode curnode;
          curnode.prev = 0;
          curnode.next = 0;
          curnode.conversion.index = Index;
          curnode.conversion.type = 0;
          curnode.conversion.mode = CCM_DYNAMIC_RESOLVE;
          curnode.conversion.converter = (void*)0;
          if (a_node){
            a_node->next = &curnode;
            curnode.prev = a_node;
          }

          unsigned int origTypeIndex = a_iasd.functionSignature.pacodes[Index];
          a_iasd.functionSignature.pacodes[Index] = 0;

          bool origDynamicCaller = a_iasd.dynamicCaller;
          a_iasd.dynamicCaller = true;

          CallSelector<Index + 1, Size, TPtrTuple, false, MaxCount + 1>()(&curnode, a_iasd, a_ignoreOrigin, true);

          a_iasd.dynamicCaller = origDynamicCaller;
          a_iasd.functionSignature.pacodes[Index] = origTypeIndex;

          if (a_iasd.result->complete) {
            return;
          }
          if (a_node) {
            a_node->next = 0;
          }
        }

        if (dynamicIteratorResolver) {
          DynamicIteratorInfo dii;
          dii.flags = DIF_INFO | DIF_GET_FLAT | DIF_GET_TYPE;
          dynamicIteratorResolver(0, &dii);
          if (dii.flat) {
            typedef Nop* pnop_type;
            typedef typename Template::TupleReplace<TPtrTuple, pnop_type, Index>::type rep_tuple_type;
            typedef typename Template::TupleInsert<rep_tuple_type, pnop_type, Index>::type pair_tuple_type;

            BaseFunctionSignature ofs = a_iasd.functionSignature;
            BaseFunctionSignature fs = BaseFunctionSignature(a_iasd.functionSignature.asize + 1);
            fs.rcode = ofs.rcode;
            std::copy(&a_iasd.functionSignature.pacodes[0],
                      &a_iasd.functionSignature.pacodes[Index],
                      &fs.pacodes[0]
                      );

            unsigned int ptrTypeIndex = dii.type;
            if (ptrTypeIndex & (8 << (24 + 1)) ) {
              ptrTypeIndex |= (16 << (24 + 1));
            } else {
              ptrTypeIndex |= (8 << (24 + 1));
            }
            fs.pacodes[Index] = a_iasd.functionSignature.getSimpleCallType(ptrTypeIndex);
            fs.pacodes[Index+1] = a_iasd.functionSignature.getSimpleCallType(ptrTypeIndex);

            std::copy(&a_iasd.functionSignature.pacodes[Index+1],
                      &a_iasd.functionSignature.pacodes[a_iasd.functionSignature.asize],
                      &fs.pacodes[Index+2]
                      );

            CallConversionNode curnode;
            curnode.prev = 0;
            curnode.next = 0;
            curnode.conversion.index     = Index;
            curnode.conversion.type      = ptrTypeIndex;
            curnode.conversion.mode      = CCM_FLAT_ITERATOR;
            curnode.conversion.converter = (void*)dynamicIteratorResolver;
            if (a_node){
              a_node->next = &curnode;
              curnode.prev = a_node;
            }

            StaticVector<void*, 8> arguments((size_t)Size+1);
            if (a_iasd.strictSource) {
              std::copy(&(*a_iasd.arguments)[0], &(*a_iasd.arguments)[Index], &arguments[0]);
              arguments[Index] = 0;
              arguments[Index+1] = 0;
              std::copy(&(*a_iasd.arguments)[Index+1], &(*a_iasd.arguments)[Size], &arguments[Index+2]);
            } else {
              std::fill(&arguments[0], &arguments[Size+1], (void*)0);
            }
            CallSelectorState repiasd
                 = { a_iasd.name, a_iasd.result, a_iasd.groupIterator, fs, &arguments, a_iasd.placeHolderVec, a_iasd.placeHolderSpecificators, a_iasd.strictSource};
            CallSelector<Index, Size+1, pair_tuple_type, false, MaxCount + 1>()(&curnode, repiasd, a_ignoreOrigin, a_dynamicCaller);
          }
        }

        if (a_node) {
          a_node->next = 0;
        }
        a_iasd.placeHolderVec.resize(placeHolderVecSize);

      } // method end
    };


    template <int Size, typename TPtrTuple, bool IgnoreIterator>
    struct CallSelector<Size, Size, TPtrTuple, IgnoreIterator, 10>{
      inline void operator()(CallConversionNode* a_node, CallSelectorState& a_iasd, bool a_ignoreOrigin, bool a_dynamicCaller){
      }

    };

    template <int Index, int Size, typename TPtrTuple, bool IgnoreIterator>
    struct CallSelector<Index, Size, TPtrTuple, IgnoreIterator, 10>{
      inline void operator()(CallConversionNode* a_node, CallSelectorState& a_iasd, bool a_ignoreOrigin, bool a_dynamicCaller){
      }
    };

    template <int Size, typename TPtrTuple, bool IgnoreIterator, unsigned int MaxCount>
    struct CallSelector<Size, Size, TPtrTuple, IgnoreIterator, MaxCount>{
        inline void operator()(CallConversionNode* a_node, CallSelectorState& a_iasd, bool a_ignoreOrigin, bool a_dynamicCaller){
          if (a_ignoreOrigin && !a_node) {
            return;
          }

          fcf::Details::IndexableFunction::CallFunctionInfo* pCall = 0;
          if (!a_iasd.dynamicCaller) {
            std::pair<fcf::Details::IndexableFunction::CallFunctions::iterator, fcf::Details::IndexableFunction::CallFunctions::iterator> range =
              a_iasd.groupIterator->second.callers.equal_range(a_iasd.functionSignature);
          for(; range.first != range.second; ++range.first) {
            size_t i = 0;
            for(; i < range.first->second.placeHolder.size(); ++i) {
              const unsigned int specificatorIndex = range.first->second.placeHolder[i].specificatorIndex;
              size_t j = 0;
              for(; j < a_iasd.placeHolderVec.size(); ++j) {
                if (specificatorIndex == a_iasd.placeHolderVec[j]){
                  break;
                }
              }
              if (j != a_iasd.placeHolderVec.size()) {
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
          a_iasd.result->complete = true;
          a_iasd.result->caller   = range.first->second.caller;
          a_iasd.result->function = Details::IndexableFunction::getStorage().functions[range.first->second.index].function;
          a_iasd.result->argCount = range.first->second.callerSignature.asize;
        } else {
          Details::IndexableFunction::CallFunctionsByArgNumber::iterator treeIt = a_iasd.groupIterator->second.callersTree.find(a_iasd.functionSignature.asize);
          if (treeIt != a_iasd.groupIterator->second.callersTree.end()) {
            ::fcf::Details::IndexableFunction::CallFunctionsMap::const_iterator it = treeIt->second.begin();
            for(; it != treeIt->second.end(); ++it) {
              unsigned int argIndex = 0;
              for(; argIndex < a_iasd.functionSignature.asize; ++argIndex){
                if (
                     a_iasd.functionSignature.pacodes[argIndex] != 0 &&
                     a_iasd.functionSignature.pacodes[argIndex] != it->first.pacodes[argIndex]
                   ){
                  break;
                }
              }
              if (argIndex == a_iasd.functionSignature.asize) {
                break;
              }
            }
            if (it != treeIt->second.end()){
              a_iasd.result->complete = true;
              a_iasd.result->dynamicCaller = true;
              a_iasd.result->name = a_iasd.name;
            }
          }
        }

        if (a_iasd.result->complete) {
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
                  a_iasd.result->conversions.push_back(cc);
                  pha = _getNextPlaceHolder(pCall, pha->argument);
                  ++phaoffset;
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
                begNode->conversion.index += phaoffset;
                a_iasd.result->conversions.push_back(begNode->conversion);
              }
              begNode = begNode->next;
            }

            while (pha) {
              CallConversion cc;
              cc.mode = CCM_SKIP;
              cc.index = pha->argument;
              a_iasd.result->conversions.push_back(cc);
              pha = _getNextPlaceHolder(pCall, pha->argument);
              ++phaoffset;
            }
          }
        }

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
    };


  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_SELECTOR_HPP___

