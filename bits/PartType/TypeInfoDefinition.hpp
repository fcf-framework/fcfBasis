#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_INFO_DEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_INFO_DEFINITION_HPP___

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <memory>
#include "../../macro.hpp"
#include "../../bits/PartConvert/ConvertFunction.hpp"
#include "../../bits/PartSpecificator/SpecificatorInfo.hpp"
#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../bits/PartSpecificator/ResolveSpecificatorDefinition.hpp"
#include "../../bits/PartType/TypeDefinition.hpp"
#include "../../bits/PartType/TypeId.hpp"
#include "../../bits/PartType/Type.hpp"
#include "../../bits/PartType/BaseTypeFactory.hpp"
#include "TypeInfoPredefinition.hpp"

namespace fcf{

  struct TypeInfo{
    typedef std::unordered_map<unsigned int, ConvertFunction> Converters;

    unsigned int                                                  index;
    std::string                                                   name;
    bool                                                          isVariantRef;
    bool                                                          isVariant;
    size_t                                                        innerSize;
    size_t                                                        size;
    unsigned int                                                  dataIndex;
    ResolveSpecificator::CallFunctionType                         resolver;
    Converters                                                    converters;
    Converters                                                    backConverters;
    std::map<unsigned int, SpecificatorInfo>                      specificators;
    BaseTypeFactory*                                              initializer;

    inline TypeInfo(unsigned int a_index, const std::string& a_name, bool a_isVariantRef, bool a_isVariant, size_t a_innerSize, size_t a_size);

    inline TypeInfo();

    inline TypeInfo(const TypeInfo& a_source);

    inline ~TypeInfo();

    inline TypeInfo& operator=(const TypeInfo& a_source);

    template <typename Ty>
    void initialize();

    template <typename TSpecificator>
    typename TSpecificator::CallType getSpecificatorCall() const;

    template <typename TSpecificator>
    typename TSpecificator::CallType getSafeSpecificatorCall() const;

    template <typename TSpecificator>
    UniversalCall getSpecificator() const;

    template <typename TSpecificator>
    UniversalCall getSafeSpecificator() const;

  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_INFO_DEFINITION_HPP___
