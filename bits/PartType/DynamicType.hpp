#ifndef ___FCF_BASIS__BITS__PART_TYPE__DYNAMIC_TYPE_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__DYNAMIC_TYPE_HPP___

#include "TypeInfo.hpp"
#include "getTypeInfo.hpp"

namespace fcf{

  class DynamicType {
    public:

      DynamicType()
        : _info(0)
        , _index(0) {
      }

      DynamicType(unsigned int a_typeIndex)
        : _index(a_typeIndex)
        , _info(0) {
      }

      unsigned int index() const{
        return _index;
      }

      std::string name(std::exception const ** a_errorDst = 0){
        if (!_prepare(a_errorDst)){
          return std::string();
        }
        return _info->name;
      }

      const TypeInfo* getTypeInfo(std::exception const ** a_errorDst = 0) {
        if (!_prepare(a_errorDst)){
          return 0;
        }
        return _info;
      }

    protected:
      inline bool _prepare(std::exception const ** a_errorDst = 0){
        if (a_errorDst) {
          *a_errorDst = 0;
        }
        if (!_info && _index){
          const TypeInfo* info = ::fcf::getTypeInfo(_index, a_errorDst);
          if (a_errorDst && *a_errorDst) {
            return false;
          }
          _info = info;
        }
        return true;
      }

      unsigned int    _index;
      const TypeInfo* _info;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__DYNAMIC_TYPE_HPP___
