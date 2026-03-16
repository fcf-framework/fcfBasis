#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_FACTORY_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_FACTORY_HPP___

#include "BaseTypeFactory.hpp"

namespace fcf {

  template <typename Ty>
  class FCF_BASIS_DECL_EXPORT TypeFactory : public BaseTypeFactory {
    public:
      virtual void   set(void* a_destination, const void* a_source);
      virtual void*  clone(void* a_mem, const void* a_pdata);
      virtual void*  create(void* a_mem);
      virtual void   destroy(void* a_mem);
      virtual BaseTypeFactory* createFactory();
  };

  template <typename Ty>
  class FCF_BASIS_DECL_EXPORT TypeFactory<Ty&> : public BaseTypeFactory {
      virtual void   set(void* a_destination, const void* a_source);
      virtual void*  clone(void* a_mem, const void* a_pdata);
      virtual void*  create(void* a_mem);
      virtual void   destroy(void* a_mem);
      virtual BaseTypeFactory* createFactory();
  };

} // fcf namespace

#include "NDetails/AssigmentWrapper.hpp"

namespace fcf {


  template <typename Ty>
  void TypeFactory<Ty>::set(void* a_destination, const void* a_source){
    NDetails::AssigmentWrapper<Ty>()(a_destination, a_source);
  }

  template <typename Ty>
  void* TypeFactory<Ty>::clone(void* a_mem, const void* a_pdata){
    if (!a_mem){
      a_mem = new char[sizeof(Ty)];
    }
    return (void*)(new (a_mem) Ty(*(const Ty*)a_pdata));
  }

  template <typename Ty>
  void* TypeFactory<Ty>::create(void* a_mem){
    if (!a_mem){
      a_mem = new char[sizeof(Ty)];
    }
    return (void*)(new (a_mem) Ty());
  }

  template <typename Ty>
  void TypeFactory<Ty>::destroy(void* a_mem){
    ((Ty*)a_mem)->~Ty();
  }

  template <typename Ty>
  BaseTypeFactory* TypeFactory<Ty>::createFactory(){
    return new TypeFactory<Ty>();
  }



  template <typename Ty>
  void TypeFactory<Ty&>::set(void* a_destination, const void* a_source){
    NDetails::AssigmentWrapper<Ty>()(a_destination, a_source);
  }

  template <typename Ty>
  void* TypeFactory<Ty&>::clone(void* a_mem, const void* a_pdata){
    if (!a_mem){
      throw std::runtime_error("The reference could not be created with memory allocation");
    }
    typedef Ty* PtrType;
    PtrType* p = (PtrType*)a_mem;
    *p = (PtrType)a_pdata;
    return *(void**)p;
  }

  template <typename Ty>
  void* TypeFactory<Ty&>::create(void* a_mem){
    throw std::runtime_error("A reference cannot be created without a data source");
    if (!a_mem){
      throw std::runtime_error("The reference could not be created with memory allocation");
    }
    typedef Ty* PtrType;
    PtrType* p = (PtrType*)a_mem;
    return *(void**)p;
  }

  template <typename Ty>
  void TypeFactory<Ty&>::destroy(void* /*a_mem*/){
  }

  template <typename Ty>
  BaseTypeFactory* TypeFactory<Ty&>::createFactory(){
    return new TypeFactory<Ty&>();
  }

} // fcf namespace


#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_FACTORY_HPP___
