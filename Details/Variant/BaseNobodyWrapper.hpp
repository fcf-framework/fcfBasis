#ifndef ___FCF_BASIS__DETAILS__VARIANT__BASE_NOBODY_WRAPPER_HPP___
#define ___FCF_BASIS__DETAILS__VARIANT__BASE_NOBODY_WRAPPER_HPP___

#include "../../macro.hpp"
#include "BaseWrapper.hpp"
namespace fcf {
  namespace Details {
    namespace Basis {
      namespace Variant {

        class FCF_BASIS_DECL_EXPORT BaseNobodyWrapper {
          public:
            virtual ~BaseNobodyWrapper();
            virtual size_t size() = 0;
            virtual BaseWrapper* clone(const void* a_pdata) = 0;
            virtual BaseWrapper* clone(char* a_mem, const void* a_pdata) = 0;
            virtual BaseWrapper* create() = 0;
            virtual BaseWrapper* create(char* a_mem) = 0;
        };

        #ifdef FCF_BASIS_IMPLEMENTATION
          BaseNobodyWrapper::~BaseNobodyWrapper(){
          }
        #endif

      } // Variant namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__VARIANT__BASE_NOBODY_WRAPPER_HPP___
