#ifndef ___FCF_BASIS__BITS__TYPE__DYNAMIC_ITERATOR_SPECIFICATOR__TYPE_DYNAMIC_TYPE_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__TYPE__DYNAMIC_ITERATOR_SPECIFICATOR__TYPE_DYNAMIC_TYPE_SPECIFICATOR_HPP___

#include "../Type.hpp"
#include "../../Specificator/DynamicIteratorInfo.hpp"
#include "../../DynamicIterator/DynamicIterator.hpp"

namespace fcf {
  
  template <typename TContainer>
  struct Type<TContainer, DynamicIteratorSpecificator >{
    enum { enable = true };

    bool operator()(TContainer& a_container, DynamicIteratorInfo& a_info){
      typedef DynamicIterator<TContainer> dynamic_iterator_type;
      dynamic_iterator_type* pit;
      if (a_info.flags & DIF_ITERATION) {
        if (!a_info.iterator.is<dynamic_iterator_type>()) {
          a_info.iterator.set(dynamic_iterator_type(a_container, DIP_BEGIN));
          pit = (dynamic_iterator_type*)a_info.iterator.ptr();
        } else {
          pit = (dynamic_iterator_type*)a_info.iterator.ptr();
          if (*pit == dynamic_iterator_type(a_container, DIP_END)){
            return false;
          }
          ++*pit;
        }
        if (*pit == dynamic_iterator_type(a_container, DIP_END)){
          return false;
        }
      } else if (a_info.flags & DIF_RESOLVE) {
        if (!a_info.iterator.is<dynamic_iterator_type>()) {
          a_info.iterator.set(dynamic_iterator_type(a_container, DIP_BEGIN));
        }
        pit = (dynamic_iterator_type*)a_info.iterator.ptr();
        if (*pit == dynamic_iterator_type(a_container, DIP_END)){
          return false;
        }
      }
      if (a_info.flags & DIF_GET_TYPE) {
        a_info.type = Type< typename dynamic_iterator_type::value_type >().index();
      }
      if (a_info.flags & DIF_GET_KEY) {
        if (!pit) {
          return false;
        }
        a_info.key.set((unsigned long long)pit->key());
      }
      if (a_info.flags & DIF_GET_VALUE) {
        if (!pit) {
          return false;
        }
        a_info.value = &pit->value();
      }
      if (a_info.flags & DIF_GET_SIZE) {
        a_info.size = a_container.size();
      }
      return true;
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__TYPE__DYNAMIC_ITERATOR_SPECIFICATOR__TYPE_DYNAMIC_TYPE_SPECIFICATOR_HPP___
