#ifndef ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_REMOVE_RIGHT_REFERENCE_HPP___
#define ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_REMOVE_RIGHT_REFERENCE_HPP___

namespace fcf{

  template<typename T>
  struct MetaTypeRemoveRightReference {
    using type = T;
  };

  template<typename T>
  struct MetaTypeRemoveRightReference<T&&> {
    using type = T;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_REMOVE_RIGHT_REFERENCE_HPP___
