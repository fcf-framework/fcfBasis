#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_REF_REGISTRAR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_REF_REGISTRAR_HPP___

#include <tuple>
#include "SpecificatorRefRegistrarDefinition.hpp"
#include "SpecificatorCallRegistrarGetter.hpp"
#include "SpecificatorRegistrarSelector.hpp"

namespace fcf{

  template <typename TContainer, typename TSpecificator>
  class SpecificatorRegistrarHandler;

  namespace NDetails {

    template <typename Ty, typename TSpecificator, typename>
    struct SpecificatorRefRegistrarImpl {
      void operator()(fcf::SpecificatorInfo&){
      }
    };

    template <typename Ty, typename TSpecificator>
    struct SpecificatorRefRegistrarImpl<Ty, TSpecificator, decltype((void)TypeId<Ty>())> {
      void operator()(fcf::SpecificatorInfo& a_sti){
        SpecificatorRegistrarSelector<Ty, TSpecificator>()(a_sti);
      }
    };

    template <typename Ty, typename TSpecificator, typename = void>
    struct SpecificatorConstRefRegistrarImplResolver {
      fcf::SpecificatorInfo operator()(fcf::SpecificatorInfo& a_sti){
        return a_sti;
      }
    };

    template <typename Ty, typename TSpecificator>
    struct SpecificatorConstRefRegistrarImplResolver<Ty, TSpecificator, decltype((void)Type<Ty, TSpecificator>().universalCall(0, 0, 0))> {
      fcf::SpecificatorInfo operator()(fcf::SpecificatorInfo& /*a_sti*/){
        fcf::SpecificatorInfo sti;
        sti.universalCall = (UniversalCall)SpecificatorRegistrarHandler<Ty, TSpecificator>::universalCall;
        sti.call = SpecificatorCallRegistrarGetter<Ty, TSpecificator>()();
        return sti;
      }
    };

    template <typename RegTy, typename Ty, typename TSpecificator, typename>
    struct SpecificatorConstRefRegistrarImpl {
      void operator()(fcf::SpecificatorInfo&){
      }
    };

    template <typename RegTy, typename Ty, typename TSpecificator>
    struct SpecificatorConstRefRegistrarImpl<RegTy, Ty, TSpecificator, decltype((void)TypeId<RegTy>())> {
      void operator()(fcf::SpecificatorInfo& a_sti){
        SpecificatorInfo sti = SpecificatorConstRefRegistrarImplResolver<Ty, TSpecificator>()(a_sti);
        SpecificatorRegistrarSelector<RegTy, TSpecificator>()(sti);
      }
    };

    template <typename Ty, typename TSpecificator, bool Ignore>
    struct SpecificatorRefRegistrar {
      void operator()(fcf::SpecificatorInfo&){
      }
    };

    template <typename Ty, typename TSpecificator>
    struct SpecificatorRefRegistrar<Ty, TSpecificator, false> {
      void operator()(fcf::SpecificatorInfo& a_sti){
        SpecificatorRefRegistrarImpl<Ty&, TSpecificator>()(a_sti);
        SpecificatorConstRefRegistrarImpl<const Ty&, const Ty, TSpecificator>()(a_sti);
        SpecificatorConstRefRegistrarImpl<const Ty, const Ty, TSpecificator>()(a_sti);
      }
    };

    template <typename Ty, typename TSpecificator>
    struct SpecificatorRefRegistrar<Ty, TSpecificator, true> {
      void operator()(fcf::SpecificatorInfo&){
      }
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_REF_REGISTRAR_HPP___
