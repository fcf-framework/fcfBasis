#ifndef ___FCF__BASIS__BITS__FOREACH__DETAILS__TUPLE_FOREACH_HPP___
#define ___FCF__BASIS__BITS__FOREACH__DETAILS__TUPLE_FOREACH_HPP___

#include <tuple>

namespace fcf {
  namespace Details {

      template <typename TTuple, int Index, int Size>
      class TupleForeach{
        public:
          template <typename TFunctor>
          void operator()(TTuple& a_container, TFunctor&& a_functor){
            a_functor(a_container, Index, std::get<Index>(a_container));
            TupleForeach<TTuple, Index+1, Size>()(a_container, a_functor);
          }
          template <typename TFunctor>
          void operator()(TTuple& a_container, const TFunctor& a_functor){
            a_functor(a_container, Index, std::get<Index>(a_container));
            TupleForeach<TTuple, Index+1, Size>()(a_container, a_functor);
          }
      };

      template <typename TTuple, int Size>
      class TupleForeach<TTuple, Size, Size>{
        public:
          template <typename TFunctor>
          void operator()(TTuple& a_container, TFunctor&& a_functor){
          }
          template <typename TFunctor>
          void operator()(TTuple& a_container, const TFunctor& a_functor){
          }
      };

  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__FOREACH__DETAILS__TUPLE_FOREACH_HPP___

