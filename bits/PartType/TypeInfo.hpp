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
#include "../../bits/PartSpecifier/SpecifierInfo.hpp"
#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../bits/PartSpecifier/ResolveSpecifierDefinition.hpp"
#include "../../bits/PartType/TypeDefinition.hpp"
#include "../../bits/PartType/TypeId.hpp"
#include "../../bits/PartType/Type.hpp"
#include "../../bits/PartType/TypeFactoryBase.hpp"
#include "../../bits/PartMetaType/MetaTypeRemoveDeepConst.hpp"

#include "../../bits/PartType/TypeIndexConverter.hpp"
#include "../../bits/PartException/exceptions.hpp"
#include "NDetails/FactoryGetter.hpp"

namespace fcf {

  TypeInfo::TypeInfo(TypeIndex a_index, const std::string& a_name, unsigned char a_flags, size_t a_size, size_t a_variantInnerSize)
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
    , specifiers(a_source.specifiers)
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
    specifiers = a_source.specifiers;
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
    template <typename TSpecifier>
    struct SpecifierUniversalResolver {
      UniversalCall operator()(const TypeInfo* a_typeInfo) const{
        const TypeIndex specifierIndex = Type<TSpecifier>().index();
        TypeInfo::SpecifiersType::const_iterator it = a_typeInfo->specifiers.find(specifierIndex);
        return it != a_typeInfo->specifiers.end() ? it->second.universalCall : 0;
      }
    };

    template <typename TSpecifier>
    struct SpecifierResolver {
      typename TSpecifier::CallType operator()(const TypeInfo* a_typeInfo) const{
        const TypeIndex specifierIndex = Type<TSpecifier>().index();
        fcf::TypeInfo::SpecifiersType::const_iterator it = a_typeInfo->specifiers.find(specifierIndex);
        return it != a_typeInfo->specifiers.end() ? (typename TSpecifier::CallType)it->second.call : (typename TSpecifier::CallType)0;
      }
    };

    template <>
    struct SpecifierUniversalResolver<ContainerAccessSpecifier> {
      UniversalCall operator()(const TypeInfo* a_typeInfo) const {
        return a_typeInfo->containerAccessUniversalCall;
      }
    };

    template <>
    struct SpecifierResolver<ResolveSpecifier> {
      ResolveSpecifier::CallType operator()(const TypeInfo* a_typeInfo) const{
        return a_typeInfo->resolveCall;
      }
    };

  }

  template <typename TSpecifier>
  typename TSpecifier::CallType TypeInfo::specifierCall() const {
    typename TSpecifier::CallType c = NDetails::SpecifierResolver<TSpecifier>()(this);
    if (c) {
      return c;
    }
    throw fcf::SpecifierNotFoundException(__FILE__, __LINE__, Type<TSpecifier>().name(), name);
  }

  template <typename TSpecifier>
  typename TSpecifier::CallType TypeInfo::specifierCall(Exception* a_error) const {
    typename TSpecifier::CallType c = NDetails::SpecifierResolver<TSpecifier>()(this);
    if (c) {
      return c;
    }
    if (a_error){
      *a_error = fcf::SpecifierNotFoundException(__FILE__, __LINE__, Type<TSpecifier>().name(), name);
    }
    return (typename TSpecifier::CallType)0;
  }

  template <typename TSpecifier>
  UniversalCall TypeInfo::specifierUniversalCall() const {
    UniversalCall uc = NDetails::SpecifierUniversalResolver<TSpecifier>()(this);
    if (uc) {
      return uc;
    }
    throw fcf::SpecifierNotFoundException(__FILE__, __LINE__, Type<TSpecifier>().name(), name);
  }

  template <typename TSpecifier>
  UniversalCall TypeInfo::specifierUniversalCall(Exception* a_error) const {
    UniversalCall uc = NDetails::SpecifierUniversalResolver<TSpecifier>()(this);
    if (uc) {
      return uc;
    }
    if (a_error) {
      *a_error = fcf::SpecifierNotFoundException(__FILE__, __LINE__, Type<TSpecifier>().name(), name);
    }
    return (UniversalCall)0;
  }

} // fcf namespace



#endif // #ifndef ___FCF__BASIS__BITS__PART_TYPE__TYPE_INFO_HPP___
