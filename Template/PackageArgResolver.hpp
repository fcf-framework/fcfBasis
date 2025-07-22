#ifndef ___FCF_BASIS__TEMPLATE__PACKAGE_ARG_RESOLVER_HPP___
#define ___FCF_BASIS__TEMPLATE__PACKAGE_ARG_RESOLVER_HPP___

#include "../Nop.hpp"

namespace fcf {
  namespace Template {

    template <size_t Index, bool OverflowMode = false, typename TOverflow = Nop>
    struct PackageArgResolver{
      template <typename TArg1, typename... TArgPack>
      inline auto operator()(TArg1 a_arg, TArgPack... a_argPack) -> decltype( PackageArgResolver<Index-1, OverflowMode, TOverflow>()(a_argPack...) ) {
        return PackageArgResolver<Index-1, OverflowMode, TOverflow>()(a_argPack...);
      }
    };

    template <size_t Index, typename TOverflow>
    struct PackageArgResolver<Index, true, TOverflow>{
      template <typename TArg1, typename... TArgPack>
      inline auto operator()(TArg1 a_arg, TArgPack... a_argPack) -> decltype( PackageArgResolver<Index-1, true, TOverflow>()(a_argPack...) ) {
        return PackageArgResolver<Index-1, true, TOverflow>()(a_argPack...);
      }
      inline TOverflow operator()() {
        return TOverflow();
      }
    };

    template <typename TOverflow>
    struct PackageArgResolver<0, false, TOverflow> {
      template <typename TArg1, typename... TArgPack>
      inline TArg1 operator()(TArg1 a_arg, TArgPack... a_argPack) {
        return a_arg;
      }
    };


    template <typename TOverflow>
    struct PackageArgResolver<0, true, TOverflow> {
      template <typename TArg1, typename... TArgPack>
      inline TArg1 operator()(TArg1 a_arg, TArgPack... a_argPack) {
        return a_arg;
      }
      inline TOverflow operator()() {
        return TOverflow();
      }
    };

  } // Template namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__TEMPLATE__PACKAGE_ARG_RESOLVER_HPP___
