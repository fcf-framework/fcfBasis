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
#include "../../bits/PartSpecificator/SpecificatorInfo.hpp"
#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../bits/PartSpecificator/ResolveSpecificatorDefinition.hpp"
#include "../../bits/PartType/TypeDefinition.hpp"
#include "../../bits/PartType/TypeId.hpp"
#include "../../bits/PartType/Type.hpp"
#include "../../bits/PartType/BaseTypeFactory.hpp"
#include "TypeInfoPredefinition.hpp"

namespace fcf{

  /**
   * @brief Structure containing metadata and runtime information for a registered type.
   * 
   * TypeInfo is the core descriptor used by the fcf type system to perform 
   * dynamic type checking, conversions, and specificator-based operations.
   */
  struct TypeInfo{
    /** @brief Map of destination type index to conversion function. */
    typedef std::unordered_map<unsigned int, ConvertFunction> Converters;

    /** @brief Unique identifier for the type. */
    unsigned int                                                  index;
    /** @brief Human-readable name of the type. */
    std::string                                                   name;
    /** @brief Flag indicating if this type is a reference to a Variant. */
    bool                                                          isVariantRef;
    /** @brief Flag indicating if this type is a Variant itself. */
    bool                                                          isVariant;
    /** @brief Size of the data payload excluding reference/pointer overhead. */
    size_t                                                        innerSize;
    /** @brief Total size of the type in memory. */
    size_t                                                        size;
    /** @brief Index of the underlying data type (ignoring const/ref qualifiers). */
    unsigned int                                                  dataIndex;
    /** @brief Function pointer to resolve the type to its underlying data. */
    ResolveSpecificator::CallFunctionType                         resolver;
    /** @brief Converters for converting FROM this type. */
    Converters                                                    converters;
    /** @brief Converters for converting TO this type. */
    Converters                                                    backConverters;
    /** @brief Registered specificators (e.g., Less, Equal, Add) for this type. */
    std::map<unsigned int, SpecificatorInfo>                      specificators;
    /** @brief Factory used to create/destroy instances of this type. */
    BaseTypeFactory*                                              initializer;

    /**
     * @brief Full constructor for TypeInfo.
     * @param a_index Unique type index.
     * @param a_name Type name.
     * @param a_isVariantRef Is it a variant reference.
     * @param a_isVariant Is it a variant.
     * @param a_innerSize Payload size.
     * @param a_size Total size.
     */
    inline TypeInfo(unsigned int a_index, const std::string& a_name, bool a_isVariantRef, bool a_isVariant, size_t a_innerSize, size_t a_size);

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
     * @brief Retrieves a specificator call as a typed function pointer.
     * @tparam TSpecificator The specificator type (e.g., LessSpecificator).
     * @return Function pointer of type TSpecificator::CallType.
     * @throws SpecificatorNotFoundException if not registered.
     */
    template <typename TSpecificator>
    typename TSpecificator::CallType getSpecificatorCall() const;

    /**
     * @brief Retrieves a specificator call without throwing exceptions.
     * @tparam TSpecificator The specificator type.
     * @param a_error Pointer to store error if not found.
     * @return Function pointer or nullptr.
     */
    template <typename TSpecificator>
    typename TSpecificator::CallType getSpecificatorCall(Exception* a_error) const;

    /**
     * @brief Retrieves a specificator call as a universal function pointer.
     * @tparam TSpecificator The specificator type.
     * @return UniversalCall function pointer.
     * @throws SpecificatorNotFoundException if not registered.
     */
    template <typename TSpecificator>
    UniversalCall getSpecificator() const;

    /**
     * @brief Retrieves a specificator call as a universal function pointer without throwing.
     * @tparam TSpecificator The specificator type.
     * @param a_error Pointer to store error if not found.
     * @return UniversalCall function pointer or nullptr.
     */
    template <typename TSpecificator>
    UniversalCall getSpecificator(Exception* a_error) const;

  };

} // fcf namespace

#endif // ___FCF_BASIS__BITS__PART_TYPE__TYPE_INFO_DEFINITION_HPP___
