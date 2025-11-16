#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__ADD_TO_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__ADD_TO_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../bits/PartType/Type.hpp"
#include "../../Variant.hpp"

namespace fcf{

  struct AddToSpecificator {
    typedef void (*CallType)(void*, const void*);
  };

  template <typename Ty>
  struct Type<Ty, AddToSpecificator> {
    enum { enable = false };
  };

  template <typename Ty>
  struct TypeImpl<Ty, AddToSpecificator> {
    enum { enable = true };

    inline Variant universalCall(Ty* a_object, Variant* a_argv, size_t a_argc) const {
      if (!a_argc){
        throw std::runtime_error("Invalid argument number");
      }
      if (!a_object) {
        throw std::runtime_error("First argument is null");
      }
      if (!a_argv) {
        throw std::runtime_error("Second argument is null");
      }
      const Ty* ptr = (const Ty*)a_argv->ptr();
      if (!ptr) {
        throw std::runtime_error("Second argument is null");
      }
      if (Type<Ty>().index() != a_argv->typeIndex()) {
        throw std::runtime_error("Error sum different types");
      }
      Type<Ty, AddToSpecificator>().call(a_object, ptr);
      return Variant();
    }

    inline void call(Ty* a_leftValue, const Ty* a_rightValue) const {
      *a_leftValue += *a_rightValue;
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__ADD_TO_SPECIFICATOR_HPP___
