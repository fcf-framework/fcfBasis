#ifndef ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__SET_CONVERTER_HPP___
#define ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__SET_CONVERTER_HPP___

#include "convertWrapper.hpp"
#include "../../../bits/PartType/Type.hpp"

namespace fcf { 
  namespace NDetails {

    #ifdef FCF_BASIS_IMPLEMENTATION
      void setConverteImpl(TypeInfo* a_firtTypeInfo, TypeInfo* a_secTypeInfo, unsigned int a_dstIndex, unsigned int a_srcIndex, ConvertFunction a_dstFunction, ConvertFunction a_srcFunction) {
        a_firtTypeInfo->converters[a_dstIndex] = a_dstFunction;
        a_secTypeInfo->backConverters[a_srcIndex] = a_srcFunction;
      }
    #else
      void setConverteImpl(TypeInfo* a_firtTypeInfo, TypeInfo* a_secTypeInfo, unsigned int a_dstIndex, unsigned int a_srcIndex, ConvertFunction a_dstFunction, ConvertFunction a_srcFunction);
    #endif


    FCF_ATTRIBUTE_MINIMIZE_BEGIN
    template <typename TDestination, typename TSource>
    void FCF_ATTRIBUTE_MINIMIZE setConverter() {
      setConverteImpl(::fcf::Type<TSource>()._info, ::fcf::Type<TDestination>()._info, ::fcf::Type<TDestination>().index(), ::fcf::Type<TSource>().index(), 
          (ConvertFunction)convertWrapper<TDestination, TSource>,
          (ConvertFunction)convertWrapper<TDestination, TSource>);
    }
    FCF_ATTRIBUTE_MINIMIZE_END

  } // NDetails namespace
} // fcf namespace


#endif // #ifndef ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__SET_CONVERTER_HPP___
