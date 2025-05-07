#ifndef ___FCF__BASIS__BITS__DYNAMIC_ITERATOR__BASE_DYNAMIC_ITERATOR_HPP___
#define ___FCF__BASIS__BITS__DYNAMIC_ITERATOR__BASE_DYNAMIC_ITERATOR_HPP___

#include "DynamicIteratorPosition.hpp"

namespace fcf {

  template <typename TContainer, typename TKey, typename TValue>
  class BaseDynamicIterator {
    public:
      typedef TContainer                                    container_type;
      typedef BaseDynamicIterator<TContainer, TKey, TValue> self_type;
      typedef typename TContainer::iterator                 iterator_type;
      typedef TKey                                          key_type;
      typedef TValue                                        value_type;

      BaseDynamicIterator()
        : _pcontiner(0) {}

      BaseDynamicIterator(TContainer& a_container, DynamicIteratorPosition a_position = fcf::DIP_BEGIN)
        : _pcontiner(&a_container)
        , _it(a_position == DIP_BEGIN ? std::begin(a_container) : std::end(a_container))
      {
      }

      bool operator==(const self_type& a_item) const{
        return a_item._it == _it;
      }

      bool operator!=(const self_type& a_item) const{
        return a_item._it != _it;
      }

    protected:
      container_type* _pcontiner;
      iterator_type   _it;
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__DYNAMIC_ITERATOR__BASE_DYNAMIC_ITERATOR_HPP___
