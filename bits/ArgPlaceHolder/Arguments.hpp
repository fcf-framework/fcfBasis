#ifndef ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__ARGUMENTS_HPP___
#define ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__ARGUMENTS_HPP___

#include "../../Details/ArgPlaceHolder/TypeResolver.hpp"

namespace fcf {
  namespace ArgPlaceHolder {

        template <typename Ty = Nop, typename... TPack>
        struct Arguments {
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<0, Ty, TPack...>::type type1;
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<1, Ty, TPack...>::type type2;
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<2, Ty, TPack...>::type type3;
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<3, Ty, TPack...>::type type4;
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<4, Ty, TPack...>::type type5;
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<5, Ty, TPack...>::type type6;
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<6, Ty, TPack...>::type type7;
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<7, Ty, TPack...>::type type8;
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<8, Ty, TPack...>::type type9;
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<9, Ty, TPack...>::type type10;
          typedef Arguments<TPack...> next_type;
        };

        template <typename TResult, typename Ty, typename... TPack>
        struct Arguments<TResult (Ty, TPack...)>{
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<0, Ty, TPack...>::type type1;
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<1, Ty, TPack...>::type type2;
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<2, Ty, TPack...>::type type3;
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<3, Ty, TPack...>::type type4;
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<4, Ty, TPack...>::type type5;
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<5, Ty, TPack...>::type type6;
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<6, Ty, TPack...>::type type7;
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<7, Ty, TPack...>::type type8;
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<8, Ty, TPack...>::type type9;
          typedef typename ::fcf::Details::Basis::ArgPlaceHolder::TypeResolver<9, Ty, TPack...>::type type10;
          typedef Arguments<TPack...> next_type;
        };

  } // ArgPlaceHolder namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__ARGUMENTS_HPP___
