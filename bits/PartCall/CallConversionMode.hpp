#ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_CONVERSION_MODE_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__CALL_CONVERSION_MODE_HPP___

namespace fcf{

  enum CallConversionMode{
    CCM_NONE            = 0,
    CCM_RESOLVE         = 1,
    CCM_CONVERT         = 2,
    CCM_DYNAMIC_RESOLVE = 3,
    CCM_FLAT_ITERATOR   = 4,
    CCM_PLACE_HOLDER    = 5,
    CCM_SKIP            = 6,
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_CONVERSION_MODE_HPP___
