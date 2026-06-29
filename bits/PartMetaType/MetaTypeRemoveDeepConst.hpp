#ifndef _FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_REMOVE_DEEP_CONST_HPP___
#define _FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_REMOVE_DEEP_CONST_HPP___

namespace fcf{

  template <typename Ty>
  struct MetaTypeRemoveDeepConst{
    typedef Ty type;
  };

  template <typename Ty>
  struct MetaTypeRemoveDeepConst<const Ty>{
    typedef Ty type;
  };

  template <typename Ty>
  struct MetaTypeRemoveDeepConst<const Ty*>{
    typedef Ty* type;
  };

  template <typename Ty>
  struct MetaTypeRemoveDeepConst<const Ty* const*>{
    typedef Ty** type;
  };

  template <typename Ty>
  struct MetaTypeRemoveDeepConst<Ty* const*>{
    typedef Ty** type;
  };

  template <typename Ty>
  struct MetaTypeRemoveDeepConst<const Ty**>{
    typedef Ty** type;
  };

  template <typename Ty>
  struct MetaTypeRemoveDeepConst<Ty const &>{
    typedef Ty& type;
  };

  template <typename Ty>
  struct MetaTypeRemoveDeepConst<Ty const *&>{
    typedef Ty*& type;
  };

  template <typename Ty>
  struct MetaTypeRemoveDeepConst<Ty const **&>{
    typedef Ty**& type;
  };

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_REMOVE_DEEP_CONST_HPP___
