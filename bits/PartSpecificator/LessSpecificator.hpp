#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__LESS_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__LESS_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../bits/PartType/Type.hpp"
#include "../../Exception.hpp"
#include "../../Variant.hpp"

namespace fcf{

  struct LessSpecificator {
    typedef bool (*CallType)(const void*, const void*);
  };

  template <typename Ty>
  struct Type<Ty, LessSpecificator> {
    enum { enable = false };
  };

  template <typename Ty>
  struct TypeImpl<Ty, LessSpecificator> {
    enum { enable = true };

    inline Variant universalCall(const Ty* a_object, const Variant* a_argv, size_t a_argc) const {
      if (!a_argc){
        throw MathArumentCountException(__FILE__, __LINE__, "<");
      }
      if (!a_object) {
        throw MathEmptyArgumentException(__FILE__, __LINE__, "<", 1);
      }
      if (Type<Ty>().index() != a_argv[0].getDataTypeIndex()){
        const Ty right = a_argv[0].cast<Ty>();
        return Variant(Type<Ty, LessSpecificator>().call(a_object, &right));
      }
      const Ty* ptr = (const Ty*)a_argv->ptr();
      if (!ptr) {
        throw MathEmptyArgumentException(__FILE__, __LINE__, "<", 2);
      }
      return Variant(Type<Ty, LessSpecificator>().call(a_object, ptr));
    }

    inline bool call(const Ty* a_leftValue, const Ty* a_rightValue) const {
      return *a_leftValue < *a_rightValue;
    }
  };


} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__LESS_SPECIFICATOR_HPP___
