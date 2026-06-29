#ifndef _FCF_BASIS__BITS__PART_TYPE__TYPE_INITIALIZER_HPP___
#define _FCF_BASIS__BITS__PART_TYPE__TYPE_INITIALIZER_HPP___

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

#endif // #ifndef _FCF_BASIS__BITS__PART_TYPE__TYPE_INITIALIZER_HPP___
