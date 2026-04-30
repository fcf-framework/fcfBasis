#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_FACTORY_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_FACTORY_HPP___

#include "BaseTypeFactory.hpp"
#include "NDetails/AssigmentWrapper.hpp"
#include "../../bits/PartException/Exception.hpp"
#include "../../bits/PartException/exceptions.hpp"

namespace fcf {

  template <typename Ty>
  class TypeFactory : public BaseTypeFactory {
    public:
      friend class BaseTypeFactory;

      TypeFactory() {
        initialize< TypeFactory<Ty> >();
      }

    protected:
      static void _set(void* a_destination, const void* a_source){
        NDetails::AssigmentWrapper<Ty>()(a_destination, a_source);
      }

      static void* _clone(void* a_mem, const void* a_pdata){
        bool allocMode = false;
        if (!a_mem){
          a_mem = new char[sizeof(Ty)];
          allocMode = true;
        }
        try {
          new (a_mem) Ty(*(const Ty*)a_pdata);
        } catch(...) {
          if (allocMode) {
            delete (char*)a_mem;
          }
          throw;
        }
        return a_mem;
      }

      static void* _create(void* a_mem){
        bool allocMode = false;
        if (!a_mem){
          a_mem = new char[sizeof(Ty)];
          allocMode = true;
        }
        try {
          new (a_mem) Ty();
        } catch(...) {
          if (allocMode) {
            delete (char*)a_mem;
          }
          throw;
        }
        return a_mem;
      }

      static void _destroy(void* a_mem){
        ((Ty*)a_mem)->~Ty();
      }

  };

  class BaseRefTypeFactory : public BaseTypeFactory {
    public:
      friend class BaseTypeFactory;

      static void* _clone(void* a_mem, const void* a_pdata){
        if (!a_mem){
          throw fcf::ReferenceAllocationException(__FILE__, __LINE__);
        }
        typedef void* PtrType;
        PtrType* p = (PtrType*)a_mem;
        *p = (PtrType)a_pdata;
        return *(void**)p;
      }

      static void* _create(void* /*a_mem*/){
        throw fcf::ReferenceCreationException(__FILE__, __LINE__);
      }

      static void _destroy(void* /*a_mem*/){
      }
  };

  template <typename Ty>
  class TypeFactory<Ty&> : public BaseRefTypeFactory {
    public:
      friend class BaseTypeFactory;

      TypeFactory() {
        initialize< TypeFactory<Ty&> >();
      }

    protected:
      static void _set(void* a_destination, const void* a_source){
        NDetails::AssigmentWrapper<Ty>()(a_destination, a_source);
      }

  };

  template <typename Ty>
  BaseTypeFactory* getTypeFactory(){
    static TypeFactory<Ty> factory;
    return &factory;
  }

} // fcf namespace


#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_FACTORY_HPP___
