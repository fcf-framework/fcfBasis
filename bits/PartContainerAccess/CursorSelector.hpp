#ifndef ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__CURSOR_SELECTOR_HPP___
#define ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__CURSOR_SELECTOR_HPP___

#include "Cursor.hpp"

namespace fcf{
  namespace NDetails {

    template <typename Ty>
    struct CursorConstTypeSwitcher;

    template <template <typename Ty> class TCursor, typename Ty>
    struct CursorConstTypeSwitcher< TCursor<Ty> >{
      typedef TCursor<const Ty> Type;
    };

    template <template <typename Ty1, typename Ty2> class TCursor, typename Ty1, typename Ty2>
    struct CursorConstTypeSwitcher< TCursor<Ty1, Ty2> >{
      typedef TCursor<const Ty1, Ty2> Type;
    };

    template <typename ConstTy>
    struct CursorSelectorByTypeChange;

    template <typename Ty>
    struct CursorSelectorByTypeChange<const Ty>{
      typedef typename CursorConstTypeSwitcher< typename Cursor<Ty>::BaseType >::Type Type;
    };


    template <typename TConstType, typename = void>
    struct CursorSelectorByDirect{
      typedef typename CursorSelectorByTypeChange<TConstType>::Type Type;
    };

    template <typename TConstType>
    struct CursorSelectorByDirect<TConstType, decltype((void)Cursor<TConstType>())>{
      typedef Cursor<TConstType> Type;
    };

  } // NDetails namespace
} // fcf namespace

namespace fcf {

  template <typename Ty>
  struct CursorSelector{
    typedef Cursor<Ty> Type;
  };

  template <typename Ty>
  struct CursorSelector<const Ty>{
    typedef typename NDetails::CursorSelectorByDirect<const Ty>::Type Type;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__CURSOR_SELECTOR_HPP___
