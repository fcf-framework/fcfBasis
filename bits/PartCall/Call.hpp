#ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__CALL_HPP___

#include "CallConversion.hpp"
#include "../../PartStaticVector.hpp"

namespace fcf{

  struct Call {
    typedef StaticVector<unsigned short, 8> ArgMapType;
    bool                            complete;
    bool                            dynamicCaller;
    void*                           function;
    void*                           caller;
    void*                           rcaller;
    StaticVector<CallConversion, 8> conversions;
    StaticVector<unsigned short, 8> argsMap;
    StaticVector<unsigned short, 8> rargsMap;
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
