#ifndef _FCF_BASIS__BITS__PART_VARIANT__NDETAILS__IS_VARIANT_HPP___
#define _FCF_BASIS__BITS__PART_VARIANT__NDETAILS__IS_VARIANT_HPP___

#include "../VariantPredefinition.hpp"

namespace fcf{
  namespace NDetails {

    template <typename Ty>
    struct IsVariant{
      enum { value = false };
    };

    template <size_t InnerBufferSize>
    struct IsVariant< VariantBasic<InnerBufferSize> >{
      enum { value = true };
    };

    template <size_t InnerBufferSize>
    struct IsVariant< const VariantBasic<InnerBufferSize> >{
      enum { value = true };
    };

    template <size_t InnerBufferSize>
    struct IsVariant< VariantBasic<InnerBufferSize>& >{
      enum { value = true };
    };

    template <size_t InnerBufferSize>
    struct IsVariant< const VariantBasic<InnerBufferSize>& >{
      enum { value = true };
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_VARIANT__NDETAILS__IS_VARIANT_HPP___
