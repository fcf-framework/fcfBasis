#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_ID_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_ID_HPP___

#include "TypeIndex.hpp"


namespace fcf{

  template <typename Ty>
  struct TypeId;

  //
  // Example:
  //
  // template <typename Ty >
  // struct TypeIdSource< std::vector<Ty> > {
  //
  //   bool autoIndex() {
  //     return (index() & 0x00ffffff) == 0;
  //   }
  //
  //   TypeIndex index(){
  //     return 0;
  //   }
  //
  //   std::string name(){
  //     return  std::string() + "std::vector<" + TypeId<Ty>().name() + ">";
  //   }
  //
  // };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_ID_HPP___
