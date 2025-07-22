#ifndef ___FCF_BASIS__TEMPLATE__DETAILS__TUPLE_INSERT_IMPL_HPP___
#define ___FCF_BASIS__TEMPLATE__DETAILS__TUPLE_INSERT_IMPL_HPP___

#include <stddef.h>
#include <tuple>
#include "../Sequence.hpp"

namespace fcf {
  namespace Template {
    namespace Details {

     template <typename TTuple, size_t TupleSize, typename TType, int Index>
      struct TupleInsertImpl {
        typedef typename Template::Sequence<0, Index-1>::type                                 left_sequence_type;
        typedef typename Template::Sequence<Index, std::tuple_size<TTuple>::value - 1 >::type right_sequence_type;
        template<int... LeftSeqPack, int... RightSeqPack>
        static auto gen(Template::Sequence<0, LeftSeqPack...>, Template::Sequence<Index, RightSeqPack...>) -> decltype(std::tuple<
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

      template <typename TTuple, size_t TupleSize, typename TType>
      struct TupleInsertImpl<TTuple, TupleSize, TType, 0> {
        typedef typename Template::Sequence<0, std::tuple_size<TTuple>::value - 1 >::type right_sequence_type;
        template<int... RightSeqPack>
        static auto gen(Template::Sequence<0, RightSeqPack...>) -> decltype(std::tuple<
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


      template <typename TTuple, typename TType>
      struct TupleInsertImpl<TTuple, 0, TType, 0> {
        typedef std::tuple<TType> type;
      };

    } // Details namespace
  } // Template namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__TEMPLATE__DETAILS__TUPLE_INSERT_IMPL_HPP___
