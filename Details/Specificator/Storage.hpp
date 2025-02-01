#ifndef ___FCF_BASIS__DETAILS__SPECIFICATOR__STORAGE_HPP___
#define ___FCF_BASIS__DETAILS__SPECIFICATOR__STORAGE_HPP___

#include <map>
#include <memory>
#include "../../macro.hpp"

namespace fcf {
  namespace Details {
    namespace Specificator {

      struct SpecificatorInfo {
        unsigned int asize;
      };

      typedef std::map<unsigned int, SpecificatorInfo> Specificators;

      struct Storage {
        std::shared_ptr<Specificators> specificators;
        Storage()
          : specificators(new Specificators()) {
        }
      };

      FCF_BASIS_DELC_EXTERN FCF_BASIS_DECL_EXPORT Storage* g_storage;

      Storage& getStorage();

      #ifdef FCF_BASIS_IMPLEMENTATION
      Storage& getStorage(){
        if (!g_storage) {
          g_storage = new Storage();
        }
        return *g_storage;
      }
      #endif

      FCF_INITIAZE_GLOBAL_PTR(g_storage, Storage);

    }
  } // Details namesace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__SPECIFICATOR__STORAGE_HPP___

