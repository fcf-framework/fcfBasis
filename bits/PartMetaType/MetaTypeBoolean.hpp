#ifndef ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_BOOLEAN_HPP___
#define ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_BOOLEAN_HPP___

#include <type_traits>

namespace fcf{

  template <bool ValueArg>
  struct MetaTypeBoolean{
    typedef std::true_type Type;
    enum { Value = 1 };
  };

  template <>
  struct MetaTypeBoolean<false>{
    typedef std::false_type Type;
    enum { Value = 0 };
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_BOOLEAN_HPP___
