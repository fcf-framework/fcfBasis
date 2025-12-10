#ifndef ___FCF_BASIS__BITS__PART_VARIANT__NDETAILS__VARIANT_INNER_SIZE_HPP___
#define ___FCF_BASIS__BITS__PART_VARIANT__NDETAILS__VARIANT_INNER_SIZE_HPP___

namespace fcf{
  namespace NDetails {
    template <typename Ty>
    struct VariantInnerSize{
      enum { value = 0 };
    };

    template <size_t InnerBufferSize>
    struct VariantInnerSize< BasicVariant<InnerBufferSize> >{
      enum { value = InnerBufferSize };
    };

    template <size_t InnerBufferSize>
    struct VariantInnerSize< const BasicVariant<InnerBufferSize> >{
      enum { value = InnerBufferSize };
    };

    template <size_t InnerBufferSize>
    struct VariantInnerSize< BasicVariant<InnerBufferSize>& >{
      enum { value = InnerBufferSize };
    };

    template <size_t InnerBufferSize>
    struct VariantInnerSize< const BasicVariant<InnerBufferSize>& >{
      enum { value = InnerBufferSize };
    };
  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_VARIANT__NDETAILS__VARIANT_INNER_SIZE_HPP___
