#ifndef ___FCF_BASIS__BITS__CALL__ARG_NUMBER_HPP___
#define ___FCF_BASIS__BITS__CALL__ARG_NUMBER_HPP___

#include "Arg.hpp"

namespace fcf {

  template <typename Ty>
  struct ArgNumber { enum { value = 0  }; };

  template <>
  struct ArgNumber<Arg1> { enum { value = Arg1::value }; };

  template <>
  struct ArgNumber<Arg2> { enum { value = Arg2::value }; };

  template <>
  struct ArgNumber<Arg3> { enum { value = Arg3::value }; };

  template <>
  struct ArgNumber<Arg4> { enum { value = Arg4::value }; };

  template <>
  struct ArgNumber<Arg5> { enum { value = Arg5::value }; };

  template <>
  struct ArgNumber<Arg6> { enum { value = Arg6::value }; };

  template <>
  struct ArgNumber<Arg7> { enum { value = Arg7::value }; };

  template <>
  struct ArgNumber<Arg8> { enum { value = Arg8::value }; };

  template <>
  struct ArgNumber<Arg9> { enum { value = Arg9::value }; };

  template <>
  struct ArgNumber<Arg10> { enum { value = Arg10::value }; };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__ARG_NUMBER_HPP___
