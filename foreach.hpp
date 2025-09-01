#ifndef ___FCF__BASIS__FOREACH_HPP___
#define ___FCF__BASIS__FOREACH_HPP___

#include "bits/Foreach/Foreach.hpp"

namespace fcf {

  template <typename TContainer, typename TFunctor>
  void foreach(TContainer& a_container, TFunctor&& a_functor){
    Foreach<TContainer>()(a_container, a_functor);
  }

  template <typename TContainer, typename TFunctor>
  void foreach(TContainer& a_container, const TFunctor& a_functor){
    Foreach<TContainer>()(a_container, a_functor);
  }

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__FOREACH_HPP___

