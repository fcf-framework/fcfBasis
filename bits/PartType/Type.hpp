#ifndef _FCF_BASIS__BITS__PART_TYPE__TYPE_HPP___
#define _FCF_BASIS__BITS__PART_TYPE__TYPE_HPP___

#include "TypeDefinition.hpp"
#include "../../bits/PartType/TypeStorage.hpp"
#include "../../bits/PartType/NDetails/TypeRegistrar.hpp"
#include "../../bits/PartVariant/NDetails/IsVariantRef.hpp"
#include "../../bits/PartVariant/NDetails/IsVariant.hpp"
#include "../../bits/PartVariant/NDetails/VariantInnerSize.hpp"
#include "../../bits/PartType/TypeGroupInitializer.hpp"

namespace fcf {
  template <typename Ty> TypeInfo* Type<Ty, Nop>::_info;
}

namespace fcf {
  namespace NDetails{
    template <typename Ty>
    struct TypeSize{
      enum { value = sizeof( typename std::remove_reference<Ty>::type ) };
    };
    template <>
    struct TypeSize<void>{
      enum { value = 0 };
    };

  }
}

namespace fcf {
  template <typename Ty>
  Type<Ty, Nop>::Type(){
    if (!_info) {
      typedef typename TypeId<Ty>::basic_type basic_type;
      TypeIndex baseTypeIndex = 0;
      if(!std::is_same<Ty, basic_type>::value){
        baseTypeIndex = Type<basic_type>().index();
      }
      const TypeIndex index = TypeId<Ty>().index();
      unsigned char flags = (NDetails::IsVariantRef<Ty>::value ? TIF_VARIANT_REF : 0) |
                            (NDetails::IsVariant<Ty>::value    ? TIF_VARIANT : 0);
      TypeInfo initTypeInfo(index, TypeId<Ty>().name(), flags, NDetails::TypeSize<Ty>::value, NDetails::VariantInnerSize<Ty>::value);
      _info = getTypeStorage().insert(initTypeInfo, TypeId<Ty>().autoIndex(), baseTypeIndex);
      typedef typename std::decay<typename std::decay<Ty>::type>::type simple_type;
      ::fcf::NDetails::TypeRegistrar<simple_type, __COUNTER__, Ty> typeRegistrar(_info, index);
      ::fcf::NDetails::SpecifierRegistrarCaller<Type, __COUNTER__, simple_type> specifiersRegistrar;
      if (TypeId<Ty>().isTemplate()) {
        TypeGroupInitializer<Ty> groupInitializer;
      }
    }
  }

  template <typename Ty>
  const std::string& Type<Ty, Nop>::name() {
    return _info->name;
  }

  template <typename Ty>
  TypeIndex Type<Ty, Nop>::index() {
    return _info->index;
  }

  template <typename Ty>
  size_t Type<Ty, Nop>::size() {
    return _info->size;
  }

  template <typename Ty>
  const TypeInfo* Type<Ty, Nop>::typeInfo() {
    return _info;
  }

  template <typename Ty>
  const TypeInfo::SpecifiersType& Type<Ty, Nop>::specifiers() {
    return _info->specifiers;
  }

  template <typename Ty>
  template <typename TSubSpecifier>
  UniversalCall Type<Ty, Nop>::specifierUniversalCall() const {
    return _info->specifierUniversalCall<TSubSpecifier>();
  }

  template <typename Ty>
  template <typename TSubSpecifier>
  UniversalCall Type<Ty, Nop>::specifierUniversalCall(fcf::Exception* a_dstError) const {
    return _info->specifierUniversalCall<TSubSpecifier>(a_dstError);
  }

  template <typename Ty>
  template <typename TSpecifier>
  typename TSpecifier::CallType Type<Ty, Nop>::specifierCall() const {
    return _info->specifierCall<TSpecifier>();
  }

  template <typename Ty>
  template <typename TSpecifier>
  typename TSpecifier::CallType Type<Ty, Nop>::specifierCall(fcf::Exception* a_dstError) const {
    return _info->specifierCall<TSpecifier>(a_dstError);
  }

  template <typename Ty>
  const TypeInfo::ConvertersType& Type<Ty, Nop>::converters(){
    return _info->converters;
  }

  template <typename Ty>
  const TypeInfo::ConvertersType& Type<Ty, Nop>::backConverters(){
    return _info->backConverters;
  }

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_TYPE__TYPE_HPP___
