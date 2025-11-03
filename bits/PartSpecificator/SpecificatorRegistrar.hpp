#ifndef ___FCF__BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_HPP___
#define ___FCF__BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_HPP___

#include "../PartVariant/VariantPredefinition.hpp"

namespace fcf{

  template <typename TContainer, typename TSpecificator>
  class SpecificatorRegistrar {
    public:
      SpecificatorRegistrar() {
        unsigned int specificatorIndex = Type<TSpecificator>().index();
        fcf::SpecificatorTypeInfo sti;
        sti.resolve = (void*)SpecificatorRegistrar::universalCall;
        Type<TContainer>()._info->specificators[specificatorIndex] = sti;
      }
    protected:
      static Variant universalCall(TContainer* a_container, Variant* a_argv, size_t a_argc);

  };

} // fcf namespace

#include "../../Variant.hpp"

namespace fcf {

  template <typename TContainer, typename TSpecificator>
  Variant SpecificatorRegistrar<TContainer, TSpecificator>::universalCall(TContainer* a_container, Variant* a_argv, size_t a_argc) {
    return ::fcf::Type<TContainer, TSpecificator>().universalCall(a_container, a_argv, a_argc);
  }


} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_HPP___
