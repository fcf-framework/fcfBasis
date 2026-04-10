#ifndef ___FCF_BASIS__BITS__PART_VARIANT__VARIANT_DEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_VARIANT__VARIANT_DEFINITION_HPP___

#include <string>
#include <map>
#include <stdexcept>
#include "../../macro.hpp"
#include "../../bits/PartVariant/VariantPredefinition.hpp"
#include "../../bits/PartType/DynamicTypeDefinition.hpp"
#include "../../bits/PartType/TypeIndexConverter.hpp"
#include "../../bits/PartMetaType/MetaTypeBoolean.hpp"
#include "../../bits/PartContainerAccess/VariantCursorDefinition.hpp"
#include "../../bits/PartContainerAccess/ContainerAccess.hpp"

namespace fcf {

  /**
   * @brief A type-safe, dynamic variant class capable of holding values of various types.
   *
   * @tparam innerBufferSize The size of the internal buffer used for Small Object Optimization (SOO).
   *                         If the stored type's size is less than or equal to this value, the data
   *                         is stored directly within the object, avoiding heap allocation.
   *
   * BasicVariant acts as a universal container that can store any registered type in the FCF type system.
   * It supports automatic type conversion, reference semantics, and dynamic type introspection.
   *
   * @note The class manages its own memory. If the stored type exceeds @p innerBufferSize,
   *       memory is allocated on the heap.
   */
  template <size_t innerBufferSize>
  class BasicVariant {
    public:

      /**
       * @brief Enumeration defining the data set mode for assignment and construction.
       */
      enum DataSetMode {
        WRITE = 0,          ///< Standard copy/assignment mode.
        RESET = 1,          ///< Destroy existing data and create new data (move/copy semantics).
        REFERENCE = 2,      ///< Store a reference to the source data (if supported).
        FORCE_REFERENCE = 4 ///< Force reference storage even if the source is not a reference type.
      };

      /**
       * @brief Friend declaration to allow access to private members from other BasicVariant instantiations.
       */
      template <size_t InputInnerBufferSize>
      friend class BasicVariant;

      /**
       * @brief Function pointer type for custom conversion functions.
       */
      typedef void (*convert_function_type)(void*, const void*);

      /**
       * @brief Iterator type for traversing container-like variants.
       */
      typedef ContainerAccess< BasicVariant<innerBufferSize> >        iterator;

      /**
       * @brief Const iterator type for traversing container-like variants.
       */
      typedef ContainerAccess< const BasicVariant<innerBufferSize> >  const_iterator;

      // ---------------------------------------------------------------------------
      // Constructors
      // ---------------------------------------------------------------------------

      /**
       * @brief Default constructor.
       *
       * Creates an empty variant with no type information.
       */
      BasicVariant();

      /**
       * @brief Copy constructor.
       *
       * @param a_variant The variant to copy from.
       */
      BasicVariant(const BasicVariant& a_variant);

      /**
       * @brief Copy constructor with specific data mode.
       *
       * @param a_variant The variant to copy from.
       * @param a_dataMode The mode of data transfer (e.g., WRITE, REFERENCE).
       */
      BasicVariant(const BasicVariant& a_variant, DataSetMode a_dataMode);

      /**
       * @brief Move-like constructor with specific data mode.
       *
       * @param a_variant The variant to copy from.
       * @param a_dataMode The mode of data transfer.
       */
      BasicVariant(BasicVariant& a_variant, DataSetMode a_dataMode);

      /**
       * @brief Template constructor from a generic value.
       *
       * @tparam Ty The type of the value to store.
       * @param a_value The value to store.
       */
      template <typename Ty>
      BasicVariant(const Ty& a_value);

      /**
       * @brief Template constructor with explicit type and data mode.
       *
       * @tparam Ty The target type.
       * @tparam TSource The source type.
       * @param a_type The explicit type descriptor.
       * @param a_value The value to store.
       * @param a_dataMode The mode of data transfer.
       */
      template <typename Ty, typename TSource>
      BasicVariant(const Type<Ty>& a_type, TSource& a_value, DataSetMode a_dataMode = WRITE);

      /**
       * @brief Template constructor with explicit type and const source.
       *
       * @tparam Ty The target type.
       * @tparam TSource The source type.
       * @param a_type The explicit type descriptor.
       * @param a_value The value to store.
       * @param a_dataMode The mode of data transfer.
       */
      template <typename Ty, typename TSource>
      BasicVariant(const Type<Ty>& a_type, const TSource& a_value, DataSetMode a_dataMode = WRITE);

