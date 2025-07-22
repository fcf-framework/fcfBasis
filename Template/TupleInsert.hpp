#ifndef ___FCF_BASIS__TEMPLATE__TUPLE_INSERT_HPP___
#define ___FCF_BASIS__TEMPLATE__TUPLE_INSERT_HPP___

#include "Details/TupleInsertImpl.hpp"

namespace fcf {
  namespace Template {

    template <typename TTuple, typename TType, int Index>
    struct TupleInsert {
      typedef typename ::fcf::Template::Details::TupleInsertImpl<TTuple, std::tuple_size<TTuple>::value, TType, Index>::type type;
    };

  } // Template namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__TEMPLATE__TUPLE_INSERT_HPP___
