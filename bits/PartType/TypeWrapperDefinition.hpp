#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_WRAPPER_DEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_WRAPPER_DEFINITION_HPP___

#include "../../macro.hpp"
#include "BaseTypeWrapper.hpp"

namespace fcf{
  
  template <typename Ty>
  class FCF_BASIS_DECL_EXPORT TypeWrapper : public BaseTypeWrapper {
    public:
      typedef typename std::remove_const<Ty>::type UnconstType;

      TypeWrapper(const Ty& a_item);
      TypeWrapper(); 
      ~TypeWrapper(); 
      virtual void*             rootPtr();
      virtual BaseTypeWrapper*  rootWrapper();
      virtual size_t            size(); 
      virtual void              set(const void* a_source);
      virtual BaseTypeWrapper*  clone();
      virtual BaseTypeWrapper*  clone(char* a_mem);
      virtual BaseTypeWrapper*  cloneData();
      virtual BaseTypeWrapper*  cloneData(char* a_mem);
      virtual BaseTypeWrapper*  referenceClone(char* a_mem);
      virtual BaseTypeWrapper*  create();
      virtual BaseTypeWrapper*  create(char* a_mem);

      UnconstType data;
  };

  template <typename Ty>
  class FCF_BASIS_DECL_EXPORT TypeWrapper<Ty&> : public BaseTypeWrapper {
    public:
      typedef typename std::remove_const<Ty>::type UnconstType;

      TypeWrapper(const Ty& a_item);
      TypeWrapper();
      ~TypeWrapper();
      virtual void*             rootPtr();
      virtual BaseTypeWrapper*  rootWrapper();
      virtual size_t            size();
      virtual void              set(const void* a_source);
      virtual BaseTypeWrapper*  clone();
      virtual BaseTypeWrapper*  clone(char* a_mem);
      virtual BaseTypeWrapper*  cloneData();
      virtual BaseTypeWrapper*  cloneData(char* a_mem);
      virtual BaseTypeWrapper*  referenceClone(char* a_mem);
      virtual BaseTypeWrapper*  create();
      virtual BaseTypeWrapper*  create(char* a_mem);

      UnconstType* data;
  };
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_WRAPPER_DEFINITION_HPP___
