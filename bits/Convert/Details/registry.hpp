#ifndef ___FCF_BASIS__BITS__CONVERT__DETAILS__REGISTRY_HPP___
#define ___FCF_BASIS__BITS__CONVERT__DETAILS__REGISTRY_HPP___

#include "../ConvertInitializer.hpp"

#include "../../../bits/PartConvert/NDetails/ConvertersRegistrar.hpp"
/*
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
*/
#ifdef FCF_BASIS_IMPLEMENTATION
FCF_CONVERTERS_REGISTRY_FORCE(char);
FCF_CONVERTERS_REGISTRY_FORCE(unsigned char);
FCF_CONVERTERS_REGISTRY_FORCE(short);
FCF_CONVERTERS_REGISTRY_FORCE(unsigned short);
FCF_CONVERTERS_REGISTRY_FORCE(int);
FCF_CONVERTERS_REGISTRY_FORCE(unsigned int);
FCF_CONVERTERS_REGISTRY_FORCE(long long);
FCF_CONVERTERS_REGISTRY_FORCE(unsigned long long);
FCF_CONVERTERS_REGISTRY_FORCE(long int);
FCF_CONVERTERS_REGISTRY_FORCE(unsigned long int);
FCF_CONVERTERS_REGISTRY_FORCE(float);
FCF_CONVERTERS_REGISTRY_FORCE(double);
FCF_CONVERTERS_REGISTRY_FORCE(long double);
FCF_CONVERTERS_REGISTRY_FORCE(std::string);
#endif

#endif // #ifndef ___FCF_BASIS__BITS__CONVERT__DETAILS__REGISTRY_HPP___
