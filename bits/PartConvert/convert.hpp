#ifndef _FCF_BASIS__BITS__PART_CONVERT__CONVERT_HPP___
#define _FCF_BASIS__BITS__PART_CONVERT__CONVERT_HPP___

#include "ConvertOptions.hpp"
#include "ConvertSelector.hpp"

namespace fcf {

  template <typename TResult, typename TSource>
  TResult convert(const TSource& a_source, Error& a_error) {
    TResult result;
    ConvertSelector<TResult, TSource>()(result, a_source, 0, a_error);
    return result;
  }

  template <typename TResult, typename TSource>
  inline TResult convert(const TSource& a_source, Error&& a_error = Error{true}) {
    return convert<TResult>(a_source, a_error);
  }



  template <typename TResult, typename TSource>
  TResult convert(const TSource& a_source, ConvertOptions* a_options, Error& a_error) {
    TResult result;
    ConvertSelector<TResult, TSource>()(result, a_source, a_options, a_error);
    return result;
  }

  template <typename TResult, typename TSource>
  inline TResult convert(const TSource& a_source, ConvertOptions* a_options, Error&& a_error = Error{true}) {
    return convert<TResult>(a_source, a_options, a_error);
  }



  template <typename TDest, typename TSource>
  void convert(TDest& a_dst, const TSource& a_source, ConvertOptions* a_options, Error& a_error) {
    ConvertSelector<TDest, TSource>()(a_dst, a_source, a_options, a_error);
  }

  template <typename TDest, typename TSource>
  inline void convert(TDest& a_dst, const TSource& a_source, ConvertOptions* a_options, Error&& a_error = Error{true}) {
    convert(a_dst, a_source, a_options, a_error);
  }



  template <typename TDest, typename TSource>
  void convert(TDest& a_dst, const TSource& a_source, Error& a_error) {
    ConvertSelector<TDest, TSource>()(a_dst, a_source, nullptr, a_error);
  }

  template <typename TDest, typename TSource>
  inline void convert(TDest& a_dst, const TSource& a_source, Error&& a_error = Error{true}) {
    return convert(a_dst, a_source, a_error);
  }

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_CONVERT__CONVERT_HPP___
