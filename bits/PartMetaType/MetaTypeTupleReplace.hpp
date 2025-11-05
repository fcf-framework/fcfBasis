#ifndef ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_TUPLE_REPLACE_HPP___
#define ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_TUPLE_REPLACE_HPP___

#include <type_traits>
#include <tuple>
#include "MetaTypeSequence.hpp"

namespace fcf{

  template <typename TTuple, typename TType, int Index>
  struct MetaTypeTupleReplace {
    typedef typename MetaTypeSequence<0, Index>::type                                   left_sequence_type;
    typedef typename MetaTypeSequence<Index+1, std::tuple_size<TTuple>::value >::type right_sequence_type;
    template<int... LeftSeqPack, int... RightSeqPack>
    static auto gen(MetaTypeSequence<LeftSeqPack...>, MetaTypeSequence<RightSeqPack...>) -> decltype(std::tuple<
          typename std::remove_reference< decltype(std::get<LeftSeqPack>(TTuple())) >::type...,
          TType,
          typename std::remove_reference< decltype(std::get<RightSeqPack>(TTuple())) >::type...
        >()) {
      return std::tuple<
          typename std::remove_reference< decltype(std::get<LeftSeqPack>(TTuple())) >::type...,
          TType,
          typename std::remove_reference< decltype(std::get<RightSeqPack>(TTuple())) >::type...
        >();
    }
    typedef decltype(gen(left_sequence_type(), right_sequence_type())) type;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_TUPLE_REPLACE_HPP___
