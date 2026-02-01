#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_HPP___

#include <type_traits>
#include <list>
#include <set>
#include <vector>
#include "../../Nop.hpp"
#include "../../bits/PartType/TypeStorage.hpp"

#include "../../bits/PartConvert/NDetails/setConverterDefinition.hpp"
#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../bits/PartType/TypeId.hpp"
#include "../../bits/PartSpecificator/NDetails/SpecificatorRefRegistrarDefinition.hpp"

namespace fcf{

  template <typename Ty>
  struct Type<Ty, Nop> {

      template <typename TContainer, typename TSubSpecificator>
      friend class SpecificatorRegistrar;

      template <typename, typename, typename>
      friend struct NDetails::SpecificatorRefRegistrarImpl;

      template <typename, typename, typename, typename>
      friend struct NDetails::SpecificatorRegistrarIfTypeDeclaredImpl;



      template <typename TDestination, typename TSource>
      friend void ::fcf::NDetails::setConverter();

      typedef Ty         owner_type;

      Type();

      const std::string& name();

      unsigned int index();

      unsigned int dataIndex();

      const TypeInfo* getTypeInfo();

      size_t getWrapperSize();

      const std::map<unsigned int, SpecificatorInfo>& specificators();

      template <typename TSubSpecificator>
      UniversalCall getSpecificator() const;

      const TypeInfo::Converters& converters();

      const TypeInfo::Converters& backConverters();

    protected:
      static TypeInfo* _info;
  };

  template <typename Ty> TypeInfo* Type<Ty, Nop>::_info;

} // fcf namespace

#include "../../bits/PartType/NDetails/TypeRegistrar.hpp"
#include "../../bits/PartType/TypeWrapper.hpp"
#include "../../bits/PartVariant/NDetails/IsVariantRef.hpp"
#include "../../bits/PartVariant/NDetails/IsVariant.hpp"
#include "../../bits/PartVariant/NDetails/VariantInnerSize.hpp"

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
      unsigned int baseTypeIndex = 0;
      if(!std::is_same<Ty, basic_type>::value){
        baseTypeIndex = Type<basic_type>().index();
      }
      const unsigned int index = TypeId<Ty>().index();
      TypeInfo initTypeInfo(index, TypeId<Ty>().name(), NDetails::IsVariantRef<Ty>::value, NDetails::IsVariant<Ty>::value, NDetails::VariantInnerSize<Ty>::value, NDetails::TypeSize<Ty>::value );
      _info = typeStorage.insert(initTypeInfo, TypeId<Ty>().autoIndex(), baseTypeIndex);
      //if ((index & 0xc4000000) == 0) { // if not right ref
      typedef typename std::decay<typename std::decay<Ty>::type>::type simple_type;
      ::fcf::NDetails::TypeRegistrar<simple_type, __COUNTER__, Ty> typeRegistrar(_info, index);
      ::fcf::NDetails::SpecificatorRegistrarCaller<Type, __COUNTER__, simple_type> specificatorsRegistrar;
      //}
    }
  }

  template <typename Ty>
  const std::string& Type<Ty, Nop>::name() {
    return _info->name;
  }

  template <typename Ty>
  unsigned int Type<Ty, Nop>::index() {
    return _info->index;
  }

  template <typename Ty>
  unsigned int Type<Ty, Nop>::dataIndex() {
    return _info->dataIndex;
  }

  template <typename Ty>
  const TypeInfo* Type<Ty, Nop>::getTypeInfo() {
    return _info;
  }

  template <typename Ty>
  size_t Type<Ty, Nop>::getWrapperSize(){
    return sizeof(fcf::TypeWrapper<Ty>);
  }

  template <typename Ty>
  const std::map<unsigned int, SpecificatorInfo>& Type<Ty, Nop>::specificators() {
    return _info->specificators;
  }

  template <typename Ty>
  template <typename TSubSpecificator>
  UniversalCall Type<Ty, Nop>::getSpecificator() const {
    return _info->getSpecificator<TSubSpecificator>();
  }

  template <typename Ty>
  const TypeInfo::Converters& Type<Ty, Nop>::converters(){
    return _info->converters;
  }

  template <typename Ty>
  const TypeInfo::Converters& Type<Ty, Nop>::backConverters(){
    return _info->backConverters;
  }

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_HPP___
