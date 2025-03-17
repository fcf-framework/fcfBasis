#ifndef ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__IS_PLACE_HOLDER_HPP___
#define ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__IS_PLACE_HOLDER_HPP___

#include <type_traits>
#include "../../Nop.hpp"
#include "Arg.hpp"

namespace fcf {
  namespace ArgPlaceHolder {

    template <typename Ty = Nop, typename... TPack>
    struct IsPlaceHolder {
      typedef typename std::remove_reference<Ty>::type check_type;
      enum {
        value = std::is_same<Arg1,  check_type>::value ||
                std::is_same<Arg2,  check_type>::value ||
                std::is_same<Arg3,  check_type>::value ||
                std::is_same<Arg4,  check_type>::value ||
                std::is_same<Arg5,  check_type>::value ||
                std::is_same<Arg6,  check_type>::value ||
                std::is_same<Arg7,  check_type>::value ||
                std::is_same<Arg8,  check_type>::value ||
                std::is_same<Arg9,  check_type>::value ||
                std::is_same<Arg10, check_type>::value
        };
    };

  } // ArgPlaceHolder namespace  
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__IS_PLACE_HOLDER_HPP___
