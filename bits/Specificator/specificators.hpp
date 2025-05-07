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

  #ifndef FCF_MEMORY_TYPE_SPECIFICATOR
    #define FCF_MEMORY_TYPE_SPECIFICATOR
    struct MemoryTypeSpecificator { };
  #endif //#ifndef FCF_MEMORY_TYPE_SPECIFICATOR

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

  #ifndef FCF_MIN_MAX_SPECIFICATOR
    #define FCF_MIN_MAX_SPECIFICATOR
    struct MinMaxSpecificator { };
  #endif //#ifndef FCF_MIN_MAX_SPECIFICATOR

  #ifndef FCF_VALUE_SPECIFICATOR
    #define FCF_VALUE_SPECIFICATOR
    struct ValueSpecificator { };
  #endif //#ifndef FCF_VALUE_SPECIFICATOR

  #ifndef FCF_DYNAMIC_ITERATOR_SPECIFICATOR
    #define FCF_DYNAMIC_ITERATOR_SPECIFICATOR

    struct DynamicIteratorSpecificator {
      enum { enable = false };
      typedef bool (*function_type)(void* a_container, DynamicIteratorInfo* a_info);
    };

  #endif //#ifndef FCF_DYNAMIC_ITERATOR_SPECIFICATOR
  
  
  


} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__SPECIFICATOR__SPECIFICATORS_HPP___
