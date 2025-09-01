#ifndef ___FCF__BASIS__BITS__CALL__CALL_CONVERSION_HPP___
#define ___FCF__BASIS__BITS__CALL__CALL_CONVERSION_HPP___

#include "../../StaticVector.hpp"
#include "../ArgPlaceHolder/SignatureData.hpp"
#include "CallConversionMode.hpp"

namespace fcf {

  struct CallConversion {
    CallConversionMode                                mode;
    unsigned int                                      type;
    unsigned int                                      index;
    void*                                             converter;
    unsigned int                                      converterArgCount;
    unsigned int                                      specificatorIndex;
    unsigned int                                      pointerCounter;
    StaticVector<ArgPlaceHolder::PlaceHolderArgEx, 2> placeHolders;
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__CALL__CALL_CONVERSION_HPP___
