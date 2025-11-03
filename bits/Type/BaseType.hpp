#ifndef ___FCF_BASIS__BITS__TYPE__BASE_TYPE_HPP___
#define ___FCF_BASIS__BITS__TYPE__BASE_TYPE_HPP___

#include <type_traits>
#include "../Convert/Details/setConverterDecl.hpp"
#include "../../bits/TemplateSpecializationInitializer.hpp"
#include "../../bits/PartType/NDetails/TypeRegistrar.hpp"
#include "../../bits/PartTypes/UniversalCall.hpp"
#include "TypeId.hpp"
#include <iostream>
namespace fcf {

  template <typename Ty>
  struct BaseType {
    public:

      enum { container = false };

      template <typename TContainer, typename TSpecificator>
      friend class SpecificatorRegistrar;

      template <typename TSource, typename TDestination>
      friend void ::fcf::Details::Basis::Convert::setConverter();

      typedef Ty         owner_type;
      BaseType(){
        if (!_info) {
          typedef typename TypeId<Ty>::basic_type basic_type;
          unsigned int baseTypeIndex = 0;
          if(!std::is_same<Ty, basic_type>::value){
            baseTypeIndex = BaseType<basic_type>().index();
          }
          const unsigned int index = TypeId<Ty>().index();
          TypeInfo initTypeInfo(index, TypeId<Ty>().name());
          _info = Details::typeStorage.insert(initTypeInfo, TypeId<Ty>().autoIndex(), baseTypeIndex);
          if ((index & 0xce000000) == 0) { // if not ref and not const
            typedef typename std::decay<typename std::decay<Ty>::type>::type simple_type;
            ::fcf::NDetails::TypeRegistrar<simple_type, __COUNTER__, simple_type> typeRegistrar(_info, index);
            ::fcf::NDetails::SpecificatorRegistrarCaller<BaseType, __COUNTER__, simple_type> specificatorsRegistrar;
          }
        }
      }

      const std::string& name() {
        return _info->name;
      }

      unsigned int index() {
        return _info->index;
      }

      const TypeInfo* getTypeInfo() {
        return _info;
      }

      const std::map<unsigned int, SpecificatorTypeInfo>& specificators() {
        return _info->specificators;
      }

      template <typename TSpecificator>
      UniversalCall getSpecificator() const {
        return _info->getSpecificator<TSpecificator>();
      }

      const TypeInfo::Converters& converters(){
        return _info->converters;
      }

      const TypeInfo::Converters& backConverters(){
        return _info->backConverters;
      }

    protected:
      static TypeInfo* _info;
  };

  template <typename Ty> TypeInfo* BaseType<Ty>::_info;

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__TYPE__BASE_TYPE_HPP___


