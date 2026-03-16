#ifndef ___FCF__BASIS__BITS__PART_TYPE__TYPE_INFO_HPP___
#define ___FCF__BASIS__BITS__PART_TYPE__TYPE_INFO_HPP___

#include "TypeInfoDefinition.hpp"

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <memory>
#include "../../macro.hpp"
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

  template <typename TSpecificator>
  typename TSpecificator::CallType TypeInfo::getSpecificatorCall() const {
    const unsigned int specificatorIndex = Type<TSpecificator>().index();
    std::map<unsigned int, SpecificatorInfo>::const_iterator it = specificators.find(specificatorIndex);
    if (it != specificators.end()) {
      return (typename TSpecificator::CallType)it->second.call;
    }
    return (typename TSpecificator::CallType)0;
  }

  template <typename TSpecificator>
  typename TSpecificator::CallType TypeInfo::getSafeSpecificatorCall() const {
    const unsigned int specificatorIndex = Type<TSpecificator>().index();
    std::map<unsigned int, SpecificatorInfo>::const_iterator it = specificators.find(specificatorIndex);
    if (it != specificators.end() && !!it->second.call) {
      return (typename TSpecificator::CallType)it->second.call;
    }
    throw fcf::SpecificatorNotFoundException(__FILE__, __LINE__, Type<TSpecificator>().name(), name);
  }

  template <typename TSpecificator>
  UniversalCall TypeInfo::getSpecificator() const {
    const unsigned int specificatorIndex = Type<TSpecificator>().index();
    std::map<unsigned int, SpecificatorInfo>::const_iterator it = specificators.find(specificatorIndex);
    if (it != specificators.end()) {
      return (UniversalCall)it->second.universalCall;
    }
    return (UniversalCall)0;
  }

  template <typename TSpecificator>
  UniversalCall TypeInfo::getSafeSpecificator() const {
    const unsigned int specificatorIndex = Type<TSpecificator>().index();
    std::map<unsigned int, SpecificatorInfo>::const_iterator it = specificators.find(specificatorIndex);
    if (it != specificators.end() && !!it->second.universalCall) {
      return (UniversalCall)it->second.universalCall;
    }
    throw fcf::SpecificatorNotFoundException(__FILE__, __LINE__, Type<TSpecificator>().name(), name);
  }

} // fcf namespace



#endif // #ifndef ___FCF__BASIS__BITS__PART_TYPE__TYPE_INFO_HPP___
