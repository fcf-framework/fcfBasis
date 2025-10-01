#ifndef ___FCF_BASIS__BITS__TYPE__DYNAMIC_ITERATOR_SPECIFICATOR__TYPE_DYNAMIC_TYPE_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__TYPE__DYNAMIC_ITERATOR_SPECIFICATOR__TYPE_DYNAMIC_TYPE_SPECIFICATOR_HPP___

#include "../Type.hpp"
#include "../../Specificator/DynamicIteratorInfo.hpp"
#include "../../PartIterator/DynamicIterator.hpp"

namespace fcf {
  
  template <typename TContainer>
  struct Type<TContainer, DynamicIteratorSpecificator >{
    enum { enable = true };

    bool operator()(TContainer* a_container, DynamicIteratorInfo* a_info){
      typedef DynamicIterator<TContainer> dynamic_iterator_type;
      dynamic_iterator_type* pit;
      if (a_info->flags & DIF_ITERATION) {
        if (!a_info->iterator.is<dynamic_iterator_type>()) {
          a_info->iterator.set(dynamic_iterator_type(*a_container, IP_BEGIN));
          pit = (dynamic_iterator_type*)a_info->iterator.ptr();
        } else {
          pit = (dynamic_iterator_type*)a_info->iterator.ptr();
          if (*pit == dynamic_iterator_type(*a_container, IP_END)){
            return false;
          }
          ++*pit;
        }
        if (*pit == dynamic_iterator_type(*a_container, IP_END)){
          return false;
        }
      } else if (a_info->flags & DIF_RESOLVE) {
        if (!a_info->iterator.is<dynamic_iterator_type>()) {
          if (!a_info->key.empty()) {
            a_info->iterator.set(dynamic_iterator_type(*a_container, a_info->key.convert<typename dynamic_iterator_type::key_type>()));
          } else {
            a_info->iterator.set(dynamic_iterator_type(*a_container, IP_BEGIN));
          }
        }
        pit = (dynamic_iterator_type*)a_info->iterator.ptr();
        if (*pit == dynamic_iterator_type(*a_container, IP_END)){
          return false;
        }
      } else if (a_info->flags & DIF_BEGIN) {
        a_info->iterator.set(dynamic_iterator_type(*a_container, IP_BEGIN));
        pit = (dynamic_iterator_type*)a_info->iterator.ptr();
      } else if (a_info->flags & DIF_END) {
        a_info->iterator.set(dynamic_iterator_type(*a_container, IP_END));
        pit = (dynamic_iterator_type*)a_info->iterator.ptr();
      }
      if (a_info->flags & DIF_GET_TYPE) {
        a_info->type = Type< typename dynamic_iterator_type::value_type >().index();
      }
      if (a_info->flags & DIF_GET_KEY) {
        if (!pit) {
          return false;
        }
        a_info->key.set((unsigned long long)pit->key());
      }
      if (a_info->flags & DIF_GET_VALUE) {
        if (!pit) {
          return false;
        }
        a_info->value = &pit->value();
      }
      if (a_info->flags & DIF_GET_SIZE) {
        if (!a_container) {
          return false;
        }
        a_info->size = a_container->size();
      }
      if (a_info->flags & DIF_GET_FLAT) {
        a_info->flat = dynamic_iterator_type::is_flat;
      }
      return true;
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__TYPE__DYNAMIC_ITERATOR_SPECIFICATOR__TYPE_DYNAMIC_TYPE_SPECIFICATOR_HPP___
