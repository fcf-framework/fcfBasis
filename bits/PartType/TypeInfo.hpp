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

#include "../../bits/PartType/TypeIndexConverter.hpp"
#include "../../bits/PartException/exceptions.hpp"

namespace fcf {

  TypeInfo::TypeInfo(unsigned int a_index, const std::string& a_name, bool a_isVariantRef, bool a_isVariant, size_t a_innerSize, size_t a_size)
    : index(a_index)
    , name(a_name)
    , isVariantRef(a_isVariantRef)
    , isVariant(a_isVariant)
    , innerSize(a_innerSize)
    , size(a_size)
    , dataIndex(TypeIndexConverter<>::getDataIndex(a_index))
    , resolver(0) {
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
