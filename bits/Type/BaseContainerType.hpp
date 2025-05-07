#ifndef ___FCF_BASIS__BITS__BASE_CONTAINER_TYPE_HPP___
#define ___FCF_BASIS__BITS__BASE_CONTAINER_TYPE_HPP___

#include "BaseType.hpp"

namespace fcf {

  template <typename Ty, bool IsFlat>
  struct BaseContainerType : public BaseType<Ty> {
    using typename BaseType<Ty>::owner_type;

    enum { container = true };

    enum { flat = IsFlat };

  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__BASE_CONTAINER_TYPE_HPP___
