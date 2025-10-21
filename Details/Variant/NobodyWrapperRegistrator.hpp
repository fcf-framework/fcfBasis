#ifndef ___FCF_BASIS__DETAILS__VARIANT__NOBODY_WRAPPER_REGISTRATOR_HPP___
#define ___FCF_BASIS__DETAILS__VARIANT__NOBODY_WRAPPER_REGISTRATOR_HPP___

#include "Storage.hpp"
#include "NobodyWrapper.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace Variant {

        template <typename Ty>
        class NobodyWrapperRegistrator {
          public:
            NobodyWrapperRegistrator(unsigned int a_typeIndex){
              NobodyWrapperStorage::iterator it = getStorage().find(a_typeIndex);
              if (it == getStorage().end()) {
                getStorage()[a_typeIndex] = std::shared_ptr< BaseNobodyWrapper >(new NobodyWrapper<Ty>());
              }
            }
        };

        template <>
        class NobodyWrapperRegistrator<void> {
          public:
            NobodyWrapperRegistrator(unsigned int a_typeIndex){
            }
        };

      } // Variant namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__VARIANT__NOBODY_WRAPPER_REGISTRATOR_HPP___

