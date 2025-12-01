#ifndef ___FCF_BASIS__BITS__PART_CONVERT__CONVERT_HPP___
#define ___FCF_BASIS__BITS__PART_CONVERT__CONVERT_HPP___

#include "ConvertOptions.hpp"
#include "ConvertSelector.hpp"

namespace fcf {

  template <typename TResult, typename TSource>
  TResult convert(const TSource& a_source, ConvertOptions* a_options = 0) {
    TResult result;
    ConvertSelector<TResult, TSource>()(result, a_source, a_options);
    return result;
  }

  template <typename TDest, typename TSource>
  void convert(TDest& a_dst, const TSource& a_source, ConvertOptions* a_options = 0) {
    ConvertSelector<TDest, TSource>()(a_dst, a_source, a_options);
  }

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CONVERT__CONVERT_HPP___