      /**
       * @brief Template constructor from another BasicVariant with explicit type.
       *
       * @tparam Ty The target type.
       * @tparam InputInnerBufferSize The buffer size of the source variant.
       * @param a_type The explicit type descriptor.
       * @param a_value The source variant.
       * @param a_dataMode The mode of data transfer.
       */
      template <typename Ty, size_t InputInnerBufferSize>
      BasicVariant(const Type<Ty>& a_type, BasicVariant<InputInnerBufferSize>& a_value, DataSetMode a_dataMode = WRITE);

      /**
       * @brief Template constructor from a const BasicVariant with explicit type.
       *
       * @tparam Ty The target type.
       * @tparam InputInnerBufferSize The buffer size of the source variant.
       * @param a_type The explicit type descriptor.
       * @param a_value The source variant.
       * @param a_dataMode The mode of data transfer.
       */
      template <typename Ty, size_t InputInnerBufferSize>
      BasicVariant(const Type<Ty>& a_type, const BasicVariant<InputInnerBufferSize>& a_value, DataSetMode a_dataMode = WRITE);

      /**
       * @brief Template constructor from a generic source with data mode.
       *
       * @tparam TSource The source type.
       * @param a_value The value to store.
       * @param a_dataMode The mode of data transfer.
       */
      template <typename TSource>
      BasicVariant(const TSource& a_value, DataSetMode a_dataMode);

      /**
       * @brief Template constructor from a generic source reference with data mode.
       *
       * @tparam TSource The source type.
       * @param a_value The value to store.
       * @param a_dataMode The mode of data transfer.
       */
      template <typename TSource>
      BasicVariant(TSource& a_value, DataSetMode a_dataMode);

      /**
       * @brief Constructor from a C-style string.
       *
       * @param a_value The C-string to store.
       */
      BasicVariant(const char* a_value);

      /**
       * @brief Constructor from a C-style string with data mode.
       *
       * @param a_value The C-string to store.
       * @param a_dataMode The mode of data transfer.
       */
      BasicVariant(const char* a_value, DataSetMode a_dataMode);

      /**
       * @brief Template constructor from another BasicVariant (different buffer size).
       *
       * @tparam InputInnerBufferSize The buffer size of the source variant.
       * @param a_variant The source variant.
       */
      template <size_t InputInnerBufferSize>
      BasicVariant(const BasicVariant<InputInnerBufferSize>& a_variant);

      /**
       * @brief Template constructor from another BasicVariant (different buffer size, non-const).
       *
       * @tparam InputInnerBufferSize The buffer size of the source variant.
       * @param a_variant The source variant.
       */
      template <size_t InputInnerBufferSize>
      BasicVariant(BasicVariant<InputInnerBufferSize>& a_variant);

      /**
       * @brief Template constructor from another BasicVariant with data mode.
       *
       * @tparam InputInnerBufferSize The buffer size of the source variant.
       * @param a_variant The source variant.
       * @param a_dataMode The mode of data transfer.
       */
      template <size_t InputInnerBufferSize>
      BasicVariant(const BasicVariant<InputInnerBufferSize>& a_variant, DataSetMode a_dataMode);

      /**
       * @brief Template constructor from another BasicVariant (non-const) with data mode.
       *
       * @tparam InputInnerBufferSize The buffer size of the source variant.
       * @param a_variant The source variant.
       * @param a_dataMode The mode of data transfer.
       */
      template <size_t InputInnerBufferSize>
      BasicVariant(BasicVariant<InputInnerBufferSize>& a_variant, DataSetMode a_dataMode);

      /**
       * @brief Constructor from a Type descriptor (creates default instance of that type).
       *
       * @tparam Ty The type to instantiate.
       * @param a_type The type descriptor.
       */
      template <typename Ty>
      BasicVariant(Type<Ty, Nop> a_type);

      /**
       * @brief Constructor from a DynamicType.
       *
       * @param a_dynamicType The dynamic type descriptor.
       */
      BasicVariant(DynamicType a_dynamicType);

      /**
       * @brief Constructor from a TypeInfo pointer.
       *
       * @param a_typeInfo Pointer to the type information.
       */
      BasicVariant(const TypeInfo* a_typeInfo);

