#ifndef ___FCF_BASIS__BITS__PART_CONVERT__GET_CONVERT_FUNCTION_HPP___
#define ___FCF_BASIS__BITS__PART_CONVERT__GET_CONVERT_FUNCTION_HPP___

#include <type_traits>
#include "../../macro.hpp"
#include "ConvertFunction.hpp"
#include "../../bits/PartType/TypeStorage.hpp"
#include "../../bits/PartType/Type.hpp"
#include "../../PartException.hpp"

namespace fcf {

  FCF_BASIS_DECL_EXPORT ConvertFunction getConvertFunction(TypeIndex a_destinationTypeIndex, TypeIndex a_sourceTypeIndex);
  FCF_BASIS_DECL_EXPORT ConvertFunction getConvertFunction(TypeIndex a_destinationTypeIndex, TypeIndex a_sourceTypeIndex, Exception* a_error);

  #ifdef FCF_BASIS_IMPLEMENTATION
    namespace NDetails {
      template <typename TException>
      inline ConvertFunction getConvertFunctionImpl(TypeIndex a_destinationTypeIndex, TypeIndex a_sourceTypeIndex, TException* a_error) {
        a_destinationTypeIndex = TypeIndexConverter<>::getDataIndex(a_destinationTypeIndex);
        a_sourceTypeIndex = TypeIndexConverter<>::getDataIndex(a_sourceTypeIndex);
        do {
          const TypeInfo* pti = fcf::getTypeStorage().get(a_sourceTypeIndex);
          if (!pti)
            break;
          const ::fcf::TypeInfo::ConvertersType& converters = pti->converters; 
          ::fcf::TypeInfo::ConvertersType::const_iterator convIt = converters.find(a_destinationTypeIndex);
          if (convIt == converters.end()) {
            break;
          }
          return (ConvertFunction)convIt->second;
        } while(false);
        const TypeInfo* destinationTypeInfo = getTypeInfo(a_destinationTypeIndex, 0);
        const char*     destinationTypeName = destinationTypeInfo ? destinationTypeInfo->name.c_str() : "(Invalid type index)";
        const TypeInfo* sourceTypeInfo = getTypeInfo(a_sourceTypeIndex, 0);
        const char*     sourceTypeName = sourceTypeInfo ? sourceTypeInfo->name.c_str() : "(Invalid type index)";
        FCF_INVARIANT_EXCEPTION(TException, a_error, (ConversionNotFoundException(__FILE__, __LINE__, destinationTypeName, sourceTypeName)));
        return (ConvertFunction)0;
      }
    } // NDetails namespace
  #endif

  #ifdef FCF_BASIS_IMPLEMENTATION
    ConvertFunction getConvertFunction(TypeIndex a_destinationTypeIndex, TypeIndex a_sourceTypeIndex) {
      return NDetails::getConvertFunctionImpl<Nop>(a_destinationTypeIndex, a_sourceTypeIndex, nullptr);
    }
  #endif

  #ifdef FCF_BASIS_IMPLEMENTATION
    ConvertFunction getConvertFunction(TypeIndex a_destinationTypeIndex, TypeIndex a_sourceTypeIndex, Exception* a_error) {
      return NDetails::getConvertFunctionImpl<Exception>(a_destinationTypeIndex, a_sourceTypeIndex, a_error);
    }
  #endif


  namespace NDetails{
    template <typename TDestination, typename TException>
    inline ConvertFunction getConvertFunctionByDestinationImpl(TypeIndex a_sourceTypeIndex, TException* a_error){
      a_sourceTypeIndex = TypeIndexConverter<>::getDataIndex(a_sourceTypeIndex);
      const ::fcf::TypeInfo::ConvertersType& converters = Type<TDestination>().backConverters(); 
      ::fcf::TypeInfo::ConvertersType::const_iterator convIt = converters.find(a_sourceTypeIndex);
      if (convIt == converters.end()) {
        const TypeInfo* destinationTypeInfo = Type<TDestination>().typeInfo();
        const TypeInfo* sourceTypeInfo = getTypeInfo(a_sourceTypeIndex, 0);
        const char*     sourceTypeName = sourceTypeInfo ? sourceTypeInfo->name.c_str() : "(Invalid type index)";
        FCF_INVARIANT_EXCEPTION(TException, a_error, (ConversionNotFoundException(__FILE__, __LINE__, destinationTypeInfo->name, sourceTypeName)));
        return (ConvertFunction)0;
      }
      return (ConvertFunction)convIt->second;
    }
  } // NDetails namespace

  template <typename TDestination>
  ConvertFunction getConvertFunctionByDestination(TypeIndex a_sourceTypeIndex){
    return NDetails::getConvertFunctionByDestinationImpl<TDestination, Nop>(a_sourceTypeIndex, nullptr);
  }

  template <typename TDestination>
  ConvertFunction getConvertFunctionByDestination(TypeIndex a_sourceTypeIndex, Exception* a_error){
    return NDetails::getConvertFunctionByDestinationImpl<TDestination, Exception>(a_sourceTypeIndex, a_error);
  }

  namespace NDetails {
    template <typename TSource, typename TException>
    inline ConvertFunction getConvertFunctionBySourceImpl(TypeIndex a_destinationTypeIndex, TException* a_error){
      a_destinationTypeIndex = TypeIndexConverter<>::getDataIndex(a_destinationTypeIndex);
      const ::fcf::TypeInfo::ConvertersType& converters = Type<TSource>().converters(); 
      ::fcf::TypeInfo::ConvertersType::const_iterator convIt = converters.find(a_destinationTypeIndex);
      if (convIt == converters.end()) {
        const TypeInfo* destinationTypeInfo = getTypeInfo(a_destinationTypeIndex, 0);
        const char*     destinationTypeName = destinationTypeInfo ? destinationTypeInfo->name.c_str() : "(Invalid type index)";
        const TypeInfo* sourceTypeInfo = Type<TSource>().typeInfo();
        FCF_INVARIANT_EXCEPTION(TException, a_error, (ConversionNotFoundException(__FILE__, __LINE__, destinationTypeName, sourceTypeInfo->name)));
        return (ConvertFunction)0;
      }
      return (ConvertFunction)convIt->second;
    }
  } // NDetails namespace

  template <typename TSource>
  ConvertFunction getConvertFunctionBySource(TypeIndex a_destinationTypeIndex){
    return NDetails::getConvertFunctionBySourceImpl<TSource, Nop>(a_destinationTypeIndex, nullptr);
  }

  template <typename TSource>
  ConvertFunction getConvertFunctionBySource(TypeIndex a_destinationTypeIndex, Exception* a_error){
    return NDetails::getConvertFunctionBySourceImpl<TSource, Exception>(a_destinationTypeIndex, a_error);
  }

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CONVERT__GET_CONVERT_FUNCTION_HPP___
