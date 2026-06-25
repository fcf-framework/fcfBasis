#ifndef ___FCF_BASIS__BITS__PART_SPECIFIER__SUB_SPECIFIER_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFIER__SUB_SPECIFIER_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../bits/PartType/PartType.hpp"
#include "../../PartVariant.hpp"
#include "../../PartException.hpp"
namespace fcf{

  struct SubSpecifier {
    typedef void (*CallType)(void*, const void*, const void*);
  };

  template <typename Ty>
  struct Type<Ty, SubSpecifier> {
  };

  template <typename Ty>
  struct TypeImpl<Ty, SubSpecifier> {

    inline void operator()(Ty* a_result, const Ty* a_leftValue, const Ty* a_rightValue){
      *a_result = *a_leftValue - *a_rightValue;
    }

    inline void call(Ty* a_result, const Ty* a_leftValue, const Ty* a_rightValue) {
      Type<Ty,SubSpecifier>()(a_result, a_leftValue, a_rightValue);
    }

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
        Type<Ty, SubSpecifier>().call(a_object, &left, &right);
      } else {
        const Ty* leftPtr = (const Ty*)a_argv->ptr();
        if (!leftPtr) {
          throw MathEmptyArgumentException(__FILE__, __LINE__, "-", 1);
        }
        const Ty* rightPtr = (const Ty*)(a_argv+1)->ptr();
        if (!rightPtr) {
          throw MathEmptyArgumentException(__FILE__, __LINE__, "-", 2);
        }
        Type<Ty, SubSpecifier>().call(a_object, leftPtr, rightPtr);
      }
      return Variant();
    }

  };


} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFIER__SUB_SPECIFIER_HPP___
