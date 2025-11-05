#ifndef ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_TUPLE_INSERT_HPP___
#define ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_TUPLE_INSERT_HPP___

#include "NDetails/MetaTypeTupleInsertImpl.hpp"

namespace fcf {

    template <typename TTuple, typename TType, int Index>
    struct MetaTypeTupleInsert {
      typedef typename ::fcf::NDetails::MetaTypeTupleInsertImpl<TTuple, std::tuple_size<TTuple>::value, TType, Index>::type type;
    };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_TUPLE_INSERT_HPP___
