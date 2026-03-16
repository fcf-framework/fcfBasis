#ifndef ___FCF_BASIS__BITS__PART_VARIANT__NDETAILS__VARIANT_ALLOCATOR_HPP___
#define ___FCF_BASIS__BITS__PART_VARIANT__NDETAILS__VARIANT_ALLOCATOR_HPP___

namespace fcf{

  namespace NDetails {

    template <typename Ty, int InnerBufferMode>
    struct VariantAllocatorHandler {
       template <typename InputType>
       inline Ty* operator()(void* a_innerBuffer, const InputType& a_value) {
        return new (a_innerBuffer) Ty(a_value);
      }
    };

    template <typename Ty>
    struct VariantAllocatorHandler<Ty, 0> {
      template <typename InputType>
      inline Ty* operator()(void* //a_innerBuffer
                                  , const InputType& a_value) {
        return new Ty(a_value);
      }
    };

    template <typename Ty, size_t InnerBufferSize>
    struct VariantAllocator {
      enum { InnerBufferMode = sizeof(Ty) > InnerBufferSize ? 0 : 1 };

      template <typename InputType>
      inline Ty* operator()(void* a_innerBuffer, const InputType& a_value) {
        return VariantAllocatorHandler<Ty, InnerBufferMode>()(a_innerBuffer, a_value);
      }
    };

  
  } //NDetails namespace

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_VARIANT__NDETAILS__VARIANT_ALLOCATOR_HPP___
