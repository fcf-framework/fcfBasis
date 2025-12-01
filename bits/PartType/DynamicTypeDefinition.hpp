#ifndef ___FCF_BASIS__BITS__PART_TYPE__DYNAMIC_TYPE_DEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__DYNAMIC_TYPE_DEFINITION_HPP___

#include "TypeInfo.hpp"

namespace fcf{

  class DynamicType {
    public:

      inline DynamicType();

      inline DynamicType(unsigned int a_typeIndex);

      inline unsigned int index() const;

      inline std::string name(std::exception const ** a_errorDst = 0);

      inline const TypeInfo* getTypeInfo(std::exception const ** a_errorDst = 0);

      inline size_t getWrapperSize(std::exception const ** a_errorDst = 0);

    protected:
      inline bool _prepare(std::exception const ** a_errorDst = 0);

      unsigned int    _index;
      const TypeInfo* _info;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__DYNAMIC_TYPE_DEFINITION_HPP___
