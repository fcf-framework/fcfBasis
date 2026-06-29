#ifndef _FCF_BASIS__BITS__PART_CALL__CALL_CONVERSION_HPP___
#define _FCF_BASIS__BITS__PART_CALL__CALL_CONVERSION_HPP___

#include "../../PartStaticVector.hpp"
#include "../../bits/PartCallPlaceHolder/CallPlaceHolderInfo.hpp"
#include "../../bits/PartType/TypeIndex.hpp"
#include "CallConversionMode.hpp"

namespace fcf{

  struct CallConversion {
    CallConversionMode                                mode;
    TypeIndex                                         type;
    unsigned int                                      index;
    unsigned int                                      sourceIndex;
    void*                                             converter;
    void*                                             values;
    TypeIndex                                         specifierIndex;
    unsigned int                                      pointerCounter;
    bool                                              invariantIteration;
    StaticVector<CallPlaceHolderArgEx, 2>             placeHolders;
  };

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_CALL__CALL_CONVERSION_HPP___
