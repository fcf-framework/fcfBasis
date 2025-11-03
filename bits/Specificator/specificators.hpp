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


 
  
  


} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__SPECIFICATOR__SPECIFICATORS_HPP___
