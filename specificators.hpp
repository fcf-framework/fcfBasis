#ifndef ___FCF_BASIS__SPECIFICATOR_HPP___
#define ___FCF_BASIS__SPECIFICATOR_HPP___

namespace fcf {

  #ifndef FCF_ITERATOR_SPECIFICATOR
    #define FCF_ITERATOR_SPECIFICATOR
    struct IteratorSpecificator{};
  #endif //#ifndef FCF_ITERATOR_SPECIFICATOR

  #ifndef FCF_ITERATOR_CONTAINER_SPECIFICATOR
    #define FCF_ITERATOR_CONTAINER_SPECIFICATOR
    struct IteratorContainerSpecificator{};
  #endif //#ifndef FCF_ITERATOR_CONTAINER_SPECIFICATOR

  #ifndef FCF_MIN_MAX_SPECIFICATOR
    #define FCF_MIN_MAX_SPECIFICATOR
    struct MinMaxSpecificator{};
  #endif //#ifndef FCF_MIN_MAX_SPECIFICATOR

  #ifndef FCF_VALUE_SPECIFICATOR
    #define FCF_VALUE_SPECIFICATOR
    struct ValueSpecificator{};
  #endif //#ifndef FCF_VALUE_SPECIFICATOR

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__SPECIFICATOR_HPP___
