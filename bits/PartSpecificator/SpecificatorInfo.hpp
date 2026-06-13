#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_INFO_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_INFO_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"

namespace fcf{

  /**
   * @brief Structure containing information about a specific part's operator.
   * 
   * This structure stores pointers to functions used for executing 
   * operations specific to a particular part, supporting both 
   * specialized and universal calling mechanisms.
   */
  struct SpecificatorInfo {
    /**
     * @brief Pointer to a specialized function.
     * 
     * Used for direct, high-performance execution of part-specific logic.
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