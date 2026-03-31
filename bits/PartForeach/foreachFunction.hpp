#ifndef ___FCF_BASIS__BITS__PART_FOREACH__FOREACH_FUNCTION_HPP___
#define ___FCF_BASIS__BITS__PART_FOREACH__FOREACH_FUNCTION_HPP___

#include "Foreach.hpp"

namespace fcf{
  template <typename TContainer, typename TFunctor, typename ...TPack>
  void foreach(TContainer&& a_container, TFunctor&& a_functor, TPack&&... a_packArgs){
    typedef typename std::remove_reference<TContainer>::type container_type;
    Foreach<container_type>()(a_container, a_functor, a_packArgs...);
  }
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_FOREACH__FOREACH_FUNCTION_HPP___
