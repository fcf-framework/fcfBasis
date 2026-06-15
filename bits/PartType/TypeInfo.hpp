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
#include "../../bits/PartType/TypeFactoryBase.hpp"
#include "../../bits/PartMetaType/MetaTypeRemoveDeepConst.hpp"

#include "../../bits/PartType/TypeIndexConverter.hpp"
#include "../../bits/PartException/exceptions.hpp"
#include "NDetails/FactoryGetter.hpp"

namespace fcf {

  TypeInfo::TypeInfo(unsigned int a_index, const std::string& a_name, unsigned char a_flags, size_t a_size, size_t a_variantInnerSize)
    : index(a_index)
    , name(a_name)
    , flags(a_flags)
    , size(a_size)
    , containerAccessUniversalCall(0)
    , resolveCall(0)
    , variantInnerSize(a_variantInnerSize)
    , initializer(0) {
  }

  TypeInfo::TypeInfo()
    : index(0)
    , flags(0)
    , size(0)
    , containerAccessUniversalCall(0)
    , resolveCall(0)
    , variantInnerSize(0)
    , initializer(0) {
  }

  TypeInfo::TypeInfo(const TypeInfo& a_source)
    : index(a_source.index)
    , name(a_source.name)
    , flags(a_source.flags)
    , size(a_source.size)
    , converters(a_source.converters)
    , backConverters(a_source.backConverters)
    , specificators(a_source.specificators)
    , containerAccessUniversalCall(a_source.containerAccessUniversalCall)
    , resolveCall(a_source.resolveCall)
    , variantInnerSize(a_source.variantInnerSize)
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
    flags = a_source.flags;
    size = a_source.size;
    converters = a_source.converters;
    backConverters = a_source.backConverters;
    specificators = a_source.specificators;
    containerAccessUniversalCall = a_source.containerAccessUniversalCall;
    resolveCall = a_source.resolveCall;
    variantInnerSize = a_source.variantInnerSize;

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
        TypeInfo::SpecificatorsType::const_iterator it = a_typeInfo->specificators.find(specificatorIndex);
        return it != a_typeInfo->specificators.end() ? it->second.universalCall : 0;
      }
    };

    template <typename TSpecificator>
    struct SpecificatorResolver {
      typename TSpecificator::CallType operator()(const TypeInfo* a_typeInfo) const{
        const unsigned int specificatorIndex = Type<TSpecificator>().index();
        fcf::TypeInfo::SpecificatorsType::const_iterator it = a_typeInfo->specificators.find(specificatorIndex);
        return it != a_typeInfo->specificators.end() ? (typename TSpecificator::CallType)it->second.call : (typename TSpecificator::CallType)0;
      }
    };

    template <>
    struct SpecificatorUniversalResolver<ContainerAccessSpecificator> {
      UniversalCall operator()(const TypeInfo* a_typeInfo) const {
        return a_typeInfo->containerAccessUniversalCall;
      }
    };

    template <>
    struct SpecificatorResolver<ResolveSpecificator> {
      ResolveSpecificator::CallType operator()(const TypeInfo* a_typeInfo) const{
        return a_typeInfo->resolveCall;
      }
    };

  }

  template <typename TSpecificator>
  typename TSpecificator::CallType TypeInfo::specificatorCall() const {
    typename TSpecificator::CallType c = NDetails::SpecificatorResolver<TSpecificator>()(this);
    if (c) {
      return c;
    }
    throw fcf::SpecificatorNotFoundException(__FILE__, __LINE__, Type<TSpecificator>().name(), name);
  }

  template <typename TSpecificator>
  typename TSpecificator::CallType TypeInfo::specificatorCall(Exception* a_error) const {
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
  UniversalCall TypeInfo::specificatorUniversalCall() const {
    UniversalCall uc = NDetails::SpecificatorUniversalResolver<TSpecificator>()(this);
    if (uc) {
      return uc;
    }
    throw fcf::SpecificatorNotFoundException(__FILE__, __LINE__, Type<TSpecificator>().name(), name);
  }

  template <typename TSpecificator>
  UniversalCall TypeInfo::specificatorUniversalCall(Exception* a_error) const {
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
