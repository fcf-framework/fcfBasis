#ifndef ___FCF__BASIS__BITS__PART_TYPE__NDETAILS__TYPE_REGISTRAR_HPP___
#define ___FCF__BASIS__BITS__PART_TYPE__NDETAILS__TYPE_REGISTRAR_HPP___

#include "SpecificatorRegistrarCaller.hpp"

namespace fcf {
  namespace NDetails {

    template <typename TUnstatic, unsigned int UnstaticCounter, typename Ty>
    struct TypeRegistrar {
      typedef Ty type;
      TypeRegistrar(unsigned int a_index){
        ::fcf::Details::Basis::Variant::NobodyWrapperRegistrator<type> registrer(a_index);
      }
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_TYPE__NDETAILS__TYPE_REGISTRAR_HPP___
