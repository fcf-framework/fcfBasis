#ifndef _FCF_BASIS__BITS__PART_CONVERT__CONVERT_WITH_RUNTIME_FUNCTION_HPP___
#define _FCF_BASIS__BITS__PART_CONVERT__CONVERT_WITH_RUNTIME_FUNCTION_HPP___

#include <stdexcept>
#include "ConvertOptions.hpp"
#include "ConvertFunction.hpp"
#include "getConversion.hpp"
#include "../../bits/PartType/Type.hpp"
#include "../../bits/PartType/TypeIndexConverter.hpp"
#include "../../bits/PartType/TypeStorage.hpp"

namespace fcf {

  template <typename TDestination>
  void convertWithRuntimeSource(TDestination* a_destinationData, const void* a_source, TypeIndex a_sourceTypeIndex, ConvertOptions& a_options, Error& a_error) {
    if (std::is_pointer<TDestination>::value && TypeIndexConverter<>::isPointer(a_sourceTypeIndex)) {
      *(int**)a_destinationData = *(int**)a_source;
      return;
    }
    ConvertFunction convertFunction = getConversionTo<TDestination>(a_sourceTypeIndex);
    convertFunction(a_destinationData, a_source, a_options, a_error);
  }

  template <typename TDestination>
  void convertWithRuntimeSource(TDestination* a_destinationData, const void* a_source, TypeIndex a_sourceTypeIndex, ConvertOptions& a_options, Error&& a_error = Error{true}) {
    convertWithRuntimeSource(a_destinationData, a_source, a_sourceTypeIndex, a_options, a_error);
  }



  template <typename TDestination>
  void convertWithRuntimeSource(TDestination* a_destinationData, const void* a_source, TypeIndex a_sourceTypeIndex, Error& a_error) {
    if (std::is_pointer<TDestination>::value && TypeIndexConverter<>::isPointer(a_sourceTypeIndex)) {
      *(int**)a_destinationData = *(int**)a_source;
      return;
    }
    ConvertFunction convertFunction = getConversionTo<TDestination>(a_sourceTypeIndex);
    ConvertOptions co;
    convertFunction(a_destinationData, a_source, co, a_error);
  }

  template <typename TDestination>
  void convertWithRuntimeSource(TDestination* a_destinationData, const void* a_source, TypeIndex a_sourceTypeIndex, Error&& a_error = Error{true}) {
    convertWithRuntimeSource(a_destinationData, a_source, a_sourceTypeIndex, a_error);
  }



  template <typename TSource>
  void convertWithRuntimeDestination(void* a_destinationData, TypeIndex a_destinationTypeIndex, const TSource* a_source, ConvertOptions& a_options, Error& a_error) {
    if (std::is_pointer<TSource>::value && TypeIndexConverter<>::isPointer(a_destinationTypeIndex)){
      *((int**)a_destinationData) = *(int**)a_source;
      return;
    }
    ConvertFunction convertFunction = getConversionFrom<TSource>(a_destinationTypeIndex);
    convertFunction(a_destinationData, a_source, a_options, a_error);
  }

  template <typename TSource>
  void convertWithRuntimeDestination(void* a_destinationData, TypeIndex a_destinationTypeIndex, const TSource* a_source, ConvertOptions& a_options, Error&& a_error = Error{true}) {
    convertWithRuntimeDestination(a_destinationData, a_destinationTypeIndex, a_source, a_options, a_error);
  }



  FCF_BASIS_DECL_EXPORT void convertWithRuntime(void* a_resultData, TypeIndex a_resultTypeIndex, const void* a_sourceData, TypeIndex a_sourceTypeIndex, ConvertOptions& a_options, Error& a_error);

  inline void convertWithRuntime(void* a_resultData, TypeIndex a_resultTypeIndex, const void* a_sourceData, TypeIndex a_sourceTypeIndex, ConvertOptions& a_options, Error&& a_error = Error{true}) {
    convertWithRuntime(a_resultData, a_resultTypeIndex, a_sourceData, a_sourceTypeIndex, a_options, a_error);
  }

  #ifdef FCF_BASIS_IMPLEMENTATION
    void convertWithRuntime(void* a_resultData, TypeIndex a_resultTypeIndex, const void* a_sourceData, TypeIndex a_sourceTypeIndex, ConvertOptions& a_options, Error& a_error) {
      if (TypeIndexConverter<>::isPointer(a_resultTypeIndex) && TypeIndexConverter<>::isPointer(a_sourceTypeIndex)){
        *((int**)a_resultData) = *(int**)a_sourceData;
        return;
      }
      ConvertFunction convertFunction = getConversion(a_resultTypeIndex, a_sourceTypeIndex, a_error);
      if (a_error) {
        return;
      }
      convertFunction(a_resultData, a_sourceData, a_options, a_error);
    }
  #endif

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_CONVERT__CONVERT_WITH_RUNTIME_FUNCTION_HPP___
