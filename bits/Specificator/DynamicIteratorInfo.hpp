#ifndef ___FCF__BASIS__BITS__SPECIFICATOR__DYNAMIC_ITERATOR_INFO_HPP___
#define ___FCF__BASIS__BITS__SPECIFICATOR__DYNAMIC_ITERATOR_INFO_HPP___

#include "../../Variant.hpp"
#include "DynamicIteratorInfoDecl.hpp"

namespace fcf {

  struct DynamicIteratorInfo {
    unsigned int         flags; // enum DynamicIteratorFlags
    unsigned int         type;
    size_t               size;
    Variant              key;
    void*                value;
    Variant              iterator;
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__SPECIFICATOR__DYNAMIC_ITERATOR_INFO_HPP___
