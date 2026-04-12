#ifndef ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__CONTAINER_ACCESS_DEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__CONTAINER_ACCESS_DEFINITION_HPP___

#include <stdexcept>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>

#include "ContainerPosition.hpp"
#include "CursorSelector.hpp"

#include "FlatCursor.hpp"
#include "MapIteratableCursor.hpp"
#include "SetIteratableCursor.hpp"
#include "ListIteratableCursor.hpp"
#include "VariantCursorDefinition.hpp"

namespace fcf{

  template <typename TContainer>
  class ContainerAccess {
    public:
      //typedef typename CursorSelector<const TContainer>::Type           cursor_type;
      typedef Cursor<TContainer>                                    cursor_type;
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
      enum ResolveMode { is_const_resolve_value = std::is_const< typename std::remove_reference<resolve_value_type>::type >::value };

      inline ContainerAccess();

      inline ContainerAccess(container_type& a_container, ::fcf::ContainerPosition a_position = ::fcf::CP_BEGIN);

      inline ContainerAccess(container_type& a_container, key_type a_position, bool a_create = false);

      inline void setPosition(key_type a_position, bool a_create = false);

      inline void setBeginPosition();

      inline void setEndPosition();

      inline void addPosition(size_t a_offset);

      inline void decPosition(size_t a_offset);

      inline ContainerAccess& operator--();

      inline ContainerAccess operator--(int);

      inline ContainerAccess& operator++();

      inline ContainerAccess operator++(int);

      inline resolve_value_ret_type value();

      inline void* ptr();

      inline size_t distance(const ContainerAccess& a_iterator) const;

      resolve_stored_ref_type operator*();

      stored_value_type* operator->();

      inline key_type key() const;

      inline size_t getContainerSize() const;

      inline ContainerAccess operator+(size_t a_diff) const;

      inline ContainerAccess operator-(size_t a_diff) const;

      inline bool operator==(const ContainerAccess& a_iterator) const;

      inline bool operator==(const ContainerAccess<const TContainer>& a_iterator) const;

      inline bool operator!=(const ContainerAccess& a_iterator) const;

      inline bool operator!=(const ContainerAccess<const TContainer>& a_iterator) const;

      inline bool isEnd() const;

      template <typename TContainerAccess>
      inline void erase(const TContainerAccess& a_endAccess);

      cursor_type cursor;
  };



  template <typename TContainer>
  class ContainerAccess<const TContainer> {
    public:
      typedef typename CursorSelector<const TContainer>::Type           cursor_type;
      typedef typename std::remove_const<TContainer>::type              container_type;
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

      inline ContainerAccess();

      inline ContainerAccess(const container_type& a_container, ::fcf::ContainerPosition a_position = ::fcf::CP_BEGIN);

      inline ContainerAccess(const container_type& a_container, key_type a_position);

      inline void setPosition(key_type a_position, bool a_create = false);

      inline void setBeginPosition();

      inline void setEndPosition();

      inline void addPosition(size_t a_offset);

      inline void decPosition(size_t a_offset);

      inline ContainerAccess& operator--();

      inline ContainerAccess operator--(int);

      inline ContainerAccess& operator++();

      inline ContainerAccess operator++(int);

      inline resolve_value_ret_type value() const;

      inline const void* ptr() const;

      inline size_t distance(const ContainerAccess& a_iterator) const;

      inline const resolve_stored_ref_type operator*() const;

      inline const stored_value_type* operator->() const;

      inline key_type key() const;

      inline size_t getContainerSize() const;

      inline ContainerAccess operator+(size_t a_diff) const;

      inline ContainerAccess operator-(size_t a_diff) const;

      inline bool operator==(const ContainerAccess& a_iterator) const;

      inline bool operator==(const ContainerAccess<TContainer>& a_iterator) const;

      inline bool operator!=(const ContainerAccess& a_iterator) const;

      inline bool operator!=(const ContainerAccess<TContainer>& a_iterator) const;

      inline bool isEnd() const;

      inline value_type& resolve(key_type a_key);

      inline void set(key_type a_key, const value_type& a_value);

      template <typename TContainerAccess>
      inline void erase(const TContainerAccess& a_endAccess);

      cursor_type cursor;
  };

} // fcf namespace

namespace std {

  template <typename TContainer>
  size_t distance(const fcf::ContainerAccess<TContainer>& a_begin, const fcf::ContainerAccess<TContainer>& a_end) {
    return a_begin.distance(a_end);
  }

}

#endif // #ifndef ___FCF_BASIS__BITS__PART_CONTAINER_ACCESS__CONTAINER_ACCESS_DEFINITION_HPP___
