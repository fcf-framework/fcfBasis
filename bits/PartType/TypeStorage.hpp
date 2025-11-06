#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_STORAGE_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_STORAGE_HPP___

#include <string>
#include <map>
#include <unordered_map>
#include <memory>
#include "../../macro.hpp"
#include "../../bits/Convert/ConvertFunction.hpp"
#include "../../bits/PartSpecificator/SpecificatorInfo.hpp"
#include "../../bits/PartType/TypeId.hpp"
#include "../../bits/PartType/TypeInfo.hpp"

namespace fcf{

    class TypeStorage {
      public:
        typedef std::shared_ptr<TypeInfo>          SPTypeInfo;

      protected:
        typedef std::map<std::string, SPTypeInfo>  NameStorage;
        typedef std::map<unsigned int, SPTypeInfo> IndexStorage;

      public:

        inline TypeStorage()
          : _ac(0) { }

        inline const TypeInfo* get(unsigned int a_index) {
          IndexStorage::iterator it = _is.find(a_index);
          return it == _is.end() ? (const TypeInfo*)0 : it->second.get();
        }

        inline const TypeInfo* get(const std::string& a_name) {
          NameStorage::iterator it = _ns.find(a_name);
          return it == _ns.end() ? (const TypeInfo*)0 : it->second.get();
        }

        inline const TypeInfo* get(const char* a_name) {
          NameStorage::iterator it = _ns.find(a_name);
          return it == _ns.end() ? (const TypeInfo*)0 : it->second.get();
        }

        inline TypeInfo* insert(const TypeInfo& a_ti, bool a_autoIndex, unsigned int a_baseIndex) {
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
            SPTypeInfo spti(new TypeInfo(typeIndex, a_ti.name));
            nit = _ns.insert({spti->name, spti}).first;
            _is.insert({spti->index, spti});
          }
          return nit->second.get();
        }

      private:
        NameStorage   _ns;
        IndexStorage  _is;
        unsigned int  _ac;
    };

    FCF_BASIS_DELC_EXTERN FCF_BASIS_DECL_EXPORT TypeStorage typeStorage;

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_STORAGE_HPP___
