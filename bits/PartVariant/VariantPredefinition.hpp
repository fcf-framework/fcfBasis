#ifndef ___FCF_BASIS__BITS__PART_VARIANT__VARIANT_PREDEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_VARIANT__VARIANT_PREDEFINITION_HPP___

#include <string>
#include <map>
#include "../../bits/PartMetaType/MetaTypeMaxTypeSize.hpp"
#include "../../bits/PartType/TypeWrapperDefinition.hpp"

namespace fcf{

  enum { DefaultVariantBufferSize = MetaTypeMaxTypeSize<
                          TypeWrapper<std::string>,
                          TypeWrapper<std::wstring>,
                          TypeWrapper< std::map<std::string, std::string> >
                          >::size };

  template <size_t InnerBufferSize = DefaultVariantBufferSize>
  class BasicVariant;

  typedef BasicVariant<DefaultVariantBufferSize> Variant;

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_VARIANT__VARIANT_PREDEFINITION_HPP___
