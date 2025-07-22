#ifndef ___FCF__BASIS__BITS__CALL__CALL_HPP___
#define ___FCF__BASIS__BITS__CALL__CALL_HPP___

#include "CallConversion.hpp"
#include "../../StaticVector.hpp"

namespace fcf {

  struct Call {
    bool                          complete;
    bool                          dynamicCaller;
    void*                         function;
    void*                         caller;
    StaticVector<CallConversion, 8>   conversions;
    std::string                   name;

    Call()
      : complete(false)
      , dynamicCaller(false)
      , function(0)
      , caller(0)
    {
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__CALL__CALL_HPP___
