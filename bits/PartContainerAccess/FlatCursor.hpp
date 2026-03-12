#ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__FLAT_CURSOR_HPP___
#define ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__FLAT_CURSOR_HPP___

#include <vector>
#include "Cursor.hpp"

namespace fcf {

  template <typename TContainer>
  struct FlatCursor {
    typedef FlatCursor self_type;
    typedef typename std::remove_const<TContainer>::type              container_type;
    typedef size_t                                                    key_type;
    typedef decltype( (*((TContainer*)0x01))[0] )                     resolve_value_type;
    typedef typename std::remove_reference<resolve_value_type>::type  value_type;
    typedef value_type                                                stored_value_type;
    typedef resolve_value_type                                        resolve_stored_value_type;

    enum { is_flat = true };

    FlatCursor(){
      container = 0;
      key = 0;
    }

    FlatCursor(TContainer& a_container)
      : container((container_type*)&a_container)
      , key(0){
    }

    inline void setPosition(const key_type& a_position, bool a_create = false) {
      size_t s = container->size();
      if (s > a_position) {
        key = a_position;
      } else {
        if (a_create){
          if (a_position == s) {
            (*container).push_back(value_type());
          } else if (a_position > s) {
            (*container).resize(a_position + 1);
          }
          key = a_position;
        } else {
          key = container->size();
        }
      }
    }

    inline void addPosition(size_t a_position) {
      key += a_position;
    }

    inline void decPosition(size_t a_position) {
      key -= a_position;
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

    inline size_t getDistance(const self_type& a_cursor) const{
      return a_cursor.key - key;
    }

    inline key_type getKey() const {
      return key;
    }

    inline resolve_value_type getValue() {
      return (*container)[key];
    }

    inline void* getValuePtr() {
      // For ignore exceptions and compilation 
      if (container->size()){
        return (void*)(&(*container)[0] + key);
      } else {
        long zero_addr = 0x00;
        return (void*)(((value_type*)(void*)(long)zero_addr) + key);
      }
    }

    inline resolve_stored_value_type getStoredValue() {
      return (*container)[key];
    }

    inline size_t getContainerSize() const{
      return container->size();
    }

    inline bool isEnd() const {
      return key >= container->size();
    }

    template <typename TCursor>
    inline bool equal(const TCursor& a_cursor) const {
      return key == a_cursor.key;
    }

    template <typename TCursor>
    inline void erase(const TCursor& a_endCursor){
      const key_type s = container->size();
      if (key + 1 == s && a_endCursor.key >= s){
        container->pop_back();
      } else {
        container->erase(container->begin() + key,  this->container->begin() + a_endCursor.key);
      }
    }

    container_type* container;
    key_type        key;
  };


  template <typename Ty>
  struct Cursor< std::vector<Ty> >: public FlatCursor< std::vector<Ty> > {
    typedef FlatCursor< std::vector<Ty> > BaseType;
    using FlatCursor< std::vector<Ty> >::FlatCursor;
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__FLAT_CURSOR_HPP___
