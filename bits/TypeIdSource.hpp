#ifndef ___FCF_BASIS__BITS__TYPE_ID_SOURCE_HPP___
#define ___FCF_BASIS__BITS__TYPE_ID_SOURCE_HPP___

#include <string>

namespace fcf {

  template <typename Ty>
  struct TypeId;

  template <typename Ty>
  struct TypeIdSource;

  
  //
  // Example:
  //
  // template <typename Ty >
  // struct TypeIdSource< std::vector<Ty> > {
  //   unsigned int index(){
  //     return 0;
  //   }
  //   std::string name(){
  //     return  std::string() + "std::vector<" + TypeId<Ty>().name() + ">";
  //   }
  // };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__TYPE_ID_SOURCE_HPP___
