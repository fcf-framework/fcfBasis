#ifndef ___FCF_BASIS__BITS__PART_FOREACH__NDETAILS__TUPLE_FOREACH_HPP___
#define ___FCF_BASIS__BITS__PART_FOREACH__NDETAILS__TUPLE_FOREACH_HPP___

#include <tuple>

namespace fcf {
  namespace Details {

      template <typename TTuple, int Index, int Size>
      class TupleForeach{
        public:
          template <typename TContainer, typename TFunctor, typename ...TArgPack>
          inline void operator()(TContainer&& a_container, TFunctor&& a_functor, TArgPack&&... a_packArgs){
            a_functor(Index, std::get<Index>(a_container), a_packArgs...);
            TupleForeach<TTuple, Index+1, Size>()(a_container, a_functor, a_packArgs...);
          }
      };

      template <typename TTuple, int Size>
      class TupleForeach<TTuple, Size, Size>{
        public:
          template <typename TContainer, typename TFunctor, typename ...TArgPack>
          inline void operator()(TContainer&& /*a_container*/, TFunctor&& /*a_functor*/, TArgPack&&... /*a_packArgs*/){
          }
      };

  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_FOREACH__NDETAILS__TUPLE_FOREACH_HPP___
