#ifndef ___FCF_BASIS__BITS__PART_SPECIFIER__NDETAILS__SPECIFIER_REF_REGISTRAR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFIER__NDETAILS__SPECIFIER_REF_REGISTRAR_HPP___

#include <tuple>
#include "SpecifierRefRegistrarDefinition.hpp"
#include "SpecifierCallRegistrarGetter.hpp"
#include "SpecifierRegistrarSelector.hpp"
#include "../SpecifierRegistrarGetter.hpp"

namespace fcf{

  template <typename TContainer, typename TSpecifier>
  class SpecifierRegistrarHandler;

  namespace NDetails {

    template <typename Ty, typename TSpecifier, typename>
    struct SpecifierRefRegistrarImpl {
      void operator()(fcf::SpecifierInfo&){
      }
    };

    template <typename Ty, typename TSpecifier>
    struct SpecifierRefRegistrarImpl<Ty, TSpecifier, decltype((void)TypeId<Ty>())> {
      void operator()(fcf::SpecifierInfo& a_sti){
        SpecifierRegistrarSelector<Ty, TSpecifier>()(a_sti);
      }
    };

    template <typename Ty, typename TSpecifier, typename = void>
    struct SpecifierRegistrarGetterResolverImpl {
      fcf::SpecifierInfo operator()(fcf::SpecifierInfo& a_sti){
        return a_sti;
      }
    };

    template <typename Ty, typename TSpecifier>
    struct SpecifierRegistrarGetterResolverImpl<Ty, TSpecifier, decltype((void)Type<Ty, TSpecifier>().universalCall(0, 0, 0))> {
      fcf::SpecifierInfo operator()(fcf::SpecifierInfo& /*a_sti*/){
        return fcf::SpecifierRegistrarGetter<Ty, TSpecifier>()();
      }
    };

    template <typename Ty, typename TSpecifier, typename = void>
    struct SpecifierRegistrarGetterIfDefaultGetterImpl {
      fcf::SpecifierInfo operator()(fcf::SpecifierInfo&){
        return fcf::SpecifierRegistrarGetter<Ty, TSpecifier>()();
      }
    };

    template <typename Ty, typename TSpecifier>
    struct SpecifierRegistrarGetterIfDefaultGetterImpl<Ty, TSpecifier, decltype((void)::fcf::SpecifierRegistrarGetter<Ty, TSpecifier>::defaultImplementationMarker)> {
      fcf::SpecifierInfo operator()(fcf::SpecifierInfo& a_sti){
        return SpecifierRegistrarGetterResolverImpl<Ty, TSpecifier>()(a_sti);
      }
    };


    template <typename RegTy, typename Ty, typename TSpecifier, typename>
    struct SpecifierRegistrarIfTypeDeclaredImpl {
      void operator()(fcf::SpecifierInfo&){
      }
    };

    template <typename RegTy, typename Ty, typename TSpecifier>
    struct SpecifierRegistrarIfTypeDeclaredImpl<RegTy, Ty, TSpecifier, decltype((void)TypeId<RegTy>())> {
      void operator()(fcf::SpecifierInfo& a_sti){
        SpecifierInfo sti = SpecifierRegistrarGetterIfDefaultGetterImpl<Ty, TSpecifier>()(a_sti);
        SpecifierRegistrarSelector<RegTy, TSpecifier>()(sti);
      }
    };

    template <typename Ty, typename TSpecifier, bool Ignore>
    struct SpecifierRefRegistrar {
      void operator()(fcf::SpecifierInfo&){
      }
    };

    template <typename Ty, typename TSpecifier>
    struct SpecifierRefRegistrar<Ty, TSpecifier, false> {
      void operator()(fcf::SpecifierInfo& a_sti){
        SpecifierRefRegistrarImpl<Ty&, TSpecifier>()(a_sti);
        SpecifierRegistrarIfTypeDeclaredImpl<const Ty&, const Ty, TSpecifier>()(a_sti);
        SpecifierRegistrarIfTypeDeclaredImpl<const Ty, const Ty, TSpecifier>()(a_sti);
      }
    };

    template <typename Ty, typename TSpecifier>
    struct SpecifierRefRegistrar<Ty, TSpecifier, true> {
      void operator()(fcf::SpecifierInfo&){
      }
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFIER__NDETAILS__SPECIFIER_REF_REGISTRAR_HPP___
