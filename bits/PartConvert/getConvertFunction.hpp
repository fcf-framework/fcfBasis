#ifndef ___FCF_BASIS__BITS__PART_CONVERT__GET_CONVERT_FUNCTION_HPP___
#define ___FCF_BASIS__BITS__PART_CONVERT__GET_CONVERT_FUNCTION_HPP___

#include "../../macro.hpp"
#include "../../error.hpp"
#include "ConvertFunction.hpp"
#include "../../bits/PartType/TypeStorage.hpp"
#include "../../bits/PartType/Type.hpp"
#include "../../Exception.hpp"

namespace fcf {

  FCF_BASIS_DECL_EXPORT ConvertFunction getConvertFunction(unsigned int a_destinationTypeIndex, unsigned int a_sourceTypeIndex);
  FCF_BASIS_DECL_EXPORT ConvertFunction getConvertFunction(unsigned int a_destinationTypeIndex, unsigned int a_sourceTypeIndex, int* a_error);

  #ifdef FCF_BASIS_IMPLEMENTATION
    ConvertFunction getConvertFunction(unsigned int a_destinationTypeIndex, unsigned int a_sourceTypeIndex) {
      a_destinationTypeIndex = TypeIndexConverter<>::getDataIndex(a_destinationTypeIndex);
      a_sourceTypeIndex = TypeIndexConverter<>::getDataIndex(a_sourceTypeIndex);
      do {
        const TypeInfo* pti = fcf::typeStorage.get(a_sourceTypeIndex);
        if (!pti)
          break;
        const ::fcf::TypeInfo::Converters& converters = pti->converters; 
        ::fcf::TypeInfo::Converters::const_iterator convIt = converters.find(a_destinationTypeIndex);
        if (convIt == converters.end()) {
          break;
        }
        return (ConvertFunction)convIt->second;
      } while(false);
      const TypeInfo* destinationTypeInfo = getTypeInfo(a_destinationTypeIndex);
      const TypeInfo* sourceTypeInfo = getTypeInfo(a_sourceTypeIndex);
      throw ConversionNotFoundException(__FILE__, __LINE__, destinationTypeInfo->name, sourceTypeInfo->name);
    }
  #endif

  #ifdef FCF_BASIS_IMPLEMENTATION
    ConvertFunction getConvertFunction(unsigned int a_destinationTypeIndex, unsigned int a_sourceTypeIndex, int* a_error) {
      a_destinationTypeIndex = TypeIndexConverter<>::getDataIndex(a_destinationTypeIndex);
      a_sourceTypeIndex = TypeIndexConverter<>::getDataIndex(a_sourceTypeIndex);
      do {
        const TypeInfo* pti = fcf::typeStorage.get(a_sourceTypeIndex);
        if (!pti)
          break;
        const ::fcf::TypeInfo::Converters& converters = pti->converters; 
        ::fcf::TypeInfo::Converters::const_iterator convIt = converters.find(a_destinationTypeIndex);
        if (convIt == converters.end()) {
          break;
        }
        if (a_error) {
          *a_error = 0;
        }
        return (ConvertFunction)convIt->second;
      } while(false);
      if (a_error) {
        *a_error = FCF_ERROR_FUNCTION_NOT_FOUND;
      }
      return 0;
    }
  #endif

  template <typename TDestination>
  ConvertFunction getConvertFunctionByDestination(unsigned int a_sourceTypeIndex){
    a_sourceTypeIndex = TypeIndexConverter<>::getDataIndex(a_sourceTypeIndex);
    const ::fcf::TypeInfo::Converters& converters = Type<TDestination>().backConverters(); 
    ::fcf::TypeInfo::Converters::const_iterator convIt = converters.find(a_sourceTypeIndex);
    if (convIt == converters.end()) {
      const TypeInfo* destinationTypeInfo = Type<TDestination>(). getTypeInfo();
      const TypeInfo* sourceTypeInfo = getTypeInfo(a_sourceTypeIndex);
      throw ConversionNotFoundException(__FILE__, __LINE__, destinationTypeInfo->name, sourceTypeInfo->name);
    }
    return (ConvertFunction)convIt->second;
  }

  template <typename TDestination>
  ConvertFunction getConvertFunctionByDestination(unsigned int a_sourceTypeIndex, int* a_error){
    a_sourceTypeIndex = TypeIndexConverter<>::getDataIndex(a_sourceTypeIndex);
    const ::fcf::TypeInfo::Converters& converters = Type<TDestination>().backConverters(); 
    ::fcf::TypeInfo::Converters::const_iterator convIt = converters.find(a_sourceTypeIndex);
    if (convIt == converters.end()) {
      if (a_error) {
        *a_error = FCF_ERROR_FUNCTION_NOT_FOUND;
      }
      return 0;
    }
    return (ConvertFunction)convIt->second;
  }

  template <typename TSource>
  ConvertFunction getConvertFunctionBySource(unsigned int a_destinationTypeIndex){
    a_destinationTypeIndex = TypeIndexConverter<>::getDataIndex(a_destinationTypeIndex);
    const ::fcf::TypeInfo::Converters& converters = Type<TSource>().converters(); 
    ::fcf::TypeInfo::Converters::const_iterator convIt = converters.find(a_destinationTypeIndex);
    if (convIt == converters.end()) {
      const TypeInfo* destinationTypeInfo = getTypeInfo(a_destinationTypeIndex);
      const TypeInfo* sourceTypeInfo = Type<TSource>(). getTypeInfo();
      throw ConversionNotFoundException(__FILE__, __LINE__, destinationTypeInfo->name, sourceTypeInfo->name);
    }
    return (ConvertFunction)convIt->second;
  }

  template <typename TSource>
  ConvertFunction getConvertFunctionBySource(unsigned int a_destinationTypeIndex, int* a_error){
    a_destinationTypeIndex = TypeIndexConverter<>::getDataIndex(a_destinationTypeIndex);
    const ::fcf::TypeInfo::Converters& converters = Type<TSource>().converters(); 
    ::fcf::TypeInfo::Converters::const_iterator convIt = converters.find(a_destinationTypeIndex);
    if (convIt == converters.end()) {
      if (a_error) {
        *a_error = FCF_ERROR_FUNCTION_NOT_FOUND;
      }
      return 0;
    }
    return (ConvertFunction)convIt->second;
  }

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CONVERT__GET_CONVERT_FUNCTION_HPP___
