#ifndef _FCF_BASIS__BITS__PART_CONVERT__CONVERTER_LEVEL_HPP___
#define _FCF_BASIS__BITS__PART_CONVERT__CONVERTER_LEVEL_HPP___

namespace fcf{

  enum ConverterLevel {
    CL_ALL_LOW                = 0,
    CL_ALL                    = 1,
    CL_DIRECT_SOURCE_LOW      = 2,
    CL_DIRECT_SOURCE          = 3,
    CL_DIRECT_DESTINATION_LOW = 4,
    CL_DIRECT_DESTINATION     = 5,
    CL_DIRECT_LOW             = 6,
    CL_DIRECT                 = 7
  };

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_CONVERT__CONVERTER_LEVEL_HPP___
