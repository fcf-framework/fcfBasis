#ifndef _FCF_BASIS__BITS__PART_CONVERT__NDETAILS__CONVERT_WRAPPER_HPP___
#define _FCF_BASIS__BITS__PART_CONVERT__NDETAILS__CONVERT_WRAPPER_HPP___

#include "../ConvertOptions.hpp"
#include "../ConvertSelector.hpp"
namespace fcf { 
  namespace NDetails {

    template <typename TDest, typename TSrc>
    void convertWrapper(TDest* a_dst, const TSrc* a_src, ConvertOptions& a_options, Error& a_error) {
      ConvertSelector<TDest, TSrc>()(*a_dst, *a_src, a_options, a_error);
    }

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_CONVERT__NDETAILS__CONVERT_WRAPPER_HPP___
