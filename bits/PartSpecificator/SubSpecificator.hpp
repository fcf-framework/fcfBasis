#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__SUB_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__SUB_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../bits/PartType/Type.hpp"
#include "../../Variant.hpp"
#include "../../Exception.hpp"
namespace fcf{

  struct SubSpecificator {
    typedef void (*CallType)(void*, const void*, const void*);
  };

  template <typename Ty>
  struct Type<Ty, SubSpecificator> {
    enum { enable = false };
  };

  template <typename Ty>
  struct TypeImpl<Ty, SubSpecificator> {
    enum { enable = true };

    inline Variant universalCall(Ty* a_object, Variant* a_argv, size_t a_argc) const {
      if (a_argc < 2){
        throw MathArumentCountException(__FILE__, __LINE__, "-");
      }
      if (!a_object) {
        throw MathEmptyResultPointerException(__FILE__, __LINE__, "-");
      }
      if (Type<Ty>().index() != a_argv[0].getDataTypeIndex() ||
          Type<Ty>().index() != a_argv[1].getDataTypeIndex()
         ){
        const Ty left = a_argv[0].cast<Ty>();
        const Ty right = a_argv[1].cast<Ty>();
        Type<Ty, SubSpecificator>().call(a_object, &left, &right);
      } else {
        const Ty* leftPtr = (const Ty*)a_argv->ptr();
        if (!leftPtr) {
          throw std::runtime_error("Second argument is null");
        }
        const Ty* rightPtr = (const Ty*)(a_argv+1)->ptr();
        if (!rightPtr) {
          throw std::runtime_error("Second argument is null");
        }
        if (Type<Ty>().index() != a_argv->getTypeIndex()) {
          throw std::runtime_error("Error subtration for different types");
        }
        if (Type<Ty>().index() != (a_argv+1)->getTypeIndex()) {
          throw std::runtime_error("Error subtration for different types");
        }
        Type<Ty, SubSpecificator>().call(a_object, leftPtr, rightPtr);
      }
      return Variant();
    }

    inline void call(Ty* a_result, const Ty* a_leftValue, const Ty* a_rightValue) const {
      *a_result = *a_leftValue - *a_rightValue;
    }
  };


} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__SUB_SPECIFICATOR_HPP___
