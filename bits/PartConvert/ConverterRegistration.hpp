#ifndef ___FCF_BASIS__BITS__PART_CONVERT__CONVERT_REGISTRATION_HPP___
#define ___FCF_BASIS__BITS__PART_CONVERT__CONVERT_REGISTRATION_HPP___

#include "NDetails/convertWrapper.hpp"
#include "../../bits/PartType/Type.hpp"

namespace fcf{

  FCF_ATTRIBUTE_MINIMIZE_BEGIN
  template <typename TDestination, typename TSource>
  inline void FCF_ATTRIBUTE_MINIMIZE converterRegistration() {
    TypeInfo* srcti = Type<TSource>()._info;
    TypeInfo* dstti = Type<TDestination>()._info;
    srcti->converters[dstti->index] = (ConvertFunction)NDetails::convertWrapper<TDestination, TSource>;
    dstti->backConverters[srcti->index] = (ConvertFunction)NDetails::convertWrapper<TDestination, TSource>;
  }
  FCF_ATTRIBUTE_MINIMIZE_END

  template <typename TDestination, typename TSource>
  struct ConverterRegistration{
    inline ConverterRegistration() {
      converterRegistration<TDestination, TSource>();
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CONVERT__CONVERT_REGISTRATION_HPP___
