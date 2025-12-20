#ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__CONTAINER_ACCESS_HPP___
#define ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__CONTAINER_ACCESS_HPP___

#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>

#include "ContainerPosition.hpp"
#include "ContainerAccessInfo.hpp"
#include "FlatCursor.hpp"
#include "MapIteratableCursor.hpp"
#include "SetIteratableCursor.hpp"
#include "ListIteratableCursor.hpp"
#include "VariantCursorDefinition.hpp"

namespace fcf {

  template <typename TContainer>
  class ContainerAccess {
    public:
      typedef typename ContainerAccessInfo<TContainer>::cursor_type cursor_type;
      typedef typename cursor_type::container_type                  container_type;
      typedef typename cursor_type::key_type                        key_type;
      typedef typename cursor_type::value_type                      value_type;
      typedef typename cursor_type::stored_value_type               stored_value_type;
      typedef typename cursor_type::resolve_value_type              resolve_value_type;
      typedef typename cursor_type::resolve_stored_value_type       resolve_stored_value_type;
      typedef decltype(cursor_type().getStoredValue())              resolve_stored_ref_type;
      typedef decltype(cursor_type().getValue())                    resolve_value_ret_type;

      friend container_type;
      enum Mode        { constMode = false };
      enum MemMode     { is_flat = cursor_type::is_flat };
      enum ResolveMode { is_const_resolve_value = std::is_const<resolve_value_type>::value };

      inline ContainerAccess(){
      }

      inline ContainerAccess(container_type& a_container, ::fcf::ContainerPosition a_position = ::fcf::CP_BEGIN)
        : cursor(a_container)
      {
        if (a_position == ::fcf::CP_BEGIN) {
          cursor.setBeginPosition();
        } else {
          cursor.setEndPosition();
        }
      }

      inline ContainerAccess(container_type& a_container, key_type a_position, bool a_create = false)
        : cursor(a_container)
      {
        cursor.setPosition(a_position, a_create);
      }

      inline void setPosition(key_type a_position, bool a_create = false){
        cursor.setPosition(a_position, a_create);
      }

      inline void setBeginPosition() {
        cursor.setBeginPosition();
      }

      inline void setEndPosition() {
        cursor.setEndPosition();
      }

      inline void addPosition(size_t a_offset){
        cursor.addPosition(a_offset);
      }

      inline void decPosition(size_t a_offset){
        cursor.decPosition(a_offset);
      }

      inline ContainerAccess& operator--(){
        cursor.decPosition();
        return *this;
      }

      inline ContainerAccess operator--(int){
        ContainerAccess result(*this);
        cursor.decPosition();
        return result;
      }

      inline ContainerAccess& operator++(){
        cursor.incPosition();
        return *this;
      }

      inline ContainerAccess operator++(int){
        ContainerAccess result(*this);
        cursor.incPosition();
        return result;
      }

      inline resolve_value_ret_type value(){
        return cursor.getValue();
      }

      inline void* ptr(){
        return (void*)cursor.getValuePtr();
      }

      inline size_t distance(const ContainerAccess& a_iterator) const {
        return cursor.getDistance(a_iterator.cursor);
      }

      resolve_stored_ref_type operator*() {
        return cursor.getStoredValue();
      }

      stored_value_type* operator->() {
        return &cursor.getStoredValue();
      }

      inline key_type key() const {
        return cursor.getKey();
      }

      inline size_t getContainerSize() const {
        return cursor.getContainerSize();
      }

      inline ContainerAccess operator+(size_t a_diff) const {
        ContainerAccess result(*this);
        result.cursor.addPosition(a_diff);
        return result;
      }

      inline ContainerAccess operator-(size_t a_diff) const {
        ContainerAccess result(*this);
        result.cursor.decPosition(a_diff);
        return result;
      }

      inline bool operator==(const ContainerAccess& a_iterator) const {
        return cursor.equal(a_iterator.cursor);
      }

      inline bool operator==(const ContainerAccess<const TContainer>& a_iterator) const {
        return cursor.equal(a_iterator.cursor);
      }

      inline bool operator!=(const ContainerAccess& a_iterator) const {
        return !cursor.equal(a_iterator.cursor);
      }

      inline bool operator!=(const ContainerAccess<const TContainer>& a_iterator) const {
        return !cursor.equal(a_iterator.cursor);
      }

      inline bool isEnd() const {
        return cursor.isEnd();
      }

      cursor_type cursor;
  };

  template <typename TContainer>
  class ContainerAccess<const TContainer> {
    public:
      typedef typename std::remove_const<TContainer>::type              container_type;
      typedef typename ContainerAccessInfo<container_type>::cursor_type cursor_type;
      typedef typename cursor_type::key_type                            key_type;
      typedef typename cursor_type::value_type                          value_type;
      typedef typename cursor_type::stored_value_type                   stored_value_type;
      typedef typename cursor_type::resolve_value_type                  resolve_value_type;
      typedef typename cursor_type::resolve_stored_value_type           resolve_stored_value_type;
      typedef const decltype(cursor_type().getStoredValue())            resolve_stored_ref_type;
      typedef const decltype(cursor_type().getValue())                  resolve_value_ret_type;

