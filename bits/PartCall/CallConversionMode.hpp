#ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_CONVERSION_MODE_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__CALL_CONVERSION_MODE_HPP___

namespace fcf{

  enum CallConversionMode{
    CCM_NONE            = 0,
    CCM_SKIP            = 1,
    CCM_RESOLVE         = 2,
    CCM_POINTER_RESOLVE = 3,
    CCM_CONVERT         = 4,
    CCM_DYNAMIC_RESOLVE = 5,
    CCM_FLAT_ITERATOR   = 6,
    CCM_ITERATOR        = 7,
    CCM_PLACE_HOLDER    = 8,
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_CONVERSION_MODE_HPP___
