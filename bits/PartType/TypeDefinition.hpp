#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_DEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_DEFINITION_HPP___

#include <list>
#include <set>
#include <vector>
#include <type_traits>

#include "TypePredefinition.hpp"

#include "../../bits/PartType/TypeStorageDefinition.hpp"
#include "../../bits/PartConvert/NDetails/setConverterDefinition.hpp"
#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../bits/PartType/TypeId.hpp"
#include "../../bits/PartSpecificator/NDetails/SpecificatorRefRegistrarDefinition.hpp"

namespace fcf{

  template <typename Ty, typename TInfoMode>
  struct Type;

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

      inline const std::string& name();

      inline unsigned int index();

      inline unsigned int dataIndex();

      inline  const TypeInfo* getTypeInfo();

      inline const std::map<unsigned int, SpecificatorInfo>& specificators();

      template <typename TSubSpecificator>
      inline UniversalCall getSpecificator() const;

      inline const TypeInfo::Converters& converters();

      inline const TypeInfo::Converters& backConverters();

    protected:
      static TypeInfo* _info;
  };




} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_DEFINITION_HPP___
