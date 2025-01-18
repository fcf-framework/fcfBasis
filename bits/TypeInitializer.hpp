#ifndef ___FCF_BASIS__BITS__TYPE_INITIALIZER_HPP___
#define ___FCF_BASIS__BITS__TYPE_INITIALIZER_HPP___

#include "../macro.hpp"
#include "../Type.hpp"

namespace fcf {

  template <typename Ty>
  struct TypeInitializer {
    TypeInitializer() {
      fcf::Type<Ty>::index();
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__TYPE_INITIALIZER_HPP___

