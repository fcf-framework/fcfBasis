#ifndef ___FCF_BASIS__SPECIFICATOR_HPP___
#define ___FCF_BASIS__SPECIFICATOR_HPP___
#include "macro.hpp"
#include "bits/TypeInitializer.hpp"
#include "Details/Specificator/Registrator.hpp"

  #ifndef FCF_ITERATOR_SPECIFICATOR
    #define FCF_ITERATOR_SPECIFICATOR
    namespace fcf {
      struct IteratorSpecificator{  };
    } // fcf namespace
  #endif //#ifndef FCF_ITERATOR_SPECIFICATOR

  #ifndef FCF_ITERATOR_CONTAINER_SPECIFICATOR
    #define FCF_ITERATOR_CONTAINER_SPECIFICATOR
    namespace fcf {
      struct IteratorContainerSpecificator { };
    } // fcf namespace
  #endif //#ifndef FCF_ITERATOR_CONTAINER_SPECIFICATOR

  #ifndef FCF_MEMORY_TYPE_SPECIFICATOR
    #define FCF_MEMORY_TYPE_SPECIFICATOR
    namespace fcf {
      struct MemoryTypeSpecificator { };
    } // fcf namespace
  #endif //#ifndef FCF_MEMORY_TYPE_SPECIFICATOR

  #ifndef FCF_DEFAULT_CONVERT_SPECIFICATOR
    #define FCF_DEFAULT_CONVERT_SPECIFICATOR
    namespace fcf {
      struct DefaultConvertSpecificator { };
    } // fcf namespace
  #endif //#ifndef FCF_DEFAULT_CONVERT_SPECIFICATOR


  #ifndef FCF_RAW_DATA_SPECIFICATOR
    #define FCF_RAW_DATA_SPECIFICATOR
    namespace fcf {
      struct RawDataSpecificator { };
    } // fcf namespace
  #endif //#ifndef FCF_RAW_DATA_SPECIFICATOR

  #ifndef FCF_MIN_MAX_SPECIFICATOR
    #define FCF_MIN_MAX_SPECIFICATOR
    namespace fcf {
      struct MinMaxSpecificator { };
    } // fcf namespace
    FCF_TYPEID_REGISTRY(fcf::MinMaxSpecificator, "fcf::MinMaxSpecificator",        0);
  #endif //#ifndef FCF_MIN_MAX_SPECIFICATOR

  #ifndef FCF_VALUE_SPECIFICATOR
    #define FCF_VALUE_SPECIFICATOR
    namespace fcf {
      struct ValueSpecificator { };
    } // fcf namespace
    FCF_TYPEID_REGISTRY(fcf::ValueSpecificator, "fcf::ValueSpecificator",        0);
  #endif //#ifndef FCF_VALUE_SPECIFICATOR

#endif // #ifndef ___FCF_BASIS__SPECIFICATOR_HPP___
