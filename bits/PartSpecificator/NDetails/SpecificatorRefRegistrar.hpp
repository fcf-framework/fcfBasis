#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_REF_REGISTRAR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_REF_REGISTRAR_HPP___

#include "SpecificatorRefRegistrarDefinition.hpp"

namespace fcf{
  namespace NDetails {

    template <typename Ty, bool IsRef, typename>
    struct SpecificatorRefRegistrar{
      void operator()(fcf::SpecificatorInfo&, unsigned int){
      }
    };

    template <typename Ty>
    struct SpecificatorRefRegistrar<Ty, false, decltype((void)TypeId<Ty&>())>{
      void operator()(fcf::SpecificatorInfo& a_sti, unsigned int a_specificatorIndex){
        typedef Ty& RefType;
        Type<RefType>()._info->specificators[a_specificatorIndex] = a_sti;
      }
    };

    template <typename Ty>
    struct SpecificatorRefRegistrar<Ty, true, decltype((void)TypeId<Ty&>())>{
      void operator()(fcf::SpecificatorInfo&, unsigned int){
      }
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_REF_REGISTRAR_HPP___
