#ifndef ___FCF_BASIS__BITS__CONVERT__DETAILS__REGISTRY_HPP___
#define ___FCF_BASIS__BITS__CONVERT__DETAILS__REGISTRY_HPP___

#include "../ConvertInitializer.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace Convert {

        #ifdef FCF_BASIS_IMPLEMENTATION
          ConvertInitializer<char,
                            unsigned char,
                            short,
                            unsigned short,
                            int,
                            unsigned int,
                            long long,
                            unsigned long long,
                            unsigned long int,
                            float,
                            double,
                            long double,
                            std::string> initilaizer;
        #endif
      }
    }
  }
}

#endif // #ifndef ___FCF_BASIS__BITS__CONVERT__DETAILS__REGISTRY_HPP___