      friend container_type;
      enum Mode { constMode = true };
      enum MemMode { is_flat = cursor_type::is_flat };
      enum ResolveMode { is_const_resolve_value = true };

      inline ContainerAccess(){
      }

      inline ContainerAccess(const container_type& a_container, ::fcf::ContainerPosition a_position = ::fcf::CP_BEGIN) \
        : cursor((container_type&)a_container)
      {
        if (a_position == ::fcf::CP_BEGIN) {
          cursor.setBeginPosition();
        } else {
          cursor.setEndPosition();
        }
      }

      inline ContainerAccess(const container_type& a_container, key_type a_position)
        : cursor((container_type&)a_container)
      {
        cursor.setPosition(a_position);
      }

      inline void setPosition(key_type a_position, bool a_create = false){
        cursor.setPosition(a_position, a_create);
      }

      inline void setBeginPosition() {
        cursor.setBeginPosition();
      }

      inline void setEndPosition() {
        cursor.setEndPosition();
      }

      inline void addPosition(size_t a_offset){
        cursor.addPosition(a_offset);
      }

      inline void decPosition(size_t a_offset){
        cursor.decPosition(a_offset);
      }

      inline ContainerAccess& operator--(){
        cursor.decPosition();
        return *this;
      }

      inline ContainerAccess operator--(int){
        ContainerAccess result(*this);
        cursor.decPosition();
        return result;
      }

      inline ContainerAccess& operator++(){
        cursor.incPosition();
        return *this;
      }

      inline ContainerAccess operator++(int){
        ContainerAccess result(*this);
        cursor.incPosition();
        return result;
      }

      inline resolve_value_ret_type value() const{
        return ((cursor_type&)cursor).getValue();
      }

      inline const void* ptr() const{
        return (const void*)((cursor_type&)cursor).getValuePtr();
      }

      inline size_t distance(const ContainerAccess& a_iterator) const {
        return cursor.getDistance(a_iterator.cursor);
      }

      inline const resolve_stored_ref_type operator*() const {
        return ((cursor_type&)cursor).getStoredValue();
      }

      inline const stored_value_type* operator->() const{
        return &((cursor_type&)cursor).getStoredValue();
      }

      inline key_type key() const {
        return cursor.getKey();
      }

      inline size_t getContainerSize() const {
        return cursor.getContainerSize();
      }

      inline ContainerAccess operator+(size_t a_diff) const {
        ContainerAccess result(*this);
        result.cursor.addPosition(a_diff);
        return result;
      }

      inline ContainerAccess operator-(size_t a_diff) const {
        ContainerAccess result(*this);
        result.cursor.decPosition(a_diff);
        return result;
      }

      inline bool operator==(const ContainerAccess& a_iterator) const {
        return cursor.equal(a_iterator.cursor);
      }

      inline bool operator==(const ContainerAccess<TContainer>& a_iterator) const {
        return cursor.equal(a_iterator.cursor);
      }

      inline bool operator!=(const ContainerAccess& a_iterator) const {
        return !cursor.equal(a_iterator.cursor);
      }

      inline bool operator!=(const ContainerAccess<TContainer>& a_iterator) const {
        return !cursor.equal(a_iterator.cursor);
      }

      inline bool isEnd() const {
        return cursor.isEnd();
      }

      inline value_type& resolve(key_type a_key) {
        return cursor.resolve(a_key);
      }

      inline void set(key_type a_key, const value_type& a_value) {
        cursor.set(a_key, a_value);
      }

      cursor_type cursor;
  };

} // fcf namespace


namespace std {

  template <typename TContainer>
  size_t distance(const fcf::ContainerAccess<TContainer>& a_begin, const fcf::ContainerAccess<TContainer>& a_end) {
    return a_begin.distance(a_end);
  }

}

namespace fcf {
  template <typename Ty>
  struct ContainerAccessInfo< std::vector<Ty> > {
    typedef FlatCursor< std::vector<Ty> > cursor_type;
  };

  template <typename Ty>
  struct ContainerAccessInfo< const std::vector<Ty> > {
    typedef FlatCursor< const std::vector<Ty> > cursor_type;
  };

  template <typename Ty>
  struct ContainerAccessInfo< std::list<Ty> > {
    typedef ListIteratableCursor< std::list<Ty> > cursor_type;
  };

  template <typename TKey, typename TValue>
  struct ContainerAccessInfo< std::map<TKey, TValue> > {
    typedef MapIteratableCursor< std::map<TKey, TValue> > cursor_type;
  };

  template <typename TKey, typename TValue>
  struct ContainerAccessInfo< std::unordered_map<TKey, TValue> > {
    typedef MapIteratableCursor< std::unordered_map<TKey, TValue> > cursor_type;
  };

  template <typename TKey>
  struct ContainerAccessInfo< std::set<TKey> > {
    typedef SetIteratableCursor< std::set<TKey> > cursor_type;
  };
} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__CONTAINER_ACCESS_HPP___

