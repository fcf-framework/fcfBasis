#ifndef ___FCF_BASIS__DETAILS__INDEXABLE_FUNCTION__STORAGE_HPP___
#define ___FCF_BASIS__DETAILS__INDEXABLE_FUNCTION__STORAGE_HPP___

#include "../../macro.hpp"

namespace fcf {
  namespace Details {
    namespace IndexableFunction {

        typedef std::map< BaseFunctionSignature, std::map<std::string, unsigned int>  > Indexes;

        struct Storage {
          Indexes                           indexes;
          std::vector<IndexableFunctionInfo>   functions;
        };

        FCF_MATH_DELC_EXTERN FCF_MATH_DECL_EXPORT Storage* g_storage;

        Storage& getStorage();

        #ifdef FCF_MATH_IMPLEMENTATION
        Storage& getStorage(){
          if (!g_storage) {
            g_storage = new Storage();
          }
          return *g_storage;
        }
        #endif

        FCF_INITIAZE_GLOBAL_PTR(g_storage, Storage);

    } // IndexableFunctionRegistrator namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__INDEXABLE_FUNCTION_REGISTRATOR__STORAGE_HPP___
