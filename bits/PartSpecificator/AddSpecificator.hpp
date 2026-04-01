#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__ADD_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__ADD_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../bits/PartType/Type.hpp"
#include "../../PartException.hpp"
#include "../../PartVariant.hpp"

namespace fcf{

  struct AddSpecificator {
    typedef void (*CallType)(void* a_destination, const void* a_leftValue, const void* a_rightValue);
  };

  template <typename Ty>
  struct Type<Ty, AddSpecificator> {
    enum { enable = false };
  };

  template <typename Ty>
  struct TypeImpl<Ty, AddSpecificator> {
    enum { enable = true };

    inline Variant universalCall(Ty* a_object, Variant* a_argv, size_t a_argc) const {
      if (a_argc < 2){
        throw MathArumentCountException(__FILE__, __LINE__, "+");
      }
      if (!a_object) {
        throw MathEmptyResultPointerException(__FILE__, __LINE__, "+");
      }
      if (Type<Ty>().index() != a_argv[0].getDataTypeIndex() ||
          Type<Ty>().index() != a_argv[1].getDataTypeIndex()
         ){
        const Ty left = a_argv[0].cast<Ty>();
        const Ty right = a_argv[1].cast<Ty>();
        Type<Ty, AddSpecificator>().call(a_object, &left, &right);
      } else {
        const Ty* leftPtr = (const Ty*)a_argv->ptr();
        if (!leftPtr) {
          throw MathEmptyArgumentException(__FILE__, __LINE__, "+", 1);
        }
        const Ty* rightPtr = (const Ty*)(a_argv+1)->ptr();
        if (!rightPtr) {
          throw MathEmptyArgumentException(__FILE__, __LINE__, "+", 2);
        }
        Type<Ty, AddSpecificator>().call(a_object, leftPtr, rightPtr);
      }
      return Variant();
    }

    inline void call(Ty* a_destination, const Ty* a_leftValue, const Ty* a_rightValue) const {
      *a_destination = *a_leftValue + *a_rightValue;
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__ADD_SPECIFICATOR_HPP___
