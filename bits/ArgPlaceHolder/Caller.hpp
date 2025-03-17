#ifndef ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__CALLER_HPP___
#define ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__CALLER_HPP___

#include "../../Details/ArgPlaceHolder/CallerImpl.hpp"
#include "RemovePlaceHolder.hpp"
namespace fcf {
  namespace ArgPlaceHolder {

    template <typename TMask, typename TResult, typename... TArgPack>
    struct Caller{
      typedef Variant arr_variants_type[10];
      typedef arr_variants_type& ref_variants_type;
      typedef TResult(*function_type)(TArgPack...);
      typedef typename RemovePlaceHolder<TResult,
                        function_type, 
                        ref_variants_type,
                        typename TMask::type1,
                        typename TMask::type2,
                        typename TMask::type3,
                        typename TMask::type4,
                        typename TMask::type5,
                        typename TMask::type6,
                        typename TMask::type7,
                        typename TMask::type8
                        >::caller_type caller_type;
      template <typename TFunction, typename TVars, typename... TCallPack>
      static void call(TFunction a_function, TVars& a_variants, TCallPack&&... a_args) {
        ::fcf::Details::Basis::ArgPlaceHolder::CallerImpl<sizeof...(TArgPack), TMask, TArgPack...>::call(a_function, a_variants, a_args...);
      }
    };

    template <typename TMask, typename TResult, typename... TArgPack>
    struct Caller<TMask, TResult (TArgPack...)>{
      typedef Variant arr_variants_type[10];
      typedef arr_variants_type& ref_variants_type;
      typedef TResult(*function_type)(TArgPack...);
      typedef typename RemovePlaceHolder<void,
                        function_type, 
                        ref_variants_type,
                        typename TMask::type1,
                        typename TMask::type2,
                        typename TMask::type3,
                        typename TMask::type4,
                        typename TMask::type5,
                        typename TMask::type6,
                        typename TMask::type7,
                        typename TMask::type8
                        >::caller_type caller_type;
      template <typename TFunction, typename TVars, typename... TCallPack>
      static void call(TFunction a_function, TVars& a_variants, TCallPack&&... a_args) {
        ::fcf::Details::Basis::ArgPlaceHolder::CallerImpl<sizeof...(TArgPack), TMask, TArgPack...>::call(a_function, a_variants, a_args...);
      }
    };

    template <typename TResult, typename... TArgPack>
    struct Caller<Nop, TResult, TArgPack...>{
      typedef Variant arr_variants_type[10];
      typedef arr_variants_type& ref_variants_type;
      typedef TResult(*function_type)(TArgPack...);
      typedef void (*caller_type)(function_type, ref_variants_type, TArgPack&&...);
      template <typename... TCallPack>
      static void call(TCallPack... a_args) {
      }
    };

    template <typename TResult, typename... TArgPack>
    struct Caller<Nop, TResult (TArgPack...)>{
      typedef Variant arr_variants_type[10];
      typedef arr_variants_type& ref_variants_type;
      typedef TResult(*function_type)(TArgPack...);
      typedef void (*caller_type)(function_type, ref_variants_type, TArgPack&&...);
      template <typename... TCallPack>
      static void call(TCallPack... a_args) {
      }
    };

  } // ArgPlaceHolder namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__CALLER_HPP___
