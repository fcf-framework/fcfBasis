#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_REF_REGISTRAR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_REF_REGISTRAR_HPP___

#include "SpecificatorRefRegistrarDefinition.hpp"

namespace fcf{
  namespace NDetails {

    template <typename Ty, typename>
    struct SpecificatorRefRegistrarImpl {
      void operator()(fcf::SpecificatorInfo&, unsigned int){
      }
    };

    template <typename Ty>
    struct SpecificatorRefRegistrarImpl<Ty, decltype((void)TypeId<Ty>())> {
      void operator()(fcf::SpecificatorInfo& a_sti, unsigned int a_specificatorIndex){
        Type<Ty>()._info->specificators[a_specificatorIndex] = a_sti;
      }
    };

    template <typename Ty, bool Ignore>
    struct SpecificatorRefRegistrar {
      void operator()(fcf::SpecificatorInfo&, unsigned int){
      }
    };

    template <typename Ty>
    struct SpecificatorRefRegistrar<Ty, false> {
      void operator()(fcf::SpecificatorInfo& a_sti, unsigned int a_specificatorIndex){
        SpecificatorRefRegistrarImpl<Ty&>()(a_sti, a_specificatorIndex);
        SpecificatorRefRegistrarImpl<const Ty&>()(a_sti, a_specificatorIndex);
        SpecificatorRefRegistrarImpl<const Ty>()(a_sti, a_specificatorIndex);
      }
    };

    template <typename Ty>
    struct SpecificatorRefRegistrar<Ty, true> {
      void operator()(fcf::SpecificatorInfo&, unsigned int){
      }
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_REF_REGISTRAR_HPP___
