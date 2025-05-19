#ifndef ___FCF__BASIS__BITS__DYNAMIC_ITERATOR__DYNAMIC_ITERATOR_HPP___
#define ___FCF__BASIS__BITS__DYNAMIC_ITERATOR__DYNAMIC_ITERATOR_HPP___

#include <vector>
#include <list>
#include <map>
#include <set>
#include "DynamicIteratorPosition.hpp"
#include "VectorDynamicIterator.hpp"
#include "ListDynamicIterator.hpp"
#include "MapDynamicIterator.hpp"
#include "SetDynamicIterator.hpp"

namespace fcf {

  template <typename TContainer>
  struct DynamicIterator;

  template <typename Ty>
  class DynamicIterator< std::vector<Ty> >: public VectorDynamicIterator< std::vector<Ty> >{
    public:
      typedef VectorDynamicIterator< std::vector<Ty> > base_type;
      using base_type::BaseDynamicIterator;
      typedef typename base_type::container_type container_type;
      typedef typename base_type::iterator_type  iterator_type;
      typedef typename base_type::key_type       key_type;
      typedef typename base_type::value_type     value_type;

      using base_type::VectorDynamicIterator;
      using base_type::is_flat;
  };

  template <typename Ty>
  class DynamicIterator< std::list<Ty> >: public ListDynamicIterator< std::list<Ty> >{
    typedef ListDynamicIterator< std::list<Ty> > base_type;
    using base_type::ListDynamicIterator;
    using base_type::is_flat;
    typedef typename base_type::container_type container_type;
    typedef typename base_type::iterator_type  iterator_type;
    typedef typename base_type::key_type       key_type;
    typedef typename base_type::value_type     value_type;
  };

  template <typename TKey, typename TValue>
  class DynamicIterator< std::map<TKey, TValue> >: public MapDynamicIterator< std::map<TKey, TValue> >{
    typedef MapDynamicIterator< std::map<TKey, TValue> > base_type;
    using base_type::MapDynamicIterator;
    using base_type::is_flat;
    typedef typename base_type::container_type container_type;
    typedef typename base_type::iterator_type  iterator_type;
    typedef typename base_type::key_type       key_type;
    typedef typename base_type::value_type     value_type;
  };


  template <typename TKey>
  class DynamicIterator< std::set<TKey> >: public SetDynamicIterator< std::set<TKey> >{
    typedef SetDynamicIterator< std::set<TKey> > base_type;
    using base_type::SetDynamicIterator;
    using base_type::is_flat;
    typedef typename base_type::container_type container_type;
    typedef typename base_type::iterator_type  iterator_type;
    typedef typename base_type::key_type       key_type;
    typedef typename base_type::value_type     value_type;
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__DYNAMIC_ITERATOR__DYNAMIC_ITERATOR_HPP___
