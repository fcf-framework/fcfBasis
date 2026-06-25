#ifndef ___FCF_BASIS__BITS__PART_TYPES__UNIVERSAL_PACK_HPP___
#define ___FCF_BASIS__BITS__PART_TYPES__UNIVERSAL_PACK_HPP___

#include "../../PartVariant.hpp"
#include "../../PartStaticVector.hpp"

namespace fcf {

  struct UniversalPack : public StaticVector<Variant, 4> {
    typedef StaticVector<Variant, 4> base_type;
    using base_type::StaticVector;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPES__UNIVERSAL_PACK_HPP___
