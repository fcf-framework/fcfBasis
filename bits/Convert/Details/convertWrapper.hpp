#ifndef ___FCF_BASIS__BITS__CONVERT__DETAILS__CONVERT_WRAPPER_HPP___
#define ___FCF_BASIS__BITS__CONVERT__DETAILS__CONVERT_WRAPPER_HPP___

#include "../ConvertOptions.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace Convert {

        template <typename TDest, typename TSrc>
        void convertWrapper(TDest* a_dst, const TSrc* a_src, ConvertOptions* a_options) {
          Converter<TDest, TSrc>()(*a_dst, *a_src, a_options);
        }

      } // Convert namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__CONVERT__DETAILS__CONVERT_WRAPPER_HPP___

