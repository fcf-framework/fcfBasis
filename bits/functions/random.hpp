#ifndef ___FCF_BASIS__BITS__FUNCTIONS__RANDOM_HPP___
#define ___FCF_BASIS__BITS__FUNCTIONS__RANDOM_HPP___

#include "../../InvariantCaller.hpp"
#include "../../Details/randomGenerator.hpp"

namespace fcf {

    template <typename Ty1, typename Ty2>
    Ty1 random(Ty1 a_min, Ty2 a_max) {
      double r = (double)Details::getRandomGenerator()() / (unsigned int)0xffffffff;
      return a_min + (((Ty1)a_max - a_min) * r);
    }

    namespace Details {
      struct RandomExecutor {
        template <typename TIterator, typename TyMin, typename TyMax>
        void call(TIterator a_begin, TIterator a_end, const TyMin& a_min, const TyMax& a_max) {
          for(; a_begin != a_end; ++a_begin) {
            *a_begin = random(a_min, a_max);
          }
        }
        template <typename TContainer, typename TIterator>
        void callA(TContainer& a_container, TIterator a_begin, TIterator a_end) {
          InvariantCaller<RandomExecutor>().rangeCall(a_begin,
                                                      a_end,
                                                      Type<TContainer, MinMaxSpecificator>().min(a_container),
                                                      Type<TContainer, MinMaxSpecificator>().max(a_container)
                                                      );
        }
      };
    }

    template <typename TIterator, typename TMinValue, typename TMaxValue >
    void random(TIterator a_begin, TIterator a_end, TMinValue a_min, TMaxValue a_max) {
      InvariantCaller<Details::RandomExecutor>().rangeCall(a_begin, a_end, a_min, a_max);
    }


   template <typename TContainer, typename TMinValue, typename TMaxValue >
    void random(TContainer& a_container, TMinValue a_min, TMaxValue a_max) {
      InvariantCaller<Details::RandomExecutor>().call(a_container, a_min, a_max);
    }

    template <typename TContainer >
    void random(TContainer& a_container) {
      InvariantCaller<Details::RandomExecutor>().callA<MinMaxSpecificator>(a_container);
    }

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__FUNCTIONS__RANDOM_HPP___

