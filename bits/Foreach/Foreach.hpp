#ifndef ___FCF__BASIS__BITS__FOREACH__FOREACH_HPP___
#define ___FCF__BASIS__BITS__FOREACH__FOREACH_HPP___

#include <tuple>
#include "Details/TupleForeach.hpp"

namespace fcf {

  template <typename Ty>
  class Foreach;

  template <typename... TPack>
  class Foreach< std::tuple<TPack...> >{
    public:
      typedef std::tuple<TPack...> container_type;

      template <typename TFunctor>
      void operator()(container_type& a_container, TFunctor&& a_functor){
        Details::TupleForeach<container_type, 0, sizeof...(TPack)>()(a_container, a_functor);
      }

      template <typename TFunctor>
      void operator()(container_type& a_container, const TFunctor& a_functor){
        Details::TupleForeach<container_type, 0, sizeof...(TPack)>()(a_container, a_functor);
      }

  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__FOREACH__FOREACH_HPP___

