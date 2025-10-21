#ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__FLAT_CURSOR_HPP___
#define ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__FLAT_CURSOR_HPP___

namespace fcf {

  template <typename TContainer, typename TKey, typename TValue>
  struct FlatCursor {
    typedef FlatCursor self_type;
    typedef TContainer container_type;
    typedef TKey       key_type;
    typedef TValue     value_type;
    typedef TValue     stored_value_type;
    typedef TValue     resolve_value_type;
    typedef TValue     resolve_stored_value_type;
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

    inline value_type& getValue() {
      return (*container)[key];
    }

    inline resolve_stored_value_type& getStoredValue() {
      return (*container)[key];
    }

    inline size_t getContainerSize() const{
      return container->size();
    }

    inline bool isEnd() const {
      return key >= container->size();
    }

    inline bool equal(const self_type& a_cursor) const {
      return key == a_cursor.key;
    }

    container_type* container;
    key_type        key;
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_CONTAINER_ACCESS__FLAT_CURSOR_HPP___
