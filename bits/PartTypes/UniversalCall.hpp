#ifndef ___FCF_BASIS__BITS__PART_TYPES__UNIVERSAL_CALL_HPP___
#define ___FCF_BASIS__BITS__PART_TYPES__UNIVERSAL_CALL_HPP___

#include "../PartVariant/VariantPredefinition.hpp"

namespace fcf{

  /**
   * @typedef UniversalCall
   * @brief A standardized function pointer type for universal invocation.
   *
   * This type definition is used to provide a uniform interface for calling
   * various functions, specifiers, or operators within the framework,
   * regardless of their original signature.
   *
   * @param a_object A pointer to the object or container on which the operation is performed.
   * @param a_argv A pointer to an array of Variant objects representing the arguments.
   * @param a_argc The number of arguments provided in the a_argv array.
   * @return A Variant containing the result of the operation.
   *         If the operation returns multiple values, the returned Variant
   *         contains a UniversalPack object, which serves as a
   *         container for the multiple return elements.
   */
  typedef Variant (*UniversalCall)(void* a_object, Variant* a_argv, size_t a_argc);

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPES__UNIVERSAL_CALL_HPP___
