#ifndef ___FCF_BASIS__DETAILS__TYPE_STORAGE_HPP___
#define ___FCF_BASIS__DETAILS__TYPE_STORAGE_HPP___

#include <map>
#include <unordered_map>
#include <memory>
#include "../macro.hpp"
#include "../bits/Convert/ConvertFunction.hpp"
#include "../bits/SpecificatorTypeInfo.hpp"
#include "../bits/Specificator/specificators.hpp"

namespace fcf {
  namespace Details {

    struct TypeInfo{
      typedef std::unordered_map<unsigned int, ConvertFunction> Converters;

      unsigned int                                      index;
      std::string                                       name;
      void*                                             toConverter;
      void*                                             fromConverter;
      RawDataSpecificator::function_type                rawDataResolver;
      std::unordered_map<unsigned int, ConvertFunction> converters;
      std::unordered_map<unsigned int, ConvertFunction> backConverters;
      std::map<unsigned int, SpecificatorTypeInfo>      specificators;
    };

    typedef std::shared_ptr<TypeInfo> SPTypeInfo;

    class TypeStorageContainer {
        typedef std::map<std::string, SPTypeInfo>  NameStorage;
        typedef std::map<unsigned int, SPTypeInfo> IndexStorage;
      public:

        inline TypeStorageContainer()
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
            SPTypeInfo spti(new TypeInfo({typeIndex, a_ti.name, 0, 0, 0}));
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

    FCF_BASIS_DELC_EXTERN FCF_BASIS_DECL_EXPORT TypeStorageContainer typeStorage;

  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__TYPE_STORAGE_HPP___
