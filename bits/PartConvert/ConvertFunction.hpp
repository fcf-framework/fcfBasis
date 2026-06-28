#ifndef ___FCF_BASIS__BITS__PART_CONVERT__CONVERT_FUNCTION_HPP___
#define ___FCF_BASIS__BITS__PART_CONVERT__CONVERT_FUNCTION_HPP___

#include "ConvertOptions.hpp"

namespace fcf {

  /**
   * @brief Function pointer type for performing type conversions.
   * 
   * This type defines the signature for functions responsible for converting 
   * data from a source type to a destination type at runtime.
   * 
   * @param a_destination Pointer to the destination memory where the converted value will be stored.
   * @param a_source Pointer to the source memory containing the original value.
   * @param a_option Pointer to optional configuration settings for the conversion process.
   */
  typedef void (*ConvertFunction)(void*, const void*, ConvertOptions* a_option);

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CONVERT__CONVERT_FUNCTION_HPP___
