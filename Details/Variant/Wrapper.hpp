#ifndef ___FCF_BASIS__DETAILS__VARIANT__WRAPPER_HPP___
#define ___FCF_BASIS__DETAILS__VARIANT__WRAPPER_HPP___

#include "BaseWrapper.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace Variant {

        template <typename Ty>
        class Wrapper : public BaseWrapper {
          public:
            Wrapper() {
            }
            Wrapper(const Ty& a_value) 
              : data(a_value) {
            }
            virtual BaseWrapper* clone() {
              return new Wrapper(data);
            };
            virtual BaseWrapper* clone(char* a_mem) {
              return new (a_mem) Wrapper(data);
            };
            Ty data;
        };

      } // Variant namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__VARIANT__WRAPPER_HPP___
