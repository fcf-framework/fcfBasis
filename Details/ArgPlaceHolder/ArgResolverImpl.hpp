#ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__ARG_RESOLVER_IMPL_HPP___
#define ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__ARG_RESOLVER_IMPL_HPP___

#include <cstddef>
#include "../../Variant.hpp"
#include "../../bits/ArgPlaceHolder/IsPlaceHolder.hpp"
#include "TypeResolver.hpp"
#include "ArgInfoResolver.hpp"
#include "SimpleArgResolver.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace ArgPlaceHolder {

        template <bool IsPlaceHolder, size_t Index, typename TMask, typename... TRealArgPack>
        struct ArgResolverImpl {
          typedef ArgInfoResolver<
                          ::fcf::ArgPlaceHolder::IsPlaceHolder< typename TMask::type1 >::value,
                          Index,
                          0,
                          0,
                          TMask,
                          TRealArgPack...
                          > info_resolver_type;
          template <typename TVars, typename... TArgPack>
          inline static typename TypeResolver<Index, TRealArgPack...>::type call(TVars& a_variants, TArgPack&... a_argPack){
            return SimpleArgResolver<info_resolver_type::argIndex>::call(a_argPack...);
          }
        };

        template <size_t Index, typename TMask, typename... TRealArgPack>
        struct ArgResolverImpl<true, Index, TMask, TRealArgPack...> {
          typedef ArgInfoResolver<
                          ::fcf::ArgPlaceHolder::IsPlaceHolder< typename TMask::type1 >::value,
                          Index,
                          0,
                          0,
                          TMask,
                          TRealArgPack...
                          > info_resolver_type;
          template <typename TVars, typename... TArgPack>
          inline static typename TypeResolver<Index, TRealArgPack...>::type call(TVars& a_variants , TArgPack&... a_argPack){
            return a_variants[info_resolver_type::argIndex].template convert<typename info_resolver_type::type>();
          }
        };


      } // ArgPlaceHolder namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace


#endif // #ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__ARG_RESOLVER_IMPL_HPP___
