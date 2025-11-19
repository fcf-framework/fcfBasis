#ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_PLACE_HOLDER_SIGNATURES_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_PLACE_HOLDER_SIGNATURES_HPP___

#include <tuple>
#include "../../../Nop.hpp"

namespace fcf {
  namespace NDetails {

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

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_PLACE_HOLDER_SIGNATURES_HPP___
