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
  };


  template <typename Ty>
  struct TypeImpl<Ty, ValueSpecifier> {

    template <typename TArg>
    inline auto call(TArg* a_object) -> decltype( Type<TArg, ValueSpecifier>()(a_object) ) {
      return Type<TArg, ValueSpecifier>()(a_object);
    }

    inline Variant universalCall(Ty* a_object, Variant* /*a_argv*/, size_t /*a_argc*/) const {
      return Variant(Type<Ty, ValueSpecifier>()(a_object));
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
