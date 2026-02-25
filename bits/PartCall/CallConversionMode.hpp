#ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_CONVERSION_MODE_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__CALL_CONVERSION_MODE_HPP___

namespace fcf{

  enum CallConversionMode{
    CCM_NONE             = 0,
    CCM_SKIP             = 1,
    CCM_RESOLVE          = 2,
    CCM_POINTER_RESOLVE  = 3,
    CCM_CONVERT          = 4,
    CCM_PTR_CONVERT      = 5,
    CCM_DYNAMIC_RESOLVE  = 6,
    CCM_FLAT_ITERATOR    = 7,
    CCM_ITERATOR         = 8,
    CCM_FLAT_PAIR        = 9,
    CCM_SEPARATE_PAIR    = 10,
    CCM_PLACE_HOLDER     = 11,
    CCM_SINGLE_PAIR      = 12,
    CCM_SINGLE_PAIR_COPY = 13,
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_CONVERSION_MODE_HPP___
