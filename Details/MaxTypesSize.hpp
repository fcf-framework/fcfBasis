#ifndef ___FCF_BASIS__DETAILS__MAX_TYPES_SIZE_HPP___
#define ___FCF_BASIS__DETAILS__MAX_TYPES_SIZE_HPP___

namespace fcf {
  namespace Details {
    namespace Basis {
      template <typename Ty, typename... TPack>
      struct MaxTypesSize {
        enum { size =  sizeof(Ty) > MaxTypesSize<TPack...>::size ? sizeof(Ty) : MaxTypesSize<TPack...>::size };
      };

      template <typename Ty>
      struct MaxTypesSize<Ty> {
        enum { size =  sizeof(Ty) };
      };
    }
  }
}


#endif // #ifndef ___FCF_BASIS__DETAILS__MAX_TYPES_SIZE_HPP___
