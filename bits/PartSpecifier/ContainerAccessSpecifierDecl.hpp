#ifndef _FCF_BASIS__BITS__PART_SPECIFIER__CONTAINER_ACCESS_SPECIFIER_DECL_HPP___
#define _FCF_BASIS__BITS__PART_SPECIFIER__CONTAINER_ACCESS_SPECIFIER_DECL_HPP___

#include "../PartType/TypeDecl.hpp"

namespace fcf{

  struct ContainerAccessSpecifier {
    /*
      typedef DynamicContainerAccess< ContainerAccess<Ty> > (*CallType)(void* a_container);
      typedef DynamicContainerAccess< ContainerAccess<Ty> > (*HandleType)(void* a_container);
    */
  };

  template <typename Ty>
  struct Type<Ty, ContainerAccessSpecifier>;

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_SPECIFIER__CONTAINER_ACCESS_SPECIFIER_DECL_HPP___
