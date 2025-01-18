#ifndef ___FCF_BASIS__BITS__TYPE_ID_HPP___
#define ___FCF_BASIS__BITS__TYPE_ID_HPP___

#include <stdexcept>
#include "../Details/typeStorage.hpp"
#include "TypeIdSource.hpp"

namespace fcf {

    template <typename Ty>
    struct TypeId {
      TypeId()
        : typeName(TypeIdSource<Ty>().name()) {
        Details::TypeStorage::iterator it = Details::typeStorage.find(name());
        if (it == Details::typeStorage.end()){
          typeIndex = TypeIdSource<Ty>().index();
          if (!typeIndex) {
            typeIndex = Details::typeStorage.size() + 1 + (1 << 30);
          }
          Details::typeStorage[name()] = typeIndex;
        } else {
          if (name() != it->first){
            throw std::runtime_error(
              std::string() +
              "Re-registration of the data type. "
              "The structure of fcf::TypeIdSource is announced once with different names like " + name() + "."
              );
          }
          typeIndex = it->second;
        }
      }

      const char* name() {
        return typeName.c_str();
      }

      unsigned int index() {
        return typeIndex;
      }

      unsigned int typeIndex;
      std::string  typeName;
    };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__TYPE_ID_HPP___
