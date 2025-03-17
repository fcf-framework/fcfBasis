#ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__REMOVE_PLACE_HOLDER_BY_INDEX_IMPL_HPP___
#define ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__REMOVE_PLACE_HOLDER_BY_INDEX_IMPL_HPP___

#include <cstddef>
#include "../../bits/ArgPlaceHolder/IsPlaceHolder.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace ArgPlaceHolder {

        template <bool IsPlaceHolder, size_t Index, size_t CurrentIndex, typename Ty = Nop, typename... TArgPack>
        struct RemovePlaceHolderByIndexImpl {
          typedef typename RemovePlaceHolderByIndexImpl<
                              ::fcf::ArgPlaceHolder::IsPlaceHolder<TArgPack...>::value,
                              Index,
                              CurrentIndex + 1,
                              TArgPack...
                               >::type type;
        };

        template <size_t Index, size_t CurrentIndex, typename Ty, typename... TArgPack>
        struct RemovePlaceHolderByIndexImpl<true, Index, CurrentIndex, Ty, TArgPack...>{
          typedef typename RemovePlaceHolderByIndexImpl<
                              ::fcf::ArgPlaceHolder::IsPlaceHolder<TArgPack...>::value,
                              Index,
                              CurrentIndex,
                              TArgPack...
                               >::type type;
        };

        template <size_t Index, typename Ty, typename... TArgPack>
        struct RemovePlaceHolderByIndexImpl<false, Index, Index, Ty, TArgPack...>{
          typedef Ty type;
        };

      } // ArgPlaceHolder namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__REMOVE_PLACE_HOLDER_BY_INDEX_IMPL_HPP___
