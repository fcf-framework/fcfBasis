#ifndef _FCF_BASIS__BITS__PART_TYPE__TYPE_STORAGE_DEFINITION_HPP___
#define _FCF_BASIS__BITS__PART_TYPE__TYPE_STORAGE_DEFINITION_HPP___

#include <string>
#include <map>
#include <memory>

#include "../../macro.hpp"

#include "../../bits/PartConvert/ConvertFunction.hpp"
#include "../../bits/PartSpecifier/SpecifierInfo.hpp"
#include "../../bits/PartType/TypeId.hpp"
#include "../../bits/PartType/TypeIndex.hpp"
#include "../../bits/PartType/TypeInfoDefinition.hpp"


namespace fcf {
  
  class TypeStorage {
    public:
      typedef std::shared_ptr<TypeInfo>          SPTypeInfo;

    protected:
      typedef std::map<std::string, SPTypeInfo>  NameStorage;
      typedef std::map<TypeIndex, SPTypeInfo> IndexStorage;

    public:

      inline TypeStorage();

      inline const TypeInfo* get(TypeIndex a_index);

      inline const TypeInfo* get(const std::string& a_name);

      inline const TypeInfo* get(const char* a_name);

      inline TypeInfo* insert(const TypeInfo& a_ti, bool a_autoIndex, TypeIndex a_baseIndex);

    private:
      NameStorage   _ns;
      IndexStorage  _is;
      unsigned int  _ac;
  };

  FCF_BASIS_DECL_EXPORT TypeStorage& getTypeStorage();
} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_TYPE__TYPE_STORAGE_DEFINITION_HPP___
