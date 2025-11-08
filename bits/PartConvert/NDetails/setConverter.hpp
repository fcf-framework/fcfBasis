#ifndef ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__SET_CONVERTER_HPP___
#define ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__SET_CONVERTER_HPP___

#include "convertWrapper.hpp"
#include "../../../bits/PartType/Type.hpp"

namespace fcf::NDetails {

  template <typename TSource, typename TDestination>
  inline void setConverter() {
    ::fcf::Type<TSource>()._info->converters[::fcf::Type<TDestination>().index()] = (ConvertFunction)convertWrapper<TDestination, TSource>;
    ::fcf::Type<TDestination>()._info->backConverters[::fcf::Type<TSource>().index()] = (ConvertFunction)convertWrapper<TDestination, TSource>;
  }

} // fcf::NDetails namespace


#endif // #ifndef ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__SET_CONVERTER_HPP___
