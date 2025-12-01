#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_FACTORY_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_FACTORY_HPP___

#include "BaseTypeWrapper.hpp"
#include "TypeWrapper.hpp"
#include "NDetails/AssigmentWrapper.hpp"

namespace fcf {

  template <typename Ty>
  class FCF_BASIS_DECL_EXPORT TypeFactory : public BaseTypeFactory {
    public:
      virtual size_t size(); 
      virtual void set(void* a_destination, const void* a_source);
      virtual BaseTypeWrapper* clone(const void* a_pdata);
      virtual BaseTypeWrapper* clone(char* a_mem, const void* a_pdata);
      virtual BaseTypeWrapper* create();
      virtual BaseTypeWrapper* create(char* a_mem);
  };

  template <typename Ty>
  class FCF_BASIS_DECL_EXPORT TypeFactory<Ty&> : public BaseTypeFactory {
    public:
      virtual size_t size(); 
      virtual void set(void* a_destination, const void* a_source);
      virtual BaseTypeWrapper* clone(const void* a_pdata);
      virtual BaseTypeWrapper* clone(char* a_mem, const void* a_pdata);
      virtual BaseTypeWrapper* create();
      virtual BaseTypeWrapper* create(char* a_mem);
  };


  template <typename Ty>
  size_t TypeFactory<Ty>::size() {
    return sizeof(TypeWrapper<Ty>);
  }


  template <typename Ty>
  void TypeFactory<Ty>::set(void* a_destination, const void* a_source){
    NDetails::AssigmentWrapper<Ty>()(a_destination, a_source);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeFactory<Ty>::clone(const void* a_pdata){
    return new TypeWrapper<Ty>(*(Ty*)a_pdata);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeFactory<Ty>::clone(char* a_mem, const void* a_pdata){
    return new (a_mem) TypeWrapper<Ty>(*(Ty*)a_pdata);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeFactory<Ty>::create(){
    return new TypeWrapper<Ty>();
  }

  template <typename Ty>
  BaseTypeWrapper* TypeFactory<Ty>::create(char* a_mem){
    return new (a_mem) TypeWrapper<Ty>();
  }

  
  
  
  
  
  template <typename Ty>
  size_t TypeFactory<Ty&>::size() {
    return sizeof(TypeWrapper<Ty&>);
  }


  template <typename Ty>
  void TypeFactory<Ty&>::set(void* a_destination, const void* a_source){
    NDetails::AssigmentWrapper<Ty>()(a_destination, a_source);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeFactory<Ty&>::clone(const void* a_pdata){
    return new TypeWrapper<Ty&>(*(Ty*)a_pdata);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeFactory<Ty&>::clone(char* a_mem, const void* a_pdata){
    return new (a_mem) TypeWrapper<Ty&>(*(Ty*)a_pdata);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeFactory<Ty&>::create(){
    return new TypeWrapper<Ty&>();
  }

  template <typename Ty>
  BaseTypeWrapper* TypeFactory<Ty&>::create(char* a_mem){
    return new (a_mem) TypeWrapper<Ty&>();
  }

} // fcf namespace


#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_FACTORY_HPP___
