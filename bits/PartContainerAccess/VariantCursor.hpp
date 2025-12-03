#ifndef ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__VARIANT_CURSOR_HPP___
#define ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__VARIANT_CURSOR_HPP___

#include "VariantCursorDefinition.hpp"
#include "../../Variant.hpp"
#include "../../Type.hpp"

namespace fcf{

  template <unsigned int InnerBufferSize>
  VariantCursor<InnerBufferSize>::VariantCursor() {
  }

  template <unsigned int InnerBufferSize>
  VariantCursor<InnerBufferSize>::VariantCursor(BasicVariant<InnerBufferSize>& a_variant) {
    iterator = a_variant.getTypeInfo()->template getSpecificatorCall<ContainerAccessSpecificator>()(a_variant.ptr());
  }

  template <unsigned int InnerBufferSize>
  void VariantCursor<InnerBufferSize>::setPosition(const key_type& a_position, bool a_create) {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    return piterator->setPosition(a_position, a_create);
  }

  template <unsigned int InnerBufferSize>
  void VariantCursor<InnerBufferSize>::addPosition(size_t a_position) {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    piterator->addPosition(a_position);
  }

  template <unsigned int InnerBufferSize>
  void VariantCursor<InnerBufferSize>::decPosition(size_t a_position) {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    piterator->decPosition(a_position);
  }

  template <unsigned int InnerBufferSize>
  void VariantCursor<InnerBufferSize>::decPosition() {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    --(*piterator);
  }

  template <unsigned int InnerBufferSize>
  void VariantCursor<InnerBufferSize>::incPosition() {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    ++(*piterator);
  }

  template <unsigned int InnerBufferSize>
  void VariantCursor<InnerBufferSize>::setBeginPosition() {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    piterator->setBeginPosition();
  }

  template <unsigned int InnerBufferSize>
  void VariantCursor<InnerBufferSize>::setEndPosition() {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    piterator->setEndPosition();
  }

  template <unsigned int InnerBufferSize>
  size_t VariantCursor<InnerBufferSize>::getDistance(const self_type& a_cursor) const{
    DynamicContainerAccessBase* selfIterator = (DynamicContainerAccessBase*)iterator.ptr();
    DynamicContainerAccessBase* argIterator  = (DynamicContainerAccessBase*)a_cursor.iterator.ptr();
    if (!selfIterator || !argIterator){
      throw std::runtime_error("Iterator unset");
    }
    return selfIterator->distance(*argIterator);
  }

  template <unsigned int InnerBufferSize>
  typename VariantCursor<InnerBufferSize>::key_type VariantCursor<InnerBufferSize>::getKey() const {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    return piterator->getKey();
  }

  template <unsigned int InnerBufferSize>
  typename VariantCursor<InnerBufferSize>::resolve_value_type VariantCursor<InnerBufferSize>::getValue() {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    return piterator->getRefValue();
  }

  template <unsigned int InnerBufferSize>
  void* VariantCursor<InnerBufferSize>::getValuePtr() {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    return piterator->getRefValue().ptr();
  }

  // (this is the stub)!
  template <unsigned int InnerBufferSize>
  typename VariantCursor<InnerBufferSize>::resolve_stored_value_type& VariantCursor<InnerBufferSize>::getStoredValue() {
    return getValue();
  }

  template <unsigned int InnerBufferSize>
  size_t VariantCursor<InnerBufferSize>::getContainerSize() const{
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    return piterator->getContainerSize();
  }

  template <unsigned int InnerBufferSize>
  bool VariantCursor<InnerBufferSize>::isEnd() const {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    return piterator->isEnd();
  }

  template <unsigned int InnerBufferSize>
  bool VariantCursor<InnerBufferSize>::equal(const self_type& a_cursor) const {
    DynamicContainerAccessBase* sourceIterator = (DynamicContainerAccessBase*)a_cursor.iterator.ptr();
    DynamicContainerAccessBase* selfIterator = (DynamicContainerAccessBase*)iterator.ptr();
    if (!sourceIterator){
      return !selfIterator;
    }
    return selfIterator->equal(*sourceIterator);
  }


} // fcf namespace



#endif // #ifndef ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__VARIANT_CURSOR_HPP___
