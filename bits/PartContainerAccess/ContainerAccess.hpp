#ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__CONTAINER_ACCESS_HPP___
#define ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__CONTAINER_ACCESS_HPP___

#include "ContainerAccessDefinition.hpp"
#include "../../Type.hpp"
namespace fcf {

  template <typename TContainer>
  ContainerAccess<TContainer>::ContainerAccess(){
  }

  template <typename TContainer>
  ContainerAccess<TContainer>::ContainerAccess(container_type& a_container, ::fcf::ContainerPosition a_position)
    : cursor(a_container)
  {
    if (a_position == ::fcf::CP_BEGIN) {
      cursor.setBeginPosition();
    } else {
      cursor.setEndPosition();
    }
  }

  template <typename TContainer>
  ContainerAccess<TContainer>::ContainerAccess(container_type& a_container, key_type a_position, bool a_create)
    : cursor(a_container)
  {
    cursor.setPosition(a_position, a_create);
  }

  template <typename TContainer>
  void ContainerAccess<TContainer>::setPosition(key_type a_position, bool a_create){
    cursor.setPosition(a_position, a_create);
  }

  template <typename TContainer>
  void ContainerAccess<TContainer>::setBeginPosition() {
    cursor.setBeginPosition();
  }

  template <typename TContainer>
  void ContainerAccess<TContainer>::setEndPosition() {
    cursor.setEndPosition();
  }

  template <typename TContainer>
  void ContainerAccess<TContainer>::addPosition(size_t a_offset){
    cursor.addPosition(a_offset);
  }

  template <typename TContainer>
  void ContainerAccess<TContainer>::decPosition(size_t a_offset){
    cursor.decPosition(a_offset);
  }

  template <typename TContainer>
  ContainerAccess<TContainer>& ContainerAccess<TContainer>::operator--(){
    cursor.decPosition();
    return *this;
  }

  template <typename TContainer>
  ContainerAccess<TContainer> ContainerAccess<TContainer>::operator--(int){
    ContainerAccess result(*this);
    cursor.decPosition();
    return result;
  }

  template <typename TContainer>
  ContainerAccess<TContainer>& ContainerAccess<TContainer>::operator++(){
    cursor.incPosition();
    return *this;
  }

  template <typename TContainer>
  ContainerAccess<TContainer> ContainerAccess<TContainer>::operator++(int){
    ContainerAccess result(*this);
    cursor.incPosition();
    return result;
  }

  template <typename TContainer>
  typename ContainerAccess<TContainer>::resolve_value_ret_type ContainerAccess<TContainer>::value(){
    return cursor.getValue();
  }

  template <typename TContainer>
  void* ContainerAccess<TContainer>::ptr(){
    return (void*)cursor.getValuePtr();
  }

  template <typename TContainer>
  size_t ContainerAccess<TContainer>::distance(const ContainerAccess& a_iterator) const {
    return cursor.getDistance(a_iterator.cursor);
  }

  template <typename TContainer>
  typename ContainerAccess<TContainer>::resolve_stored_ref_type ContainerAccess<TContainer>::operator*() {
    return cursor.getStoredValue();
  }

  template <typename TContainer>
  typename ContainerAccess<TContainer>::stored_value_type* ContainerAccess<TContainer>::operator->() {
    return &cursor.getStoredValue();
  }

  template <typename TContainer>
  typename ContainerAccess<TContainer>::key_type ContainerAccess<TContainer>::key() const {
    return cursor.getKey();
  }

  template <typename TContainer>
  size_t ContainerAccess<TContainer>::getContainerSize() const {
    return cursor.getContainerSize();
  }

  template <typename TContainer>
  ContainerAccess<TContainer> ContainerAccess<TContainer>::operator+(size_t a_diff) const {
    ContainerAccess result(*this);
    result.cursor.addPosition(a_diff);
    return result;
  }

  template <typename TContainer>
  ContainerAccess<TContainer> ContainerAccess<TContainer>::operator-(size_t a_diff) const {
    ContainerAccess result(*this);
    result.cursor.decPosition(a_diff);
    return result;
  }

  template <typename TContainer>
  bool ContainerAccess<TContainer>::operator==(const ContainerAccess& a_iterator) const {
    return cursor.equal(a_iterator.cursor);
  }

  template <typename TContainer>
  bool ContainerAccess<TContainer>::operator==(const ContainerAccess<const TContainer>& a_iterator) const {
    return cursor.equal(a_iterator.cursor);
  }

  template <typename TContainer>
  bool ContainerAccess<TContainer>::operator!=(const ContainerAccess& a_iterator) const {
    return !cursor.equal(a_iterator.cursor);
  }

  template <typename TContainer>
  bool ContainerAccess<TContainer>::operator!=(const ContainerAccess<const TContainer>& a_iterator) const {
    return !cursor.equal(a_iterator.cursor);
  }

  template <typename TContainer>
  bool ContainerAccess<TContainer>::isEnd() const {
    return cursor.isEnd();
  }

  template <typename TContainer>
  template <typename TContainerAccess>
  void ContainerAccess<TContainer>::erase(const TContainerAccess& a_endAccess){
    cursor.erase(a_endAccess.cursor);
  }







  template <typename TContainer>
  ContainerAccess<const TContainer>::ContainerAccess(){
  }

