#ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_CONVERSION_NODE_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_CONVERSION_NODE_HPP___

#include "../CallConversion.hpp"

namespace fcf{
  namespace NDetails {

    struct CallConversionNode {
      CallConversionNode* prev;
      CallConversionNode* next;
      CallConversion  conversion;
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_CONVERSION_NODE_HPP___
