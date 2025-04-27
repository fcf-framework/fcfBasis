#ifndef ___FCF_BASIS__DETAILS__VARIANT__BASE_WRAPPER_HPP___
#define ___FCF_BASIS__DETAILS__VARIANT__BASE_WRAPPER_HPP___

#include "../../macro.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace Variant {

        class FCF_BASIS_DECL_EXPORT BaseWrapper{
          public:
            virtual ~BaseWrapper();
            virtual BaseWrapper* clone() = 0;
            virtual BaseWrapper* clone(char* a_mem) = 0;
        };

        #ifdef FCF_BASIS_IMPLEMENTATION
          BaseWrapper::~BaseWrapper(){
          }
        #endif

      } // Variant namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__VARIANT__BASE_WRAPPER_HPP___
