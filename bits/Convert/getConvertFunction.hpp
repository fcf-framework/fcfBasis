#ifndef ___FCF__BASIS__BITS__CONVERT__GET_CONVERT_FUNCTION_HPP___
#define ___FCF__BASIS__BITS__CONVERT__GET_CONVERT_FUNCTION_HPP___

#include "../../macro.hpp"
#include "../../error.hpp"
#include "ConvertFunction.hpp"
#include "../../Details/typeStorage.hpp"
#include "../../bits/Type/Type.hpp"

namespace fcf {

  FCF_BASIS_DECL_EXPORT ConvertFunction getConvertFunction(unsigned int a_destinationTypeIndex, unsigned int a_sourceTypeIndex);
  FCF_BASIS_DECL_EXPORT ConvertFunction getConvertFunction(unsigned int a_destinationTypeIndex, unsigned int a_sourceTypeIndex, int* a_error);

  #ifdef FCF_BASIS_IMPLEMENTATION
    ConvertFunction getConvertFunction(unsigned int a_destinationTypeIndex, unsigned int a_sourceTypeIndex) {
      do {
        const TypeInfo* pti = fcf::Details::typeStorage.get(a_sourceTypeIndex);
        if (!pti)
          break;
        const ::fcf::TypeInfo::Converters& converters = pti->converters; 
        ::fcf::TypeInfo::Converters::const_iterator convIt = converters.find(a_destinationTypeIndex);
        if (convIt == converters.end()) {
          break;
        }
        return (ConvertFunction)convIt->second;
      } while(false);
      throw std::runtime_error("No conversion function found");
    }
  #endif

  #ifdef FCF_BASIS_IMPLEMENTATION
    ConvertFunction getConvertFunction(unsigned int a_destinationTypeIndex, unsigned int a_sourceTypeIndex, int* a_error) {
      do {
        const TypeInfo* pti = fcf::Details::typeStorage.get(a_sourceTypeIndex);
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
    const ::fcf::TypeInfo::Converters& converters = Type<TDestination>().backConverters(); 
    ::fcf::TypeInfo::Converters::const_iterator convIt = converters.find(a_sourceTypeIndex);
    if (convIt == converters.end()) {
      throw std::runtime_error("No conversion function found");
    }
    return (ConvertFunction)convIt->second;
  }

  template <typename TDestination>
  ConvertFunction getConvertFunctionByDestination(unsigned int a_sourceTypeIndex, int* a_error){
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
    const ::fcf::TypeInfo::Converters& converters = Type<TSource>().converters(); 
    ::fcf::TypeInfo::Converters::const_iterator convIt = converters.find(a_destinationTypeIndex);
    if (convIt == converters.end()) {
      throw std::runtime_error("No conversion function found");
    }
    return (ConvertFunction)convIt->second;
  }

  template <typename TSource>
  ConvertFunction getConvertFunctionBySource(unsigned int a_destinationTypeIndex, int* a_error){
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

#endif // #ifndef ___FCF__BASIS__BITS__CONVERT__GET_CONVERT_FUNCTION_HPP___
