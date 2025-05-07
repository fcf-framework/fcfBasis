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
    using VectorDynamicIterator< std::vector<Ty> >::VectorDynamicIterator;
  };

  template <typename Ty>
  class DynamicIterator< std::list<Ty> >: public ListDynamicIterator< std::list<Ty> >{
    using ListDynamicIterator< std::vector<Ty> >::ListDynamicIterator;
  };

  template <typename TKey, typename TValue>
  class DynamicIterator< std::map<TKey, TValue> >: public MapDynamicIterator< std::map<TKey, TValue> >{
    using MapDynamicIterator< std::map<TKey, TValue> >::MapDynamicIterator;
  };


  template <typename TKey>
  class DynamicIterator< std::set<TKey> >: public SetDynamicIterator< std::set<TKey> >{
    using SetDynamicIterator< std::set<TKey> >::MapDynamicIterator;
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__DYNAMIC_ITERATOR__DYNAMIC_ITERATOR_HPP___
