#ifndef ___FCF__BASIS__BITS__PART_TYPE__GET_TYPE_INFO_HPP___
#define ___FCF__BASIS__BITS__PART_TYPE__GET_TYPE_INFO_HPP___

#include <exception>
#include "TypeInfo.hpp"
#include "../../Exception.hpp"
namespace fcf {

  inline const TypeInfo* getTypeInfo(unsigned int a_typeIndex){
    const fcf::TypeInfo* ptr = typeStorage.get(a_typeIndex);
    if (!ptr) {
      throw TypeIndexNotRegisteredException(__FILE__, __LINE__, a_typeIndex);
    }
    return ptr;
  }

  inline const TypeInfo* getTypeInfo(unsigned int a_typeIndex, Exception* a_errorDst){
    try {
      return getTypeInfo(a_typeIndex);
    } catch(const Exception& e){
      if (a_errorDst){
        *a_errorDst = e;
      }
      return 0;
    }
  }

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_TYPE__GET_TYPE_INFO_HPP___
