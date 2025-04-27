#ifndef ___FCF_BASIS__DETAILS__VARIANT__NOBODY_WRAPPER_HPP___
#define ___FCF_BASIS__DETAILS__VARIANT__NOBODY_WRAPPER_HPP___

#include <memory>
#include "Wrapper.hpp"
#include "BaseNobodyWrapper.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace Variant {

        template <typename Ty>
        class NobodyWrapper : public BaseNobodyWrapper {
          public:
            virtual size_t size(){
              return sizeof(Wrapper<Ty>);
            }

            virtual BaseWrapper* clone(const void* a_pdata) {
              return new Wrapper<Ty>(*(const Ty*)a_pdata);
            };

            virtual BaseWrapper* clone(char* a_mem, const void* a_pdata) {
              return new (a_mem) Wrapper<Ty>(*(const Ty*)a_pdata);
            };

            virtual BaseWrapper* create() {
              return new Wrapper<Ty>();
            }

            virtual BaseWrapper* create(char* a_mem) {
              return new (a_mem) Wrapper<Ty>();
            }
        };

      } // Variant namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__VARIANT__NOBODY_WRAPPER_HPP___
