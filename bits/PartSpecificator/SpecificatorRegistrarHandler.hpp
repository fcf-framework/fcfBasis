#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_HANDLER_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_HANDLER_HPP___

#include "../PartVariant/VariantPredefinition.hpp"

namespace fcf{

  template <typename TContainer, typename TSpecificator>
  class SpecificatorRegistrarHandler {
    public:
      SpecificatorRegistrarHandler();
  };

} // fcf namespace


#include "NDetails/SpecificatorCallRegistrarGetter.hpp"
#include "SpecificatorInfo.hpp"
#include "SpecificatorRegistrar.hpp"
#include "SpecificatorRegistrarGetter.hpp"
#include "NDetails/SpecificatorRefRegistrar.hpp"
#include "../../PartVariant.hpp"

namespace fcf {

  template <typename TContainer, typename TSpecificator>
  SpecificatorRegistrarHandler<TContainer, TSpecificator>::SpecificatorRegistrarHandler() {
    fcf::SpecificatorInfo sti = SpecificatorRegistrarGetter<TContainer, TSpecificator>()();
    SpecificatorRegistrar<TContainer, TSpecificator>()(sti);
    NDetails::SpecificatorRefRegistrar<TContainer, TSpecificator, std::is_reference<TContainer>::value || std::is_const<TContainer>::value >()(sti);
  }

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_HANDLER_HPP___
