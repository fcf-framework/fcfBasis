#ifndef ___FCF_BASIS__DETAILS__RANDEM_GENERATOR_HPP___
#define ___FCF_BASIS__DETAILS__RANDEM_GENERATOR_HPP___

#include <chrono>
#include <random>

#include "../macro.hpp"

namespace fcf {
  namespace Details {

    FCF_BASIS_DELC_EXTERN FCF_BASIS_DECL_EXPORT std::mt19937* g_randomGenerator;

    FCF_BASIS_DECL_EXPORT std::mt19937& getRandomGenerator();

    #ifdef FCF_BASIS_IMPLEMENTATION
      #pragma message("11")
      std::mt19937& getRandomGenerator(){
        if(!g_randomGenerator){
          (std::mt19937::result_type) rp =
            (std::mt19937::result_type)std::chrono::duration_cast<std::chrono::seconds>(
                                         std::chrono::system_clock::now().time_since_epoch()
                                       ).count()
            +
            (std::mt19937::result_type)std::chrono::duration_cast<std::chrono::microseconds>(
                                         std::chrono::high_resolution_clock::now().time_since_epoch()
                                       ).count();
          g_randomGenerator = new std::mt19937(rp);
        }
        return *g_randomGenerator;
      }
    #endif // #ifdef FCF_BASIS_IMPLEMENTATION

  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__RANDEM_GENERATOR_HPP___
