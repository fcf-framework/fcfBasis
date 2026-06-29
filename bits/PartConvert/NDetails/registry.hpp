#ifndef _FCF_BASIS__BITS__PART_CONVERT__NDETAILS__REGISTRY_HPP___
#define _FCF_BASIS__BITS__PART_CONVERT__NDETAILS__REGISTRY_HPP___

#include "ConvertersRegistrar.hpp"

namespace fcf {
  struct  DefaultCrossConvert {
  };

  struct  IntPointerCrossConvert {
  };

  struct  BoolCrossConvert {
  };

} // fcf namespace

FCF_CONVERTERS_REGISTRATION(DefaultCrossConvert, char, true, true);
FCF_CONVERTERS_REGISTRATION(DefaultCrossConvert, const char*, true, false);
FCF_CONVERTERS_REGISTRATION(DefaultCrossConvert, char*, true, false);
FCF_CONVERTERS_REGISTRATION(DefaultCrossConvert, unsigned char, true, true);
FCF_CONVERTERS_REGISTRATION(DefaultCrossConvert, short, true, true);
FCF_CONVERTERS_REGISTRATION(DefaultCrossConvert, unsigned short, true, true);
FCF_CONVERTERS_REGISTRATION(DefaultCrossConvert, int, true, true);
FCF_CONVERTERS_REGISTRATION(DefaultCrossConvert, unsigned int, true, true);
FCF_CONVERTERS_REGISTRATION(DefaultCrossConvert, long long, true, true);
FCF_CONVERTERS_REGISTRATION(DefaultCrossConvert, unsigned long long, true, true);
FCF_CONVERTERS_REGISTRATION(DefaultCrossConvert, long int, true, true);
FCF_CONVERTERS_REGISTRATION(DefaultCrossConvert, unsigned long int, true, true);
FCF_CONVERTERS_REGISTRATION(DefaultCrossConvert, float, true, true);
FCF_CONVERTERS_REGISTRATION(DefaultCrossConvert, double, true, true);
FCF_CONVERTERS_REGISTRATION(DefaultCrossConvert, long double, true, true);
FCF_CONVERTERS_REGISTRATION(DefaultCrossConvert, std::string, true, true);
FCF_CONVERTERS_REGISTRATION(DefaultCrossConvert, fcf::Variant, true, true);

FCF_CONVERTERS_REGISTRATION(IntPointerCrossConvert, int*, true, true);
FCF_CONVERTERS_REGISTRATION(IntPointerCrossConvert, unsigned int*, true, true);

FCF_CONVERTERS_REGISTRATION(BoolCrossConvert, bool, true, true);
FCF_CONVERTERS_REGISTRATION(BoolCrossConvert, std::string, true, true);


#endif // #ifndef _FCF_BASIS__BITS__PART_CONVERT__NDETAILS__REGISTRY_HPP___
