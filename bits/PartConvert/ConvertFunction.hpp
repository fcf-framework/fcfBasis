#ifndef ___FCF_BASIS__BITS__PART_CONVERT__CONVERT_FUNCTION_HPP___
#define ___FCF_BASIS__BITS__PART_CONVERT__CONVERT_FUNCTION_HPP___

#include "ConvertOptions.hpp"

namespace fcf {

  typedef void (*ConvertFunction)(void*, const void*, ConvertOptions* a_option);

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CONVERT__CONVERT_FUNCTION_HPP___
