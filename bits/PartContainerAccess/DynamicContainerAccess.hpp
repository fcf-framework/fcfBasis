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
  struct DynamicContainerAccessHelper<true>{

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

      virtual void addPosition(size_t a_offset);

      virtual void decPosition(size_t a_offset);

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

      virtual size_t distance(const DynamicContainerAccessBase& a_iterator) const;

      virtual bool isEnd() const;

      virtual bool equal(DynamicContainerAccessBase& a_containerAccess) const;

    protected:
      TContainerAccess _containerAccess;
  };

  template <typename TContainer>
  class DynamicContainerAccess< ContainerAccess<const TContainer> > : public DynamicContainerAccessBase {
    public:
      typedef ContainerAccess<const TContainer> ContainerAccessType;

      enum { is_const_resolve_value = ContainerAccessType::is_const_resolve_value };

      typedef typename ContainerAccessType::container_type          container_type;
      typedef typename ContainerAccessType::key_type                key_type;
      typedef typename ContainerAccessType::value_type              value_type;
      typedef DynamicContainerAccessHelper<is_const_resolve_value>  helper_type;

      DynamicContainerAccess();

      DynamicContainerAccess(const container_type& a_container, ::fcf::ContainerPosition a_position = ::fcf::CP_BEGIN);

      virtual ~DynamicContainerAccess();

      virtual bool isFlatContainer();

      virtual void setBeginPosition();

      virtual void setEndPosition();

      virtual void setPosition(const ::fcf::Variant& a_key, bool a_create = false);

      virtual void addPosition(size_t a_offset);

      virtual void decPosition(size_t a_offset);

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

      virtual size_t distance(const DynamicContainerAccessBase& a_iterator) const;

      virtual bool isEnd() const;

      virtual bool equal(DynamicContainerAccessBase& a_containerAccess) const;

    protected:
      ContainerAccessType _containerAccess;
  };

} // fcf namespace

#include "../../Variant.hpp"

namespace fcf {

  template <typename TContainerAccess>
  DynamicContainerAccess<TContainerAccess>::DynamicContainerAccess(){
  }

  template <typename TContainerAccess>
  DynamicContainerAccess<TContainerAccess>::DynamicContainerAccess(container_type& a_container, ::fcf::ContainerPosition a_position)
    : _containerAccess((container_type&)a_container, a_position){
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
  void DynamicContainerAccess<TContainerAccess>::addPosition(size_t a_offset){
    _containerAccess.addPosition(a_offset);
  }

  template <typename TContainerAccess>
  void DynamicContainerAccess<TContainerAccess>::decPosition(size_t a_offset){
    _containerAccess.decPosition(a_offset);
  }

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
    return _containerAccess.ptr();
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
    return ((TContainerAccess&)_containerAccess).ptr();
  };

  template <typename TContainerAccess>
  Variant DynamicContainerAccess<TContainerAccess>::getValue() const {
    return Variant(((TContainerAccess&)_containerAccess).value());
  }

