#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__BOOL_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__BOOL_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../bits/PartType/Type.hpp"
#include "../../PartException.hpp"
#include "../../PartVariant.hpp"

namespace fcf{

  struct BoolSpecificator {
    typedef bool (*CallType)(const void*);
  };

  template <typename Ty>
  struct Type<Ty, BoolSpecificator> {
    enum { enable = false };
  };

  template <typename Ty>
  struct TypeImpl<Ty, BoolSpecificator> {
    enum { enable = true };

    inline Variant universalCall(const Ty* a_object, const Variant* /*a_argv*/, size_t a_argc) const {
      if (!a_argc){
        throw MathArumentCountException(__FILE__, __LINE__, "bool");
      }
      if (!a_object) {
        throw MathEmptyArgumentException(__FILE__, __LINE__, "bool", 1);
      }
      return Variant(Type<Ty, BoolSpecificator>().call(a_object));
    }

    inline bool call(const Ty* a_value) const {
      return !!(*a_value);
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__BOOL_SPECIFICATOR_HPP___
