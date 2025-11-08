#ifndef ___FCF__BASIS__BITS__PART_TYPE__TYPE_INFO_HPP___
#define ___FCF__BASIS__BITS__PART_TYPE__TYPE_INFO_HPP___

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

namespace fcf {

  struct TypeInfo{
    typedef std::unordered_map<unsigned int, ConvertFunction> Converters;

    unsigned int                                                  index;
    std::string                                                   name;
    ResolveSpecificator::CallFunctionType                         resolver;
    Converters                                                    converters;
    Converters                                                    backConverters;
    std::map<unsigned int, SpecificatorInfo>                      specificators;
    std::shared_ptr< BaseTypeFactory >                            initializer;

    TypeInfo(unsigned int a_index, const std::string& a_name)
      : index(a_index)
      , name(a_name)
      , resolver(0) {

    }

    template <typename TSpecificator>
    UniversalCall getSpecificator() const {
      const unsigned int specificatorIndex = Type<TSpecificator>().index();
      std::map<unsigned int, SpecificatorInfo>::const_iterator it = specificators.find(specificatorIndex);
      if (it != specificators.end()) {
        return (UniversalCall)it->second.universalCall;
      }
      return (UniversalCall)0;
    }
  };

} // fcf namespace



#endif // #ifndef ___FCF__BASIS__BITS__PART_TYPE__TYPE_INFO_HPP___
