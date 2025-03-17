#ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__TYPE_RESOLVER_IMPL_HPP___
#define ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__TYPE_RESOLVER_IMPL_HPP___

#include <cstddef>
#include "../../Nop.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace ArgPlaceHolder {

        template <size_t Index, size_t CurrentIndex, typename Ty = Nop, typename... TPack>
        struct TypeResolverImpl {
          typedef typename TypeResolverImpl<Index, CurrentIndex + 1, TPack...>::type type;
        };

        template <size_t Index, typename Ty, typename... TPack>
        struct TypeResolverImpl<Index, Index, Ty, TPack...> {
          typedef Ty type;
        };

      } // ArgPlaceHolder namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__TYPE_RESOLVER_IMPL_HPP___
