#ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_DETAILS_PACK_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__CALL_DETAILS_PACK_HPP___

#include <tuple>
#include "../../bits/PartTypes/Nop.hpp"

namespace fcf{

  template <typename TSignature1 = Nop, typename TSignature2 = Nop, typename TSignature3 = Nop>
  class CallDetailsPack {
    public:
      typedef std::tuple<TSignature1, TSignature2, TSignature3> signatures_type;
  };

  template <typename TSignature1, typename TSignature2>
  class CallDetailsPack<TSignature1, TSignature2, Nop> {
    public:
      typedef std::tuple<TSignature1, TSignature2> signatures_type;
  };

  template <typename TSignature1>
  class CallDetailsPack<TSignature1, Nop, Nop> {
    public:
      typedef std::tuple<TSignature1> signatures_type;
  };

  template <>
  class CallDetailsPack<Nop, Nop, Nop> {
    public:
      typedef std::tuple<> signatures_type;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_DETAILS_PACK_HPP___
