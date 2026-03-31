#ifndef ___FCF_BASIS__TEST__TESTS__BITS__RANDOM_HPP___
#define ___FCF_BASIS__TEST__TESTS__BITS__RANDOM_HPP___

#include <fcfBasis/PartCall.hpp>
#include <fcfBasis/Variant.hpp>
#include <fcfBasis/Details/randomGenerator.hpp>

namespace fcf {

    #ifdef _MSC_VER
      #pragma warning(push)
      #pragma warning(disable : 4244)
    #endif
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
    #ifdef _MSC_VER
      #pragma warning(pop)
    #endif

} // fcf namespace


#ifdef FCF_BASIS_IMPLEMENTATION
  FCF_DECLARE_FUNCTION(random,
                       "engine_cpu",
                       fcf::random,
                       void(*) (float*, float*, const float&, const float&),
                       (
                        (fcf::CallOptions, 1, fcf::CallArgumentOptions<fcf::CAO_PAIR_ITERATION_POINTER|fcf::CAO_PAIR_SEGMENTATION>),
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
                          (fcf::CallOptions, 1, fcf::CallArgumentOptions<fcf::CAO_PAIR_ITERATION_POINTER|fcf::CAO_PAIR_SEGMENTATION>),
                        ), 
                        );
#endif // #ifdef FCF_BASIS_IMPLEMENTATION

#endif // #ifndef ___FCF_BASIS__TEST__TESTS__BITS__RANDOM_HPP___
