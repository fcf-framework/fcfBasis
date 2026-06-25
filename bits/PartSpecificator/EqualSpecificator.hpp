#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__EQUAL_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__EQUAL_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../bits/PartType/Type.hpp"
#include "../../PartException.hpp"
#include "../../PartVariant.hpp"

namespace fcf{

  struct EqualSpecificator {
    typedef bool (*CallType)(const void*, const void*);
    typedef bool (*HandleType)(const void*, const void*);
  };

  template <typename Ty>
  struct Type<Ty, EqualSpecificator> {
  };

  template <typename Ty>
  struct TypeImpl<Ty, EqualSpecificator> {

    inline bool operator()(const Ty* a_leftValue, const Ty* a_rightValue) {
      return *a_leftValue == *a_rightValue;
    }

    inline bool call(const Ty* a_leftValue, const Ty* a_rightValue) {
      return Type<Ty, EqualSpecificator>()(a_leftValue, a_rightValue);
    }

    inline Variant universalCall(const Ty* a_object, const Variant* a_argv, size_t a_argc) const {
      if (!a_argc){
        throw MathArumentCountException(__FILE__, __LINE__, "==");
      }
      if (!a_object) {
        throw MathEmptyArgumentException(__FILE__, __LINE__, "==", 1);
      }
      if (Type<Ty>().index() != a_argv[0].getDataTypeIndex()){
        const Ty right = a_argv[0].cast<Ty>();
        return Variant(Type<Ty, EqualSpecificator>().call(a_object, &right));
      }
      const Ty* ptr = (const Ty*)a_argv->ptr();
      if (!ptr) {
        throw MathEmptyArgumentException(__FILE__, __LINE__, "==", 2);
      }
      return Variant(Type<Ty, EqualSpecificator>().call(a_object, ptr));
    }

  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__EQUAL_SPECIFICATOR_HPP___
