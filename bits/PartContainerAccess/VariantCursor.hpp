#ifndef ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__VARIANT_CURSOR_HPP___
#define ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__VARIANT_CURSOR_HPP___

#include "VariantCursorDefinition.hpp"
#include "../../PartVariant.hpp"
#include "../../PartType.hpp"
#include "../PartException/exceptions.hpp"

namespace fcf{

  template <typename TContainer>
  VariantCursor<TContainer>::VariantCursor() {
  }

  template <typename TContainer>
  VariantCursor<TContainer>::VariantCursor(TContainer& a_variant) {
    if (std::is_const<TContainer>::value) {
      if (TypeIndexConverter<>::isConst(a_variant.getTypeInfo()->index)){
        this->iterator = a_variant.getTypeInfo()->template getSpecificator<ContainerAccessSpecificator>(0)((void*)a_variant.ptr(), 0, 0);
      } else {
        const TypeInfo* ti = getTypeInfo(TypeIndexConverter<>::getConstIndex(a_variant.getTypeInfo()->index));
        if (!ti){
          throw fcf::CursorIteratorUnsetException(__FILE__, __LINE__, Type<TContainer>().name());
        }
        this->iterator = ti->template getSpecificator<ContainerAccessSpecificator>(0)((void*)a_variant.ptr(), 0, 0);
      }
    } else {
      iterator = a_variant.getTypeInfo()->template getSpecificator<ContainerAccessSpecificator>(0)((void*)a_variant.ptr(), 0, 0);
    }
  }

  template <typename TContainer>
  void VariantCursor<TContainer>::setPosition(const key_type& a_position, bool a_create) {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    if (!piterator) {
      throw fcf::CursorIteratorUnsetException(__FILE__, __LINE__, Type<TContainer>().name());
    }
    return piterator->setPosition(a_position, a_create);
  }

  template <typename TContainer>
  void VariantCursor<TContainer>::addPosition(size_t a_position) {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    if (!piterator) {
      throw fcf::CursorIteratorUnsetException(__FILE__, __LINE__, Type<TContainer>().name());
    }
    piterator->addPosition(a_position);
  }

  template <typename TContainer>
  void VariantCursor<TContainer>::decPosition(size_t a_position) {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    if (!piterator) {
      throw fcf::CursorIteratorUnsetException(__FILE__, __LINE__, Type<TContainer>().name());
    }
    piterator->decPosition(a_position);
  }

  template <typename TContainer>
  void VariantCursor<TContainer>::decPosition() {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    if (!piterator) {
      throw fcf::CursorIteratorUnsetException(__FILE__, __LINE__, Type<TContainer>().name());
    }
    --(*piterator);
  }

  template <typename TContainer>
  void VariantCursor<TContainer>::incPosition() {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    if (!piterator) {
      throw fcf::CursorIteratorUnsetException(__FILE__, __LINE__, Type<TContainer>().name());
    }
    ++(*piterator);
  }

  template <typename TContainer>
  void VariantCursor<TContainer>::setBeginPosition() {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    if (!piterator) {
      throw fcf::CursorIteratorUnsetException(__FILE__, __LINE__, Type<TContainer>().name());
    }
    piterator->setBeginPosition();
  }

  template <typename TContainer>
  void VariantCursor<TContainer>::setEndPosition() {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    if (!piterator) {
      throw fcf::CursorIteratorUnsetException(__FILE__, __LINE__, Type<TContainer>().name());
    }
    piterator->setEndPosition();
  }

  template <typename TContainer>
  size_t VariantCursor<TContainer>::getDistance(const self_type& a_cursor) const{
    DynamicContainerAccessBase* selfIterator = (DynamicContainerAccessBase*)iterator.ptr();
    DynamicContainerAccessBase* argIterator  = (DynamicContainerAccessBase*)a_cursor.iterator.ptr();
    if (!selfIterator || !argIterator){
      throw fcf::CursorIteratorUnsetException(__FILE__, __LINE__, Type<TContainer>().name());
    }
    return selfIterator->distance(*argIterator);
  }

  template <typename TContainer>
  typename VariantCursor<TContainer>::key_type VariantCursor<TContainer>::getKey() const {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    if (!piterator) {
      throw fcf::CursorIteratorUnsetException(__FILE__, __LINE__, Type<TContainer>().name());
    }
    return piterator->getKey();
  }

  template <typename TContainer>
  typename VariantCursor<TContainer>::resolve_value_type VariantCursor<TContainer>::getValue() {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    if (!piterator) {
      throw fcf::CursorIteratorUnsetException(__FILE__, __LINE__, Type<TContainer>().name());
    }
    return piterator->getRefValue();
  }

  template <typename TContainer>
  void* VariantCursor<TContainer>::getValuePtr() {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    if (!piterator) {
      throw fcf::CursorIteratorUnsetException(__FILE__, __LINE__, Type<TContainer>().name());
    }
    return piterator->getRefValue().ptr();
  }

  // (this is the stub)!
  template <typename TContainer>
  typename VariantCursor<TContainer>::resolve_stored_value_type VariantCursor<TContainer>::getStoredValue() {
    if (!iterator.ptr()) {
      throw fcf::CursorIteratorUnsetException(__FILE__, __LINE__, Type<TContainer>().name());
    }
    return getValue();
  }

  template <typename TContainer>
  size_t VariantCursor<TContainer>::getContainerSize() const{
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    if (!piterator) {
      throw fcf::CursorIteratorUnsetException(__FILE__, __LINE__, Type<TContainer>().name());
    }
    return piterator->getContainerSize();
  }

  template <typename TContainer>
  bool VariantCursor<TContainer>::isEnd() const {
    DynamicContainerAccessBase* piterator = (DynamicContainerAccessBase*)iterator.ptr();
    if (!piterator) {
      throw fcf::CursorIteratorUnsetException(__FILE__, __LINE__, Type<TContainer>().name());
    }
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
    if (!selfIterator) {
      throw fcf::CursorIteratorUnsetException(__FILE__, __LINE__, Type<TContainer>().name());
    }
    return selfIterator->equal(*sourceIterator);
  }

  template <typename TContainer>
  template <typename TCursor>
  void VariantCursor<TContainer>::erase(const TCursor& a_cursor) {
    DynamicContainerAccessBase* sourceIterator = (DynamicContainerAccessBase*)a_cursor.iterator.ptr();
    DynamicContainerAccessBase* selfIterator = (DynamicContainerAccessBase*)iterator.ptr();
    if (!selfIterator || !sourceIterator) {
      throw fcf::CursorIteratorUnsetException(__FILE__, __LINE__, Type<TContainer>().name());
    }
    return selfIterator->erase(*sourceIterator);
  }


} // fcf namespace



#endif // #ifndef ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__VARIANT_CURSOR_HPP___
