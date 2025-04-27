#ifndef ___FCF_BASIS__DETAILS__VARIANT__STORAGE_HPP___
#define ___FCF_BASIS__DETAILS__VARIANT__STORAGE_HPP___

#include "../../macro.hpp"
#include "BaseNobodyWrapper.hpp"
#include "NobodyWrapperStorage.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace Variant {

        #ifdef FCF_BASIS_IMPLEMENTATION
          FCF_BASIS_DELC_EXTERN FCF_BASIS_DECL_EXPORT NobodyWrapperStorage* g_storage = 0;
        #else
          FCF_BASIS_DELC_EXTERN FCF_BASIS_DECL_EXPORT NobodyWrapperStorage* g_storage;
        #endif // #ifdef FCF_BASIS_IMPLEMENTATION

        FCF_BASIS_DECL_EXPORT NobodyWrapperStorage& getStorage();

        #ifdef FCF_BASIS_IMPLEMENTATION
          NobodyWrapperStorage& getStorage() {
            if (!g_storage) {
              g_storage = new NobodyWrapperStorage();
            }
            return *g_storage;
          }
        #endif // #ifdef FCF_BASIS_IMPLEMENTATION

      } // Variant namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__VARIANT__STORAGE_HPP___
