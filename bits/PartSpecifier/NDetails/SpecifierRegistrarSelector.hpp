#ifndef _FCF_BASIS__BITS__PART_SPECIFIER__NDETAILS__SPECIFIER_REGISTRAR_SELECTOR_HPP___
#define _FCF_BASIS__BITS__PART_SPECIFIER__NDETAILS__SPECIFIER_REGISTRAR_SELECTOR_HPP___

#include "../SpecifierInfo.hpp"
#include "../SpecifierRegistrar.hpp"

namespace fcf{
  namespace NDetails {

    template <typename Ty, typename TSpecifier, typename = void>
    struct SpecifierRegistrarSelector{
      void operator()(const SpecifierInfo& a_si){
        typedef typename std::remove_cv< typename std::remove_reference< typename std::remove_reference<Ty>::type >::type >::type type;
        SpecifierRegistrar<type, TSpecifier>()(a_si);
      }
    };

    template <typename Ty, typename TSpecifier>
    struct SpecifierRegistrarSelector<Ty, TSpecifier, decltype((void)SpecifierRegistrar<Ty, TSpecifier>())>{
      void operator()(const SpecifierInfo& a_si){
        SpecifierRegistrar<Ty, TSpecifier>()(a_si);
      }
    };

  }
} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_SPECIFIER__NDETAILS__SPECIFIER_REGISTRAR_SELECTOR_HPP___
