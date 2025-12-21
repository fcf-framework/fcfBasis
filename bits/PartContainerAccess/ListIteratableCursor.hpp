#ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__LIST_ITERATABLE_CURSOR_HPP___
#define ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__LIST_ITERATABLE_CURSOR_HPP___

#include <list>
#include "Cursor.hpp"

namespace fcf {

  template <typename TContainer>
  struct ListIteratableCursor {
    typedef ListIteratableCursor                                      self_type;
    typedef typename std::remove_const<TContainer>::type              container_type;
    typedef size_t                                                    key_type;
    typedef decltype(std::begin(*((TContainer*)0x01)))                iterator_type;
    typedef decltype(*(*(iterator_type*)0x01))                        resolve_value_type;
    typedef typename std::remove_reference<resolve_value_type>::type  value_type;
    typedef value_type                                                stored_value_type;
    typedef resolve_value_type                                        resolve_stored_value_type;
    enum { is_flat = false };

    ListIteratableCursor(){
      container = 0;
      key = 0;
    }

    ListIteratableCursor(TContainer& a_container)
      : container((container_type*)&a_container)
      , key(0)
      , iterator(std::begin(*container)){
    }

    inline void setPosition(const key_type& a_position, bool a_create) {
      size_t s = container->size();
      if (a_position < s) {
        if (key > a_position){
          key = 0;
          iterator = std::begin(*container);
        }
        for(; key != a_position; ++key, ++iterator);
      } else {
        if (a_create){
          for(; key <= a_position; ++key){
            container->push_back(value_type());
          }
          key -= 1;
          iterator = --std::end(*container);
        } else {
          iterator = std::end(*container);
          key = s;
        }
      }
    }

    inline void addPosition(size_t a_position) {
      if (a_position + key >= getContainerSize()) {
        setEndPosition();
        return;
      }
      while(a_position--){
        ++iterator;
      };
    }

    inline void decPosition(size_t a_position) {
      if (a_position > key){
        setBeginPosition();
        return;
      }
      while(a_position--){
        --iterator;
      };
    }

    inline void decPosition() {
      if (!key){
        return;
      }
      --iterator;
      --key;
    }

    inline void incPosition() {
      if (isEnd()){
        return;
      }
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

    inline size_t getDistance(const self_type& a_cursor) const {
      size_t counter = 0;
      for(iterator_type it = iterator; it != a_cursor.iterator; ++it){
        ++counter;
      }
      return counter;
    }

    inline key_type getKey() const {
      return key;
    }

    inline resolve_value_type getValue() {
      return *iterator;
    }

    inline void* getValuePtr() {
      return &(*iterator);
    }

    inline resolve_stored_value_type getStoredValue() {
      return *iterator;
    }

    inline size_t getContainerSize() const {
      return container->size();
    }

    inline bool isEnd() const {
      return iterator == container->end();
    }

    template <typename TCursor>
    inline bool equal(const TCursor& a_cursor) const {
      return iterator == a_cursor.iterator;
    }

    template <typename TCursor>
    inline void erase(const TCursor& a_endCursor){
      container->erase(iterator,  a_endCursor.iterator);
    }

/*
    inline value_type& resolve(key_type a_key){
      const size_t s = container->size();
      if (a_key < s){
        if (key > a_key){
          key = 0;
          iterator = std::begin(*container);
        }
        for(; a_key != key; ++key, ++iterator);
      } else if (a_key == s) {
        (*container).push_back(value_type());
        iterator = --(*container).end();
        key = a_key;
      } else {
        for(size_t i = s; i <= a_key; ++i){
          (*container).push_back(value_type());
        }
        iterator = --(*container).end();
        key = a_key;
      }
      return *iterator;
    }
*/
    container_type* container;
    iterator_type   iterator;
    key_type        key;
  };


  template <typename Ty>
  struct Cursor< std::list<Ty> > : public ListIteratableCursor< std::list<Ty> >{
    typedef ListIteratableCursor< std::list<Ty> > BaseType;
    using BaseType::ListIteratableCursor;
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__LIST_ITERATABLE_CURSOR_HPP___
