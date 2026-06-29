#ifndef _FCF_BASIS__BITS__PART_TYPES__UNIVERSAL_PACK_HPP___
#define _FCF_BASIS__BITS__PART_TYPES__UNIVERSAL_PACK_HPP___

#include "../../PartVariant.hpp"
#include "../../PartStaticVector.hpp"

namespace fcf {

  /**
   * @struct UniversalPack
   * @brief A specialized container for returning multiple values through a single Variant.
   *
   * This structure is used in conjunction with the UniversalCall mechanism.
   * When a function or specifier needs to return more than one result, it wraps
   * them into a UniversalPack and returns it as a {@link Variant}.
   *
   * It inherits from StaticVector with a fixed capacity of 2 elements
   * to optimize performance for common multi-return scenarios by using stack memory.
   */
  struct UniversalPack : public StaticVector<Variant, 2> {
    typedef StaticVector<Variant, 2> base_type;
    using base_type::StaticVector;
  };

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_TYPES__UNIVERSAL_PACK_HPP___
