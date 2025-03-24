#ifndef ___FCF_BASIS__BITS__BASE_TYPE_HPP___
#define ___FCF_BASIS__BITS__BASE_TYPE_HPP___

#include <type_traits>
#include "TypeId.hpp"

namespace fcf {

  template <typename Ty>
  struct BaseType {
    typedef Ty owner_type;
    static TypeId<Ty>* typeId;
    BaseType(){
      if (!typeId) {
        typedef typename TypeIdSource<Ty>::basic_type basic_type;
        unsigned int baseTypeIndex = 0;
        if(!std::is_same<Ty, basic_type>::value){
          baseTypeIndex = BaseType<basic_type>().index();
        }
        typeId = new TypeId<Ty>(baseTypeIndex);
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


