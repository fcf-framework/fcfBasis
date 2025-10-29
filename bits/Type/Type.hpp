#ifndef ___FCF__BASIS__BITS__TYPE__TYPE_HPP___
#define ___FCF__BASIS__BITS__TYPE__TYPE_HPP___

#include <list>
#include <set>
#include <vector>
#include "../../Nop.hpp"
#include "../Specificator/specificators.hpp"
#include "../../Details/typeStorage.hpp"
#include "BaseType.hpp"
#include "BaseContainerType.hpp"

namespace fcf {

  template <typename Ty, typename TSpecificator>
  struct TypeImpl;

  template <typename Ty, typename TInfoMode>
  struct Type : public BaseType<Ty> {
    enum { container = false };

    typedef Ty data_type;
  };
} // fcf namespace

namespace fcf {
  template <typename Ty>
  struct Type<Ty, RawDataSpecificator> {
    enum { enable = false };
  };


} // fcf namespace


#endif // #ifndef ___FCF__BASIS__BITS__TYPE__TYPE_HPP___
