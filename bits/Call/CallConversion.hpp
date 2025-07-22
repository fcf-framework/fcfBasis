#ifndef ___FCF__BASIS__BITS__CALL__CALL_CONVERSION_HPP___
#define ___FCF__BASIS__BITS__CALL__CALL_CONVERSION_HPP___

#include "CallConversionMode.hpp"

namespace fcf {

  struct CallConversion {
    CallConversionMode mode;
    unsigned int   type;
    unsigned int   index;
    void*          converter;
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__CALL__CALL_CONVERSION_HPP___
