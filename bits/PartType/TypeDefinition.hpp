#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_DEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_DEFINITION_HPP___

#include <list>
#include <set>
#include <vector>
#include <type_traits>

#include "TypePredefinition.hpp"

#include "../../bits/PartType/TypeStorageDefinition.hpp"
#include "../../bits/PartConvert/ConverterRegistrationDefinition.hpp"
#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../bits/PartType/TypeId.hpp"
#include "../../bits/PartSpecifier/NDetails/SpecifierRefRegistrarDefinition.hpp"

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
   * It provides access to type metadata, converters, and specifiers.
   */
  template <typename Ty>
  struct Type<Ty, Nop> {

      template <typename TContainer, typename TSubSpecifier>
      friend class SpecifierRegistrar;

      template <typename, typename, typename>
      friend struct NDetails::SpecifierRefRegistrarImpl;

      template <typename, typename, typename, typename>
      friend struct NDetails::SpecifierRegistrarIfTypeDeclaredImpl;

      template <typename TDestination, typename TSource>
      friend void converterRegistration();

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
       * @brief Returns the size of the data for the type.
       * @return Type size in bytes
       */
      inline size_t size();

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
      inline const TypeInfo* typeInfo();

      /**
       * @brief Returns the map of specifiers registered for this type.
       * @return A constant reference to the map of specifier information.
       */
      inline const TypeInfo::SpecifiersType& specifiers();

      /**
       * @brief Retrieves a specifier universal call for a given specifier type.
       *
       * If the specifier is not found, throw fcf::SpecifierNotFoundException.
       *
       * @tparam TSpecifier The type of the specifier to retrieve.
       * @return A UniversalCall function pointer.
       */
      template <typename TSubSpecifier>
      inline UniversalCall specifierUniversalCall() const;

      /**
       * @brief Retrieves a specifier universal call for a given specifier type.
       *
       * @tparam TSpecifier The type of the specifier to retrieve.
       * @param fcf::Exception* a_dstError - Pointer to an error object whose fields 
       *                                     will be filled in case of failure. May be zero.
       * @return A UniversalCall function pointer. If the specifier is not found, a null pointer is returned.
       */
      template <typename TSubSpecifier>
      inline UniversalCall specifierUniversalCall(fcf::Exception* a_dstError) const;

      /**
       * @brief Retrieves a specifier call for a given specifier type.
       *
       * If the specifier is not found, throw fcf::SpecifierNotFoundException.
       * 
       * @tparam TSpecifier The type of the specifier to retrieve.
       * @return A TSpecifier::CallType function pointer.
       */
      template <typename TSpecifier>
      inline typename TSpecifier::CallType specifierCall() const;

      /**
       * @brief Retrieves a specifier call for a given specifier type.
       *
       * @tparam TSpecifier The type of the specifier to retrieve.
       * @param fcf::Exception* a_dstError - Pointer to an error object whose fields 
       *                                     will be filled in case of failure. May be zero.
       * @return A TSpecifier::CallType function pointer. If the specifier is not found, a null pointer is returned.
       */
      template <typename TSpecifier>
      inline typename TSpecifier::CallType specifierCall(fcf::Exception* a_dstError) const;

      /**
       * @brief Returns the map of converters for this type.
       * @return A constant reference to the map of converters.
       */
      inline const TypeInfo::ConvertersType& converters();

      /**
       * @brief Returns the map of back-converters for this type.
       * @return A constant reference to the map of back-converters.
       */
      inline const TypeInfo::ConvertersType& backConverters();

    protected:
      /** @brief Static pointer to the type's metadata in the global storage. */
      static TypeInfo* _info;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_DEFINITION_HPP___
