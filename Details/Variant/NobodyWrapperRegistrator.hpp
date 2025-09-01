#ifndef ___FCF_BASIS__DETAILS__VARIANT__NOBODY_WRAPPER_REGISTRATOR_HPP___
#define ___FCF_BASIS__DETAILS__VARIANT__NOBODY_WRAPPER_REGISTRATOR_HPP___

#include "../../Type.hpp"
#include "Storage.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace Variant {

        template <typename Ty>
        class NobodyWrapperRegistrator {
          public:
            NobodyWrapperRegistrator(){
              unsigned int index = Type<Ty>().index();
              if (0x1100000c == index ){
                std::cout << "!!!!!!!!!!!!" << std::endl;
              }
              NobodyWrapperStorage::iterator it = getStorage().find(index);
              if (it == getStorage().end()) {
                getStorage()[index] = std::shared_ptr< BaseNobodyWrapper >(new NobodyWrapper<Ty>());
              }
            }
        };

        template <>
        class NobodyWrapperRegistrator<void> {
        };

      } // Variant namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__VARIANT__NOBODY_WRAPPER_REGISTRATOR_HPP___

