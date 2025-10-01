#ifndef ___FCF__BASIS__BITS__PART_ITERATOR__DYNAMIC_ITERATOR_HPP___
#define ___FCF__BASIS__BITS__PART_ITERATOR__DYNAMIC_ITERATOR_HPP___

#include <vector>
#include <list>
#include <map>
#include <set>
#include "IteratorPosition.hpp"
#include <iostream>

#define FCF_DECLARE_ITERATOR_BODY(a_iterator_type_name, a_cursor_type_name, a_resolve_value_ref)\
  public:\
  typedef typename a_cursor_type_name::container_type container_type;\
  typedef typename a_cursor_type_name::key_type key_type;\
  typedef typename a_cursor_type_name::value_type value_type;\
  enum { is_flat = a_cursor_type_name::is_flat };\
  \
  inline a_iterator_type_name() {\
  }\
  \
  inline a_iterator_type_name(container_type& a_container, ::fcf::IteratorPosition a_position = ::fcf::IP_BEGIN) \
    : cursor(a_container)\
  {\
    if (a_position == ::fcf::IP_BEGIN) {\
      cursor.setBeginPosition();\
    } else { \
      cursor.setEndPosition(); \
    }\
  }\
  \
  inline a_iterator_type_name(container_type& a_container, key_type a_position) \
    : cursor(a_container)\
  {\
    cursor.setPosition(a_position); \
  }\
  \
  inline a_iterator_type_name& operator--(){\
    cursor.decPosition();\
    return *this;\
  }\
  \
  inline a_iterator_type_name operator--(int){\
    a_iterator_type_name result(*this);\
    cursor.decPosition();\
    return result;\
  }\
  \
  inline a_iterator_type_name& operator++(){\
    cursor.incPosition();\
    return *this;\
  }\
  \
  inline a_iterator_type_name operator++(int){\
    a_iterator_type_name result(*this);\
    cursor.incPosition();\
    return result;\
  }\
  \
  inline a_resolve_value_ref value(){\
    return cursor.getValue();\
  }\
  \
  inline key_type key(){\
    return cursor.getKey();\
  }\
  \
  inline size_t container_size(){\
    return cursor.getContainerSize();\
  }\
  \
  inline bool operator==(const a_iterator_type_name& a_iterator) const {\
    return cursor.equal(a_iterator.cursor);\
  }\
  \
  inline bool operator!=(const a_iterator_type_name& a_iterator) const {\
    return !cursor.equal(a_iterator.cursor);\
  }\
  \
  a_cursor_type_name cursor;\
  \

namespace fcf {

  template <typename TContainer, typename TKey, typename TValue>
  struct FlatCursor {
    typedef FlatCursor self_type;
    typedef TContainer container_type;
    typedef TKey       key_type;
    typedef TValue     value_type;
    enum { is_flat = true };

    FlatCursor(){
      container = 0;
      key = 0;
    }

    FlatCursor(TContainer& a_container)
      : container(&a_container){
    }

    inline void setPosition(const key_type& a_position) {
      key = container->size() > a_position ? a_position : container->size();
    }

    inline void decPosition() {
      --key;
    }

    inline void incPosition() {
      ++key;
    }

    inline void setBeginPosition() {
      key = 0;
    }

    inline void setEndPosition() {
      key = container->size();
    }

    inline key_type getKey() const {
      return key;
    }

    inline value_type& getValue() {
      return (*container)[key];
    }

    inline size_t getContainerSize() const{
      return container->size();
    }

    inline bool equal(const self_type& a_cursor) const {
      return key == a_cursor.key;
    }
/*
    inline FlatCursor insert(const key_type& a_key, const value_type& a_value) {

      return MapIteratableCursor{container, container->insert({a_key, a_value}).first};
    }

    inline FlatCursor erase() {
      return MapIteratableCursor{container, container->erase(iterator)};
    }
*/
    container_type* container;
    key_type        key;
  };


  template <typename TContainer, typename TKey, typename TValue>
  struct MapIteratableCursor {
    typedef MapIteratableCursor           self_type;
    typedef TContainer                    container_type;
    typedef TKey                          key_type;
    typedef TValue                        value_type;
    typedef typename TContainer::iterator iterator_type;
    enum { is_flat = false };

    MapIteratableCursor(){
      container = 0;
    }

    MapIteratableCursor(TContainer& a_container)
      : container(&a_container){
    }

    inline void setPosition(const key_type& a_position) {
      iterator = container->find(a_position);
    }

    inline void decPosition() {
      --iterator;
    }

    inline void incPosition() {
      ++iterator;
    }

    inline void setBeginPosition() {
      iterator = container->begin();
    }

