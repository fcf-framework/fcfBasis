#ifndef ___FCF_BASIS__BITS__TYPE_ID_HPP___
#define ___FCF_BASIS__BITS__TYPE_ID_HPP___

#include <stdexcept>
#include "../Details/typeStorage.hpp"
#include "TypeIdSource.hpp"
#include "SpecificatorTypeInfo.hpp"

namespace fcf {

    template <typename TContainer, typename TSpecificator>
    class SpecificatorTypeRegistrator;

    template <typename Ty>
    class TypeId {
      public:

        template <typename TContainer, typename TSpecificator>
        friend class SpecificatorTypeRegistrator;

        TypeId()
          : _typeName(TypeIdSource<Ty>().name()) {
          Details::TypeStorage::iterator it = Details::typeStorage.find(name());
          if (it == Details::typeStorage.end()){
            _typeIndex = TypeIdSource<Ty>().index();
            if (!_typeIndex) {
              _typeIndex = Details::typeStorage.size() + 1 + (1 << 30);
            }
            Details::typeStorage[name()] = _typeIndex;
          } else {
            if (name() != it->first){
              throw std::runtime_error(
                std::string() +
                "Re-registration of the data type. "
                "The structure of fcf::TypeIdSource is announced once with different names like " + name() + "."
                );
            }
            _typeIndex = it->second;
          }
        }

        const char* name() {
          return _typeName.c_str();
        }

        unsigned int index() {
          return _typeIndex;
        }

        const std::map<unsigned int, SpecificatorTypeInfo>& specificators() {
          return _typeSpecificators;
        }

      private:

        unsigned int                                  _typeIndex;
        std::string                                   _typeName;
        std::map<unsigned int, SpecificatorTypeInfo>  _typeSpecificators;
    };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__TYPE_ID_HPP___
