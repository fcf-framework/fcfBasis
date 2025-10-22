#ifndef ___FCF__BASIS__BITS__PART_TYPE__GET_TYPE_INFO_HPP___
#define ___FCF__BASIS__BITS__PART_TYPE__GET_TYPE_INFO_HPP___

#include <exception>
#include "TypeInfo.hpp"

namespace fcf {

  inline const TypeInfo& getTypeInfo(unsigned int a_typeIndex){
    const fcf::TypeInfo* ptr = Details::typeStorage.get(a_typeIndex);
    if (!ptr) {
      throw std::runtime_error("The requested type index is not registered");
    }
    return *ptr;
  }

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_TYPE__GET_TYPE_INFO_HPP___
