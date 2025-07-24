#ifndef ___FCF_BASIS__CALL_HPP___
#define ___FCF_BASIS__CALL_HPP___

#include "macro.hpp"
#include "bits/Call/CallSeeker.hpp"
#include "bits/Call/Details/CallerByArg.hpp"
#include "bits/Call/Details/CallerByList.hpp"


namespace fcf {

  template <typename... TArgPack>
  inline void call(const char* a_functionName, const TArgPack& ... a_argPack) {
    fcf::Call dc;
    fcf::CallSeeker<void, TArgPack...>()(a_functionName, &dc, a_argPack...);
    StaticVector<void*, sizeof...(TArgPack)*2> args(sizeof...(TArgPack));
    ::fcf::Details::CallerByArg<sizeof...(TArgPack), 0, 0>()(dc, args, 0, 0, a_argPack...);
    /*
    typedef std::pair<void*, unsigned int> arg_type;
    StaticVector<arg_type, sizeof...(TArgPack)*2> args{ arg_type((void*)&a_argPack, Type<TArgPack>().index())... };
    ::fcf::Details::CallerByList<0, sizeof...(TArgPack), (sizeof...(TArgPack) + 2)*2>()(dc, 0, args);
    */
  }

  template <typename... TArgPack>
  inline void call(const Call* a_dc, const TArgPack& ... a_argPack) {
    if (a_dc->dynamicCaller) {
      call(a_dc->name.c_str(), a_argPack...);
    } else {
      StaticVector<void*, sizeof...(TArgPack)*2> args(sizeof...(TArgPack));
      ::fcf::Details::CallerByArg<sizeof...(TArgPack), 0, 0>()(*a_dc, args, 0, 0, a_argPack...);
      /*
      typedef std::pair<void*, unsigned int> arg_type;
      StaticVector<arg_type, sizeof...(TArgPack)*2> args{ arg_type((void*)&a_argPack, Type<TArgPack>().index())... };
      ::fcf::Details::CallerByList<0, sizeof...(TArgPack), (sizeof...(TArgPack) + 2)*2>()(*a_dc, 0, args);
      */
    }
  }

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__CALL_HPP___
