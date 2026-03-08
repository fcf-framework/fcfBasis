#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_STORAGE_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_STORAGE_HPP___

#include "TypeStorageDefinition.hpp"
#include "../../bits/PartType/TypeInfo.hpp"

namespace fcf{

  TypeStorage::TypeStorage()
    : _ac(0) { }

  const TypeInfo* TypeStorage::get(unsigned int a_index) {
    IndexStorage::iterator it = _is.find(a_index);
    return it == _is.end() ? (const TypeInfo*)0 : it->second.get();
  }

  const TypeInfo* TypeStorage::get(const std::string& a_name) {
    NameStorage::iterator it = _ns.find(a_name);
    return it == _ns.end() ? (const TypeInfo*)0 : it->second.get();
  }

  const TypeInfo* TypeStorage::get(const char* a_name) {
    NameStorage::iterator it = _ns.find(a_name);
    return it == _ns.end() ? (const TypeInfo*)0 : it->second.get();
  }

  TypeInfo* TypeStorage::insert(const TypeInfo& a_ti, bool a_autoIndex, unsigned int a_baseIndex) {
    NameStorage::iterator nit = _ns.find(a_ti.name);
    if (nit == _ns.end()) {
      unsigned int typeIndex = a_ti.index;
      if (a_autoIndex) {
        unsigned int typeCounter = a_baseIndex
                                      ? (a_baseIndex & 0x00ffffff)
                                      : (++_ac);
        typeIndex &= 0xff000000;
        typeIndex |= typeCounter | 0x01000000;
      };
      SPTypeInfo spti(new TypeInfo(typeIndex, a_ti.name, a_ti.isVariantRef, a_ti.isVariant, a_ti.innerSize, a_ti.size));
      nit = _ns.insert({spti->name, spti}).first;
      _is.insert({spti->index, spti});
    }
    return nit->second.get();
  }

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_STORAGE_HPP___
