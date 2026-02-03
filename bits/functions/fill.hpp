#ifndef ___FCF_BASIS__BITS__FUNCTIONS__FILL_HPP___
#define ___FCF_BASIS__BITS__FUNCTIONS__FILL_HPP___

#include "../../ArgPlaceHolder.hpp"
#include "../../call.hpp"
namespace fcf {

    template <typename TIterator, typename TValue>
    void fill(TIterator a_begin, TIterator a_end, TValue a_value) {
      for(; a_begin != a_end; ++a_begin) {
        *a_begin = a_value;
      }
    }

} // fcf namespace




#ifdef FCF_BASIS_IMPLEMENTATION
  FCF_DECLARE_FUNCTION(fill,
                       "engine_cpu",
                       fcf::fill,
                       void(*) (int*, int*, int),
                       (
                         (fcf::CallOptions, 1, fcf::CallArgumentOptions<fcf::CAO_RESOLVE_POINTER|fcf::CAO_PAIR_ITERATION_POINTER|fcf::CAO_PAIR_SEGMENTATION>),
                         (fcf::ValueSpecificator, 1, int*, int*, fcf::Arg1)
                       ),
                      );

  FCF_DECLARE_FUNCTION(fill,
                   "engine_cpu",
                   fcf::fill,
                   void(*) (std::string*, std::string*, std::string),
                   (
                    (fcf::CallOptions, 1, fcf::CallArgumentOptions<fcf::CAO_RESOLVE_POINTER|fcf::CAO_PAIR_ITERATION_POINTER|fcf::CAO_PAIR_SEGMENTATION>),
                    (fcf::ValueSpecificator, 1, std::string*, std::string*, fcf::Arg1)
                   ),
                  );

#endif // #ifdef FCF_BASIS_IMPLEMENTATION



#endif // #ifndef ___FCF_BASIS__BITS__FUNCTIONS__FILL_HPP___

