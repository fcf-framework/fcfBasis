#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_INFO_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_INFO_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"

namespace fcf{

  /**
   * @brief Structure containing information about a specificator operator.
   * 
   * This structure stores pointers to functions used to perform 
   * the specifier operations, supporting both 
   * specialized and generic calling mechanisms.
   */
  struct SpecificatorInfo {
    /**
     * @brief Pointer to a specialized function.
     * 
     * Used for direct, high-performance execution of part-specific logic.
     *
     * This field may be zero if the function specifier signature 
     * cannot be represented in a generic way 
     * (if it returns different data types depending on the type being processed).
     */
    void*         call;

    /**
     * @brief Universal call function wrapper.
     * 
     * Provides a standardized interface for invoking the operator 
     * through the framework's universal calling mechanism.
     */
    UniversalCall universalCall;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_INFO_HPP___
