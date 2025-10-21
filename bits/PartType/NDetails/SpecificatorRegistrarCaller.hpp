#ifndef ___FCF__BASIS__BITS__PART_TYPE__NDETAILS__SPECIFICATOR_REGISTRAR_CALLER_HPP___
#define ___FCF__BASIS__BITS__PART_TYPE__NDETAILS__SPECIFICATOR_REGISTRAR_CALLER_HPP___

#include "SpecificatorRegistrarCallerWalker.hpp"

namespace fcf {
  namespace NDetails {

    template <typename TUnstatic, unsigned int UnstaticCounter, typename Ty>
    struct SpecificatorRegistrarCaller {
      SpecificatorRegistrarCaller(){
      }
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_TYPE__NDETAILS__SPECIFICATOR_REGISTRAR_CALLER_HPP___
