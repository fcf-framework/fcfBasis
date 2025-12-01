#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_WRAPPER_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_WRAPPER_HPP___

#include <iostream>
#include "../../macro.hpp"
#include "BaseTypeWrapper.hpp"
#include "NDetails/AssigmentWrapper.hpp"

namespace fcf{
  
  template <typename Ty>
  class FCF_BASIS_DECL_EXPORT TypeWrapper : public BaseTypeWrapper {
    public:
      typedef typename std::remove_const<Ty>::type UnconstType;

      TypeWrapper(const Ty& a_item);
      TypeWrapper(); 
      ~TypeWrapper(); 
      virtual void* ptr();
      virtual size_t size(); 
      virtual void set(const void* a_source);
      virtual BaseTypeWrapper* clone();
      virtual BaseTypeWrapper* clone(char* a_mem);
      virtual BaseTypeWrapper* referenceClone(char* a_mem);
      virtual BaseTypeWrapper* create();
      virtual BaseTypeWrapper* create(char* a_mem);

      UnconstType data;
  };

  template <typename Ty>
  class FCF_BASIS_DECL_EXPORT TypeWrapper<Ty&> : public BaseTypeWrapper {
    public:
      typedef typename std::remove_const<Ty>::type UnconstType;

      TypeWrapper(const Ty& a_item);
      TypeWrapper();
      ~TypeWrapper();
      virtual void* ptr();
      virtual size_t size();
      virtual void set(const void* a_source);
      virtual BaseTypeWrapper* clone();
      virtual BaseTypeWrapper* clone(char* a_mem);
      virtual BaseTypeWrapper* referenceClone(char* a_mem);
      virtual BaseTypeWrapper* create();
      virtual BaseTypeWrapper* create(char* a_mem);

      UnconstType* data;
  };


  template <typename Ty>
  TypeWrapper<Ty&>::TypeWrapper(const Ty& a_item)
    : data((UnconstType*)&a_item){
  }

  template <typename Ty>
  TypeWrapper<Ty&>::TypeWrapper() {
  }

  template <typename Ty>
  TypeWrapper<Ty&>::~TypeWrapper() {
  }

  template <typename Ty>
  void* TypeWrapper<Ty&>::ptr(){
    return (void*)data;
  }

  template <typename Ty>
  size_t TypeWrapper<Ty&>::size() {
    return sizeof(TypeWrapper<Ty&>);
  }

  template <typename Ty>
  void TypeWrapper<Ty&>::set(const void* a_source){
    NDetails::AssigmentWrapper<Ty>()((void*)data, a_source);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty&>::clone(){
    return new TypeWrapper<Ty&>(*data);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty&>::clone(char* a_mem){
    return new (a_mem) TypeWrapper<Ty&>(*data);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty&>::referenceClone(char* a_mem){
    return new (a_mem) TypeWrapper<Ty&>(*data);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty&>::create(){
    return new TypeWrapper<Ty&>();
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty&>::create(char* a_mem){
    return new (a_mem) TypeWrapper<Ty&>();
  }





  template <typename Ty>
  TypeWrapper<Ty>::TypeWrapper(const Ty& a_item)
    : data(a_item){
  }

  template <typename Ty>
  TypeWrapper<Ty>::TypeWrapper() {
  }

  template <typename Ty>
  TypeWrapper<Ty>::~TypeWrapper() {
  }

  template <typename Ty>
  void* TypeWrapper<Ty>::ptr(){
    return (void*)&data;
  }

  template <typename Ty>
  size_t TypeWrapper<Ty>::size() {
    return sizeof(TypeWrapper<Ty>);
  }

  template <typename Ty>
  void TypeWrapper<Ty>::set(const void* a_source){
    NDetails::AssigmentWrapper<Ty>()((void*)&data, a_source);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty>::clone(){
    return new TypeWrapper<Ty>(data);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty>::clone(char* a_mem){
    return new (a_mem) TypeWrapper<Ty>(data);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty>::referenceClone(char* a_mem){
    return new (a_mem) TypeWrapper<Ty&>(data);
  }


  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty>::create(){
    return new TypeWrapper<Ty>();
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty>::create(char* a_mem){
    return new (a_mem) TypeWrapper<Ty>();
  }

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_WRAPPER_HPP___
