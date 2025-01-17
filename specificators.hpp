#ifndef ___FCF_BASIS__SPECIFICATOR_HPP___
#define ___FCF_BASIS__SPECIFICATOR_HPP___

namespace fcf {

  #ifndef FCF_ITERATIVE_SPECIFICATOR
    #define FCF_ITERATIVE_SPECIFICATOR
    struct IterativeSpecificator{};
  #endif //#ifndef FCF_MIN_MAX_SPECIFICATOR

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
