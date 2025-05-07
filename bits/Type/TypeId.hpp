#ifndef ___FCF_BASIS__BITS__TYPE__TYPE_ID_HPP___
#define ___FCF_BASIS__BITS__TYPE__TYPE_ID_HPP___

namespace fcf {

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
  //   unsigned int index(){
  //     return 0;
  //   }
  //
  //   std::string name(){
  //     return  std::string() + "std::vector<" + TypeId<Ty>().name() + ">";
  //   }
  //
  // };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__TYPE__TYPE_ID_HPP___
