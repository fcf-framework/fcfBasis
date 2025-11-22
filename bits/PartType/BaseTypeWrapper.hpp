#ifndef ___FCF_BASIS__BITS__PART_TYPE__BASE_TYPE_WRAPPER_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__BASE_TYPE_WRAPPER_HPP___

#include "../../macro.hpp"

namespace fcf{

  class FCF_BASIS_DECL_EXPORT BaseTypeWrapper {
    public:
      virtual ~BaseTypeWrapper();
      virtual size_t size() = 0;
      virtual void set(const void* a_source) = 0;
      virtual BaseTypeWrapper* clone() = 0;
      virtual BaseTypeWrapper* clone(char* a_mem) = 0;
      virtual BaseTypeWrapper* referenceClone(char* a_mem) = 0;
      virtual BaseTypeWrapper* create() = 0;
      virtual BaseTypeWrapper* create(char* a_mem) = 0;
      virtual void* ptr() = 0;
  };

  #ifdef FCF_BASIS_IMPLEMENTATION
    BaseTypeWrapper::~BaseTypeWrapper(){
    }
  #endif

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__BASE_TYPE_WRAPPER_HPP___
