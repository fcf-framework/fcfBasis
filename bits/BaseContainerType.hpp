#ifndef ___FCF_BASIS__BASE_CONTAINER_TYPE_HPP___
#define ___FCF_BASIS__BASE_CONTAINER_TYPE_HPP___

#include "BaseType.hpp"

namespace fcf {
  
  template <typename Ty>
  struct BaseContainerType : public BaseType<Ty> {
    using typename BaseType<Ty>::owner_type;

    enum { container = true };

  };
  
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BASE_CONTAINER_TYPE_HPP___
