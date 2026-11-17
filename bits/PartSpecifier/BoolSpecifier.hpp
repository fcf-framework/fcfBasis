#ifndef _FCF_BASIS__BITS__PART_SPECIFIER__BOOL_SPECIFIER_HPP___
#define _FCF_BASIS__BITS__PART_SPECIFIER__BOOL_SPECIFIER_HPP___

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
    bool operator()(const Ty* a_value);
    bool call(const Ty* a_value);
    Variant universalCall(const Ty* a_object, const Variant* /*a_argv*/, size_t a_argc) const;
  };

  template <typename Ty>
  bool TypeImpl<Ty, BoolSpecifier>::operator()(const Ty* a_value) {
    return !!(*a_value);
  }

  template <typename Ty>
  bool TypeImpl<Ty, BoolSpecifier>::call(const Ty* a_value) {
    return Type<Ty, BoolSpecifier>()(a_value);
  }

  template <typename Ty>
  Variant TypeImpl<Ty, BoolSpecifier>::universalCall(const Ty* a_object, const Variant* /*a_argv*/, size_t a_argc) const {
    if (!a_argc){
      throw MathArumentCountException(__FILE__, __LINE__, "bool");
    }
    if (!a_object) {
      throw MathEmptyArgumentException(__FILE__, __LINE__, "bool", 1);
    }
    return Variant(Type<Ty, BoolSpecifier>().call(a_object));
  }

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_SPECIFIER__BOOL_SPECIFIER_HPP___
