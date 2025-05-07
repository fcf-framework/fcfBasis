#ifndef ___FCF__BASIS__BITS__SPECIFICATOR__DYNAMIC_ITERATOR_FLAGS_HPP___
#define ___FCF__BASIS__BITS__SPECIFICATOR__DYNAMIC_ITERATOR_FLAGS_HPP___

namespace fcf {
  enum DynamicIteratorFlags {
    DIF_ITERATION = 0x01,
    DIF_RESOLVE   = 0x02,
    DIF_INFO      = 0x04,
    DIF_GET_TYPE  = 0x0100,
    DIF_GET_KEY   = 0x0200,
    DIF_GET_VALUE = 0x0400,
    DIF_GET_SIZE  = 0x0800,
  };
} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__SPECIFICATOR__DYNAMIC_ITERATOR_FLAGS_HPP___
