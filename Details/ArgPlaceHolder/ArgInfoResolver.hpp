#ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__ARG_INFO_RESOLVER_HPP___
#define ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__ARG_INFO_RESOLVER_HPP___

#include <cstddef>
#include "../../bits/ArgPlaceHolder/IsPlaceHolder.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace ArgPlaceHolder {

        template <bool IsPlaceHolder, size_t Index, size_t CurrentIndex, size_t ArgIndex, typename TMask, typename Ty = Nop, typename... TRealArgPack>
        struct ArgInfoResolver {
          typedef typename TMask::next_type next_mask_type;
          typedef ArgInfoResolver<::fcf::ArgPlaceHolder::IsPlaceHolder<typename next_mask_type::type1>::value,
                                  Index,
                                  CurrentIndex + 1,
                                  ArgIndex + 1,
                                  next_mask_type,
                                  TRealArgPack...
                                 > next_type;
          enum { argIndex = next_type::argIndex };
          enum { isPlaceHolder = next_type::isPlaceHolder };
          typedef typename next_type::type type;
        };

        template <size_t Index, size_t CurrentIndex, size_t ArgIndex, typename TMask, typename Ty, typename... TRealArgPack>
        struct ArgInfoResolver<true, Index, CurrentIndex, ArgIndex, TMask, Ty, TRealArgPack...> {
          typedef typename TMask::next_type next_mask_type;
          typedef ArgInfoResolver<::fcf::ArgPlaceHolder::IsPlaceHolder<typename next_mask_type::type1>::value,
                                  Index,
                                  CurrentIndex + 1,
                                  ArgIndex,
                                  next_mask_type,
                                  TRealArgPack...
                                 > next_type;
          enum { argIndex = next_type::argIndex };
          enum { isPlaceHolder = next_type::isPlaceHolder };
          typedef typename next_type::type type;
        };

        template <size_t Index, size_t ArgIndex, typename TMask, typename Ty, typename... TRealArgPack>
        struct ArgInfoResolver<false, Index, Index, ArgIndex, TMask, Ty, TRealArgPack...>{
          enum { argIndex = ArgIndex };
          enum { isPlaceHolder = false };
          typedef Ty type;
        };

        template <size_t Index, size_t ArgIndex, typename TMask, typename Ty, typename... TRealArgPack>
        struct ArgInfoResolver<true, Index, Index, ArgIndex, TMask, Ty, TRealArgPack...>{
          enum { argIndex         = TMask::type1::value - 1};
          enum { isPlaceHolder = true };
          typedef Ty type;
        };

      } // ArgPlaceHolder namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__ARG_INFO_RESOLVER_HPP___
