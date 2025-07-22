#ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_SELECTOR_STATE_HPP___
#define ___FCF__BASIS__BITS__CALL__DETAILS__CALL_SELECTOR_STATE_HPP___

#include "../../../Details/IndexableFunction/Storage.hpp"
#include "../../../StaticVector.hpp"
#include "../Call.hpp"

namespace fcf {
  namespace Details {

    struct CallSelectorState {
      const char*                                       name;
      Call*                                             result;
      fcf::Details::IndexableFunction::Groups::iterator groupIterator;
      BaseFunctionSignature&                            functionSignature;
      StaticVector<void*, 8>*                           arguments;
      bool                                              strictSource;
      bool                                              dynamicCaller;
    };

  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_SELECTOR_STATE_HPP___
