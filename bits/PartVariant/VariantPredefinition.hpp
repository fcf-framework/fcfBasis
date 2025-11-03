#ifndef ___FCF_BASIS__BITS__PART_VARIANT__VARIANT_PREDEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_VARIANT__VARIANT_PREDEFINITION_HPP___

#include "../../Details/MaxTypesSize.hpp"
#include "../../Details/Variant/Wrapper.hpp"

namespace fcf{

  enum { DefaultVariantBufferSize = fcf::Details::Basis::MaxTypesSize<
                          typename Details::Basis::Variant::Wrapper<std::string>,
                          typename Details::Basis::Variant::Wrapper<std::wstring>,
                          typename Details::Basis::Variant::Wrapper< std::map<std::string, std::string> >
                          >::size };

  template <size_t InnerBufferSize = DefaultVariantBufferSize>
  class BasicVariant;

  typedef BasicVariant<DefaultVariantBufferSize> Variant;

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_VARIANT__VARIANT_PREDEFINITION_HPP___
