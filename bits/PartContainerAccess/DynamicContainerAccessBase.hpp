#ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__DYNAMIC_CONTAINER_ACCESS_BASE_HPP___
#define ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__DYNAMIC_CONTAINER_ACCESS_BASE_HPP___

#include "../../macro.hpp"
#include "ContainerPosition.hpp"
#include "../../Variant.hpp"

namespace fcf {

  class DynamicContainerAccessBase {
    public:
      virtual ~DynamicContainerAccessBase();

      virtual bool          isFlatContainer() = 0;
      virtual void          setBeginPosition() = 0;
      virtual void          setEndPosition() = 0;
      virtual void          setPosition(const ::fcf::Variant& a_key, bool a_create = false) = 0;
      virtual void          dec() = 0;
      virtual void          inc() = 0;
      virtual void*         getValuePtr() = 0;
      virtual const void*   getConstValuePtr() const = 0;
      virtual Variant       getValue() const = 0;
      virtual void          setValue(const Variant& a_value) = 0;
      virtual unsigned int  getValueTypeIndex() const = 0;
      virtual Variant       getKey() const = 0;
      virtual unsigned int  getKeyTypeIndex() const = 0;
      virtual size_t        getContainerSize() const = 0;
      virtual bool          isEnd() const = 0;
      virtual bool          equal(DynamicContainerAccessBase& a_containerAccess) const = 0;

      inline operator bool(){
        return !isEnd();
      }
      inline DynamicContainerAccessBase& operator++(){
        inc();
        return *this;
      }

      inline DynamicContainerAccessBase& operator--(){
        dec();
        return *this;
      }
  };

  #ifdef FCF_BASIS_IMPLEMENTATION
    DynamicContainerAccessBase::~DynamicContainerAccessBase(){
    };
  #endif
} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__DYNAMIC_CONTAINER_ACCESS_BASE_HPP___
