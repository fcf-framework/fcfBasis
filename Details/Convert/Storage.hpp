#ifndef ___FCF_BASIS__DETAILS__CONVERT__STORAGE_HPP___
#define ___FCF_BASIS__DETAILS__CONVERT__STORAGE_HPP___

#include "../../macro.hpp"
#include "ConvertInitializer.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace Convert {

        #ifdef FCF_BASIS_IMPLEMENTATION
          FCF_BASIS_DELC_EXTERN FCF_BASIS_DECL_EXPORT ConvertStorage* g_storage = 0;
        #else
          FCF_BASIS_DELC_EXTERN FCF_BASIS_DECL_EXPORT ConvertStorage* g_storage;
        #endif // #ifdef FCF_BASIS_IMPLEMENTATION

        FCF_BASIS_DECL_EXPORT ConvertStorage& getStorage();

        #ifdef FCF_BASIS_IMPLEMENTATION
          ConvertStorage& getStorage() {
            if (!g_storage) {
              ConvertStorage* storage = new ConvertStorage();
              ConvertInitializer<char, 
                                unsigned char, 
                                short, 
                                unsigned short, 
                                int, 
                                unsigned int, 
                                long long, 
                                unsigned long long, 
                                float, 
                                double, 
                                long double,
                                std::string> ci;
              ci.call(storage);
              g_storage = storage;
            }
            return *g_storage;
          }
        #endif // #ifdef FCF_BASIS_IMPLEMENTATION

      } // Convert namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__CONVERT__STORAGE_HPP___
