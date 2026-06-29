#ifndef _FCF_BASIS__BITS__PART_SPECIFIER__SPECIFIER_REGISTRAR_HANDLER_HPP___
#define _FCF_BASIS__BITS__PART_SPECIFIER__SPECIFIER_REGISTRAR_HANDLER_HPP___

#include "../PartVariant/VariantPredefinition.hpp"

namespace fcf{

  template <typename TContainer, typename TSpecifier>
  class SpecifierRegistrarHandler {
    public:
      SpecifierRegistrarHandler();
  };

} // fcf namespace


#include "NDetails/SpecifierCallRegistrarGetter.hpp"
#include "SpecifierInfo.hpp"
#include "SpecifierRegistrar.hpp"
#include "SpecifierRegistrarGetter.hpp"
#include "NDetails/SpecifierRefRegistrar.hpp"
#include "../../PartVariant.hpp"

namespace fcf {

  template <typename TContainer, typename TSpecifier>
  SpecifierRegistrarHandler<TContainer, TSpecifier>::SpecifierRegistrarHandler() {
    fcf::SpecifierInfo sti = SpecifierRegistrarGetter<TContainer, TSpecifier>()();
    SpecifierRegistrar<TContainer, TSpecifier>()(sti);
    NDetails::SpecifierRefRegistrar<TContainer, TSpecifier, std::is_reference<TContainer>::value || std::is_const<TContainer>::value >()(sti);
  }

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_SPECIFIER__SPECIFIER_REGISTRAR_HANDLER_HPP___
