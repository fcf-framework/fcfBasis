#ifndef ___FCF__BASIS__BITS__PART_SPECIFIER__VALUE_SPECIFIER_HPP___
#define ___FCF__BASIS__BITS__PART_SPECIFIER__VALUE_SPECIFIER_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "SpecifierRegistrarHandler.hpp"
#include "../PartType/PartType.hpp"
#include "../../PartVariant.hpp"

namespace fcf {

  struct ValueSpecifier { 
  };

  template <typename Ty>
  struct Type<Ty, ValueSpecifier> {
    enum { enable = false };
  };


  template <typename Ty>
  struct TypeImpl<Ty, ValueSpecifier> {
    enum { enable = true };

    inline Variant universalCall(Ty* a_object, Variant* /*a_argv*/, size_t /*a_argc*/) const {
      return Type<Ty, ValueSpecifier>().call(a_object);
    }

    //
    // Example call mathod
    // 
    // inline auto call(Ty* a_container) -> decltype(a_container->value) const {
    //  return a_container->value;
    //}

  };


}

#endif // #ifndef ___FCF__BASIS__BITS__PART_SPECIFIER__VALUE_SPECIFIER_HPP___