      /**
       * @brief Low-level constructor using type indices and raw data.
       *
       * @param a_typeIndex The index of the target type.
       * @param a_sourceData Pointer to the source data.
       * @param a_sourceTypeIndex The index of the source type (0 if same as target).
       * @param a_options Conversion options.
       * @param a_convertFunction Custom conversion function.
       */
      BasicVariant(unsigned int a_typeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex = 0, ConvertOptions* a_options = 0, ConvertFunction a_convertFunction = 0);

      /**
       * @brief Destructor.
       *
       * Destroys the stored value and frees any allocated memory.
       */
      ~BasicVariant();

      // ---------------------------------------------------------------------------
      // Reset and Assignment
      // ---------------------------------------------------------------------------

      /**
       * @brief Resets the variant to a new DynamicType.
       *
       * @param a_dynamicType The new dynamic type.
       */
      void reset(DynamicType a_dynamicType);

      /**
       * @brief Resets the variant to a new TypeInfo.
       *
       * @param a_typeInfo Pointer to the new type information.
       */
      void reset(const TypeInfo* a_typeInfo);

      /**
       * @brief Resets the variant to a new Type.
       *
       * @tparam Ty The new type.
       * @param a_dynamicType The type descriptor.
       */
      template <typename Ty>
      void reset(Type<Ty, Nop> a_dynamicType);

      /**
       * @brief Copy assignment operator.
       *
       * @param a_variant The variant to assign from.
       * @return Reference to this variant.
       */
      BasicVariant& operator=(const BasicVariant& a_variant);

      /**
       * @brief Assignment from a BasicVariant with different buffer size.
       *
       * @tparam InputInnerBufferSize The buffer size of the source variant.
       * @param a_variant The variant to assign from.
       * @return Reference to this variant.
       */
      template <size_t InputInnerBufferSize>
      BasicVariant& operator=(const BasicVariant<InputInnerBufferSize>& a_variant);

      /**
       * @brief Assignment from a generic value.
       *
       * @tparam Ty The type of the value.
       * @param a_value The value to assign.
       * @return Reference to this variant.
       */
      template <typename Ty>
      BasicVariant& operator=(const Ty& a_value);

      /**
       * @brief Assignment from a C-style string.
       *
       * @param a_value The C-string to assign.
       * @return Reference to this variant.
       */
      BasicVariant& operator=(const char* a_value);

      /**
       * @brief Sets the value from another variant.
       *
       * @param a_variant The variant to copy from.
       */
      void set(const BasicVariant& a_variant);

      /**
       * @brief Sets the value from another variant with specific mode.
       *
       * @param a_variant The variant to copy from.
       * @param a_dataMode The mode of data transfer.
       */
      void set(const BasicVariant& a_variant, DataSetMode a_dataMode);

      /**
       * @brief Sets the value from a non-const variant with specific mode.
       *
       * @param a_variant The variant to copy from.
       * @param a_dataMode The mode of data transfer.
       */
      void set(BasicVariant& a_variant, DataSetMode a_dataMode);

      /**
       * @brief Sets the value from a generic value.
       *
       * @tparam Ty The type of the value.
       * @param a_value The value to set.
       */
      template <typename Ty>
      void set(const Ty& a_value);

      /**
       * @brief Sets the value from a generic reference with specific mode.
       *
       * @tparam Ty The type of the value.
       * @param a_value The value to set.
       * @param a_dataMode The mode of data transfer.
       */
      template <typename Ty>
      void set(Ty& a_value, DataSetMode a_dataMode);

      /**
       * @brief Sets the value from a generic const value with specific mode.
       *
       * @tparam Ty The type of the value.
       * @param a_value The value to set.
       * @param a_dataMode The mode of data transfer.
       */
      template <typename Ty>
      void set(const Ty& a_value, DataSetMode a_dataMode);

      /**
       * @brief Sets the value from a C-style string.
       *
       * @param a_value The C-string to set.
       */
      void set(const char* a_value);

      /**
       * @brief Sets the value from a C-style string with specific mode.
       *
       * @param a_value The C-string to set.
       * @param a_dataMode The mode of data transfer.
       */
      void set(const char* a_value, DataSetMode a_dataMode);

      /**
       * @brief Low-level set using type indices and raw data.
       *
       * @param a_typeIndex The index of the target type.
       * @param a_sourceData Pointer to the source data.
       * @param a_sourceTypeIndex The index of the source type.
       * @param a_options Conversion options.
       * @param a_convertFunction Custom conversion function.
       */
      void set(unsigned int a_typeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex = 0, ConvertOptions* a_options = 0, ConvertFunction a_convertFunction = 0);

      /**
       * @brief Clears the variant, destroying the stored value.
       */
      void clear();

