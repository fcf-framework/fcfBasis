#ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_CONVERSION_NODE_HPP___
#define ___FCF__BASIS__BITS__CALL__DETAILS__CALL_CONVERSION_NODE_HPP___

#include "../CallConversion.hpp"

namespace fcf {
  namespace Details {

    struct CallConversionNode {
      CallConversionNode* prev;
      CallConversionNode* next;
      CallConversion  conversion;
    };

  } // Details namespace
} // fcf namespace
#endif // #ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_CONVERSION_NODE_HPP___
