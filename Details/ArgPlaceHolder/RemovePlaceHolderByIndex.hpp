#ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__REMOVE_PLACE_HOLDER_BY_INDEX_HPP___
#define ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__REMOVE_PLACE_HOLDER_BY_INDEX_HPP___

#include <cstddef>
#include "../../bits/ArgPlaceHolder/IsPlaceHolder.hpp"
#include "RemovePlaceHolderByIndexImpl.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace ArgPlaceHolder {

        template <size_t Index, typename... TArgPack>
        struct RemovePlaceHolderByIndex {
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndexImpl<
                                ::fcf::ArgPlaceHolder::IsPlaceHolder<TArgPack...>::value,
                                Index,
                                0,
                                TArgPack...
                              >::type type;
        };

      } // ArgPlaceHolder namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__REMOVE_PLACE_HOLDER_BY_INDEX_IMPL_HPP___

