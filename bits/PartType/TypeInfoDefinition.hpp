#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_INFO_DEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_INFO_DEFINITION_HPP___

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <memory>
#include "../../macro.hpp"
#include "../../bits/PartException/ExceptionPredefinition.hpp"
#include "../../bits/PartConvert/ConvertFunction.hpp"
#include "../../bits/PartSpecifier/SpecifierInfo.hpp"
#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../bits/PartSpecifier/ResolveSpecifierDefinition.hpp"
#include "../../bits/PartType/TypeDefinition.hpp"
#include "../../bits/PartType/TypeId.hpp"
#include "../../bits/PartType/Type.hpp"
#include "../../bits/PartType/TypeFactoryBase.hpp"
#include "TypeInfoPredefinition.hpp"
#include "TypeInfoFlags.hpp"

namespace fcf{

  /**
   * @brief Structure containing metadata and runtime information for a registered type.
   * 
   * TypeInfo is the core descriptor used by the fcf type system to perform 
   * dynamic type checking, conversions, and specifier-based operations.
   */
  struct TypeInfo{
    /** @brief Map of destination type index to conversion function. */
    typedef std::unordered_map<unsigned int, ConvertFunction> ConvertersType;

    /** @brief Map of the mapping from the specifier type index to the specifier information. */
    typedef std::unordered_map<unsigned int, SpecifierInfo> SpecifiersType;

    /** @brief Unique identifier for the type. */
    unsigned int                                                  index;
    /** @brief Human-readable name of the type. */
    std::string                                                   name;
    /** @brief Flags belonging to the type variant. **/
    unsigned char                                                 flags;
    /** @brief Total size of the type in memory. */
    size_t                                                        size;
    /** @brief Converters for converting FROM this type. */
    ConvertersType                                                converters;
    /** @brief Converters for converting TO this type. */
    ConvertersType                                                backConverters;
    /** @brief Registered specifiers (e.g., Less, Equal, Add) for this type. */
    SpecifiersType                                             specifiers;
    /** @brief Container access specifier for fast access. */
    UniversalCall                                                 containerAccessUniversalCall;
    /** @brief Function pointer to resolve the type to its underlying data. */
    ResolveSpecifier::CallType                                 resolveCall;
    /** @brief filled for type Variant, stores the size of the inner buffer. */
    size_t                                                        variantInnerSize;
    /** @brief Factory used to create/destroy instances of this type. */
    TypeFactoryBase*                                              initializer;

    /**
     * @brief Full constructor for TypeInfo.
     * @param a_index Unique type index.
     * @param a_name Type name.
     * @param a_isVariantRef Is it a variant reference.
     * @param a_isVariant Is it a variant.
     * @param a_variantInnerSize Payload size.
     * @param a_size Total size.
     */
    inline TypeInfo(unsigned int a_index, const std::string& a_name, unsigned char a_flags, size_t a_size, size_t a_variantInnerSize);

    /** @brief Default constructor. */
    inline TypeInfo();

    /** @brief Copy constructor. */
    inline TypeInfo(const TypeInfo& a_source);

    /** @brief Destructor. */
    inline ~TypeInfo();

    /** @brief Copy assignment operator. */
    inline TypeInfo& operator=(const TypeInfo& a_source);

    /**
     * @brief Initializes the type metadata.
     * @tparam Ty The actual C++ type.
     */
    template <typename Ty>
    void initialize();

    /**
     * @brief Retrieves a specifier call as a typed function pointer.
     * @tparam TSpecifier The specifier type (e.g., LessSpecifier).
     * @return Function pointer of type TSpecifier::CallType.
     * @throws SpecifierNotFoundException if not registered.
     */
    template <typename TSpecifier>
    typename TSpecifier::CallType specifierCall() const;

    /**
     * @brief Retrieves a specifier call without throwing exceptions.
     * @tparam TSpecifier The specifier type.
     * @param a_error Pointer to store error if not found.
     * @return Function pointer or nullptr.
     */
    template <typename TSpecifier>
    typename TSpecifier::CallType specifierCall(Exception* a_error) const;

    /**
     * @brief Retrieves a specifier call as a universal function pointer.
     * @tparam TSpecifier The specifier type.
     * @return UniversalCall function pointer.
     * @throws SpecifierNotFoundException if not registered.
     */
    template <typename TSpecifier>
    UniversalCall specifierUniversalCall() const;

    /**
     * @brief Retrieves a specifier call as a universal function pointer without throwing.
     * @tparam TSpecifier The specifier type.
     * @param a_error Pointer to store error if not found.
     * @return UniversalCall function pointer or nullptr.
     */
    template <typename TSpecifier>
    UniversalCall specifierUniversalCall(Exception* a_error) const;

  };

} // fcf namespace

#endif // ___FCF_BASIS__BITS__PART_TYPE__TYPE_INFO_DEFINITION_HPP___