      // ---------------------------------------------------------------------------
      // Container Access
      // ---------------------------------------------------------------------------

      /**
       * @brief Returns the size of the container if the variant holds a container type.
       * @return The number of elements, or 0 if not a container.
       */
      size_t containerSize();

      /**
       * @brief Erases an element identified by a key.
       *
       * @param a_key The key of the element to erase.
       */
      void erase(const BasicVariant& a_key);

      /**
       * @brief Erases an element at the specified iterator position.
       *
       * @param a_iterator Iterator pointing to the element to erase.
       */
      void erase(const iterator& a_iterator);

      /**
       * @brief Erases elements in the range [a_begin, a_end).
       *
       * @param a_begin Iterator to the start of the range.
       * @param a_end Iterator to the end of the range.
       */
      void erase(const iterator& a_begin, const iterator& a_end);

      /**
       * @brief Returns an iterator to the beginning of the container.
       * @return Iterator to the first element.
       */
      inline iterator begin() {
        return iterator(*this);
      }

      /**
       * @brief Returns an iterator to the end of the container.
       * @return Iterator past the last element.
       */
      inline iterator end() {
        return iterator(*this, CP_END);
      }

      /**
       * @brief Returns a const iterator to the beginning of the container.
       * @return Const iterator to the first element.
       */
      inline const_iterator begin() const {
        return const_iterator(*this);
      }

      /**
       * @brief Returns a const iterator to the end of the container.
       * @return Const iterator past the last element.
       */
      inline const_iterator end() const{
        return const_iterator(*this, CP_END);
      }

      /**
       * @brief Returns a const iterator to the beginning of the container.
       * @return Const iterator to the first element.
       */
      inline const_iterator cbegin() const {
        return const_iterator(*this);
      }

      /**
       * @brief Returns a const iterator to the end of the container.
       * @return Const iterator past the last element.
       */
      const_iterator cend() const{
        return const_iterator(*this, CP_END);
      }

      /**
       * @brief Accesses an element by key (operator[]).
       *
       * @param a_key The key to access.
       * @return A Variant containing the value.
       */
      Variant operator[](const Variant& a_key);

      /**
       * @brief Accesses an element by key (operator[]).
       *
       * @tparam Ty The type of the key.
       * @param a_key The key to access.
       * @return A Variant containing the value.
       */
      template <typename Ty>
      Variant operator[](const Ty& a_key);

      /**
       * @brief Accesses an element by C-string key.
       *
       * @param a_key The C-string key.
       * @return A Variant containing the value.
       */
      Variant operator[](const char* a_key);

      /**
       * @brief Conversion to bool.
       *
       * Returns true if the variant is not empty and evaluates to true according to its type's BoolSpecificator.
       */
      operator bool() const;

      // ---------------------------------------------------------------------------
      // Comparison Operators
      // ---------------------------------------------------------------------------

      /**
       * @brief Less than operator.
       * @param a_value The value to compare against.
       * @return true if *this < a_value.
       */
      bool operator<(const BasicVariant& a_value) const;

      /**
       * @brief Less than operator (template).
       * @tparam Ty The type of the value.
       * @param a_value The value to compare against.
       * @return true if *this < a_value.
       */
      template <typename Ty>
      bool operator<(const Ty& a_value) const;

      /**
       * @brief Less than operator (C-string).
       * @param a_value The C-string to compare against.
       * @return true if *this < a_value.
       */
      bool operator<(const char* a_value) const;

      /**
       * @brief Less than or equal operator.
       * @param a_value The value to compare against.
       * @return true if *this <= a_value.
       */
      bool operator<=(const BasicVariant& a_value) const;

      /**
       * @brief Less than or equal operator (template).
       * @tparam Ty The type of the value.
       * @param a_value The value to compare against.
       * @return true if *this <= a_value.
       */
      template <typename Ty>
      bool operator<=(const Ty& a_value) const;

      /**
       * @brief Less than or equal operator (C-string).
       * @param a_value The C-string to compare against.
       * @return true if *this <= a_value.
       */
      bool operator<=(const char* a_value) const;

      /**
       * @brief Equality operator.
       * @param a_value The value to compare against.
       * @return true if *this == a_value.
       */
      bool operator==(const BasicVariant& a_value) const;

      /**
       * @brief Equality operator (template).
       * @tparam Ty The type of the value.
       * @param a_value The value to compare against.
       * @return true if *this == a_value.
       */
      template <typename Ty>
      bool operator==(const Ty& a_value) const;

