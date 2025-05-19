#ifndef ___FCF_BASIS__BITS__TYPE__BASE_TYPE_HPP___
#define ___FCF_BASIS__BITS__TYPE__BASE_TYPE_HPP___

#include <type_traits>
#include "../Convert/Details/setConverterDecl.hpp"
#include "TypeId.hpp"

namespace fcf {

  template <typename Ty>
  struct BaseType {
    public:

      enum { container = false };

      enum { flat = false };

      template <typename TContainer, typename TSpecificator>
      friend class SpecificatorTypeRegistrator;

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
          Details::TypeInfo initTypeInfo = { TypeId<Ty>().index(), TypeId<Ty>().name()};
          _info = Details::typeStorage.insert(initTypeInfo, TypeId<Ty>().autoIndex(), baseTypeIndex);
        }
      }
      const std::string& name() {
        return _info->name;
      }
      unsigned int index() {
        return _info->index;
      }
      const std::map<unsigned int, SpecificatorTypeInfo>& specificators() {
        return _info->specificators;
      }

      const Details::TypeInfo::Converters& converters(){
        return _info->converters;
      }

      const Details::TypeInfo::Converters& backConverters(){
        return _info->backConverters;
      }

      DynamicIteratorSpecificator::function_type dynamicIteratorResolver(){
        return _info->dynamicIteratorResolver;
      }

      RawDataSpecificator::function_type rawDataResolver(){
        return _info->rawDataResolver;
      }

    protected:
      static Details::TypeInfo* _info;
  };

  template <typename Ty> Details::TypeInfo* BaseType<Ty>::_info;

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__TYPE__BASE_TYPE_HPP___


