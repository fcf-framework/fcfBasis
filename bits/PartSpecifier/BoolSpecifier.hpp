#ifndef ___FCF_BASIS__BITS__PART_SPECIFIER__BOOL_SPECIFIER_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFIER__BOOL_SPECIFIER_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../bits/PartType/Type.hpp"
#include "../../PartException.hpp"
#include "../../PartVariant.hpp"

namespace fcf{

  struct BoolSpecifier {
    typedef bool (*CallType)(const void*);
    typedef bool (*HandleType)(const void*);
  };

  template <typename Ty>
  struct Type<Ty, BoolSpecifier> {
  };

  template <typename Ty>
  struct TypeImpl<Ty, BoolSpecifier> {

    inline bool operator()(const Ty* a_value) {
      return !!(*a_value);
    }

    inline bool call(const Ty* a_value) {
      return Type<Ty, BoolSpecifier>()(a_value);
    }

    inline Variant universalCall(const Ty* a_object, const Variant* /*a_argv*/, size_t a_argc) const {
      if (!a_argc){
        throw MathArumentCountException(__FILE__, __LINE__, "bool");
      }
      if (!a_object) {
        throw MathEmptyArgumentException(__FILE__, __LINE__, "bool", 1);
      }
      return Variant(Type<Ty, BoolSpecifier>().call(a_object));
    }

  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFIER__BOOL_SPECIFIER_HPP___
