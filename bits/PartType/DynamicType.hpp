
#ifndef ___FCF_BASIS__BITS__PART_TYPE__DYNAMIC_TYPE_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__DYNAMIC_TYPE_HPP___

#include "DynamicTypeDefinition.hpp"
#include "TypeInfo.hpp"
#include "getTypeInfo.hpp"
#include "../../PartException.hpp"

namespace fcf{

  DynamicType::DynamicType()
    : _index(0)
    , _info(0) {
  }

  DynamicType::DynamicType(unsigned int a_typeIndex)
    : _index(a_typeIndex)
    , _info(0) {
  }

  unsigned int DynamicType::index() const{
    return _index;
  }

  std::string DynamicType::name(){
    _prepare();
    return _info->name;
  }

  std::string DynamicType::name(Exception* a_errorDst){
    if (!_prepare(a_errorDst)){
      return std::string();
    }
    return _info->name;
  }

  const TypeInfo* DynamicType::getTypeInfo() {
    _prepare();
    return _info;
  }

  const TypeInfo* DynamicType::getTypeInfo(Exception* a_errorDst) {
    if (!_prepare(a_errorDst)){
      return 0;
    }
    return _info;
  }

  void DynamicType::_prepare(){
    if (!_info){
      _info = ::fcf::getTypeInfo(_index);
    }
  }

  bool DynamicType::_prepare(Exception* a_errorDst){
    if (!_info){
      const TypeInfo* info = ::fcf::getTypeInfo(_index, a_errorDst);
      if (a_errorDst && a_errorDst->name()) {
        return false;
      }
      _info = info;
    }
    return true;
  }

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__DYNAMIC_TYPE_HPP___