  template <typename TContainer>
  ContainerAccess<const TContainer>::ContainerAccess(const container_type& a_container, ::fcf::ContainerPosition a_position) \
    : cursor((container_type&)a_container)
  {
    if (a_position == ::fcf::CP_BEGIN) {
      cursor.setBeginPosition();
    } else {
      cursor.setEndPosition();
    }
  }

  template <typename TContainer>
  ContainerAccess<const TContainer>::ContainerAccess(const container_type& a_container, key_type a_position)
    : cursor((container_type&)a_container)
  {
    cursor.setPosition(a_position);
  }

  template <typename TContainer>
  void ContainerAccess<const TContainer>::setPosition(key_type a_position, bool a_create){
    cursor.setPosition(a_position, a_create);
  }

  template <typename TContainer>
  void ContainerAccess<const TContainer>::setBeginPosition() {
    cursor.setBeginPosition();
  }

  template <typename TContainer>
  void ContainerAccess<const TContainer>::setEndPosition() {
    cursor.setEndPosition();
  }

  template <typename TContainer>
  void ContainerAccess<const TContainer>::addPosition(size_t a_offset){
    cursor.addPosition(a_offset);
  }

  template <typename TContainer>
  void ContainerAccess<const TContainer>::decPosition(size_t a_offset){
    cursor.decPosition(a_offset);
  }

  template <typename TContainer>
  ContainerAccess<const TContainer>& ContainerAccess<const TContainer>::operator--(){
    cursor.decPosition();
    return *this;
  }

  template <typename TContainer>
  ContainerAccess<const TContainer> ContainerAccess<const TContainer>::operator--(int){
    ContainerAccess result(*this);
    cursor.decPosition();
    return result;
  }

  template <typename TContainer>
  ContainerAccess<const TContainer>& ContainerAccess<const TContainer>::operator++(){
    cursor.incPosition();
    return *this;
  }

  template <typename TContainer>
  ContainerAccess<const TContainer> ContainerAccess<const TContainer>::operator++(int){
    ContainerAccess result(*this);
    cursor.incPosition();
    return result;
  }

  template <typename TContainer>
  typename ContainerAccess<const TContainer>::resolve_value_ret_type ContainerAccess<const TContainer>::value() const{
    return ((cursor_type&)cursor).getValue();
  }

  template <typename TContainer>
  const void* ContainerAccess<const TContainer>::ptr() const{
    return (const void*)((cursor_type&)cursor).getValuePtr();
  }

  template <typename TContainer>
  size_t ContainerAccess<const TContainer>::distance(const ContainerAccess& a_iterator) const {
    return cursor.getDistance(a_iterator.cursor);
  }

  template <typename TContainer>
  const typename ContainerAccess<const TContainer>::resolve_stored_ref_type ContainerAccess<const TContainer>::operator*() const {
    return ((cursor_type&)cursor).getStoredValue();
  }

  template <typename TContainer>
  const typename ContainerAccess<const TContainer>::stored_value_type* ContainerAccess<const TContainer>::operator->() const{
    return &((cursor_type&)cursor).getStoredValue();
  }

  template <typename TContainer>
  typename ContainerAccess<const TContainer>::key_type ContainerAccess<const TContainer>::key() const {
    return cursor.getKey();
  }

  template <typename TContainer>
  size_t ContainerAccess<const TContainer>::getContainerSize() const {
    return cursor.getContainerSize();
  }

  template <typename TContainer>
  ContainerAccess<const TContainer> ContainerAccess<const TContainer>::operator+(size_t a_diff) const {
    ContainerAccess result(*this);
    result.cursor.addPosition(a_diff);
    return result;
  }

  template <typename TContainer>
  ContainerAccess<const TContainer> ContainerAccess<const TContainer>::operator-(size_t a_diff) const {
    ContainerAccess result(*this);
    result.cursor.decPosition(a_diff);
    return result;
  }

  template <typename TContainer>
  bool ContainerAccess<const TContainer>::operator==(const ContainerAccess& a_iterator) const {
    return cursor.equal(a_iterator.cursor);
  }

  template <typename TContainer>
  bool ContainerAccess<const TContainer>::operator==(const ContainerAccess<TContainer>& a_iterator) const {
    return cursor.equal(a_iterator.cursor);
  }

  template <typename TContainer>
  bool ContainerAccess<const TContainer>::operator!=(const ContainerAccess& a_iterator) const {
    return !cursor.equal(a_iterator.cursor);
  }

  template <typename TContainer>
  bool ContainerAccess<const TContainer>::operator!=(const ContainerAccess<TContainer>& a_iterator) const {
    return !cursor.equal(a_iterator.cursor);
  }

  template <typename TContainer>
  bool ContainerAccess<const TContainer>::isEnd() const {
    return cursor.isEnd();
  }

  template <typename TContainer>
  typename ContainerAccess<const TContainer>::value_type& ContainerAccess<const TContainer>::resolve(key_type a_key) {
    return cursor.resolve(a_key);
  }

  template <typename TContainer>
  void ContainerAccess<const TContainer>::set(key_type a_key, const value_type& a_value) {
    cursor.set(a_key, a_value);
  }

  template <typename TContainer>
  template <typename TContainerAccess>
  void ContainerAccess<const TContainer>::erase(const TContainerAccess& /*a_endAccess*/){
    throw ContainerReadOnlyException(__FILE__, __LINE__, Type<TContainer>().name());
  }


} // fcf namespace


#endif // #ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__CONTAINER_ACCESS_HPP___

