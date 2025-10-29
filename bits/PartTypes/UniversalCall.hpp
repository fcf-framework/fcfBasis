#ifndef ___FCF_BASIS__BITS__PART_TYPES__UNIVERSAL_CALL_HPP___
#define ___FCF_BASIS__BITS__PART_TYPES__UNIVERSAL_CALL_HPP___

namespace fcf{

  class Variant;

  typedef Variant (*UniversalCall)(void*, Variant*, size_t);

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPES__UNIVERSAL_CALL_HPP___
