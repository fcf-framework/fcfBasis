#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_WRAPPER_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_WRAPPER_HPP___

#include "TypeWrapperDefinition.hpp"
#include "NDetails/AssigmentWrapper.hpp"
#include "../../Type.hpp"

namespace fcf {


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
  void* TypeWrapper<Ty>::rootPtr(){
    return (void*)&data;
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty>::rootWrapper(){
    return this;
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
  BaseTypeWrapper* TypeWrapper<Ty>::cloneData(){
    return new TypeWrapper<Ty>(data);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty>::cloneData(char* a_mem){
    return new (a_mem) TypeWrapper<Ty>(data);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty>::referenceClone(char* a_mem){
    return new (a_mem) TypeWrapper<Ty&>(data);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty>::constReferenceClone(char* a_mem){
    typedef const typename std::remove_const<Ty>::type ResType;
    return new (a_mem) TypeWrapper<ResType&>(data);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty>::create(){
    return new TypeWrapper<Ty>();
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty>::create(char* a_mem){
    return new (a_mem) TypeWrapper<Ty>();
  }



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
  void* TypeWrapper<Ty&>::rootPtr(){
    return (void*)data;
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty&>::rootWrapper(){
    return this;
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
  BaseTypeWrapper* TypeWrapper<Ty&>::cloneData(){
    return new TypeWrapper<Ty>(*data);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty&>::cloneData(char* a_mem){
    return new (a_mem) TypeWrapper<Ty>(*data);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty&>::referenceClone(char* a_mem){
    return new (a_mem) TypeWrapper<Ty&>(*data);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty&>::constReferenceClone(char* a_mem){
    typedef const typename std::remove_const<Ty>::type ResType;
    return new (a_mem) TypeWrapper<ResType&>(*data);
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty&>::create(){
    return new TypeWrapper<Ty&>();
  }

  template <typename Ty>
  BaseTypeWrapper* TypeWrapper<Ty&>::create(char* a_mem){
    return new (a_mem) TypeWrapper<Ty&>();
  }

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_WRAPPER_HPP___
