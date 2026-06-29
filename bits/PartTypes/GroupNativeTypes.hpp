#ifndef _FCF_BASIS__BITS__PART_TYPES__GROUP_NATIVE_TYPES_HPP___
#define _FCF_BASIS__BITS__PART_TYPES__GROUP_NATIVE_TYPES_HPP___

/**
 * @file GroupNativeTypes.hpp
 * @brief Defines native type aliases and their corresponding unique type indices for the fcf framework.
 */

namespace fcf{

  /**
   * @def FCF_INT8_TYPE_INDEX
   * @brief Unique index for the 8-bit signed integer type.
   */
  #ifndef FCF_INT8_TYPE_INDEX
    #define FCF_INT8_TYPE_INDEX 1
    /** @brief Alias for signed 8-bit integer (char). */
    typedef char Int8;
  #endif // #ifndef FCF_INT8_TYPE

  /**
   * @def FCF_UINT8_TYPE_INDEX
   * @brief Unique index for the 8-bit unsigned integer type.
   */
  #ifndef FCF_UINT8_TYPE_INDEX
    #define FCF_UINT8_TYPE_INDEX 2
    /** @brief Alias for unsigned 8-bit integer (unsigned char). */
    typedef unsigned char UInt8;
  #endif // #ifndef FCF_UINT8_TYPE

  /**
   * @def FCF_INT16_TYPE_INDEX
   * @brief Unique index for the 16-bit signed integer type.
   */
  #ifndef FCF_INT16_TYPE_INDEX
    #define FCF_INT16_TYPE_INDEX 3
    /** @brief Alias for signed 16-bit integer (short). */
    typedef short Int16;
  #endif // #ifndef FCF_INT16_TYPE

  /**
   * @def FCF_UINT16_TYPE_INDEX
   * @brief Unique index for the 16-bit unsigned integer type.
   */
  #ifndef FCF_UINT16_TYPE_INDEX
    #define FCF_UINT16_TYPE_INDEX 4
    /** @brief Alias for unsigned 16-bit integer (unsigned short). */
    typedef unsigned short UInt16;
  #endif // #ifndef FCF_UINT16_TYPE

  /**
   * @def FCF_INT32_TYPE_INDEX
   * @brief Unique index for the 32-bit signed integer type.
   */
  #ifndef FCF_INT32_TYPE_INDEX
    #define FCF_INT32_TYPE_INDEX 5
    /** @brief Alias for signed 32-bit integer (int). */
    typedef int Int32;
  #endif // #ifndef FCF_INT32_TYPE

  /**
   * @def FCF_UINT32_TYPE_INDEX
   * @brief Unique index for the 32-bit unsigned integer type.
   */
  #ifndef FCF_UINT32_TYPE_INDEX
    #define FCF_UINT32_TYPE_INDEX 6
    /** @brief Alias for unsigned 32-bit integer (unsigned int). */
    typedef unsigned int UInt32;
  #endif // #ifndef FCF_UINT32_TYPE

  /**
   * @def FCF_INT64_TYPE_INDEX
   * @brief Unique index for the 64-bit signed integer type.
   */
  #ifndef FCF_INT64_TYPE_INDEX
    #define FCF_INT64_TYPE_INDEX 7
    /** @brief Alias for signed 64-bit integer (long long). */
    typedef long long Int64;
  #endif // #ifndef FCF_INT64_TYPE

  /**
   * @def FCF_UINT64_TYPE_INDEX
   * @brief Unique index for the 64-bit unsigned integer type.
   */
  #ifndef FCF_UINT64_TYPE_INDEX
    #define FCF_UINT64_TYPE_INDEX 8
    /** @brief Alias for unsigned 64-bit integer (unsigned long long). */
    typedef unsigned long long UInt64;
  #endif // #ifndef FCF_UINT64_TYPE

  /**
   * @def FCF_FLOAT32_TYPE_INDEX
   * @brief Unique index for the 32-bit floating point type.
   */
  #ifndef FCF_FLOAT32_TYPE_INDEX
    #define FCF_FLOAT32_TYPE_INDEX 9
    /** @brief Alias for 32-bit float. */
    typedef float Float32;
  #endif // #ifndef FCF_FLOAT32_TYPE

  /**
   * @def FCF_FLOAT64_TYPE_INDEX
   * @brief Unique index for the 64-bit floating point type.
   */
  #ifndef FCF_FLOAT64_TYPE_INDEX
    #define FCF_FLOAT64_TYPE_INDEX 10
    /** @brief Alias for 64-bit double. */
    typedef double Float64;
  #endif // #ifndef FCF_FLOAT64_TYPE

  /**
   * @def FCF_FLOAT128_TYPE_INDEX
   * @brief Unique index for the 128-bit floating point type.
   */
  #ifndef FCF_FLOAT128_TYPE_INDEX
    #define FCF_FLOAT128_TYPE_INDEX 11
    /** @brief Alias for long double. */
    typedef long double Float128;
  #endif // #ifndef FCF_FLOAT128_TYPE

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_TYPES__GROUP_NATIVE_TYPES_HPP___
