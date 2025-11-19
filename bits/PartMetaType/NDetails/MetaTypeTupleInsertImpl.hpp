#ifndef ___FCF_BASIS__BITS__PART_META_TYPE__NDETAILS__META_TYPE_TUPLE_INSERT_IMPL_HPP___
#define ___FCF_BASIS__BITS__PART_META_TYPE__NDETAILS__META_TYPE_TUPLE_INSERT_IMPL_HPP___

#include <stddef.h>
#include <tuple>
#include "../MetaTypeSequence.hpp"

namespace fcf {
  namespace NDetails {

    template <typename TTuple, int TupleSize, typename TType, int Index>
    struct MetaTypeTupleInsertImpl {
      typedef typename MetaTypeSequence<0, Index>::type                               left_sequence_type;
      typedef typename MetaTypeSequence<Index, std::tuple_size<TTuple>::value >::type right_sequence_type;
      template<int... LeftSeqPack, int... RightSeqPack>
      static auto gen(MetaTypeSequence<LeftSeqPack...>, MetaTypeSequence<RightSeqPack...>) -> decltype(std::tuple<
            typename std::remove_reference< typename std::tuple_element<LeftSeqPack, TTuple>::type >::type...,
            TType,
            typename std::remove_reference< typename std::tuple_element<RightSeqPack, TTuple>::type >::type...
          >()) {
        return std::tuple<
            typename std::remove_reference< typename std::tuple_element<LeftSeqPack, TTuple>::type >::type...,
            TType,
            typename std::remove_reference< typename std::tuple_element<RightSeqPack, TTuple>::type >::type...
          >();
      }
      typedef decltype(gen(left_sequence_type(), right_sequence_type())) type;
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_META_TYPE__NDETAILS__META_TYPE_TUPLE_INSERT_IMPL_HPP___
