#ifndef _FCF_BASIS__BITS__PART_TYPE__NDETAILS__TYPE_REGISTRAR_HPP___
#define _FCF_BASIS__BITS__PART_TYPE__NDETAILS__TYPE_REGISTRAR_HPP___

#include "SpecifierRegistrarCaller.hpp"
#include "../../../bits/PartType/TypeFactory.hpp"

namespace fcf {
  namespace NDetails {

    template <typename TUnstatic, typename Ty>
    struct TypeRegistrar {
      typedef Ty type;
      TypeRegistrar(::fcf::TypeInfo* a_info){
        a_info->initialize<Ty>();
      }
    };

    template <typename TUnstatic, typename Ty>
    struct TypeRegistrar<TUnstatic, Ty&&> {
      typedef Ty type;
      TypeRegistrar(::fcf::TypeInfo* a_info){
        a_info->initialize<Ty>();
      }
    };

    template <typename TUnstatic>
    struct TypeRegistrar<TUnstatic, void> {
      typedef void type;
      TypeRegistrar(::fcf::TypeInfo* /*a_info*/){
      }
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_TYPE__NDETAILS__TYPE_REGISTRAR_HPP___
