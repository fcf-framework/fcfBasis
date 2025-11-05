#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_INITIALIZER_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_INITIALIZER_HPP___

#include "../../macro.hpp"
#include "../../bits/PartType/Type.hpp"
#include <iostream>

namespace fcf{

  template <typename Ty>
  struct TypeInitializer {
    TypeInitializer() {
      ::fcf::Type<Ty>().index();
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_INITIALIZER_HPP___
