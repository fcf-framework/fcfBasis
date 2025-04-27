#ifndef ___FCF_BASIS__BITS__CONVERT__CONVERT_RUNTIME_HPP___
#define ___FCF_BASIS__BITS__CONVERT__CONVERT_RUNTIME_HPP___

#include <stdexcept>
#include "ConvertOptions.hpp"
#include "ConvertFunction.hpp"
#include "getConvertFunction.hpp"
#include "../../bits/Type/Type.hpp"
#include "../../Details/typeStorage.hpp"
//#include "../../Variant.hpp"

namespace fcf {

  template <typename TDestination>
  void convertRuntimeByDestination(TDestination* a_destinationData, const void* a_source, unsigned int a_sourceTypeIndex, ConvertOptions* a_options = 0) {
    ConvertFunction convertFunction = getConvertFunctionByDestination<TDestination>(a_sourceTypeIndex);
    convertFunction(a_destinationData, a_source, a_options);
  }

  template <typename TSource>
  void convertRuntimeBySource(void* a_destinationData, unsigned int a_destinationTypeIndex, const TSource* a_source, ConvertOptions* a_options = 0) {
    ConvertFunction convertFunction = getConvertFunctionBySource<TSource>(a_destinationTypeIndex);
    convertFunction(a_destinationData, a_source, a_options);
  }

  FCF_BASIS_DECL_EXPORT void convertRuntime(void* a_resultData, unsigned int a_resultTypeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex, ConvertOptions* a_options = 0);
  FCF_BASIS_DECL_EXPORT void convertRuntime(void* a_resultData, unsigned int a_resultTypeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex, ConvertOptions* a_options, int* a_error);

  #ifdef FCF_BASIS_IMPLEMENTATION
    void convertRuntime(void* a_resultData, unsigned int a_resultTypeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex, ConvertOptions* a_options) {
      ConvertFunction convertFunction = getConvertFunction(a_resultTypeIndex, a_sourceTypeIndex);
      convertFunction(a_resultData, a_sourceData, a_options);
    }
  #endif

  #ifdef FCF_BASIS_IMPLEMENTATION
    void convertRuntime(void* a_resultData, unsigned int a_resultTypeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex, ConvertOptions* a_options, int* a_error) {
      ConvertFunction convertFunction = getConvertFunction(a_resultTypeIndex, a_sourceTypeIndex, a_error);
      convertFunction(a_resultData, a_sourceData, a_options);
    }
  #endif

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__CONVERT__CONVERT_RUNTIME_HPP___

