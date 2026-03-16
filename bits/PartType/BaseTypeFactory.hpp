#ifndef ___FCF_BASIS__BITS__PART_TYPE__BASE_TYPE_FACTORY_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__BASE_TYPE_FACTORY_HPP___

#include "../../macro.hpp"
namespace fcf{

  class BaseTypeFactory {
    public:
      typedef void  (*SetFunction)(void* a_destination, const void* a_source);
      typedef void* (*CloneFunction)(void* a_mem, const void* a_pdata);
      typedef void* (*CreateFunction)(void* a_mem);
      typedef void  (*DestroyFunction)(void* a_mem);

      template <typename TFactory>
      inline void initialize() {
        set = TFactory::_set;
        clone = TFactory::_clone;
        create = TFactory::_create;
        destroy = TFactory::_destroy;
      }

      SetFunction     set;
      CloneFunction   clone;
      CreateFunction  create;
      DestroyFunction destroy;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__BASE_TYPE_FACTORY_HPP___
