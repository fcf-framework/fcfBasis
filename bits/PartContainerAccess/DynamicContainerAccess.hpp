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

      DynamicContainerAccess();

      DynamicContainerAccess(container_type& a_container, ::fcf::ContainerPosition a_position = ::fcf::CP_BEGIN);

      virtual ~DynamicContainerAccess();

      virtual bool isFlatContainer();

      virtual void setBeginPosition();

      virtual void setEndPosition();

      virtual void setPosition(const ::fcf::Variant& a_key, bool a_create = false);

      virtual void dec();

      virtual void inc();

      virtual void* getValuePtr();

      virtual void setValue(const Variant& a_value);

      virtual unsigned int getValueTypeIndex() const;

      virtual unsigned int getKeyTypeIndex() const;

      virtual const void* getConstValuePtr() const;

      virtual Variant getValue() const;

      virtual Variant getRefValue();

      virtual Variant getKey() const;

      virtual size_t getContainerSize() const;

      virtual bool isEnd() const;

      virtual bool equal(DynamicContainerAccessBase& a_containerAccess) const;

    protected:
      TContainerAccess _containerAccess;
  };

} // fcf namespace

#include "../../Variant.hpp"

namespace fcf {

  template <typename TContainerAccess>
  DynamicContainerAccess<TContainerAccess>::DynamicContainerAccess(){
  }

  template <typename TContainerAccess>
  DynamicContainerAccess<TContainerAccess>::DynamicContainerAccess(container_type& a_container, ::fcf::ContainerPosition a_position)
    : _containerAccess(a_container, a_position){
  }

  template <typename TContainerAccess>
  DynamicContainerAccess<TContainerAccess>::~DynamicContainerAccess() {
  }

  template <typename TContainerAccess>
  bool DynamicContainerAccess<TContainerAccess>::isFlatContainer(){
    return TContainerAccess::is_flat;
  }

  template <typename TContainerAccess>
  void DynamicContainerAccess<TContainerAccess>::setBeginPosition() {
    _containerAccess.setBeginPosition();
  }

  template <typename TContainerAccess>
  void DynamicContainerAccess<TContainerAccess>::setEndPosition() {
    _containerAccess.setEndPosition();
  }

  template <typename TContainerAccess>
  void DynamicContainerAccess<TContainerAccess>::setPosition(const ::fcf::Variant& a_key, bool a_create){
    _containerAccess.setPosition(a_key.cast<key_type>(), a_create);
  };

  template <typename TContainerAccess>
  void DynamicContainerAccess<TContainerAccess>::dec(){
    --_containerAccess;
  }

  template <typename TContainerAccess>
  void DynamicContainerAccess<TContainerAccess>::inc(){
    ++_containerAccess;
  }

  template <typename TContainerAccess>
  void* DynamicContainerAccess<TContainerAccess>::getValuePtr() {
    typedef decltype(_containerAccess.value()) resolve_type;
    if (std::is_const< resolve_type >::value) {
      throw std::runtime_error("The type does not support access to modify the stored value.");
    }
    return (void*)&_containerAccess.value();
  };

  template <typename TContainerAccess>
  void DynamicContainerAccess<TContainerAccess>::setValue(const Variant& a_value){
    helper_type().set(_containerAccess, a_value.cast<value_type>());
  }

  template <typename TContainerAccess>
  unsigned int DynamicContainerAccess<TContainerAccess>::getValueTypeIndex() const {
    return Type<typename TContainerAccess::value_type>().index();
  }

  template <typename TContainerAccess>
  unsigned int DynamicContainerAccess<TContainerAccess>::getKeyTypeIndex() const {
    return Type<typename TContainerAccess::key_type>().index();
  }

  template <typename TContainerAccess>
  const void* DynamicContainerAccess<TContainerAccess>::getConstValuePtr() const {
    return & ((TContainerAccess&)_containerAccess).value();
  };

  template <typename TContainerAccess>
  Variant DynamicContainerAccess<TContainerAccess>::getValue() const {
    return Variant(((TContainerAccess&)_containerAccess).value());
  }

  template <typename TContainerAccess>
  Variant DynamicContainerAccess<TContainerAccess>::getRefValue(){
    return Variant(((TContainerAccess&)_containerAccess).value(), Variant::REFERENCE);
  }

  template <typename TContainerAccess>
  Variant DynamicContainerAccess<TContainerAccess>::getKey() const {
    return Variant(_containerAccess.key());
  }

  template <typename TContainerAccess>
  size_t DynamicContainerAccess<TContainerAccess>::getContainerSize() const {
    return _containerAccess.getContainerSize();
  }

  template <typename TContainerAccess>
  bool DynamicContainerAccess<TContainerAccess>::isEnd() const {
    return _containerAccess.isEnd();
  }

  template <typename TContainerAccess>
  bool DynamicContainerAccess<TContainerAccess>::equal(DynamicContainerAccessBase& a_containerAccess) const{
    TContainerAccess* arg = dynamic_cast<TContainerAccess*>(&a_containerAccess);
    return _containerAccess == *arg;
  }

} // fcf namespace
#endif // #ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__DYNAMIC_CONTAINER_ACCESS_HPP___
