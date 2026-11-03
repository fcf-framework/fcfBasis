#ifndef _FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_CLEAR_TYPE_HPP___
#define _FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_CLEAR_TYPE_HPP___

#include <type_traits>

namespace fcf{

  template <typename Ty>
  struct MetaTypeClearType{
    typedef typename std::remove_const<
              typename std::remove_reference<
                typename std::remove_pointer<
                  typename std::remove_const<
                    typename std::remove_reference<
                      typename std::remove_pointer<
                        typename std::remove_const<
                          Ty
                        >::type
                      >::type
                    >::type
                  >::type
                >::type
              >::type
            >::type Type;
  };

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_CLEAR_TYPE_HPP___
