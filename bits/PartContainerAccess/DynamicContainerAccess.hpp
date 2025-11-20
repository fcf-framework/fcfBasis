#ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__DYNAMIC_CONTAINER_ACCESS_HPP___
#define ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__DYNAMIC_CONTAINER_ACCESS_HPP___

#include "DynamicContainerAccessBase.hpp"

namespace fcf {

  template <bool IsConstValue>
  struct DynamicContainerAccessHelper{

    template <typename TContainerAcces, typename TValue>
    void set(TContainerAcces& a_container, const TValue& a_value){
      a_container.value() = a_value;
    }
  };

  template <>
  struct DynamicContainerAccessHelper<false>{

    template <typename TContainerAcces, typename TValue>
    void set(TContainerAcces& /*a_container*/, const TValue& /*a_value*/){
      throw std::runtime_error("The container does not support the recording of the value");
    }
  };

  template <typename TContainerAccess>
  class DynamicContainerAccess : public DynamicContainerAccessBase {
    public:
      enum { is_const_resolve_value = TContainerAccess::is_const_resolve_value };

      typedef typename TContainerAccess::container_type             container_type;
      typedef typename TContainerAccess::key_type                   key_type;
      typedef typename TContainerAccess::value_type                 value_type;
      typedef DynamicContainerAccessHelper<is_const_resolve_value>  helper_type;

      DynamicContainerAccess(){
      }

      DynamicContainerAccess(container_type& a_container, ::fcf::ContainerPosition a_position = ::fcf::CP_BEGIN)
        : _containerAccess(a_container, a_position){
      }

      virtual ~DynamicContainerAccess() {
      }

      virtual bool isFlatContainer(){
        return TContainerAccess::is_flat;
      }

      virtual void setBeginPosition() {
        _containerAccess.setBeginPosition();
      }

      virtual void setEndPosition() {
        _containerAccess.setEndPosition();
      }

      virtual void setPosition(const ::fcf::Variant& a_key, bool a_create = false){
        _containerAccess.setPosition(a_key.cast<key_type>(), a_create);
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

      virtual void setValue(const Variant& a_value){
        helper_type().set(_containerAccess, a_value.cast<value_type>());
      }

      virtual unsigned int getValueTypeIndex() const {
        return Type<typename TContainerAccess::value_type>().index();
      }

      virtual unsigned int getKeyTypeIndex() const {
        return Type<typename TContainerAccess::key_type>().index();
      }

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
