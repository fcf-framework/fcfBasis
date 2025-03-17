#ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__ARG_RESOLVER_HPP___
#define ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__ARG_RESOLVER_HPP___

#include <cstddef>
#include "../../bits/ArgPlaceHolder/IsPlaceHolder.hpp"
#include "ArgInfoResolver.hpp"
#include "ArgResolverImpl.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace ArgPlaceHolder {

        template <size_t Index, typename TMask, typename... TRealArgPack>
        struct ArgResolver {
          typedef ArgInfoResolver<
                          ::fcf::ArgPlaceHolder::IsPlaceHolder< typename TMask::type1 >::value,
                          Index,
                          0,
                          0,
                          TMask,
                          TRealArgPack...
                          > info_resolver_type;
          typedef ArgResolverImpl<info_resolver_type::isPlaceHolder, Index, TMask, TRealArgPack... > resolver_type;

          template <typename TVars, typename... TArgPack>
          inline static typename TypeResolver<Index, TRealArgPack...>::type call(TVars& a_variants, TArgPack&... a_argPack){
            return resolver_type::call(a_variants, a_argPack...);
          }
        };

      } // ArgPlaceHolder namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__ARG_RESOLVER_HPP___
