#ifndef ___FCF_BASIS__BITS__PART_FOREACH__FOREACH_HPP___
#define ___FCF_BASIS__BITS__PART_FOREACH__FOREACH_HPP___

#include <tuple>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <list>
#include <vector>

#include "NDetails/TupleForeach.hpp"
#include "NDetails/DefaultForeach.hpp"

namespace fcf {

  template <typename Ty>
  class Foreach;

  template <typename Ty>
  class Foreach {
    public:
      template <typename TContainer, typename TFunctor, typename ...TArgPack>
      inline void operator()(TContainer&& a_container, TFunctor&& a_functor, TArgPack&&... a_packArgs) {
        typedef typename std::remove_reference<TContainer>::type container_type;
        NDetails::DefaultForeach<container_type>()(a_container, a_functor, a_packArgs...);
      }
  };

  template <typename... TPack>
  class Foreach< std::tuple<TPack...> >{
    public:
      typedef std::tuple<TPack...> container_type;

      template <typename TContainer, typename TFunctor, typename ...TArgPack>
      inline void operator()(TContainer&& a_container, TFunctor&& a_functor, TArgPack&&... a_packArgs){
        Details::TupleForeach<container_type, 0, sizeof...(TPack)>()(a_container, a_functor, a_packArgs...);
      }
  };

  template <typename... TPack>
  class Foreach< const std::tuple<TPack...> >{
    public:
      typedef std::tuple<TPack...> container_type;

      template <typename TContainer, typename TFunctor, typename ...TArgPack>
      inline void operator()(TContainer&& a_container, TFunctor&& a_functor, TArgPack&&... a_packArgs){
        Details::TupleForeach<container_type, 0, sizeof...(TPack)>()(a_container, a_functor, a_packArgs...);
      }
  };

  template <typename... TPack>
  class Foreach< std::unordered_map<TPack...> >{
    public:
      template <typename TContainer, typename TFunctor, typename ...TArgPack>
      inline void operator()(TContainer&& a_container, TFunctor&& a_functor, TArgPack&&... a_packArgs) {
        for(auto& pair : a_container){
          a_functor(pair.first, pair.second, a_packArgs...);
        }
      }
  };

  template <typename... TPack>
  class Foreach< std::map<TPack...> >{
    public:
      template <typename TContainer, typename TFunctor, typename ...TArgPack>
      inline void operator()(TContainer&& a_container, TFunctor&& a_functor, TArgPack&&... a_packArgs) {
        for(auto& pair : a_container){
          a_functor(pair.first, pair.second, a_packArgs...);
        }
      }
  };

  template <typename... TPack>
  class Foreach< std::set<TPack...> >{
    public:
      template <typename TContainer, typename TFunctor, typename ...TArgPack>
      inline void operator()(TContainer&& a_container, TFunctor&& a_functor, TArgPack&&... a_packArgs) {
        for(auto& item : a_container){
          a_functor(item, item, a_packArgs...);
        }
      }
  };

  template <typename... TPack>
  class Foreach< std::unordered_set<TPack...> >{
    public:
      template <typename TContainer, typename TFunctor, typename ...TArgPack>
      inline void operator()(TContainer&& a_container, TFunctor&& a_functor, TArgPack&&... a_packArgs) {
        for(auto& item : a_container){
          a_functor(item, item, a_packArgs...);
        }
      }
  };

  template <typename... TPack>
  class Foreach< std::vector<TPack...> >{
    public:
      template <typename TContainer, typename TFunctor, typename ...TArgPack>
      inline void operator()(TContainer&& a_container, TFunctor&& a_functor, TArgPack&&... a_packArgs) {
        for(size_t i = 0; i < a_container.size(); ++i){
          a_functor(i, a_container[i], a_packArgs...);
        }
      }
  };

  template <typename... TPack>
  class Foreach< std::list<TPack...> >{
    public:
      template <typename TContainer, typename TFunctor, typename ...TArgPack>
      inline void operator()(TContainer&& a_container, TFunctor&& a_functor, TArgPack&&... a_packArgs) {
        typename std::list<TPack...>::iterator it = a_container.begin();
        for(size_t i = 0; it != a_container.end(); ++i, ++it){
          a_functor(i, *it, a_packArgs...);
        }
      }
  };


} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_FOREACH__FOREACH_HPP___
