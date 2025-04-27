#ifndef ___FCF_BASIS__BITS__CONVERT__CONVERT_HPP___
#define ___FCF_BASIS__BITS__CONVERT__CONVERT_HPP___

#include "ConvertOptions.hpp"
#include "Converter.hpp"

namespace fcf {

  template <typename TResult, typename TSource>
  TResult convert(const TSource& a_source, ConvertOptions* a_options = 0) {
    TResult result;
    Converter<TResult, TSource>()(result, a_source, a_options);
    return result;
  }


  template <typename TDest, typename TSource>
  void convert(TDest& a_dst, const TSource& a_source, ConvertOptions* a_options = 0) {
    Converter<TDest, TSource>()(a_dst, a_source, a_options);
  }

} // fcf namespace


#endif // #ifndef ___FCF_BASIS__BITS__CONVERT__CONVERT_HPP___
