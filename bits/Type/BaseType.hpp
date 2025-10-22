#ifndef ___FCF_BASIS__BITS__TYPE__BASE_TYPE_HPP___
#define ___FCF_BASIS__BITS__TYPE__BASE_TYPE_HPP___

#include <type_traits>
#include "../Convert/Details/setConverterDecl.hpp"
#include "../../bits/TemplateSpecializationInitializer.hpp"
#include "../../Details/Variant/NobodyWrapperRegistrator.hpp"
#include "../../bits/PartType/NDetails/TypeRegistrar.hpp"
#include "TypeId.hpp"
#include <iostream>
namespace fcf {

  template <typename Ty>
  struct BaseType {
    public:

      enum { container = false };

      enum { flat = false };

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
          TypeInfo initTypeInfo = { index, TypeId<Ty>().name()};
          _info = Details::typeStorage.insert(initTypeInfo, TypeId<Ty>().autoIndex(), baseTypeIndex);
          if ((index & 0xce000000) == 0) { // if not ref and not const
            typedef typename std::decay<typename std::decay<Ty>::type>::type simple_type;
            ::fcf::NDetails::TypeRegistrar<simple_type, __COUNTER__, simple_type> typeRegistrar(index);
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

      const TypeInfo& getTypeInfo() {
        return *_info;
      }

      const std::map<unsigned int, SpecificatorTypeInfo>& specificators() {
        return _info->specificators;
      }

      const TypeInfo::Converters& converters(){
        return _info->converters;
      }

      const TypeInfo::Converters& backConverters(){
        return _info->backConverters;
      }

      DynamicIteratorSpecificator::function_type dynamicIteratorResolver(){
        return _info->dynamicIteratorResolver;
      }

      RawDataSpecificator::function_type rawDataResolver(){
        return _info->rawDataResolver;
      }

    protected:
      static TypeInfo* _info;
  };

  template <typename Ty> TypeInfo* BaseType<Ty>::_info;

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__TYPE__BASE_TYPE_HPP___


