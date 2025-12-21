#ifndef ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__VARIANT_CURSOR_HPP___
#define ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__VARIANT_CURSOR_HPP___

#include "VariantCursorDefinition.hpp"
#include "../../Variant.hpp"
#include "../../Type.hpp"

namespace fcf{

  template <typename TContainer>
  VariantCursor<TContainer>::VariantCursor() {
  }

  template <typename TContainer>
  VariantCursor<TContainer>::VariantCursor(TContainer& a_variant) {
    if (std::is_const<TContainer>::value) {
      if (TypeIndexConverter<>::isConst(a_variant.getTypeInfo()->index)){
        this->iterator = a_variant.getTypeInfo()->template getSpecificator<ContainerAccessSpecificator>()((void*)a_variant.ptr(), 0, 0);
      } else {
        const TypeInfo* ti = getTypeInfo(TypeIndexConverter<>::getConstIndex(a_variant.getTypeInfo()->index));
        if (!ti){
          throw std::runtime_error("Cannot get type info for const type");
        }
        this->iterator = ti->template getSpecificator<ContainerAccessSpecificator>()((void*)a_variant.ptr(), 0, 0);
      }
    } else {
      iterator = a_variant.getTypeInfo()->template getSpecificator<ContainerAccessSpecificator>()((void*)a_variant.ptr(), 0, 0);
    }
  }

  template <typename TContainer>
  void VariantCursor<TContainer>::setPosition(const key_type& a_position, bool a_create) {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    return piterator->setPosition(a_position, a_create);
  }

  template <typename TContainer>
  void VariantCursor<TContainer>::addPosition(size_t a_position) {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    piterator->addPosition(a_position);
  }

  template <typename TContainer>
  void VariantCursor<TContainer>::decPosition(size_t a_position) {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    piterator->decPosition(a_position);
  }

  template <typename TContainer>
  void VariantCursor<TContainer>::decPosition() {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    --(*piterator);
  }

  template <typename TContainer>
  void VariantCursor<TContainer>::incPosition() {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    ++(*piterator);
  }

  template <typename TContainer>
  void VariantCursor<TContainer>::setBeginPosition() {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    piterator->setBeginPosition();
  }

  template <typename TContainer>
  void VariantCursor<TContainer>::setEndPosition() {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    piterator->setEndPosition();
  }

  template <typename TContainer>
  size_t VariantCursor<TContainer>::getDistance(const self_type& a_cursor) const{
    DynamicContainerAccessBase* selfIterator = (DynamicContainerAccessBase*)iterator.ptr();
    DynamicContainerAccessBase* argIterator  = (DynamicContainerAccessBase*)a_cursor.iterator.ptr();
    if (!selfIterator || !argIterator){
      throw std::runtime_error("Iterator unset");
    }
    return selfIterator->distance(*argIterator);
  }

  template <typename TContainer>
  typename VariantCursor<TContainer>::key_type VariantCursor<TContainer>::getKey() const {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    return piterator->getKey();
  }

  template <typename TContainer>
  typename VariantCursor<TContainer>::resolve_value_type VariantCursor<TContainer>::getValue() {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    return piterator->getRefValue();
  }

  template <typename TContainer>
  void* VariantCursor<TContainer>::getValuePtr() {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    return piterator->getRefValue().ptr();
  }

  // (this is the stub)!
  template <typename TContainer>
  typename VariantCursor<TContainer>::resolve_stored_value_type VariantCursor<TContainer>::getStoredValue() {
    return getValue();
  }

  template <typename TContainer>
  size_t VariantCursor<TContainer>::getContainerSize() const{
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    return piterator->getContainerSize();
  }

  template <typename TContainer>
  bool VariantCursor<TContainer>::isEnd() const {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    return piterator->isEnd();
  }

  template <typename TContainer>
  template <typename TCursor>
  bool VariantCursor<TContainer>::equal(const TCursor& a_cursor) const {
    DynamicContainerAccessBase* sourceIterator = (DynamicContainerAccessBase*)a_cursor.iterator.ptr();
    DynamicContainerAccessBase* selfIterator = (DynamicContainerAccessBase*)iterator.ptr();
    if (!sourceIterator){
      return !selfIterator;
    }
    return selfIterator->equal(*sourceIterator);
  }


} // fcf namespace



#endif // #ifndef ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__VARIANT_CURSOR_HPP___
