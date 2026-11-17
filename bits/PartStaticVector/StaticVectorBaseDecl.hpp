#ifndef _FCF_BASIS__BITS__PART_STATIC_VECTOR__STATIC_VECTOR_BASE_DECL_HPP___
#define _FCF_BASIS__BITS__PART_STATIC_VECTOR__STATIC_VECTOR_BASE_DECL_HPP___

#include "../../macro.hpp"

namespace fcf{

  class FCF_BASIS_DECL_EXPORT StaticVectorBase {
    protected:
      struct FCF_BASIS_DECL_EXPORT PrebuildPowSizes {
        PrebuildPowSizes(unsigned int a_staticSize, unsigned int a_offsetSize, unsigned int a_stepSize, unsigned int a_stepModuleInt, unsigned int a_stepModuleFrac);

        bool isp(size_t a_size);

        bool is(size_t a_size);

        size_t get(size_t a_size);

        size_t getp(size_t a_size);

        size_t max;
        size_t values[10];
        unsigned int staticSize;
        unsigned int offsetSize; 
        unsigned int stepSize;
        unsigned int stepModuleInt;
        unsigned int stepModuleFrac;
        long double  stepMode;
      };

      static size_t _getPowSize(size_t a_size, size_t a_powInc, PrebuildPowSizes& a_pps);
  };

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_STATIC_VECTOR__STATIC_VECTOR_BASE_DECL_HPP___
