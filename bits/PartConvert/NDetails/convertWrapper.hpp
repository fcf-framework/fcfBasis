#ifndef ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__CONVERT_WRAPPER_HPP___
#define ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__CONVERT_WRAPPER_HPP___

#include "../ConvertOptions.hpp"

namespace fcf { 
  namespace NDetails {

    template <typename TDest, typename TSrc>
    void convertWrapper(TDest* a_dst, const TSrc* a_src, ConvertOptions* a_options) {
      Converter<TDest, TSrc>()(*a_dst, *a_src, a_options);
    }

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__CONVERT_WRAPPER_HPP___
