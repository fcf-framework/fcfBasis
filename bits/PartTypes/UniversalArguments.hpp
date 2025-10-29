#ifndef ___FCF_BASIS__BITS__PART_TYPES__UNIVERSAL_ARGUMENTS_HPP___
#define ___FCF_BASIS__BITS__PART_TYPES__UNIVERSAL_ARGUMENTS_HPP___

#include "../../Variant.hpp"
#include "../../StaticVector.hpp"

namespace fcf {

  struct UniversalArguments : public StaticVector<Variant, 4> {
    typedef StaticVector<Variant, 4> base_type;
    using base_type::StaticVector;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPES__UNIVERSAL_ARGUMENTS_HPP___
