#ifndef ___FCF__BASIS__BITS__PART_TYPE__GET_TYPE_INFO_HPP___
#define ___FCF__BASIS__BITS__PART_TYPE__GET_TYPE_INFO_HPP___

#include <exception>
#include "TypeInfo.hpp"
#include "../../PartException.hpp"

namespace fcf {

  /**
   * @brief Retrieves the constant pointer to TypeInfo for a given TypeIndex.
   * 
   * @param a_typeIndex The unique identifier of the type.
   * @return A constant pointer to the TypeInfo structure associated with the index.
   * @throws TypeIndexNotRegisteredException if the provided index is not found in the registry.
   */
  inline const TypeInfo* getTypeInfo(TypeIndex a_typeIndex){
    const fcf::TypeInfo* ptr = getTypeStorage().get(a_typeIndex);
    if (!ptr) {
      throw TypeIndexNotRegisteredException(__FILE__, __LINE__, a_typeIndex);
    }
    return ptr;
  }

  /**
   * @brief Attempts to retrieve the constant pointer to TypeInfo for a given TypeIndex without throwing an exception.
   * 
   * @param a_typeIndex The unique identifier of the type.
   * @param a_errorDst Pointer to an Exception object where error details will be stored if the index is not registered. 
   *                  If this pointer is null, no error is recorded.
   * @return A constant pointer to the TypeInfo structure, or nullptr if the index is not registered.
   */
  inline const TypeInfo* getTypeInfo(TypeIndex a_typeIndex, Exception* a_errorDst){
    const fcf::TypeInfo* ptr = getTypeStorage().get(a_typeIndex);
    if (!ptr) {
      if (a_errorDst){
        *a_errorDst = TypeIndexNotRegisteredException(__FILE__, __LINE__, a_typeIndex);
      }
      return 0;
    }
    return ptr;
  }

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_TYPE__GET_TYPE_INFO_HPP___