      /**
       * @brief Equality operator (C-string).
       * @param a_value The C-string to compare against.
       * @return true if *this == a_value.
       */
      bool operator==(const char* a_value) const;

      /**
       * @brief Inequality operator.
       * @param a_value The value to compare against.
       * @return true if *this != a_value.
       */
      bool operator!=(const BasicVariant& a_value) const;

      /**
       * @brief Inequality operator (template).
       * @tparam Ty The type of the value.
       * @param a_value The value to compare against.
       * @return true if *this != a_value.
       */
      template <typename Ty>
      bool operator!=(const Ty& a_value) const;

      /**
       * @brief Inequality operator (C-string).
       * @param a_value The C-string to compare against.
       * @return true if *this != a_value.
       */
      bool operator!=(const char* a_value) const;

      /**
       * @brief Greater than operator.
       * @param a_value The value to compare against.
       * @return true if *this > a_value.
       */
      bool operator>(const BasicVariant& a_value) const;

      /**
       * @brief Greater than operator (template).
       * @tparam Ty The type of the value.
       * @param a_value The value to compare against.
       * @return true if *this > a_value.
       */
      template <typename Ty>
      bool operator>(const Ty& a_value) const;

      /**
       * @brief Greater than operator (C-string).
       * @param a_value The C-string to compare against.
       * @return true if *this > a_value.
       */
      bool operator>(const char* a_value) const;

      /**
       * @brief Greater than or equal operator.
       * @param a_value The value to compare against.
       * @return true if *this >= a_value.
       */
      bool operator>=(const BasicVariant& a_value) const;

      /**
       * @brief Greater than or equal operator (template).
       * @tparam Ty The type of the value.
       * @param a_value The value to compare against.
       * @return true if *this >= a_value.
       */
      template <typename Ty>
      bool operator>=(const Ty& a_value) const;

      /**
       * @brief Greater than or equal operator (C-string).
       * @param a_value The C-string to compare against.
       * @return true if *this >= a_value.
       */
      bool operator>=(const char* a_value) const;

      // ---------------------------------------------------------------------------
      // Arithmetic Operators
      // ---------------------------------------------------------------------------

      /**
       * @brief Addition assignment operator.
       * @param a_value The value to add.
       * @return Reference to this variant.
       */
      BasicVariant& operator+=(const BasicVariant& a_value);

      /**
       * @brief Addition assignment operator (template).
       * @tparam Ty The type of the value.
       * @param a_value The value to add.
       * @return Reference to this variant.
       */
      template <typename Ty>
      BasicVariant& operator+=(const Ty& a_value);

      /**
       * @brief Addition assignment operator (C-string).
       * @param a_value The C-string to add.
       * @return Reference to this variant.
       */
      BasicVariant& operator+=(const char* a_value);

      /**
       * @brief Addition operator.
       * @param a_value The value to add.
       * @return A new variant with the result.
       */
      BasicVariant operator+(const BasicVariant& a_value) const;

      /**
       * @brief Addition operator (template).
       * @tparam Ty The type of the value.
       * @param a_value The value to add.
       * @return A new variant with the result.
       */
      template <typename Ty>
      BasicVariant operator+(const Ty& a_value) const;

      /**
       * @brief Addition operator (C-string).
       * @param a_value The C-string to add.
       * @return A new variant with the result.
       */
      BasicVariant operator+(const char* a_value) const;

      /**
       * @brief Subtraction assignment operator.
       * @param a_value The value to subtract.
       * @return Reference to this variant.
       */
      BasicVariant& operator-=(const BasicVariant& a_value);

      /**
       * @brief Subtraction assignment operator (template).
       * @tparam Ty The type of the value.
       * @param a_value The value to subtract.
       * @return Reference to this variant.
       */
      template <typename Ty>
      BasicVariant& operator-=(const Ty& a_value);

      /**
       * @brief Subtraction assignment operator (C-string).
       * @param a_value The C-string to subtract.
       * @return Reference to this variant.
       */
      BasicVariant& operator-=(const char* a_value);

      /**
       * @brief Subtraction operator.
       * @param a_value The value to subtract.
       * @return A new variant with the result.
       */
      BasicVariant operator-(const BasicVariant& a_value) const;

      /**
       * @brief Subtraction operator (template).
       * @tparam Ty The type of the value.
       * @param a_value The value to subtract.
       * @return A new variant with the result.
       */
      template <typename Ty>
      BasicVariant operator-(const Ty& a_value) const;

