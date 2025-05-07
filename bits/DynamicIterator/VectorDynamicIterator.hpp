#ifndef ___FCF__BASIS__BITS__DYNAMIC_ITERATOR__VECTOR_DYNAMIC_ITERATOR_HPP___
#define ___FCF__BASIS__BITS__DYNAMIC_ITERATOR__VECTOR_DYNAMIC_ITERATOR_HPP___

#include "BaseDynamicIterator.hpp"

namespace fcf {

  template <typename TContainer>
  class VectorDynamicIterator: public BaseDynamicIterator<TContainer, typename TContainer::size_type, typename TContainer::value_type> {
    public:
      typedef BaseDynamicIterator<TContainer, typename TContainer::size_type, typename TContainer::value_type> base_type;

      using base_type::BaseDynamicIterator;
      typedef typename base_type::container_type container_type;
      typedef typename base_type::iterator_type  iterator_type;
      typedef typename base_type::key_type       key_type;
      typedef typename base_type::value_type     value_type;

      typedef VectorDynamicIterator<TContainer> self_type;

      enum { is_flat_value = true };

      VectorDynamicIterator(container_type& a_container, key_type a_position) {
        this->_pcontiner = &a_container;
        this->_it = std::begin(a_container) + a_position;
      }

      self_type operator--() {
        --this->_it;
        return *this;
      }

      self_type operator--(int) {
        self_type result(*this);
        this->operator--();
        return result;
      }

      self_type operator++() {
        ++this->_it;
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
        return std::distance(std::begin(*this->_pcontiner), this->_it);
      }
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__DYNAMIC_ITERATOR__VECTOR_DYNAMIC_ITERATOR_HPP___
