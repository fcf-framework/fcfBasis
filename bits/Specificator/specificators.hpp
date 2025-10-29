#ifndef ___FCF__BASIS__BITS__SPECIFICATOR__SPECIFICATORS_HPP___
#define ___FCF__BASIS__BITS__SPECIFICATOR__SPECIFICATORS_HPP___

#include "DynamicIteratorInfoDecl.hpp"

namespace fcf {

  #ifndef FCF_ITERATOR_SPECIFICATOR
    #define FCF_ITERATOR_SPECIFICATOR
    struct IteratorSpecificator {  };
  #endif //#ifndef FCF_ITERATOR_SPECIFICATOR

  #ifndef FCF_ITERATOR_CONTAINER_SPECIFICATOR
    #define FCF_ITERATOR_CONTAINER_SPECIFICATOR
    struct IteratorContainerSpecificator { };
  #endif //#ifndef FCF_ITERATOR_CONTAINER_SPECIFICATOR

  #ifndef FCF_DEFAULT_CONVERT_SPECIFICATOR
    #define FCF_DEFAULT_CONVERT_SPECIFICATOR
    struct DefaultConvertSpecificator { };
  #endif //#ifndef FCF_DEFAULT_CONVERT_SPECIFICATOR


  #ifndef FCF_RAW_DATA_SPECIFICATOR
    #define FCF_RAW_DATA_SPECIFICATOR
    struct RawDataSpecificator { 
      typedef void* (*function_type)(const void* a_value /* = 0 */, unsigned int* a_type/* = 0 */, bool* a_invariantType/* = 0*/, bool* a_mayBeUnintialized/* = 0*/);
    };
  #endif //#ifndef FCF_RAW_DATA_SPECIFICATOR

 
  
  


} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__SPECIFICATOR__SPECIFICATORS_HPP___