      /**
       * @brief Subtraction operator (C-string).
       * @param a_value The C-string to subtract.
       * @return A new variant with the result.
       */
      BasicVariant operator-(const char* a_value) const;

      /**
       * @brief Multiplication assignment operator.
       * @param a_value The value to multiply by.
       * @return Reference to this variant.
       */
      BasicVariant& operator*=(const BasicVariant& a_value);

      /**
       * @brief Multiplication assignment operator (template).
       * @tparam Ty The type of the value.
       * @param a_value The value to multiply by.
       * @return Reference to this variant.
       */
      template <typename Ty>
      BasicVariant& operator*=(const Ty& a_value);

      /**
       * @brief Multiplication assignment operator (C-string).
       * @param a_value The C-string to multiply by.
       * @return Reference to this variant.
       */
      BasicVariant& operator*=(const char* a_value);

      /**
       * @brief Multiplication operator.
       * @param a_value The value to multiply by.
       * @return A new variant with the result.
       */
      BasicVariant operator*(const BasicVariant& a_value) const;

      /**
       * @brief Multiplication operator (template).
       * @tparam Ty The type of the value.
       * @param a_value The value to multiply by.
       * @return A new variant with the result.
       */
      template <typename Ty>
      BasicVariant operator*(const Ty& a_value) const;

      /**
       * @brief Multiplication operator (C-string).
       * @param a_value The C-string to multiply by.
       * @return A new variant with the result.
       */
      BasicVariant operator*(const char* a_value) const;

      /**
       * @brief Division assignment operator.
       * @param a_value The value to divide by.
       * @return Reference to this variant.
       */
      BasicVariant& operator/=(const BasicVariant& a_value);

      /**
       * @brief Division assignment operator (template).
       * @tparam Ty The type of the value.
       * @param a_value The value to divide by.
       * @return Reference to this variant.
       */
      template <typename Ty>
      BasicVariant& operator/=(const Ty& a_value);

      /**
       * @brief Division assignment operator (C-string).
       * @param a_value The C-string to divide by.
       * @return Reference to this variant.
       */
      BasicVariant& operator/=(const char* a_value);

      /**
       * @brief Division operator.
       * @param a_value The value to divide by.
       * @return A new variant with the result.
       */
      BasicVariant operator/(const BasicVariant& a_value) const;

      /**
       * @brief Division operator (template).
       * @tparam Ty The type of the value.
       * @param a_value The value to divide by.
       * @return A new variant with the result.
       */
      template <typename Ty>
      BasicVariant operator/(const Ty& a_value) const;

      /**
       * @brief Division operator (C-string).
       * @param a_value The C-string to divide by.
       * @return A new variant with the result.
       */
      BasicVariant operator/(const char* a_value) const;

      // ---------------------------------------------------------------------------
      // Type Information and Accessors
      // ---------------------------------------------------------------------------

      /**
       * @brief Returns the type index of the stored value.
       * @return The type index, or 0 if empty.
       */
      unsigned int getDataTypeIndex() const;

      /**
       * @brief Returns the full type index (including reference/const info).
       * @return The type index, or 0 if empty.
       */
      unsigned int getTypeIndex() const;

      /**
       * @brief Returns the TypeInfo structure of the stored value.
       * @return Pointer to TypeInfo, or 0 if empty.
       */
      const TypeInfo* getTypeInfo() const;

      /**
       * @brief Returns a raw pointer to the stored data.
       * @return Pointer to the data.
       */
      void* ptr();

      /**
       * @brief Returns a const raw pointer to the stored data.
       * @return Const pointer to the data.
       */
      const void* ptr() const;

      /**
       * @brief Checks if the variant is empty.
       * @return true if no type is set.
       */
      inline bool empty() const { return _typeInfo == 0; }

      /**
       * @brief Checks if the variant holds a reference type.
       * @return true if the stored type is a reference.
       */
      inline bool isReference() const { return _typeInfo ? TypeIndexConverter<>::isSingleReference(_typeInfo->index) : false; }

      /**
       * @brief Converts the variant to the specified type, potentially modifying the stored value.
       *
       * @tparam TResult The target type.
       * @return Reference to the value as TResult.
       */
      template <typename TResult>
      typename std::remove_const< typename std::remove_reference<TResult>::type >::type& as();

      /**
       * @brief Retrieves the value as the specified type without conversion.
       *
       * @tparam TResult The target type.
       * @return Reference to the value as TResult.
       * @throws VariantTypeMismatchExeption if the types do not match.
       */
      template <typename TResult>
      typename std::remove_const< typename std::remove_reference<TResult>::type >::type& get();

