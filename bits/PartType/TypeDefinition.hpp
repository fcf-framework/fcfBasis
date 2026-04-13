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

  /**
   * @brief Primary template for the Type structure.
   *
   * @tparam Ty The type being described.
   * @tparam TInfoMode The mode determining how type information is handled.
   */
  template <typename Ty, typename TInfoMode>
  struct Type;

  /**
   * @brief Specialization of the Type structure for the Nop mode.
   *
   * This is the standard implementation used for most registered types.
   * It provides access to type metadata, converters, and specificators.
   */
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

      /** @brief The underlying type owned by this Type descriptor. */
      typedef Ty         owner_type;

      /**
       * @brief Default constructor.
       *
       * Initializes the type information in the global type storage if not already present.
       */
      Type();

      /**
       * @brief Returns the human-readable name of the type.
       * @return A constant reference to the type name string.
       */
      inline const std::string& name();

      /**
       * @brief Returns the unique index of the type.
       * @return The unsigned integer index representing this type.
       */
      inline unsigned int index();

      /**
       * @brief Returns the data index of the type.
       *
       * The data index is used for type matching regardless of const/reference qualifiers.
       * @return The unsigned integer data index.
       */
      inline unsigned int dataIndex();

      /**
       * @brief Retrieves the TypeInfo structure for this type.
       * @return A pointer to the constant TypeInfo object.
       */
      inline const TypeInfo* getTypeInfo();

      /**
       * @brief Returns the map of specificators registered for this type.
       * @return A constant reference to the map of specificator information.
       */
      inline const std::map<unsigned int, SpecificatorInfo>& specificators();

      /**
       * @brief Retrieves a specificator call for a given specificator type.
       *
       * @tparam TSpecificator The type of the specificator to retrieve.
       * @return A UniversalCall function pointer. If the specifier is not found, a null pointer is returned.
       */
      template <typename TSubSpecificator>
      inline UniversalCall getSpecificator() const;

      /**
       * @brief Returns the map of converters for this type.
       * @return A constant reference to the map of converters.
       */
      inline const TypeInfo::Converters& converters();

      /**
       * @brief Returns the map of back-converters for this type.
       * @return A constant reference to the map of back-converters.
       */
      inline const TypeInfo::Converters& backConverters();

    protected:
      /** @brief Static pointer to the type's metadata in the global storage. */
      static TypeInfo* _info;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_DEFINITION_HPP___
