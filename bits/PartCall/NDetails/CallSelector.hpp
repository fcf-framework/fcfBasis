#ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_SELECTOR_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_SELECTOR_HPP___

#include "CallSelectorHandler.hpp"

namespace fcf::NDetails {

  template <int Index, int Size, typename TPtrTuple, bool IgnoreIterator = false, unsigned int MaxCount = 0>
  struct CallSelector {
    inline void operator()(CallSelectorState& a_state) {
      CallSelectorHandler csh(a_state);
      csh.initialize<TPtrTuple>();
      csh(0, 0, 0, 0, false);
    }
  };

} // fcf::NDetails namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_SELECTOR_HPP___
