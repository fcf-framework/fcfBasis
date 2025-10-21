#ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__DYNAMIC_CONTAINER_ACCESS_BASE_HPP___
#define ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__DYNAMIC_CONTAINER_ACCESS_BASE_HPP___

#include "../../macro.hpp"
#include "ContainerPosition.hpp"
#include "../../Variant.hpp"

namespace fcf {

  class DynamicContainerAccessBase {
    public:
      virtual ~DynamicContainerAccessBase();

      virtual void        setBeginPosition() = 0;
      virtual void        setEndPosition() = 0;
      virtual void        setPosition(const ::fcf::Variant& a_key) = 0;
      virtual void        dec() = 0;
      virtual void        inc() = 0;
      virtual void*       getValuePtr() = 0;
      virtual const void* getConstValuePtr() const = 0;
      virtual Variant     getValue() const = 0;
      virtual Variant     getKey() const = 0;
      virtual size_t      getContainerSize() const = 0;
      virtual bool        isEnd() const = 0;
      virtual bool        equal(DynamicContainerAccessBase& a_containerAccess) const = 0;

  };

  #ifdef FCF_BASIS_IMPLEMENTATION
    DynamicContainerAccessBase::~DynamicContainerAccessBase(){
    };
  #endif
} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__DYNAMIC_CONTAINER_ACCESS_BASE_HPP___
