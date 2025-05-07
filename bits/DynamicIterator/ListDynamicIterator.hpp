#ifndef ___FCF__BASIS__BITS__DYNAMIC_ITERATOR__LIST_DYNAMIC_ITERATOR_HPP___
#define ___FCF__BASIS__BITS__DYNAMIC_ITERATOR__LIST_DYNAMIC_ITERATOR_HPP___
#include <list>
#include "BaseDynamicIterator.hpp"

namespace fcf {

  template <typename TContainer>
  class ListDynamicIterator : public BaseDynamicIterator<TContainer, typename TContainer::size_type, typename TContainer::value_type> {
    public:
      typedef BaseDynamicIterator<TContainer, typename TContainer::size_type, typename TContainer::value_type> base_type;

      using base_type::BaseDynamicIterator;
      typedef typename base_type::container_type container_type;
      typedef typename base_type::iterator_type  iterator_type;
      typedef typename base_type::key_type       key_type;
      typedef typename base_type::value_type     value_type;

      typedef ListDynamicIterator<TContainer> self_type;

      enum { is_flat_value = false };

      ListDynamicIterator()
        : _key(0) {}

      ListDynamicIterator(container_type& a_container, DynamicIteratorPosition a_position = fcf::DIP_BEGIN)
        : base_type(a_container, a_position)
        , _key(a_position == DIP_BEGIN ? 0 : a_container.size())
      {
      }

      ListDynamicIterator(container_type& a_container, key_type a_position)
        : base_type(a_container)
        , _key(0)
      {
        while(_key < a_position) {
          operator++();
        }
      }

      self_type operator--() {
        --this->_it;
        --_key;
        return *this;
      }

      self_type operator--(int) {
        self_type result(*this);
        this->operator--();
        return result;
      }

      self_type operator++() {
        ++this->_it;
        ++_key;
        return *this;
      }

      self_type operator++(int) {
        self_type result(*this);
        this->operator++();
        return result;
      }

      value_type& value(){
        return *this->_it;
      }

      key_type key(){
        return _key;
      }

      protected:
        key_type _key;
  };

} // fcf namespace


#endif // #ifndef ___FCF__BASIS__BITS__DYNAMIC_ITERATOR__LIST_DYNAMIC_ITERATOR_HPP___
