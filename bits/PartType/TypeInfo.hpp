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
#include "../../bits/PartType/TypeIndexConverter.hpp"

namespace fcf {

  struct TypeInfo{
    typedef std::unordered_map<unsigned int, ConvertFunction> Converters;

    unsigned int                                                  index;
    std::string                                                   name;
    unsigned int                                                  dataIndex;
    ResolveSpecificator::CallFunctionType                         resolver;
    Converters                                                    converters;
    Converters                                                    backConverters;
    std::map<unsigned int, SpecificatorInfo>                      specificators;
    std::shared_ptr< BaseTypeFactory >                            initializer;

    TypeInfo(unsigned int a_index, const std::string& a_name)
      : index(a_index)
      , name(a_name)
      , dataIndex(TypeIndexConverter<>::getDataIndex(a_index))
      , resolver(0) {

    }

    template <typename TSpecificator>
    typename TSpecificator::CallType getSpecificatorCall() const {
      const unsigned int specificatorIndex = Type<TSpecificator>().index();
      std::map<unsigned int, SpecificatorInfo>::const_iterator it = specificators.find(specificatorIndex);
      if (it != specificators.end()) {
        return (typename TSpecificator::CallType)it->second.call;
      }
      return (typename TSpecificator::CallType)0;
    }

    template <typename TSpecificator>
    typename TSpecificator::CallType getSafeSpecificatorCall() const {
      const unsigned int specificatorIndex = Type<TSpecificator>().index();
      std::map<unsigned int, SpecificatorInfo>::const_iterator it = specificators.find(specificatorIndex);
      if (it != specificators.end() && !!it->second.call) {
        return (typename TSpecificator::CallType)it->second.call;
      }
      throw std::runtime_error("Specificator not found");
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

    template <typename TSpecificator>
    UniversalCall getSafeSpecificator() const {
      const unsigned int specificatorIndex = Type<TSpecificator>().index();
      std::map<unsigned int, SpecificatorInfo>::const_iterator it = specificators.find(specificatorIndex);
      if (it != specificators.end() && !!it->second.universalCall) {
        return (UniversalCall)it->second.universalCall;
      }
      throw std::runtime_error("Specificator not found");
    }
  };

} // fcf namespace



#endif // #ifndef ___FCF__BASIS__BITS__PART_TYPE__TYPE_INFO_HPP___
