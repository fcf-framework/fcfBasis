#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__LESS_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__LESS_SPECIFICATOR_HPP___

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

    inline Variant universalCall(const Ty* a_object, Variant* a_argv, size_t a_argc) const {
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
        throw std::runtime_error("Error comparing different types");
      }
      return (bool)Type<Ty, LessSpecificator>().call(a_object, ptr);
    }

    inline bool call(const Ty* a_leftValue, const Ty* a_rightValue) const {
      return *a_leftValue < *a_rightValue;
    }
  };


} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__LESS_SPECIFICATOR_HPP___
