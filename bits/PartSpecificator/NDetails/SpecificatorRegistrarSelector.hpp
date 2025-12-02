#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_REGISTRAR_SELECTOR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_REGISTRAR_SELECTOR_HPP___

#include "../SpecificatorInfo.hpp"
#include "../SpecificatorRegistrar.hpp"

namespace fcf{
  namespace NDetails {

    template <typename Ty, typename TSpecificator, typename = void>
    struct SpecificatorRegistrarSelector{
      void operator()(const SpecificatorInfo& a_si){
        typedef typename std::remove_cv< typename std::remove_reference< typename std::remove_reference<Ty>::type >::type >::type type;
        SpecificatorRegistrar<type, TSpecificator>()(a_si);
      }
    };

    template <typename Ty, typename TSpecificator>
    struct SpecificatorRegistrarSelector<Ty, TSpecificator, decltype((void)SpecificatorRegistrar<Ty, TSpecificator>())>{
      void operator()(const SpecificatorInfo& a_si){
        SpecificatorRegistrar<Ty, TSpecificator>()(a_si);
      }
    };

  }
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_REGISTRAR_SELECTOR_HPP___
