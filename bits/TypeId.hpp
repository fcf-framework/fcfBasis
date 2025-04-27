#ifndef ___FCF_BASIS__BITS__TYPE_ID_HPP___
#define ___FCF_BASIS__BITS__TYPE_ID_HPP___

#include <iostream>
#include <stdexcept>
#include "../Details/typeStorage.hpp"
#include "TypeIdSource.hpp"
#include "SpecificatorTypeInfo.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace Convert {
        struct ConvertStorage;
        template <typename TSource, typename TDestination>
        void setConverter(Details::Basis::Convert::ConvertStorage* a_storage);
      }
    }
  }
}

namespace fcf {

    template <typename TContainer, typename TSpecificator>
    class SpecificatorTypeRegistrator;

    template <typename Ty>
    class TypeId {
      public:

        template <typename TContainer, typename TSpecificator>
        friend class SpecificatorTypeRegistrator;

        template <typename TSource, typename TDestination>
        friend void ::fcf::Details::Basis::Convert::setConverter();

        TypeId(unsigned int a_baseIndex = 0) {
          Details::TypeInfo initTypeInfo = { TypeIdSource<Ty>().index(), TypeIdSource<Ty>().name()};
          _ti = Details::typeStorage.insert(initTypeInfo, TypeIdSource<Ty>().autoIndex(), a_baseIndex);
        }

        const std::string& name() {
          return _ti->name;
        }

        unsigned int index() {
          return _ti->index;
        }

        const std::map<unsigned int, SpecificatorTypeInfo>& specificators() {
          return _ti->specificators;
        }

        void* toConverter(){
          return _ti->toConverter;
        }

        void* fromConverter(){
          return _ti->fromConverter;
        }

        const Details::TypeInfo::Converters& converters(){
          return _ti->converters;
        }

        const Details::TypeInfo::Converters& backConverters(){
          return _ti->backConverters;
        }

      private:

        void addSpecificator(unsigned int a_specificatorIndex, const fcf::SpecificatorTypeInfo& a_sti) {
          _ti->specificators[a_specificatorIndex] = a_sti;
        }
        Details::TypeInfo* _ti;
    };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__TYPE_ID_HPP___
