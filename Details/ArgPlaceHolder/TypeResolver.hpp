#ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__TYPE_RESOLVER_HPP___
#define ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__TYPE_RESOLVER_HPP___

#include "TypeResolverImpl.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace ArgPlaceHolder {

        template <size_t Index, typename... TPack>
        struct TypeResolver {
          typedef typename TypeResolverImpl<Index, 0, TPack...>::type type;
        };

      } // ArgPlaceHolder namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__TYPE_RESOLVER_HPP___
