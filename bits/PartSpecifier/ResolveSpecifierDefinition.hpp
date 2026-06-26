#ifndef ___FCF_BASIS__BITS__PART_SPECIFIER__RESOLVE_SPECIFIER_DEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFIER__RESOLVE_SPECIFIER_DEFINITION_HPP___

#include "../../bits/PartType/TypePredefinition.hpp"

namespace fcf{

  struct ResolveData { 
    void*       data;
    TypeIndex   typeIndex;
    bool        invariant;
  };

  struct ResolveSpecifier {
    typedef ResolveData (*CallType)(void* a_object);
    typedef void (*HandleType)(void* /* specific type ptr (Ty*) */ a_object, void** a_dstData, TypeIndex* a_dstTypeIndex);
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFIER__RESOLVE_SPECIFIER_DEFINITION_HPP___
