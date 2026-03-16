#ifndef ___FCF_BASIS__BITS__PART_TYPE__BASE_TYPE_FACTORY_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__BASE_TYPE_FACTORY_HPP___

#include "../../macro.hpp"
namespace fcf{

  class FCF_BASIS_DECL_EXPORT BaseTypeFactory {
    public:
      virtual ~BaseTypeFactory();
      virtual void   set(void* a_destination, const void* a_source) = 0;
      virtual void*  clone(void* a_mem, const void* a_pdata) = 0;
      virtual void*  create(void* a_mem) = 0;
      virtual void   destroy(void* a_mem) = 0;
      virtual BaseTypeFactory* createFactory() = 0;
  };

  #ifdef FCF_BASIS_IMPLEMENTATION
    BaseTypeFactory::~BaseTypeFactory(){
    }
  #endif

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__BASE_TYPE_FACTORY_HPP___
