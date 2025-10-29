#ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__LIST_ITERATABLE_CURSOR_HPP___
#define ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__LIST_ITERATABLE_CURSOR_HPP___

namespace fcf {

  template <typename TContainer, typename TKey, typename TValue>
  struct ListIteratableCursor {
    typedef ListIteratableCursor         self_type;
    typedef TContainer                    container_type;
    typedef TKey                          key_type;
    typedef TValue                        value_type;
    typedef TValue                        stored_value_type;
    typedef TValue                        resolve_value_type;
    typedef TValue                        resolve_stored_value_type;
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
      if (a_position >= getContainerSize()) {
        setEndPosition();
        return;
      }
      key = 0;
      iterator = container->begin();
      while(key < a_position){
        ++iterator;
        ++key;
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

    inline value_type& getValue() {
      return *iterator;
    }

    inline resolve_stored_value_type& getStoredValue() {
      return *iterator;
    }

    inline size_t getContainerSize() const {
      return container->size();
    }

    inline bool isEnd() const {
      return iterator == container->end();
    }

    inline bool equal(const self_type& a_cursor) const {
      return iterator == a_cursor.iterator;
    }

    container_type* container;
    iterator_type   iterator;
    key_type        key;
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__LIST_ITERATABLE_CURSOR_HPP___
