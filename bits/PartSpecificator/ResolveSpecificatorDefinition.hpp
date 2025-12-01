#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__RESOLVE_SPECIFICATOR_DEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__RESOLVE_SPECIFICATOR_DEFINITION_HPP___

#include "../../bits/PartType/TypeDefinition.hpp"

namespace fcf{

  struct ResolveData { 
    void*        data;
    unsigned int typeIndex;
    bool         invariant;
  };

  struct ResolveSpecificator {
    typedef ResolveData (*CallFunctionType)(void*);
    typedef ResolveData (*CallType)(void*);
  };

  template <typename Ty>
  struct Type<Ty, ResolveSpecificator> {
    enum { enable = false };
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__RESOLVE_SPECIFICATOR_DEFINITION_HPP___
