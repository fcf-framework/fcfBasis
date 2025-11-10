#ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__CALL_HPP___

#include "CallConversion.hpp"
#include "../../StaticVector.hpp"

namespace fcf{

  struct Call {
    bool                            complete;
    bool                            dynamicCaller;
    void*                           function;
    void*                           caller;
    StaticVector<CallConversion, 8> conversions;
    StaticVector<unsigned short, 8> argsMap;
    std::string                     name;
    unsigned char                   argCount;

    Call()
      : complete(false)
      , dynamicCaller(false)
      , function(0)
      , caller(0)
    {
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_HPP___
