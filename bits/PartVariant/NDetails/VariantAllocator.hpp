#ifndef ___FCF_BASIS__BITS__PART_VARIANT__NDETAILS__VARIANT_ALLOCATOR_HPP___
#define ___FCF_BASIS__BITS__PART_VARIANT__NDETAILS__VARIANT_ALLOCATOR_HPP___

#include "../../../Details/Variant/Wrapper.hpp"

namespace fcf{

  namespace NDetails {

    template <typename Ty, int InnerBufferMode>
    struct VariantAllocatorHandler {
      void* operator()(void* a_innerBuffer, const Ty& a_value) {
        return new (a_innerBuffer) Details::Basis::Variant::Wrapper<Ty>(a_value);
      }
    };

    template <typename Ty>
    struct VariantAllocatorHandler<Ty, 0> {
      void* operator()(void* a_innerBuffer, const Ty& a_value) {
        return new Details::Basis::Variant::Wrapper<Ty>(a_value);
      }
    };

    template <typename Ty, size_t InnerBufferSize>
    struct VariantAllocator {
      enum { InnerBufferMode = sizeof(Details::Basis::Variant::Wrapper<Ty>) > InnerBufferSize ? 0 : 1 };

      void* operator()(void* a_innerBuffer, const Ty& a_value) {
        return VariantAllocatorHandler<Ty, InnerBufferMode>()(a_innerBuffer, a_value);
      }
    };

  } //NDetails namespace

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_VARIANT__NDETAILS__VARIANT_ALLOCATOR_HPP___
