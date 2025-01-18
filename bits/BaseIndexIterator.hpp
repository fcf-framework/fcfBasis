#ifndef ___FCF_BASIS__BITS__BASE_INDEX_ITERATOR_HPP___
#define ___FCF_BASIS__BITS__BASE_INDEX_ITERATOR_HPP___

#include "../Type.hpp"

namespace fcf {

    template <typename TContainer>
    class BaseIndexIterator {
      public:
        typedef TContainer                            owner_type;
        typedef typename Type<owner_type>::value_type value_type;
        BaseIndexIterator(owner_type& a_owner)
          : _index(0)
          , _owner(a_owner)
        {
        }
        BaseIndexIterator(owner_type& a_owner, size_t a_index)
          : _index(a_index)
          , _owner(a_owner)
        {
        }
        bool operator==(const BaseIndexIterator& a_it) const {
          return a_it._index == _index;
        }
        value_type* operator->() {
          return &_owner[_index];
        }
        BaseIndexIterator& operator++(){
          ++_index;
          return *this;
        }
      private:
        size_t      _index;
        owner_type& _owner;
    };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__BASE_INDEX_ITERATOR_HPP___
