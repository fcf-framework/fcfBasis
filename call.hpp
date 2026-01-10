#ifndef ___FCF_BASIS__CALL_HPP___
#define ___FCF_BASIS__CALL_HPP___

#include "macro.hpp"

#include "Type.hpp"

// Included for use macros
#include "bits/PartCall/NDetails/CallResultTypeGetter.hpp"
#include "bits/PartCallStorage/CallStorageRegistrator.hpp"

#include "bits/PartCall/CallSeeker.hpp"
#include "bits/PartCall/NDetails/Caller.hpp"

#include "bits/PartCall/CallCache.hpp"

namespace fcf {

  template <typename... TArgPack>
  inline void call(const char* a_functionName, const TArgPack& ... a_argPack) {
    Call dc;
    CallSeeker<void, TArgPack...>()(a_functionName, &dc, a_argPack...);
    NDetails::Caller().call(dc, a_argPack...);
  }

  template <typename... TArgPack>
  inline void call(const Call* a_dc, const TArgPack& ... a_argPack) {
    if (a_dc->dynamicCaller) {
      call(a_dc->name.c_str(), a_argPack...);
    } else {
      NDetails::Caller().call(*a_dc, a_argPack...);
    }
  }

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__CALL_HPP___
