#ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_CONVERSION_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__CALL_CONVERSION_HPP___

#include "../../StaticVector.hpp"
#include "../../bits/PartCallPlaceHolder/CallPlaceHolderInfo.hpp"
#include "CallConversionMode.hpp"

namespace fcf{

  struct CallConversion {
    CallConversionMode                                mode;
    unsigned int                                      type;
    unsigned int                                      index;
    unsigned int                                      sourceIndex;
    void*                                             converter;
    unsigned int                                      specificatorIndex;
    unsigned int                                      pointerCounter;
    bool                                              invariantIteration;
    StaticVector<CallPlaceHolderArgEx, 2>             placeHolders;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_CONVERSION_HPP___
