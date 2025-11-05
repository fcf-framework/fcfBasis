#ifndef ___FCF__BASIS__BITS__PART_TYPE__GET_TYPE_INFO_HPP___
#define ___FCF__BASIS__BITS__PART_TYPE__GET_TYPE_INFO_HPP___

#include <exception>
#include "TypeInfo.hpp"

namespace fcf {

  inline const TypeInfo* getTypeInfo(unsigned int a_typeIndex, std::exception const ** a_errorDst = 0){
    if (a_errorDst) {
      *a_errorDst = 0;
    }
    const fcf::TypeInfo* ptr = typeStorage.get(a_typeIndex);
    if (!ptr) {
      if (a_errorDst) {
        static const std::runtime_error error("The requested type index is not registered");
        *a_errorDst = &error;
      } else {
        throw std::runtime_error("The requested type index is not registered");
      }
    }
    return ptr;
  }

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_TYPE__GET_TYPE_INFO_HPP___
