#ifndef ___FCF_BASIS__BITS__BASE_TYPE_HPP___
#define ___FCF_BASIS__BITS__BASE_TYPE_HPP___

#include "TypeId.hpp"

namespace fcf {

  template <typename Ty>
  struct BaseType {
    typedef Ty owner_type;
    static TypeId<Ty>* typeId;
    BaseType(){
      if (!typeId) {
        typeId = new TypeId<Ty>();
      }
    }
    const std::string& name() {
      return typeId->name();
    }
    unsigned int index() {
      return typeId->index();
    }
    const std::map<unsigned int, SpecificatorTypeInfo>& specificators() {
      return typeId->specificators();
    }
  };

  template <typename Ty> TypeId<Ty>* BaseType<Ty>::typeId;

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__BASE_TYPE_HPP___


