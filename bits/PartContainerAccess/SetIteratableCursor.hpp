#ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__SET_ITERATABLE_CURSOR_HPP___
#define ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__SET_ITERATABLE_CURSOR_HPP___

namespace fcf {

  template <typename TContainer>
  struct SetIteratableCursor {
    typedef SetIteratableCursor                                                                 self_type;
    typedef TContainer                                                                          container_type;
    typedef typename std::remove_reference<decltype( *((container_type*)0xff)->begin() )>::type key_type;
    typedef key_type                                                                            value_type;
    typedef key_type                                                                            stored_value_type;
    typedef key_type&                                                                           resolve_value_type;
    typedef key_type&                                                                           resolve_stored_value_type;
    typedef decltype( ((container_type*)0xff)->begin() )                                        iterator_type;
    enum { is_flat = false };

    SetIteratableCursor(){
      container = 0;
    }

    SetIteratableCursor(TContainer& a_container)
      : container(&a_container)
      , iterator(std::begin(a_container)){
    }

    inline void setPosition(const key_type& a_position, bool a_create) {
      iterator = container->find(a_position);
      if (a_create && iterator == container->end()){
        iterator = container->insert(a_position).first;
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
      return *iterator;
    }

    inline resolve_value_type getValue() {
      return *iterator;
    }

    inline value_type* getValuePtr() {
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

    inline bool equal(const self_type& a_cursor) const {
      return iterator == a_cursor.iterator;
    }

    container_type* container;
    iterator_type   iterator;
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__SET_ITERATABLE_CURSOR_HPP___
