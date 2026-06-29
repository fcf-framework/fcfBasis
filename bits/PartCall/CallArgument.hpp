#ifndef _FCF_BASIS__BITS__PART_CALL__CALL_ARGUMENT_HPP___
#define _FCF_BASIS__BITS__PART_CALL__CALL_ARGUMENT_HPP___

#include "../../bits/PartVariant/VariantDefinition.hpp"

namespace fcf{

  struct CallArgument {
    TypeIndex    specifier;
    unsigned int argumentNumber;
    Variant      path;
    Variant      values;
    bool         defaultMode;
  };

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_CALL__CALL_ARGUMENT_HPP___
