#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_HANDLER_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_HANDLER_HPP___

#include "../PartVariant/VariantPredefinition.hpp"

namespace fcf{

  template <typename TContainer, typename TSpecificator>
  class SpecificatorRegistrarHandler {
    public:
      SpecificatorRegistrarHandler();
      static Variant universalCall(TContainer* a_container, Variant* a_argv, size_t a_argc);
  };

} // fcf namespace


#include "NDetails/SpecificatorCallRegistrarGetter.hpp"
#include "SpecificatorInfo.hpp"
#include "SpecificatorRegistrar.hpp"
#include "NDetails/SpecificatorRefRegistrar.hpp"
#include "../../Variant.hpp"

namespace fcf {

  template <typename TContainer, typename TSpecificator>
  SpecificatorRegistrarHandler<TContainer, TSpecificator>::SpecificatorRegistrarHandler() {
    fcf::SpecificatorInfo sti;
    sti.universalCall = (UniversalCall)SpecificatorRegistrarHandler::universalCall;
    sti.call          = NDetails::SpecificatorCallRegistrarGetter<TContainer, TSpecificator>()();
    SpecificatorRegistrar<TContainer, TSpecificator>()(sti);
    NDetails::SpecificatorRefRegistrar<TContainer, TSpecificator, std::is_reference<TContainer>::value || std::is_const<TContainer>::value >()(sti);
  }

  template <typename TContainer, typename TSpecificator>
  Variant SpecificatorRegistrarHandler<TContainer, TSpecificator>::universalCall(TContainer* a_container, Variant* a_argv, size_t a_argc) {
    return ::fcf::Type<TContainer, TSpecificator>().universalCall(a_container, a_argv, a_argc);
  }


} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_HANDLER_HPP___
