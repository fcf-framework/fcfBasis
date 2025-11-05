#ifndef ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_MAX_TYPE_SIZE_HPP___
#define ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_MAX_TYPE_SIZE_HPP___

namespace fcf{

  template <typename Ty, typename... TPack>
  struct MetaTypeMaxTypeSize {
    enum { size =  sizeof(Ty) > MetaTypeMaxTypeSize<TPack...>::size ? sizeof(Ty) : MetaTypeMaxTypeSize<TPack...>::size };
  };

  template <typename Ty>
  struct MetaTypeMaxTypeSize<Ty> {
    enum { size =  sizeof(Ty) };
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_MAX_TYPE_SIZE_HPP___
