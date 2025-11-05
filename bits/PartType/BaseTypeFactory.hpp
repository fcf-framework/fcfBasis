#ifndef ___FCF_BASIS__BITS__PART_TYPE__BASE_TYPE_FACTORY_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__BASE_TYPE_FACTORY_HPP___

#include "../../macro.hpp"
#include "BaseTypeWrapper.hpp"
namespace fcf{

  class FCF_BASIS_DECL_EXPORT BaseTypeFactory {
    public:
      virtual ~BaseTypeFactory();
      virtual size_t size() = 0;
      virtual BaseTypeWrapper* clone(const void* a_pdata) = 0;
      virtual BaseTypeWrapper* clone(char* a_mem, const void* a_pdata) = 0;
      virtual BaseTypeWrapper* create() = 0;
      virtual BaseTypeWrapper* create(char* a_mem) = 0;
  };

  #ifdef FCF_BASIS_IMPLEMENTATION
    BaseTypeFactory::~BaseTypeFactory(){
    }
  #endif

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__BASE_TYPE_FACTORY_HPP___
