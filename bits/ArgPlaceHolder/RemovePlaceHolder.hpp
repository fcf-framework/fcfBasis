#ifndef ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__REMOVE_PLACE_HOLDER_HPP___
#define ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__REMOVE_PLACE_HOLDER_HPP___

#include "../../Details/ArgPlaceHolder/RemovePlaceHolderByIndex.hpp"
#include "../../Details/ArgPlaceHolder/FunctionTypeBuilder.hpp"

namespace fcf {
  namespace ArgPlaceHolder {

    template <typename TResult, typename... TArgPack>
    struct RemovePlaceHolder {
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<0, TArgPack...>::type type1;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<1, TArgPack...>::type type2;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<2, TArgPack...>::type type3;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<3, TArgPack...>::type type4;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<4, TArgPack...>::type type5;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<5, TArgPack...>::type type6;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<6, TArgPack...>::type type7;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<7, TArgPack...>::type type8;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<8, TArgPack...>::type type9;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<9, TArgPack...>::type type10;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::FunctionTypeBuilder<
                            TResult,
                            type1,
                            type2,
                            type3,
                            type4,
                            type5,
                            type6,
                            type7,
                            type8,
                            type9,
                            type10
                          >::type function_type;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::FunctionTypeBuilder<
                            TResult,
                            type1,
                            type2,
                            type3,
                            type4,
                            type5,
                            type6,
                            type7,
                            type8,
                            type9,
                            type10
                          >::caller_type caller_type;
    };

    template <typename TResult, typename... TArgPack>
    struct RemovePlaceHolder<TResult (TArgPack...)> {
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<0, TArgPack...>::type type1;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<1, TArgPack...>::type type2;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<2, TArgPack...>::type type3;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<3, TArgPack...>::type type4;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<4, TArgPack...>::type type5;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<5, TArgPack...>::type type6;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<6, TArgPack...>::type type7;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<7, TArgPack...>::type type8;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<8, TArgPack...>::type type9;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<9, TArgPack...>::type type10;

      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::FunctionTypeBuilder<
                            TResult,
                            type1,
                            type2,
                            type3,
                            type4,
                            type5,
                            type6,
                            type7,
                            type8,
                            type9,
                            type10
                          >::type function_type;
      typedef typename ::fcf::Details::Basis::ArgPlaceHolder::FunctionTypeBuilder<
                            TResult,
                            type1,
                            type2,
                            type3,
                            type4,
                            type5,
                            type6,
                            type7,
                            type8,
                            type9,
                            type10
                          >::caller_type caller_type;
    };

  } // ArgPlaceHolder namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__REMOVE_PLACE_HOLDER_HPP___
