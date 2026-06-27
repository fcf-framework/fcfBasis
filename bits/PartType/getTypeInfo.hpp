#ifndef ___FCF__BASIS__BITS__PART_TYPE__GET_TYPE_INFO_HPP___
#define ___FCF__BASIS__BITS__PART_TYPE__GET_TYPE_INFO_HPP___

#include <exception>
#include "TypeInfo.hpp"
#include "../../PartException.hpp"

namespace fcf {

  inline const TypeInfo* getTypeInfo(TypeIndex a_typeIndex){
    const fcf::TypeInfo* ptr = getTypeStorage().get(a_typeIndex);
    if (!ptr) {
      throw TypeIndexNotRegisteredException(__FILE__, __LINE__, a_typeIndex);
    }
    return ptr;
  }

  inline const TypeInfo* getTypeInfo(TypeIndex a_typeIndex, Exception* a_errorDst){
    const fcf::TypeInfo* ptr = getTypeStorage().get(a_typeIndex);
    if (ptr) {
      return ptr;
    }
    if (a_errorDst){
      *a_errorDst = TypeIndexNotRegisteredException(__FILE__, __LINE__, a_typeIndex);
    }
    return 0;
  }

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_TYPE__GET_TYPE_INFO_HPP___
