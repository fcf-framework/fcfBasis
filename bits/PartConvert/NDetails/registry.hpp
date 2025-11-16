#ifndef ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__REGISTRY_HPP___
#define ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__REGISTRY_HPP___

#include "ConvertersRegistrar.hpp"

#ifdef FCF_BASIS_IMPLEMENTATION
  FCF_CONVERTERS_REGISTRY_FORCE(char, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(const char*, true, false);
  FCF_CONVERTERS_REGISTRY_FORCE(char*, true, false);
  FCF_CONVERTERS_REGISTRY_FORCE(unsigned char, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(short, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(unsigned short, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(int, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(unsigned int, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(long long, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(unsigned long long, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(long int, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(unsigned long int, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(float, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(double, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(long double, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(std::string, true, true);
#endif


#endif // #ifndef ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__REGISTRY_HPP___
