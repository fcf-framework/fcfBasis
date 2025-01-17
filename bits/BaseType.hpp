#ifndef ___FCF_BASIS__BASE_TYPE_HPP___
#define ___FCF_BASIS__BASE_TYPE_HPP___

#include "TypeId.hpp"

namespace fcf {

  template <typename Ty>
  struct BaseType {
    typedef Ty owner_type;
    static TypeId<Ty>* typeId;
    static const char* name() {
      if (!typeId) {
        typeId = new TypeId<Ty>();
      }
      return typeId->name();
    }
    static unsigned int index() {
      if (!typeId) {
        typeId = new TypeId<Ty>();
      }
      return typeId->index();
    }
  };

  template <typename Ty> TypeId<Ty>* BaseType<Ty>::typeId;

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BASE_TYPE_HPP___