    inline void setEndPosition() {
      iterator = container->end();
    }

    inline key_type getKey() const {
      return iterator->first;
    }

    inline value_type& getValue() {
      return iterator->second;
    }

    inline size_t getContainerSize() const {
      return container->size();
    }

    inline bool equal(const self_type& a_cursor) const {
      return iterator == a_cursor.iterator;
    }

    inline MapIteratableCursor insert(const key_type& a_key, const value_type& a_value) {
      return MapIteratableCursor{container, container->insert({a_key, a_value}).first};
    }

    inline MapIteratableCursor erase() {
      return MapIteratableCursor{container, container->erase(iterator)};
    }

    container_type* container;
    iterator_type   iterator;
  };


  template <typename TContainer, typename TValue>
  struct SetIteratableCursor {
    typedef SetIteratableCursor         self_type;
    typedef TContainer                    container_type;
    typedef TValue                        key_type;
    typedef TValue                        value_type;
    typedef typename TContainer::iterator iterator_type;
    enum { is_flat = false };

    SetIteratableCursor(){
      container = 0;
    }

    SetIteratableCursor(TContainer& a_container)
      : container(&a_container){
    }

    inline void setPosition(const key_type& a_position) {
      iterator = container->find(a_position);
    }

    inline void decPosition() {
      --iterator;
    }

    inline void incPosition() {
      ++iterator;
    }

    inline void setBeginPosition() {
      iterator = container->begin();
    }

    inline void setEndPosition() {
      iterator = container->end();
    }

    inline key_type getKey() const {
      return *iterator;
    }

    inline const value_type& getValue() {
      return *iterator;
    }

    inline size_t getContainerSize() const {
      return container->size();
    }

    inline bool equal(const self_type& a_cursor) const {
      return iterator == a_cursor.iterator;
    }

    container_type* container;
    iterator_type   iterator;
  };

  template <typename TContainer, typename TKey, typename TValue>
  struct ListIteratableCursor {
    typedef ListIteratableCursor         self_type;
    typedef TContainer                    container_type;
    typedef TKey                          key_type;
    typedef TValue                        value_type;
    typedef typename TContainer::iterator iterator_type;
    enum { is_flat = false };

    ListIteratableCursor(){
      container = 0;
      key = 0;
    }

    ListIteratableCursor(TContainer& a_container)
      : container(&a_container){
    }

    inline void setPosition(const key_type& a_position) {
      key = 0;
      iterator = container->begin();
      while(key < a_position){
        ++iterator;
        ++key;
      }
    }

    inline void decPosition() {
      --iterator;
      --key;
    }

    inline void incPosition() {
      ++iterator;
      ++key;
    }

    inline void setBeginPosition() {
      iterator = container->begin();
      key = 0;
    }

    inline void setEndPosition() {
      iterator = container->end();
      key = container->size();
    }

    inline key_type getKey() const {
      return key;
    }

    inline value_type& getValue() {
      return *iterator;
    }

    inline size_t getContainerSize() const {
      return container->size();
    }

    inline bool equal(const self_type& a_cursor) const {
      return iterator == a_cursor.iterator;
    }

    container_type* container;
    iterator_type   iterator;
    key_type        key;
  };

  template <typename TContainer>
  struct DynamicIterator;

  template <typename Ty>
  class DynamicIterator< std::vector<Ty> > {
    public:
      typedef FlatCursor<std::vector<Ty>, typename std::vector<Ty>::size_type, typename std::vector<Ty>::value_type> cursor_type;
      FCF_DECLARE_ITERATOR_BODY(DynamicIterator, cursor_type, Ty&);
  };

  template <typename Ty>
  class DynamicIterator< std::list<Ty> > {
    typedef ListIteratableCursor<std::list<Ty>, size_t, typename std::list<Ty>::value_type> cursor_type;
    FCF_DECLARE_ITERATOR_BODY(DynamicIterator, cursor_type, Ty&);
  };

  template <typename TKey, typename TValue>
  class DynamicIterator< std::map<TKey, TValue> > {
    typedef MapIteratableCursor<std::map<TKey, TValue>, TKey, TValue> cursor_type;
    FCF_DECLARE_ITERATOR_BODY(DynamicIterator, cursor_type, TValue&);
  };


  template <typename TKey>
  class DynamicIterator< std::set<TKey> > {
    typedef SetIteratableCursor<std::set<TKey>, TKey> cursor_type;
    FCF_DECLARE_ITERATOR_BODY(DynamicIterator, cursor_type, const TKey&);
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_ITERATOR__DYNAMIC_ITERATOR_HPP___
