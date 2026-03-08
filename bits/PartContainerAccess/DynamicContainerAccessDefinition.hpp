#ifndef ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__DYNAMIC_CONTAINER_ACCESS_DEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__DYNAMIC_CONTAINER_ACCESS_DEFINITION_HPP___

#include "DynamicContainerAccessBase.hpp"

namespace fcf{

  template <bool IsConstValue>
  struct DynamicContainerAccessHelper{
    template <typename TContainerAcces, typename TValue>
    void set(TContainerAcces& a_container, const TValue& a_value);
  };

  template <>
  struct DynamicContainerAccessHelper<true> {
    template <typename TContainerAcces, typename TValue>
    void set(TContainerAcces& /*a_container*/, const TValue& /*a_value*/);
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

      virtual const TypeInfo* getValueTypeInfo() const;

      virtual unsigned int getKeyTypeIndex() const;

      virtual const void* getConstValuePtr() const;

      virtual Variant getValue() const;

      virtual Variant getRefValue();

      virtual Variant getKey() const;

      virtual size_t getContainerSize() const;

      virtual size_t distance(const DynamicContainerAccessBase& a_iterator) const;

      virtual bool isEnd() const;

      virtual bool equal(DynamicContainerAccessBase& a_containerAccess) const;

      virtual void erase(DynamicContainerAccessBase& a_endAccess);

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

      virtual const TypeInfo* getValueTypeInfo() const;

      virtual unsigned int getKeyTypeIndex() const;

      virtual const void* getConstValuePtr() const;

      virtual Variant getValue() const;

      virtual Variant getRefValue();

      virtual Variant getKey() const;

      virtual size_t getContainerSize() const;

      virtual size_t distance(const DynamicContainerAccessBase& a_iterator) const;

      virtual bool isEnd() const;

      virtual bool equal(DynamicContainerAccessBase& a_containerAccess) const;

      virtual void erase(DynamicContainerAccessBase& a_endAccess);

    protected:
      ContainerAccessType _containerAccess;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__DYNAMIC_CONTAINER_ACCESS_DEFINITION_HPP___
