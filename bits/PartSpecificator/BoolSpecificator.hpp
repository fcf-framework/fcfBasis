#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__BOOL_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__BOOL_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../bits/PartType/Type.hpp"
#include "../../Variant.hpp"

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

    inline Variant universalCall(const Ty* a_object, Variant* a_argv, size_t a_argc) const {
      if (!a_argc){
        std::runtime_error("Invalid argument number");
      }
      if (!a_object) {
        std::runtime_error("First argument is null");
      }
      if (!a_argv) {
        std::runtime_error("Second argument is null");
      }
      const Ty* ptr = (const Ty*)a_argv->ptr();
      if (!ptr) {
        std::runtime_error("Second argument is null");
      }
      if (Type<Ty>().index() != a_argv->getTypeIndex()) {
        std::runtime_error("Error comparing different types");
      }
      return (bool)Type<Ty, BoolSpecificator>().call(a_object);
    }

    inline bool call(const Ty* a_value) const {
      return !!(*a_value);
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__BOOL_SPECIFICATOR_HPP___
