#ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_FUNCTION_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__CALL_FUNCTION_HPP___

#include "../../macro.hpp"
#include "../../PartType.hpp"
#include "CallSeeker.hpp"
#include "NDetails/Caller.hpp"
#include "CallCache.hpp"
#include "CallOptions.hpp"

// Included for use macros
#include "../../bits/PartCallStorage/CallStorageRegistrator.hpp"

namespace fcf{

  template <typename... TArgPack>
  inline void call(const char* a_functionName, const TArgPack& ... a_argPack) {
    Call dc;
    CallSeeker<void, TArgPack...>()(a_functionName, &dc, a_argPack...);
    NDetails::Caller().call(dc, a_argPack...);
  }

  template <typename... TArgPack>
  inline void call(const CallOptions& a_callOptions, const char* a_functionName, const TArgPack& ... a_argPack) {
    Call dc;
    CallSeeker<void, TArgPack...>(*a_callOptions.storage)(a_functionName, &dc, a_argPack...);
    NDetails::Caller(&a_callOptions).call(dc, a_argPack...);
  }

  template <typename... TArgPack>
  inline Variant rcall(const char* a_functionName, const TArgPack& ... a_argPack) {
    Call dc;
    CallSeeker<void, TArgPack...>()(a_functionName, &dc, a_argPack...);
    return NDetails::Caller().rcall(dc, a_argPack...);
  }

  template <typename... TArgPack>
  inline Variant rcall(const CallOptions& a_callOptions, const char* a_functionName, const TArgPack& ... a_argPack) {
    Call dc;
    CallSeeker<void, TArgPack...>(*a_callOptions.storage)(a_functionName, &dc, a_argPack...);
    return NDetails::Caller(&a_callOptions).rcall(dc, a_argPack...);
  }

  template <typename... TArgPack>
  inline void call(const Call* a_dc, const TArgPack& ... a_argPack) {
    if (a_dc->dynamicCaller) {
      call(a_dc->name.c_str(), a_argPack...);
    } else {
      NDetails::Caller().call(*a_dc, a_argPack...);
    }
  }

  template <typename... TArgPack>
  inline void call(const CallOptions& a_callOptions, const Call* a_dc, const TArgPack& ... a_argPack) {
    if (a_dc->dynamicCaller) {
      call(a_callOptions, a_dc->name.c_str(), a_argPack...);
    } else {
      NDetails::Caller(&a_callOptions).call(*a_dc, a_argPack...);
    }
  }

  template <typename... TArgPack>
  inline void rcall(const Call* a_dc, const TArgPack& ... a_argPack) {
    if (a_dc->dynamicCaller) {
      return rcall(a_dc->name.c_str(), a_argPack...);
    } else {
      return NDetails::Caller().rcall(*a_dc, a_argPack...);
    }
  }

  template <typename... TArgPack>
  inline void rcall(const CallOptions& a_callOptions, const Call* a_dc, const TArgPack& ... a_argPack) {
    if (a_dc->dynamicCaller) {
      return rcall(a_callOptions, a_dc->name.c_str(), a_argPack...);
    } else {
      return NDetails::Caller(&a_callOptions).rcall(*a_dc, a_argPack...);
    }
  }

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_FUNCTION_HPP___
