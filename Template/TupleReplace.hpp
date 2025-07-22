#ifndef ___FCF_BASIS__TEMPLATE__TUPLE_REPLACE_HPP___
#define ___FCF_BASIS__TEMPLATE__TUPLE_REPLACE_HPP___

#include <type_traits>
#include <tuple>
#include "Sequence.hpp"

namespace fcf {
  namespace Template {

    template <typename TTuple, typename TType, int Index>
    struct TupleReplace {
      typedef typename Template::Sequence<0, Index-1>::type                                   left_sequence_type;
      typedef typename Template::Sequence<Index+1, std::tuple_size<TTuple>::value - 1 >::type right_sequence_type;
      template<int... LeftSeqPack, int... RightSeqPack>
      static auto gen(Template::Sequence<0, LeftSeqPack...>, Template::Sequence<Index+1, RightSeqPack...>) -> decltype(std::tuple<
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

    template <typename TTuple, typename TType>
    struct TupleReplace<TTuple, TType, 0> {
      typedef typename Template::Sequence<1, std::tuple_size<TTuple>::value - 1 >::type right_sequence_type;
      template<int... LeftSeqPack, int... RightSeqPack>
      static auto gen(Template::Sequence<1, RightSeqPack...>) -> decltype(std::tuple<
            TType,
            typename std::remove_reference< decltype(std::get<RightSeqPack>(TTuple())) >::type...
          >()) {
        return std::tuple<
            TType,
            typename std::remove_reference< decltype(std::get<RightSeqPack>(TTuple())) >::type...
          >();
      }
      typedef decltype(gen(right_sequence_type())) type;
    };

  } // Template namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__TEMPLATE__TUPLE_REPLACE_HPP___
