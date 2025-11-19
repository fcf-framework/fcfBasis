#ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__SET_ITERATABLE_CURSOR_HPP___
#define ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__SET_ITERATABLE_CURSOR_HPP___

namespace fcf {

  template <typename TContainer, typename TValue>
  struct SetIteratableCursor {
    typedef SetIteratableCursor         self_type;
    typedef TContainer                    container_type;
    typedef TValue                        key_type;
    typedef TValue                        value_type;
    typedef TValue                        stored_value_type;
    typedef const TValue                  resolve_value_type;
    typedef const TValue                  resolve_stored_value_type;
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
      return *iterator;
    }

    inline const value_type& getValue() {
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

    inline void set(key_type /*a_key*/, const value_type& a_value) {
      container->insert(a_value);
    }

    container_type* container;
    iterator_type   iterator;
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__SET_ITERATABLE_CURSOR_HPP___
