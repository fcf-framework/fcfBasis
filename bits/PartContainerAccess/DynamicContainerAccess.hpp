#ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__DYNAMIC_CONTAINER_ACCESS_HPP___
#define ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__DYNAMIC_CONTAINER_ACCESS_HPP___

#include "DynamicContainerAccessBase.hpp"

namespace fcf {

  template <typename TContainerAccess>
  class DynamicContainerAccess : public DynamicContainerAccessBase {
    public:

      typedef typename TContainerAccess::container_type container_type;
      typedef typename TContainerAccess::key_type       key_type;
      typedef typename TContainerAccess::value_type     value_type;

      DynamicContainerAccess(){
      }

      DynamicContainerAccess(container_type& a_container, ::fcf::ContainerPosition a_position = ::fcf::CP_BEGIN)
        : _containerAccess(a_container, a_position){
      }

      virtual ~DynamicContainerAccess() {
      }

      virtual void setBeginPosition() {
        _containerAccess.setBeginPosition();
      }

      virtual void setEndPosition() {
        _containerAccess.setBeginPosition();
      }

      virtual void setPosition(const ::fcf::Variant& a_key){
        _containerAccess.setPosition(a_key.get<key_type>());
      };

      virtual void dec(){
        --_containerAccess;
      }

      virtual void inc(){
        ++_containerAccess;
      }

      virtual void* getValuePtr() {
        typedef decltype(_containerAccess.value()) resolve_type;
        if (std::is_const< resolve_type >::value) {
          throw std::runtime_error("The type does not support access to modify the stored value.");
        }
        return (void*)&_containerAccess.value();
      };

      virtual const void* getConstValuePtr() const {
        return & ((TContainerAccess&)_containerAccess).value();
      };

      virtual Variant getValue() const {
        return Variant(((TContainerAccess&)_containerAccess).value());
      }

      virtual Variant getKey() const {
        return Variant(_containerAccess.key());
      }

      virtual size_t getContainerSize() const {
        return _containerAccess.getContainerSize();
      }

      virtual bool isEnd() const {
        return _containerAccess.isEnd();
      }

      virtual bool equal(DynamicContainerAccessBase& a_containerAccess) const{
        TContainerAccess* arg = dynamic_cast<TContainerAccess*>(&a_containerAccess);
        return _containerAccess == *arg;
      }

    protected:
      TContainerAccess _containerAccess;
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__DYNAMIC_CONTAINER_ACCESS_HPP___
