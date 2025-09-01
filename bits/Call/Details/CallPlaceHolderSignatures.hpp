#ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_PLACE_HOLDER_SIGNATURES_HPP___
#define ___FCF__BASIS__BITS__CALL__DETAILS__CALL_PLACE_HOLDER_SIGNATURES_HPP___

#include <tuple>
#include "../../../Nop.hpp"

namespace fcf {
  namespace Details {

    template <typename TSignature1 = Nop, typename TSignature2 = Nop, typename TSignature3 = Nop>
    class CallPlaceHolderSignatures {
      public:
        typedef std::tuple<TSignature1, TSignature2, TSignature3> signatures_type;
    };

    template <typename TSignature1, typename TSignature2>
    class CallPlaceHolderSignatures<TSignature1, TSignature2, Nop> {
      public:
        typedef std::tuple<TSignature1, TSignature2> signatures_type;
    };

    template <typename TSignature1>
    class CallPlaceHolderSignatures<TSignature1, Nop, Nop> {
      public:
        typedef std::tuple<TSignature1> signatures_type;
    };

    template <>
    class CallPlaceHolderSignatures<Nop, Nop, Nop> {
      public:
        typedef std::tuple<> signatures_type;
    };

  } // namespace Details
} // namespace fcf

#endif // #ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_PLACE_HOLDER_SIGNATURES_HPP___