  template <typename TContainerAccess>
  Variant DynamicContainerAccess<TContainerAccess>::getRefValue(){
    typedef decltype(((TContainerAccess&)_containerAccess).value()) ResultType;
    typedef typename std::remove_const<ResultType>::type            CheckType;
    if (std::is_same<CheckType, Variant>::value) {
      return ((TContainerAccess&)_containerAccess).value();
    } else {
      return Variant(((TContainerAccess&)_containerAccess).value(), Variant::FORCE_REFERENCE);
    }
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
  size_t DynamicContainerAccess<TContainerAccess>::distance(const DynamicContainerAccessBase& a_iterator) const {
    const DynamicContainerAccess* p = (const DynamicContainerAccess*)&a_iterator;
    if (!p){
      throw std::runtime_error("The transferred virtual type does not correspond to the required");
    }
    return _containerAccess.distance(p->_containerAccess);
  }

  template <typename TContainerAccess>
  bool DynamicContainerAccess<TContainerAccess>::isEnd() const {
    return _containerAccess.isEnd();
  }

  template <typename TContainerAccess>
  bool DynamicContainerAccess<TContainerAccess>::equal(DynamicContainerAccessBase& a_containerAccess) const{
    //DynamicContainerAccess<TContainerAccess>* arg = dynamic_cast<DynamicContainerAccess<TContainerAccess>*>(&a_containerAccess);
    DynamicContainerAccess<TContainerAccess>* arg = (DynamicContainerAccess*)&a_containerAccess;
    return _containerAccess == arg->_containerAccess;
  }


  ///
  ///   DynamicContainerAccess<const TContainerAccess> class
  ///   Implementation
  ///

  template <typename TContainer>
  DynamicContainerAccess< ContainerAccess<const TContainer> >::DynamicContainerAccess(){
  }

  template <typename TContainer>
  DynamicContainerAccess< ContainerAccess<const TContainer> >::DynamicContainerAccess(const container_type& a_container, ::fcf::ContainerPosition a_position)
    : _containerAccess((container_type&)a_container, a_position){
  }

  template <typename TContainer>
  DynamicContainerAccess< ContainerAccess<const TContainer> >::~DynamicContainerAccess() {
  }

  template <typename TContainer>
  bool DynamicContainerAccess< ContainerAccess<const TContainer> >::isFlatContainer(){
    return ContainerAccessType::is_flat;
  }

  template <typename TContainer>
  void DynamicContainerAccess< ContainerAccess<const TContainer> >::setBeginPosition() {
    _containerAccess.setBeginPosition();
  }

  template <typename TContainer>
  void DynamicContainerAccess< ContainerAccess<const TContainer> >::setEndPosition() {
    _containerAccess.setEndPosition();
  }

  template <typename TContainer>
  void DynamicContainerAccess< ContainerAccess<const TContainer> >::setPosition(const ::fcf::Variant& a_key, bool a_create){
    _containerAccess.setPosition(a_key.cast<key_type>(), a_create);
  };

  template <typename TContainer>
  void DynamicContainerAccess< ContainerAccess<const TContainer> >::addPosition(size_t a_offset){
    _containerAccess.addPosition(a_offset);
  }

  template <typename TContainer>
  void DynamicContainerAccess< ContainerAccess<const TContainer> >::decPosition(size_t a_offset){
    _containerAccess.decPosition(a_offset);
  }

  template <typename TContainer>
  void DynamicContainerAccess< ContainerAccess<const TContainer> >::dec(){
    --_containerAccess;
  }

  template <typename TContainer>
  void DynamicContainerAccess< ContainerAccess<const TContainer> >::inc(){
    ++_containerAccess;
  }

  template <typename TContainer>
  void* DynamicContainerAccess< ContainerAccess<const TContainer> >::getValuePtr() {
    throw std::runtime_error("The type does not support access to modify the stored value.");
  };

  template <typename TContainer>
  void DynamicContainerAccess< ContainerAccess<const TContainer> >::setValue(const Variant& /*a_value*/){
    throw std::runtime_error("The type does not support access to modify the stored value.");
  }

  template <typename TContainer>
  unsigned int DynamicContainerAccess< ContainerAccess<const TContainer> >::getValueTypeIndex() const {
    return Type<typename ContainerAccessType::value_type>().index();
  }

  template <typename TContainer>
  unsigned int DynamicContainerAccess< ContainerAccess<const TContainer> >::getKeyTypeIndex() const {
    return Type<typename ContainerAccessType::key_type>().index();
  }

  template <typename TContainer>
  const void* DynamicContainerAccess< ContainerAccess<const TContainer> >::getConstValuePtr() const {
    return ((ContainerAccessType&)_containerAccess).ptr();
    //return & ((ContainerAccessType&)_containerAccess).value();
  };

  template <typename TContainer>
  Variant DynamicContainerAccess< ContainerAccess<const TContainer> >::getValue() const {
    return Variant(((ContainerAccessType&)_containerAccess).value());
  }

  template <typename TContainer>
  Variant DynamicContainerAccess< ContainerAccess<const TContainer> >::getRefValue(){
    return Variant(Type<const value_type>(),((ContainerAccessType&)_containerAccess).value(), Variant::REFERENCE);
  }

  template <typename TContainer>
  Variant DynamicContainerAccess< ContainerAccess<const TContainer> >::getKey() const {
    return Variant(_containerAccess.key());
  }

  template <typename TContainer>
  size_t DynamicContainerAccess< ContainerAccess<const TContainer> >::getContainerSize() const {
    return _containerAccess.getContainerSize();
  }

  template <typename TContainer>
  size_t DynamicContainerAccess< ContainerAccess<const TContainer> >::distance(const DynamicContainerAccessBase& a_iterator) const {
    const DynamicContainerAccess* p = (const DynamicContainerAccess*)&a_iterator;
    if (!p){
      throw std::runtime_error("The transferred virtual type does not correspond to the required");
    }
    return _containerAccess.distance(p->_containerAccess);
  }

  template <typename TContainer>
  bool DynamicContainerAccess< ContainerAccess<const TContainer> >::isEnd() const {
    return _containerAccess.isEnd();
  }

  template <typename TContainer>
  bool DynamicContainerAccess< ContainerAccess<const TContainer> >::equal(DynamicContainerAccessBase& a_containerAccess) const{
    //DynamicContainerAccess* arg = dynamic_cast<DynamicContainerAccess*>(&a_containerAccess);
    DynamicContainerAccess* arg = (DynamicContainerAccess*)&a_containerAccess;
    return _containerAccess == arg->_containerAccess;
  }


} // fcf namespace
#endif // #ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__DYNAMIC_CONTAINER_ACCESS_HPP___
