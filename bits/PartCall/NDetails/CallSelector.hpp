#ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_SELECTOR_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_SELECTOR_HPP___

#include "CallSelectorHandler.hpp"
#include "CallPairArgumentNode.hpp"

namespace fcf { 
  namespace NDetails {

    template <int Index, int Size, typename TPtrTuple, bool IgnoreIterator = false, unsigned int MaxCount = 0>
    struct CallSelector {
      inline void operator()(CallSelectorState& a_state, CallPairArgumentNode* a_pairNode = 0) {
        (void)a_state;
        (void)a_pairNode;
        /*
        CallSelectorHandler csh(a_state);
        csh.initialize<TPtrTuple>(a_pairNode);
        csh(0, 0, 0, 0, false);
        */
      }
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_SELECTOR_HPP___
