#ifndef ___FCF_BASIS__TEMPLATE__DETAILS__TUPLE_INSERT_IMPL_HPP___
#define ___FCF_BASIS__TEMPLATE__DETAILS__TUPLE_INSERT_IMPL_HPP___

#include <stddef.h>
#include <tuple>
#include "../Sequence.hpp"

namespace fcf {
  namespace Template {
    namespace Details {

     template <typename TTuple, int TupleSize, typename TType, int Index>
      struct TupleInsertImpl {
        typedef typename Template::Sequence<0, Index>::type                               left_sequence_type;
        typedef typename Template::Sequence<Index, std::tuple_size<TTuple>::value >::type right_sequence_type;
        template<int... LeftSeqPack, int... RightSeqPack>
        static auto gen(Template::Sequence<LeftSeqPack...>, Template::Sequence<RightSeqPack...>) -> decltype(std::tuple<
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

    } // Details namespace
  } // Template namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__TEMPLATE__DETAILS__TUPLE_INSERT_IMPL_HPP___
