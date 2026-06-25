#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__RESOLVE_SPECIFICATOR_DEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__RESOLVE_SPECIFICATOR_DEFINITION_HPP___

#include "../../bits/PartType/TypePredefinition.hpp"

namespace fcf{

  struct ResolveData { 
    void*        data;
    unsigned int typeIndex;
    bool         invariant;
  };

  struct ResolveSpecificator {
    typedef ResolveData (*CallType)(void* a_object);
    typedef void (*HandleType)(void* /* specific type ptr (Ty*) */ a_object, void** a_dstData, unsigned int* a_dstTypeIndex);
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__RESOLVE_SPECIFICATOR_DEFINITION_HPP___
