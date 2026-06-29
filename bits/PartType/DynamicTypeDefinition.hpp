#ifndef _FCF_BASIS__BITS__PART_TYPE__DYNAMIC_TYPE_DEFINITION_HPP___
#define _FCF_BASIS__BITS__PART_TYPE__DYNAMIC_TYPE_DEFINITION_HPP___

#include "TypeInfo.hpp"
#include "../../bits/PartException/ExceptionPredefinition.hpp"

namespace fcf{

  class DynamicType {
    public:

      inline DynamicType();

      inline DynamicType(TypeIndex a_typeIndex);

      inline TypeIndex index() const;

      inline std::string name();

      inline std::string name(Exception* a_errorDst);

      inline const TypeInfo* getTypeInfo();

      inline const TypeInfo* getTypeInfo(Exception* a_errorDst);

    protected:
      inline void _prepare();

      inline bool _prepare(Exception* a_errorDst);

      TypeIndex       _index;
      const TypeInfo* _info;
  };

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_TYPE__DYNAMIC_TYPE_DEFINITION_HPP___
