#ifndef ___FCF_BASIS__BITS__PART_FOREACH__NDETAILS__DEFAULT_FOREACH_HPP___
#define ___FCF_BASIS__BITS__PART_FOREACH__NDETAILS__DEFAULT_FOREACH_HPP___


#include "../../../bits/PartContainerAccess/ContainerAccess.hpp"
#include "../../../bits/PartContainerAccess/Cursor.hpp"

namespace fcf {
  namespace NDetails {

    template <typename TContainer, typename = void>
    struct DefaultForeach {
      template <typename TInputContainer, typename TFunctor, typename ...TArgPack>
      inline void operator()(TInputContainer&& a_container, TFunctor&& a_functor, TArgPack&&... a_packArgs) {
        auto begin = std::begin(a_container);
        auto end   = std::end(a_container);
        for(size_t i = 0; begin != end; ++begin, ++i) {
          a_functor(i, *begin, a_packArgs...);
        }
      }
    };

    template <typename TContainer>
    struct DefaultForeach<TContainer,  decltype(void(::fcf::Cursor<TContainer>())) > {
      template <typename TInputContainer, typename TFunctor, typename ...TArgPack>
      inline void operator()(TInputContainer&& a_container, TFunctor&& a_functor, TArgPack&&... a_packArgs) {
        typedef typename std::remove_reference<TInputContainer>::type container_type;
        ContainerAccess<container_type> ca(a_container);
        while(!ca.isEnd()){
          a_functor(ca.key(), ca.value(), a_packArgs...);
          ++ca;
        }
      }
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_FOREACH__NDETAILS__DEFAULT_FOREACH_HPP___
