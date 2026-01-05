#ifndef ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__REGISTRY_HPP___
#define ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__REGISTRY_HPP___

#include "ConvertersRegistrar.hpp"

namespace fcf {
  struct  DefaultCrossConvert {
  };

  struct  IntPointerCrossConvert {
  };
} // fcf namespace

#ifdef FCF_BASIS_IMPLEMENTATION
  FCF_CONVERTERS_REGISTRY_FORCE(DefaultCrossConvert, char, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(DefaultCrossConvert, const char*, true, false);
  FCF_CONVERTERS_REGISTRY_FORCE(DefaultCrossConvert, char*, true, false);
  FCF_CONVERTERS_REGISTRY_FORCE(DefaultCrossConvert, unsigned char, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(DefaultCrossConvert, short, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(DefaultCrossConvert, unsigned short, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(DefaultCrossConvert, int, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(DefaultCrossConvert, unsigned int, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(DefaultCrossConvert, long long, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(DefaultCrossConvert, unsigned long long, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(DefaultCrossConvert, long int, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(DefaultCrossConvert, unsigned long int, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(DefaultCrossConvert, float, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(DefaultCrossConvert, double, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(DefaultCrossConvert, long double, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(DefaultCrossConvert, std::string, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(DefaultCrossConvert, fcf::Variant, true, true);

  FCF_CONVERTERS_REGISTRY_FORCE(IntPointerCrossConvert, int*, true, true);
  FCF_CONVERTERS_REGISTRY_FORCE(IntPointerCrossConvert, unsigned int*, true, true);
#endif


#endif // #ifndef ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__REGISTRY_HPP___
