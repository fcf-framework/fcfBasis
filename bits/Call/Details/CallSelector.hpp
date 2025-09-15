#ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_SELECTOR_HPP___
#define ___FCF__BASIS__BITS__CALL__DETAILS__CALL_SELECTOR_HPP___

#include "CallSelectorHandler.hpp"

namespace fcf {
  namespace Details {
    template <int Index, int Size, typename TPtrTuple, bool IgnoreIterator = false, unsigned int MaxCount = 0>
    struct CallSelector {
      inline void operator()(CallSelectorState& a_state) {
        CallSelectorHandler csh(a_state);
        csh.initialize<TPtrTuple>();
        csh(0, 0, 0, 0, false);
      }
    };

  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_SELECTOR_HPP___

