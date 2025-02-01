#ifndef ___FCF_BASIS__CONVERT_HPP___
#define ___FCF_BASIS__CONVERT_HPP___

#include "Converter.hpp"

namespace fcf {

  template <typename TResult, typename TSource>
  TResult convert(const TSource& a_source){
    TResult result;
    Converter<TResult, TSource>()(result, a_source);
    return result;
  }

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__CONVERT_HPP___

