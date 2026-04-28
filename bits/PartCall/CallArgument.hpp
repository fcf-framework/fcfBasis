#ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_ARGUMENT_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__CALL_ARGUMENT_HPP___

#include "../../bits/PartVariant/VariantDefinition.hpp"

namespace fcf{

  struct CallArgument {
    unsigned int specificator;
    unsigned int argumentNumber;
    Variant      path;
    Variant      values;
    bool         defaultMode;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_ARGUMENT_HPP___
