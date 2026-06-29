#ifndef _FCF_BASIS__BITS__PART_VARIANT__VARIANT_PREDEFINITION_HPP___
#define _FCF_BASIS__BITS__PART_VARIANT__VARIANT_PREDEFINITION_HPP___

#include <string>
#include <map>
#include "../../bits/PartMetaType/MetaTypeMaxTypeSize.hpp"

namespace fcf{

  enum { DefaultVariantBufferSize = MetaTypeMaxTypeSize<
                        std::string,
                        std::wstring,
                        std::map<std::string, std::string>
                          >::size };

  template <size_t InnerBufferSize = DefaultVariantBufferSize>
  class VariantBasic;

  typedef VariantBasic<DefaultVariantBufferSize> Variant;

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_VARIANT__VARIANT_PREDEFINITION_HPP___
