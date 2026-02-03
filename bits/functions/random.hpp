#ifndef ___FCF_BASIS__BITS__FUNCTIONS__RANDOM_HPP___
#define ___FCF_BASIS__BITS__FUNCTIONS__RANDOM_HPP___

#include "../../Variant.hpp"
#include "../../ArgPlaceHolder.hpp"
#include "../../Details/randomGenerator.hpp"

namespace fcf {

    template <typename Ty1, typename Ty2>
    Ty1 random(Ty1 a_min, Ty2 a_max) {
      double r = (double)Details::getRandomGenerator()() / (unsigned int)0xffffffff;
      return a_min + (((Ty1)a_max - a_min) * r);
    }

    template <typename TItem, typename TValue>
    void random(TItem* a_begin, TItem* a_end, const TValue& a_min, const TValue& a_max) {
      for (; a_begin != a_end; ++a_begin) {
        double r = (double)Details::getRandomGenerator()() / (unsigned int)0xffffffff;
        *a_begin = a_min + ((a_max - a_min) * r);
      }
    }

} // fcf namespace


#ifdef FCF_BASIS_IMPLEMENTATION
  FCF_DECLARE_FUNCTION(random,
                       "engine_cpu",
                       fcf::random,
                       void(*) (float*, float*, const float&, const float&),
                       (
                        (fcf::CallOptions, 1, fcf::CallArgumentOptions<fcf::CAO_RESOLVE_POINTER|fcf::CAO_PAIR_ITERATION_POINTER|fcf::CAO_PAIR_SEGMENTATION>),
                        (fcf::MinMaxSpecificator, 1, float*, float*, fcf::Arg1, fcf::Arg2)
                       ),
                      );
#endif // #ifdef FCF_BASIS_IMPLEMENTATION

#ifdef FCF_BASIS_IMPLEMENTATION
  FCF_DECLARE_FUNCTION(random, 
                        "engine_cpu", 
                        fcf::random, 
                        void(*) (int*, int*, const int&, const int&),
                        (
                          (fcf::CallOptions, 1, fcf::CallArgumentOptions<fcf::CAO_RESOLVE_POINTER|fcf::CAO_PAIR_ITERATION_POINTER|fcf::CAO_PAIR_SEGMENTATION>),
                        ), 
                        );
#endif // #ifdef FCF_BASIS_IMPLEMENTATION

#endif // #ifndef ___FCF_BASIS__BITS__FUNCTIONS__RANDOM_HPP___

