#ifndef _FCF_BASIS__BITS__PART_STATIC_VECTOR__STATIC_VECTOR_BASE_IPP___
#define _FCF_BASIS__BITS__PART_STATIC_VECTOR__STATIC_VECTOR_BASE_IPP___

#include <cmath>
#include "StaticVectorBaseDecl.hpp"

namespace fcf{

  #ifdef FCF_BASIS_IMPLEMENTATION
  StaticVectorBase::PrebuildPowSizes::PrebuildPowSizes(unsigned int a_staticSize, unsigned int a_offsetSize, unsigned int a_stepSize, unsigned int a_stepModuleInt, unsigned int a_stepModuleFrac)
      : staticSize(a_staticSize) 
      , offsetSize(a_offsetSize)
      , stepSize(a_stepSize)
      , stepModuleInt(a_stepModuleInt)
      , stepModuleFrac(a_stepModuleFrac)
    {
      double pow = std::pow((double)stepModuleFrac, -std::ceil(std::log10((double)a_stepModuleFrac)));
      stepMode = (double)stepModuleInt + (double)stepModuleFrac * pow;

      size_t lastValue = staticSize + 1;
      size_t m = 0;
      for(size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i){
        m = _getPowSize(lastValue, 1, *this);
        values[i] = m;
        lastValue = m + 1;
      }
      max = m;
    }
  #endif

  #ifdef FCF_BASIS_IMPLEMENTATION
    bool StaticVectorBase::PrebuildPowSizes::isp(size_t a_size){
      return max >= a_size;
    }
  #endif

  #ifdef FCF_BASIS_IMPLEMENTATION
    bool StaticVectorBase::PrebuildPowSizes::is(size_t a_size){
      return max >= a_size;
    }
  #endif

  #ifdef FCF_BASIS_IMPLEMENTATION
    size_t StaticVectorBase::PrebuildPowSizes::get(size_t a_size) {
      for(size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i){
        if (values[i] >= a_size) {
          return values[i];
        }
      }
      return _getPowSize(a_size, 1, *this);
    }
  #endif

  #ifdef FCF_BASIS_IMPLEMENTATION
    size_t StaticVectorBase::PrebuildPowSizes::getp(size_t a_size) {
      size_t last = staticSize;
      for(size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i){
        if (values[i] >= a_size) {
          return last;
        }
        last = values[i];
      }
      return _getPowSize(a_size, 0, *this);
    }
  #endif



  #ifdef FCF_BASIS_IMPLEMENTATION
  size_t StaticVectorBase::_getPowSize(size_t a_size, size_t a_powInc, PrebuildPowSizes& a_pps) {
    if (a_pps.stepModuleInt == 1 && a_pps.stepModuleFrac == 0) {
      if (a_size >= a_pps.offsetSize){
        a_size -= a_pps.offsetSize;
      }
      size_t step = a_size / a_pps.stepSize;
      if (a_size % a_pps.stepSize){
        ++step;
      }
      if (step && a_powInc == 0){
        step -= 1;
      }
      return step * a_pps.stepSize + a_pps.offsetSize;
    } else {
      if (a_powInc) {
        if (a_pps.is(a_size)) {
          return a_pps.get(a_size);
        }
      } else  {
        if (a_pps.isp(a_size)) {
          return a_pps.getp(a_size);
        }
      }
      if (a_size >= a_pps.offsetSize){
        a_size -= a_pps.offsetSize;
      }
      long double val = ( (long double)a_size * a_pps.stepMode + (long double)a_pps.stepSize - (long double)a_size ) / (long double)a_pps.stepSize;
      long double log = std::log(val) / std::log(a_pps.stepMode);
      long double pow = std::ceil(log - 1);
      long double powStepMode = std::pow(a_pps.stepMode, pow + a_powInc);
      long double bufferSize = (long double)(a_pps.stepSize * (powStepMode - 1) ) / (long double)(a_pps.stepMode - 1);
      return (size_t)bufferSize + a_pps.offsetSize;
    }
  }
  #endif


} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_STATIC_VECTOR__STATIC_VECTOR_BASE_IPP___
