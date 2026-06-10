#ifndef ___FCF__BASIS__BITS__PART_TYPE__TYPE_INFO_HPP___
#define ___FCF__BASIS__BITS__PART_TYPE__TYPE_INFO_HPP___

#include "TypeInfoDefinition.hpp"

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <memory>
#include "../../macro.hpp"
#include "../../bits/PartException/Exception.hpp"
#include "../../bits/PartConvert/ConvertFunction.hpp"
#include "../../bits/PartSpecificator/SpecificatorInfo.hpp"
#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../bits/PartSpecificator/ResolveSpecificatorDefinition.hpp"
#include "../../bits/PartType/TypeDefinition.hpp"
#include "../../bits/PartType/TypeId.hpp"
#include "../../bits/PartType/Type.hpp"
#include "../../bits/PartType/BaseTypeFactory.hpp"
#include "../../bits/PartMetaType/MetaTypeRemoveDeepConst.hpp"

#include "../../bits/PartType/TypeIndexConverter.hpp"
#include "../../bits/PartException/exceptions.hpp"
#include "NDetails/FactoryGetter.hpp"

namespace fcf {

  TypeInfo::TypeInfo(unsigned int a_index, const std::string& a_name, bool a_isVariantRef, bool a_isVariant, size_t a_innerSize, size_t a_size)
    : index(a_index)
    , name(a_name)
    , isVariantRef(a_isVariantRef)
    , isVariant(a_isVariant)
    , innerSize(a_innerSize)
    , size(a_size)
    , dataIndex(TypeIndexConverter<>::getDataIndex(a_index))
    , resolver(0)
    , containerAccess(0)
    , initializer(0) {
  }

  TypeInfo::TypeInfo()
    : index(0)
    , isVariantRef(0)
    , isVariant(0)
    , innerSize(0)
    , size(0)
    , dataIndex(0)
    , resolver(0)
    , containerAccess(0)
    , initializer(0) {
  }

  TypeInfo::TypeInfo(const TypeInfo& a_source)
    : index(a_source.index)
    , name(a_source.name)
    , isVariantRef(a_source.isVariantRef)
    , isVariant(a_source.isVariant)
    , innerSize(a_source.innerSize)
    , size(a_source.size)
    , dataIndex(a_source.dataIndex)
    , resolver(a_source.resolver)
    , converters(a_source.converters)
    , backConverters(a_source.backConverters)
    , specificators(a_source.specificators)
    , containerAccess(a_source.containerAccess)
    , initializer(0)
  {
    if (a_source.initializer){
      initializer = a_source.initializer;
    }
  }

  TypeInfo::~TypeInfo(){
  }

  inline TypeInfo& TypeInfo::operator=(const TypeInfo& a_source) {
    index = a_source.index;
    name = a_source.name;
    isVariantRef = a_source.isVariantRef;
    isVariant = a_source.isVariant;
    innerSize = a_source.innerSize;
    size = a_source.size;
    dataIndex = a_source.dataIndex;
    resolver = a_source.resolver;
    converters = a_source.converters;
    backConverters = a_source.backConverters;
    specificators = a_source.specificators;
    containerAccess = a_source.containerAccess;

    if (a_source.initializer){
      initializer = a_source.initializer;
    } else {
      initializer = 0;
    }

    return *this;
  }

  template <typename Ty>
  void TypeInfo::initialize(){
    typedef typename MetaTypeRemoveDeepConst<Ty>::type UnconstType;
    initializer = NDetails::FactoryGetter<
                                    !std::is_reference<UnconstType>::value && std::is_pointer<UnconstType>::value,
                                    UnconstType
                                  >::get();
  }

  namespace NDetails {
    template <typename TSpecificator>
    struct SpecificatorUniversalResolver {
      UniversalCall operator()(const TypeInfo* a_typeInfo) const{
        const unsigned int specificatorIndex = Type<TSpecificator>().index();
        std::map<unsigned int, SpecificatorInfo>::const_iterator it = a_typeInfo->specificators.find(specificatorIndex);
        return it != a_typeInfo->specificators.end() ? it->second.universalCall : 0;
      }
    };

    template <typename TSpecificator>
    struct SpecificatorResolver {
      typename TSpecificator::CallType operator()(const TypeInfo* a_typeInfo) const{
        const unsigned int specificatorIndex = Type<TSpecificator>().index();
        std::map<unsigned int, SpecificatorInfo>::const_iterator it = a_typeInfo->specificators.find(specificatorIndex);
        return it != a_typeInfo->specificators.end() ? (typename TSpecificator::CallType)it->second.call : (typename TSpecificator::CallType)0;
      }
    };

    template <>
    struct SpecificatorUniversalResolver<ContainerAccessSpecificator> {
      UniversalCall operator()(const TypeInfo* a_typeInfo) const {
        return a_typeInfo->containerAccess;
      }
    };

    template <>
    struct SpecificatorResolver<ResolveSpecificator> {
      ResolveSpecificator::CallType operator()(const TypeInfo* a_typeInfo) const{
        return a_typeInfo->resolver;
      }
    };

  }

  template <typename TSpecificator>
  typename TSpecificator::CallType TypeInfo::getSpecificatorCall() const {
    typename TSpecificator::CallType c = NDetails::SpecificatorResolver<TSpecificator>()(this);
    if (c) {
      return c;
    }
    throw fcf::SpecificatorNotFoundException(__FILE__, __LINE__, Type<TSpecificator>().name(), name);
  }

  template <typename TSpecificator>
  typename TSpecificator::CallType TypeInfo::getSpecificatorCall(Exception* a_error) const {
    typename TSpecificator::CallType c = NDetails::SpecificatorResolver<TSpecificator>()(this);
    if (c) {
      return c;
    }
    if (a_error){
      *a_error = fcf::SpecificatorNotFoundException(__FILE__, __LINE__, Type<TSpecificator>().name(), name);
    }
    return (typename TSpecificator::CallType)0;
  }

  template <typename TSpecificator>
  UniversalCall TypeInfo::getSpecificator() const {
    UniversalCall uc = NDetails::SpecificatorUniversalResolver<TSpecificator>()(this);
    if (uc) {
      return uc;
    }
    throw fcf::SpecificatorNotFoundException(__FILE__, __LINE__, Type<TSpecificator>().name(), name);
  }

  template <typename TSpecificator>
  UniversalCall TypeInfo::getSpecificator(Exception* a_error) const {
    UniversalCall uc = NDetails::SpecificatorUniversalResolver<TSpecificator>()(this);
    if (uc) {
      return uc;
    }
    if (a_error) {
      *a_error = fcf::SpecificatorNotFoundException(__FILE__, __LINE__, Type<TSpecificator>().name(), name);
    }
    return (UniversalCall)0;
  }

} // fcf namespace



#endif // #ifndef ___FCF__BASIS__BITS__PART_TYPE__TYPE_INFO_HPP___