      /**
       * @brief Converts the variant to the specified type (returns by value).
       *
       * @tparam TResult The target type.
       * @return The value converted to TResult.
       */
      template <typename TResult>
      TResult cast() const;

      /**
       * @brief Checks if the variant holds the specified type (data index match).
       *
       * @tparam TType The type to check.
       * @return true if the data type matches.
       */
      template <typename TType>
      bool is() const;

      /**
       * @brief Checks if the variant holds the specified type strictly (full type index match).
       *
       * @tparam TType The type to check.
       * @return true if the full type matches.
       */
      template <typename TType>
      bool strictIs() const;

      /**
       * @brief Checks if the data is stored in the internal buffer (SOO).
       * @return true if stored internally, false if on heap.
       */
      bool isInnerMemory() const{
        return _size() <= innerBufferSize;
      }

    private:
      /**
       * @brief Structure representing a data endpoint (type info and pointer).
       */
      struct DataEndpoint {
        const TypeInfo*  typeInfo;
        void*            ptr;
      };

      /**
       * @brief Structure representing a const data endpoint.
       */
      struct ConstDataEndpoint {
        const TypeInfo*  typeInfo;
        void*            ptr;
        bool             isConst;
      };

      /**
       * @brief Structure representing an extended data endpoint.
       */
      struct DataEndpointEx {
        const TypeInfo*  typeInfo;
        void*            ptr;
      };

      /**
       * @brief Structure representing a variant endpoint (for nested variants).
       */
      struct VariantEndpoint{
        void* variant;
        bool  isConst;
        size_t innerSize;
      };

      /**
       * @brief Calculates the size of the stored type.
       * @return The size in bytes.
       */
      inline size_t _size() const{
        return _size(_typeInfo);
      }

      /**
       * @brief Calculates the size of a given TypeInfo.
       * @param a_typeInfo Pointer to TypeInfo.
       * @return The size in bytes.
       */
      inline size_t _size(const TypeInfo* a_typeInfo) const{
        return !a_typeInfo || TypeIndexConverter<>::isReference(a_typeInfo->index) ? sizeof(void*) : a_typeInfo->size;
      }

      /**
       * @brief Destroys the current value and frees memory.
       */
      void _destroy();

      /**
       * @brief Clones data from another variant (no conversion).
       * @tparam DataType The target data type.
       * @tparam ReferenceType The reference type.
       * @tparam InputInnerBufferSize The buffer size of the source.
       * @param a_enableConvert Tag indicating conversion is disabled.
       * @param a_variant The source variant.
       * @param a_mode The data mode.
       */
      template <typename DataType, typename ReferenceType, size_t InputInnerBufferSize>
      void _clone(std::false_type a_enableConvert, const BasicVariant<InputInnerBufferSize>& a_variant, DataSetMode a_mode);

      /**
       * @brief Clones data from another variant (with conversion).
       * @tparam DataType The target data type.
       * @tparam ReferenceType The reference type.
       * @tparam InputInnerBufferSize The buffer size of the source.
       * @param a_enableConvert Tag indicating conversion is enabled.
       * @param a_variant The source variant.
       * @param a_mode The data mode.
       */
      template <typename DataType, typename ReferenceType, size_t InputInnerBufferSize>
      void _clone(std::true_type a_enableConvert, const BasicVariant<InputInnerBufferSize>& a_variant, DataSetMode a_mode);

      /**
       * @brief Resets and sets a new value.
       * @tparam DataType The target data type.
       * @tparam ReferenceType The reference type.
       * @tparam Ty The source type.
       * @param a_value The value to set.
       * @param a_dataMode The data mode.
       */
      template <typename DataType, typename ReferenceType, typename Ty>
      void _reset(const Ty& a_value, DataSetMode a_dataMode);

      /**
       * @brief Assigns a value (internal helper).
       * @tparam Ty The source type.
       * @param a_value The value to assign.
       */
      template <typename Ty>
      void _assigment(const Ty& a_value);

      /**
       * @brief Initializes the variant with a value (no conversion).
       * @tparam DataType The target data type.
       * @tparam ReferenceType The reference type.
       * @tparam ArgTy The argument type.
       * @param a_enableConvert Tag indicating conversion is disabled.
       * @param a_value The value to initialize with.
       * @param a_dataMode The data mode.
       */
      template <typename DataType, typename ReferenceType, typename ArgTy>
      void _init(std::false_type a_enableConvert, ArgTy& a_value, DataSetMode a_dataMode);

