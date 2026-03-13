#ifndef ___FCF__BASIS__BITS__PART_TYPE__NDETAILS__TYPE_REGISTRAR_HPP___
#define ___FCF__BASIS__BITS__PART_TYPE__NDETAILS__TYPE_REGISTRAR_HPP___

#include "SpecificatorRegistrarCaller.hpp"
#include "../../../bits/PartType/TypeFactory.hpp"

namespace fcf {
  namespace NDetails {

    template <typename TUnstatic, unsigned int UnstaticCounter, typename Ty>
    struct TypeRegistrar {
      typedef Ty type;
      TypeRegistrar(::fcf::TypeInfo* a_info, unsigned int /*a_index*/){
        a_info->initialize<Ty>();
      }
    };

    template <typename TUnstatic, unsigned int UnstaticCounter, typename Ty>
    struct TypeRegistrar<TUnstatic, UnstaticCounter, Ty&&> {
      typedef Ty type;
      TypeRegistrar(::fcf::TypeInfo* a_info, unsigned int /*a_index*/){
        a_info->initialize<Ty>();
      }
    };

    template <typename TUnstatic, unsigned int UnstaticCounter>
    struct TypeRegistrar<TUnstatic, UnstaticCounter, void> {
      typedef void type;
      TypeRegistrar(::fcf::TypeInfo* /*a_info*/, unsigned int /*a_index*/){
      }
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_TYPE__NDETAILS__TYPE_REGISTRAR_HPP___
