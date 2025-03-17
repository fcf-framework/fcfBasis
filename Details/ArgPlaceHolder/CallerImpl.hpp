#ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__CALLER_IMPL_HPP___
#define ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__CALLER_IMPL_HPP___

#include <cstddef>
#include "ArgResolver.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace ArgPlaceHolder {

        template <size_t ArgCount, typename TMask, typename... TArgPack>
        struct CallerImpl;

        template <typename TMask, typename... TArgPack>
        struct CallerImpl<10, TMask, TArgPack...>{
          template <typename TFunction, typename TVars, typename... TCallPack>
          inline static void call(TFunction a_function, TVars& a_variants, TCallPack&... a_args) {
            a_function(
                        ArgResolver<0, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<1, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<2, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<3, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<4, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<5, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<6, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<7, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<8, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<9, TMask, TArgPack...>::call(a_variants, a_args...)
                      );
          }
        };

        template <typename TMask, typename... TArgPack>
        struct CallerImpl<9, TMask, TArgPack...>{
          template <typename TFunction, typename TVars, typename... TCallPack>
          inline static void call(TFunction a_function, TVars& a_variants, TCallPack&... a_args) {
            a_function(
                        ArgResolver<0, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<1, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<2, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<3, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<4, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<5, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<6, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<7, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<8, TMask, TArgPack...>::call(a_variants, a_args...)
                      );
          }
        };

        template <typename TMask, typename... TArgPack>
        struct CallerImpl<8, TMask, TArgPack...>{
          template <typename TFunction, typename TVars, typename... TCallPack>
          inline static void call(TFunction a_function, TVars& a_variants, TCallPack&... a_args) {
            a_function(
                        ArgResolver<0, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<1, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<2, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<3, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<4, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<5, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<6, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<7, TMask, TArgPack...>::call(a_variants, a_args...)
                      );
          }
        };

        template <typename TMask, typename... TArgPack>
        struct CallerImpl<7, TMask, TArgPack...>{
          template <typename TFunction, typename TVars, typename... TCallPack>
          inline static void call(TFunction a_function, TVars& a_variants, TCallPack&... a_args) {
            a_function(
                        ArgResolver<0, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<1, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<2, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<3, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<4, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<5, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<6, TMask, TArgPack...>::call(a_variants, a_args...)
                      );
          }
        };

        template <typename TMask, typename... TArgPack>
        struct CallerImpl<6, TMask, TArgPack...>{
          template <typename TFunction, typename TVars, typename... TCallPack>
          inline static void call(TFunction a_function, TVars& a_variants, TCallPack&... a_args) {
            a_function(
                        ArgResolver<0, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<1, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<2, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<3, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<4, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<5, TMask, TArgPack...>::call(a_variants, a_args...)
                      );
          }
        };

        template <typename TMask, typename... TArgPack>
        struct CallerImpl<5, TMask, TArgPack...>{
          template <typename TFunction, typename TVars, typename... TCallPack>
          inline static void call(TFunction a_function, TVars& a_variants, TCallPack&... a_args) {
            a_function(
                        ArgResolver<0, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<1, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<2, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<3, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<4, TMask, TArgPack...>::call(a_variants, a_args...)
                      );
          }
        };

        template <typename TMask, typename... TArgPack>
        struct CallerImpl<4, TMask, TArgPack...>{
          template <typename TFunction, typename TVars, typename... TCallPack>
          inline static void call(TFunction a_function, TVars& a_variants, TCallPack&... a_args) {
            a_function(
                        ArgResolver<0, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<1, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<2, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<3, TMask, TArgPack...>::call(a_variants, a_args...)
                      );
          }
        };

        template <typename TMask, typename... TArgPack>
        struct CallerImpl<3, TMask, TArgPack...>{
          template <typename TFunction, typename TVars, typename... TCallPack>
          inline static void call(TFunction a_function, TVars& a_variants, TCallPack&... a_args) {
            a_function(
                        ArgResolver<0, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<1, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<2, TMask, TArgPack...>::call(a_variants, a_args...)
                      );
          }
        };

        template <typename TMask, typename... TArgPack>
        struct CallerImpl<2, TMask, TArgPack...>{
          template <typename TFunction, typename TVars, typename... TCallPack>
          inline static void call(TFunction a_function, TVars& a_variants, TCallPack&... a_args) {
            a_function(
                        ArgResolver<0, TMask, TArgPack...>::call(a_variants, a_args...),
                        ArgResolver<1, TMask, TArgPack...>::call(a_variants, a_args...)
                      );
          }
        };

        template <typename TMask, typename... TArgPack>
        struct CallerImpl<1, TMask, TArgPack...>{
          template <typename TFunction, typename TVars, typename... TCallPack>
          inline static void call(TFunction a_function, TVars& a_variants, TCallPack&... a_args) {
            a_function(
                        ArgResolver<0, TMask, TArgPack...>::call(a_variants, a_args...)
                      );
          }
        };

      } // ArgPlaceHolder namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__CALLER_IMPL_HPP___
