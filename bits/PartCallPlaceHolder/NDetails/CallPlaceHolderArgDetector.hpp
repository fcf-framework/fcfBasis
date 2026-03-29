#ifndef ___FCF_BASIS__BITS__PART_CALL_PLACE_HOLDER__NDETAILS__CALL_PLACE_HOLDER_ARG_DETECTOR_HPP___
#define ___FCF_BASIS__BITS__PART_CALL_PLACE_HOLDER__NDETAILS__CALL_PLACE_HOLDER_ARG_DETECTOR_HPP___

#include <type_traits>
#include "../../../bits/PartTypes/Nop.hpp"
#include "../../../bits/PartCall/Arg.hpp"

namespace fcf { 
  namespace NDetails {

    template <typename Ty = Nop, typename... TPack>
    struct CallPlaceHolderArgDetector {
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

  } // NDetails namespace
} // NDetails namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL_PLACE_HOLDER__NDETAILS__CALL_PLACE_HOLDER_ARG_DETECTOR_HPP___