      /**
       * @brief Initializes the variant with a value (with conversion).
       * @tparam DataType The target data type.
       * @tparam ReferenceType The reference type.
       * @tparam ArgTy The argument type.
       * @param a_enableConvert Tag indicating conversion is enabled.
       * @param a_value The value to initialize with.
       * @param a_dataMode The data mode.
       */
      template <typename DataType, typename ReferenceType, typename ArgTy>
      void _init(std::true_type a_enableConvert, ArgTy& a_value, DataSetMode a_dataMode);

      /**
       * @brief Low-level set using type indices.
       * @param a_typeIndex The target type index.
       * @param a_sourceData Pointer to source data.
       * @param a_sourceTypeIndex The source type index.
       * @param a_options Conversion options.
       * @param a_convertFunction Custom conversion function.
       */
      void _set(unsigned int a_typeIndex, const void* a_sourceData, unsigned int a_sourceTypeIndex = 0, ConvertOptions* a_options = 0, ConvertFunction a_convertFunction = 0);

      /**
       * @brief Resolves the variant endpoint (handles nested variants).
       * @return The resolved VariantEndpoint.
       */
      inline VariantEndpoint _variantEndpoint();

      /**
       * @brief Resolves the data endpoint (handles nested variants).
       * @return The resolved DataEndpoint.
       */
      inline DataEndpoint _dataEndpoint();

      /**
       * @brief Resolves the const data endpoint.
       * @return The resolved ConstDataEndpoint.
       */
      inline ConstDataEndpoint _constDataEndpoint();

      /**
       * @brief Resolves the extended data endpoint.
       * @return The resolved DataEndpointEx.
       */
      inline DataEndpointEx _dataEndpointEx();

      /**
       * @brief Helper for less-than comparison.
       * @tparam Ty The type to compare against.
       * @param a_value The value.
       * @return true if *this < a_value.
       */
      template <typename Ty>
      bool _less(const Ty& a_value) const;

      /**
       * @brief Helper for less-than-or-equal comparison.
       * @tparam Ty The type to compare against.
       * @param a_value The value.
       * @return true if *this <= a_value.
       */
      template <typename Ty>
      bool _lessEqual(const Ty& a_value) const;

      /**
       * @brief Helper for equality comparison.
       * @tparam Ty The type to compare against.
       * @param a_value The value.
       * @return true if *this == a_value.
       */
      template <typename Ty>
      bool _equal(const Ty& a_value) const;

      /**
       * @brief Performs arithmetic operation in-place.
       * @tparam TSpecificator The specificator type (e.g., AddSpecificator).
       * @tparam InputInnerBufferSize The buffer size of the source.
       * @param a_value The source value.
       * @return Reference to this variant.
       */
      template <typename TSpecificator, size_t InputInnerBufferSize>
      inline BasicVariant& _selfCalcTo(const BasicVariant<InputInnerBufferSize>& a_value);

      /**
       * @brief Performs arithmetic operation returning a new variant.
       * @tparam TSpecificator The specificator type.
       * @tparam InputInnerBufferSize The buffer size of the source.
       * @param a_value The source value.
       * @return A new variant with the result.
       */
      template <typename TSpecificator, size_t InputInnerBufferSize>
      inline BasicVariant _selfCalc(const BasicVariant<InputInnerBufferSize>& a_value) const;

      /**
       * @brief Performs arithmetic operation in-place with generic type.
       * @tparam TSpecificator The specificator type.
       * @tparam Ty The source type.
       * @param a_value The source value.
       * @return Reference to this variant.
       */
      template <typename TSpecificator, typename Ty>
      inline BasicVariant& _calcTo(const Ty& a_value);

      /**
       * @brief Performs arithmetic operation returning a new variant with generic type.
       * @tparam TSpecificator The specificator type.
       * @tparam Ty The source type.
       * @param a_value The source value.
       * @return A new variant with the result.
       */
      template <typename TSpecificator, typename Ty>
      inline BasicVariant _calc(const Ty& a_value) const;


      const TypeInfo* _typeInfo; ///< Pointer to the type information of the stored value.
      void*           _ptr;      ///< Pointer to the actual data (either internal or heap).
      char            _mem[innerBufferSize]; ///< Internal buffer for Small Object Optimization.
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_VARIANT__VARIANT_DEFINITION_HPP___
