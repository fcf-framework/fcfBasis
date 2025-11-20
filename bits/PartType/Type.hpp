#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_HPP___

#include <type_traits>
#include <list>
#include <set>
#include <vector>
#include "../../Nop.hpp"
#include "../../bits/PartType/TypeStorage.hpp"

#include "../../bits/PartConvert/NDetails/setConverterDefinition.hpp"
#include "../../bits/PartType/NDetails/TypeRegistrar.hpp"
#include "../../bits/PartType/TypeWrapper.hpp"
#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../bits/PartType/TypeId.hpp"
#include "../../bits/PartSpecificator/NDetails/SpecificatorRefRegistrarDefinition.hpp"

namespace fcf{

  template <typename Ty>
  struct Type<Ty, Nop> {

      template <typename TContainer, typename TSubSpecificator>
      friend class SpecificatorRegistrar;

      template <typename, bool, typename = void>
      friend struct NDetails::SpecificatorRefRegistrar;


      template <typename TDestination, typename TSource>
      friend void ::fcf::NDetails::setConverter();

      typedef Ty         owner_type;

      Type(){
        if (!_info) {
          typedef typename TypeId<Ty>::basic_type basic_type;
          unsigned int baseTypeIndex = 0;
          if(!std::is_same<Ty, basic_type>::value){
            baseTypeIndex = Type<basic_type>().index();
          }
          const unsigned int index = TypeId<Ty>().index();
          TypeInfo initTypeInfo(index, TypeId<Ty>().name());
          _info = typeStorage.insert(initTypeInfo, TypeId<Ty>().autoIndex(), baseTypeIndex);
          if ((index & 0xcc000000) == 0) { // if not right ref and not const
            typedef typename std::decay<typename std::decay<Ty>::type>::type simple_type;
            ::fcf::NDetails::TypeRegistrar<simple_type, __COUNTER__, simple_type> typeRegistrar(_info, index);
            ::fcf::NDetails::SpecificatorRegistrarCaller<Type, __COUNTER__, simple_type> specificatorsRegistrar;
          }
        }
      }

      const std::string& name() {
        return _info->name;
      }

      unsigned int index() {
        return _info->index;
      }

      unsigned int dataIndex() {
        return _info->dataIndex;
      }

      const TypeInfo* getTypeInfo() {
        return _info;
      }

      size_t getWrapperSize(){
        return sizeof(fcf::TypeWrapper<Ty>);
      }

      const std::map<unsigned int, SpecificatorInfo>& specificators() {
        return _info->specificators;
      }

      template <typename TSubSpecificator>
      UniversalCall getSpecificator() const {
        return _info->getSpecificator<TSubSpecificator>();
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

  template <typename Ty> TypeInfo* Type<Ty, Nop>::_info;

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_HPP___
