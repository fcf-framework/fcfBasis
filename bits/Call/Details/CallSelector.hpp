#ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_SELECTOR_HPP___
#define ___FCF__BASIS__BITS__CALL__DETAILS__CALL_SELECTOR_HPP___

#include "../../../Template/TupleReplace.hpp"
#include "../../../Template/TupleInsert.hpp"
#include "../../../bits/Specificator/DynamicIteratorInfo.hpp"
#include "CallConversionNode.hpp"
#include "CallSelectorState.hpp"

namespace fcf {
  namespace Details {

    template <int Index, int Size, typename TPtrTuple>
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
          CallSelector<Index, Size, TPtrTuple>()(&curnode, a_iasd, a_ignoreOrigin, a_dynamicCaller);
          a_iasd.functionSignature.pacodes[Index] = sourceTypeIndex;
          if (a_iasd.result->complete) {
            return;
          }
          if (a_node) {
            a_node->next = 0;
          }
        }

        CallSelector<Index + 1, Size, TPtrTuple>()(a_node, a_iasd, a_ignoreOrigin, a_dynamicCaller);
        if (a_iasd.result->complete) {
          return;
        }

        if (a_iasd.strictSource) {
          Details::IndexableFunction::CallersTree::iterator treeIt = a_iasd.groupIterator->second.callersTree.find(a_iasd.functionSignature.asize);
          if (treeIt != a_iasd.groupIterator->second.callersTree.end()){
            const Details::TypeInfo* ti =  Details::typeStorage.get(sourceSimpleTypeIndex);
            BaseFunctionSignature shortSign = a_iasd.functionSignature;
            for(size_t i = Index+1; i < shortSign.asize; ++i){
              shortSign.pacodes[i] = 0;
            }
            ::fcf::Details::IndexableFunction::CallersMap::iterator rightIt = treeIt->second.lower_bound(shortSign);
            ::fcf::Details::IndexableFunction::CallersMap::iterator leftIt = rightIt;
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
                CallSelector<Index + 1, Size, TPtrTuple>()(&curnode, a_iasd, a_ignoreOrigin, a_dynamicCaller);
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
                  CallSelector<Index + 1, Size, TPtrTuple>()(&curnode, a_iasd, a_ignoreOrigin, a_dynamicCaller);
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

          CallSelector<Index + 1, Size, TPtrTuple>()(&curnode, a_iasd, a_ignoreOrigin, true);

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
                 = { a_iasd.name, a_iasd.result, a_iasd.groupIterator, fs, &arguments, a_iasd.strictSource};
            CallSelector<Index+2, Size+1, pair_tuple_type>()(&curnode, repiasd, a_ignoreOrigin, a_dynamicCaller);
          }
        }
      } // method end
    };

    template <int Size, typename TPtrTuple>
    struct CallSelector<Size, Size, TPtrTuple >{
      inline void operator()(CallConversionNode* a_node, CallSelectorState& a_iasd, bool a_ignoreOrigin, bool a_dynamicCaller){
        if (a_ignoreOrigin && !a_node) {
          return;
        }

        if (!a_iasd.dynamicCaller) {
          fcf::Details::IndexableFunction::Callers::iterator callerInfoIt =
            a_iasd.groupIterator->second.callers.find(a_iasd.functionSignature);
          if (callerInfoIt == a_iasd.groupIterator->second.callers.end()) {
            return;
          }

          a_iasd.result->complete = true;
          a_iasd.result->caller   = callerInfoIt->second.caller;
          a_iasd.result->function = Details::IndexableFunction::getStorage().functions[callerInfoIt->second.index].function;
        } else {
          Details::IndexableFunction::CallersTree::iterator treeIt = a_iasd.groupIterator->second.callersTree.find(a_iasd.functionSignature.asize);
          if (treeIt != a_iasd.groupIterator->second.callersTree.end()) {
            ::fcf::Details::IndexableFunction::CallersMap::const_iterator it = treeIt->second.begin();
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
            CallConversionNode* begNode = a_node;
            while(begNode->prev){
              begNode = begNode->prev;
            }
            while(begNode){
              if (begNode->conversion.mode != CCM_NONE) {
                a_iasd.result->conversions.push_back(begNode->conversion);
              }
              begNode = begNode->next;
            }
          }
        }

      }
    };

  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_SELECTOR_HPP___

