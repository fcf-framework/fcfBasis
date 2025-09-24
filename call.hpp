#ifndef ___FCF_BASIS__CALL_HPP___
#define ___FCF_BASIS__CALL_HPP___

#include "macro.hpp"

// Included for use macros
#include "bits/Call/Details/CallResultTypeGetter.hpp"

#include "bits/Call/CallSeeker.hpp"
#include "bits/Call/Details/Caller.hpp"


namespace fcf {

  template <typename... TArgPack>
  inline void call(const char* a_functionName, const TArgPack& ... a_argPack) {
    Call dc;
    CallSeeker<void, TArgPack...>()(a_functionName, &dc, a_argPack...);
    Details::Caller()(dc, a_argPack...);
  }

  template <typename... TArgPack>
  inline void call(const Call* a_dc, const TArgPack& ... a_argPack) {
    if (a_dc->dynamicCaller) {
      call(a_dc->name.c_str(), a_argPack...);
    } else {
      Details::Caller()(*a_dc, a_argPack...);
    }
  }

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__CALL_HPP___
