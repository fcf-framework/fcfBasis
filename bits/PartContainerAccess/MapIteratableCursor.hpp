#ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__MAP_ITERATABLE_CURSOR_HPP___
#define ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__MAP_ITERATABLE_CURSOR_HPP___

#include <map>
#include <unordered_map>
#include "Cursor.hpp"

namespace fcf {

  template <typename TContainer>
  struct MapIteratableCursor {
    typedef MapIteratableCursor                                             self_type;
    typedef typename std::remove_const<TContainer>::type                    container_type;
    typedef decltype( ((TContainer*)0xff)->begin()->first )                 key_type;
    typedef decltype( (*std::begin(*((TContainer*)0xff))).second )          value_type;
    typedef value_type&                                                     resolve_value_type;
    typedef decltype( *((TContainer*)0xff)->begin() )                       resolve_stored_value_type;
    typedef typename std::remove_reference<resolve_stored_value_type>::type stored_value_type;
    typedef decltype( ((TContainer*)0xff)->begin() )                        iterator_type;

    enum { is_flat = false };

    MapIteratableCursor(){
      container = 0;
    }

    MapIteratableCursor(TContainer& a_container)
      : container((container_type*)&a_container)
      , iterator(std::begin(a_container)){
    }

    inline void setPosition(const key_type& a_position, bool a_create) {
      iterator = container->find(a_position);
      if (a_create && iterator == container->end()){
        iterator = container->insert(stored_value_type(a_position, value_type())).first;
      }
    }

    inline void addPosition(size_t a_position) {
      while(a_position--){
        ++iterator;
      };
    }

    inline void decPosition(size_t a_position) {
      while(a_position--){
        --iterator;
      };
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

    inline size_t getDistance(const self_type& a_cursor) const {
      size_t counter = 0;
      for(iterator_type it = iterator; it != a_cursor.iterator; ++it){
        ++counter;
      }
      return counter;
    }

    inline key_type getKey() const {
      return iterator->first;
    }

    inline resolve_value_type getValue() {
      return (resolve_value_type)iterator->second;
    }

    inline value_type* getValuePtr() {
      return (value_type*)&iterator->second;
    }

    inline resolve_stored_value_type getStoredValue() {
      return *iterator;
    }

    inline size_t getContainerSize() const {
      return container->size();
    }

    template <typename TCursor>
    inline bool equal(const TCursor& a_cursor) const {
      return iterator == a_cursor.iterator;
    }

    /*
    inline MapIteratableCursor insert(const key_type& a_key, const value_type& a_value) {
      return MapIteratableCursor{container, container->insert({a_key, a_value}).first};
    }
    */

    inline bool isEnd() const {
      return iterator == container->end();
    }

    template <typename TCursor>
    inline void erase(const TCursor& a_endCursor){
      container->erase(iterator,  a_endCursor.iterator);
    }

    container_type* container;
    iterator_type   iterator;
  };

  template <typename TKey, typename TValue>
  struct Cursor< std::map<TKey, TValue> > : public MapIteratableCursor< std::map<TKey, TValue> >{
    typedef MapIteratableCursor< std::map<TKey, TValue> > BaseType;
    using BaseType::MapIteratableCursor;
  };

  template <typename TKey, typename TValue>
  struct Cursor< std::unordered_map<TKey, TValue> > : public MapIteratableCursor< std::unordered_map<TKey, TValue> >{
    typedef MapIteratableCursor< std::unordered_map<TKey, TValue> > BaseType;
    using BaseType::MapIteratableCursor;
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__MAP_ITERATABLE_CURSOR_HPP___

