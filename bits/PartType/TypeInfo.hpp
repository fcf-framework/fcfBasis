#ifndef ___FCF__BASIS__BITS__PART_TYPE__TYPE_INFO_HPP___
#define ___FCF__BASIS__BITS__PART_TYPE__TYPE_INFO_HPP___

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <memory>
#include "../../macro.hpp"
#include "../../bits/Convert/ConvertFunction.hpp"
#include "../../bits/SpecificatorTypeInfo.hpp"
#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../bits/Specificator/specificators.hpp"
#include "../../bits/Type/TypeId.hpp"
#include "../../bits/Type/Type.hpp"

namespace fcf {

  template <typename Ty, typename TInfoMode = Nop>
  struct Type;

  struct TypeInfo{
    typedef std::unordered_map<unsigned int, ConvertFunction> Converters;

    unsigned int                                      index;
    std::string                                       name;
    RawDataSpecificator::function_type                rawDataResolver;
    Converters                                        converters;
    Converters                                        backConverters;
    std::map<unsigned int, SpecificatorTypeInfo>      specificators;

    template <typename TSpecificator>
    UniversalCall getSpecificator() const {
      const unsigned int specificatorIndex = Type<TSpecificator>().index();
      std::map<unsigned int, SpecificatorTypeInfo>::const_iterator it = specificators.find(specificatorIndex);
      if (it != specificators.end()) {
        return (UniversalCall)it->second.resolve;
      }
      return (UniversalCall)0;
    }
  };

} // fcf namespace



#endif // #ifndef ___FCF__BASIS__BITS__PART_TYPE__TYPE_INFO_HPP___
