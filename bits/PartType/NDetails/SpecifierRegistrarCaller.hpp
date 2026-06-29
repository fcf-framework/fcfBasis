#ifndef _FCF_BASIS__BITS__PART_TYPE__NDETAILS__SPECIFIER_REGISTRAR_CALLER_HPP___
#define _FCF_BASIS__BITS__PART_TYPE__NDETAILS__SPECIFIER_REGISTRAR_CALLER_HPP___

#include "SpecifierRegistrarCallerWalker.hpp"

namespace fcf {
  namespace NDetails {

    template <typename TUnstatic, unsigned int UnstaticCounter, typename Ty>
    struct SpecifierRegistrarCaller {
      SpecifierRegistrarCaller(){
      }
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_TYPE__NDETAILS__SPECIFIER_REGISTRAR_CALLER_HPP___
