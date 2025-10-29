#ifndef ___FCF__BASIS__BITS__PART_SPECIFICATOR__CONTAINER_ACCESS_SPECIFICATOR_HPP___
#define ___FCF__BASIS__BITS__PART_SPECIFICATOR__CONTAINER_ACCESS_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "SpecificatorRegistrar.hpp"
#include "../Type/Type.hpp"
#include "../../Variant.hpp"
#include "../PartContainerAccess/ContainerAccess.hpp"
#include "../PartContainerAccess/DynamicContainerAccess.hpp"

namespace fcf {

  struct ContainerAccessSpecificator{
  };

  template <typename Ty>
  struct Type<Ty, ContainerAccessSpecificator> {
    enum { enable = false };
  };

  template <typename Ty>
  struct TypeImpl<Ty, ContainerAccessSpecificator> {
    enum { enable = true };

    typedef DynamicContainerAccess< ContainerAccess<Ty> > ContainerAccessType;

    inline Variant universalCall(Ty* a_object, Variant* a_argv, size_t a_argc) const {
      return Variant(Type<Ty, ContainerAccessType>().call(a_object));
    }

    inline ContainerAccessType call(Ty* a_container) const {
      return !a_container ? ContainerAccessType()
                          : ContainerAccessType(*a_container);
    }

  };

  template <typename TContainer>
  class SpecificatorRegistrar<TContainer, ContainerAccessSpecificator> {
    public:
      SpecificatorRegistrar() {
        unsigned int specificatorIndex = Type<ContainerAccessSpecificator>().index();
        fcf::SpecificatorTypeInfo sti;
        sti.argc = 1;
        sti.resolve = (void*)universalCall;
        Type<TContainer>()._info->specificators[specificatorIndex] = sti;
      }

      static Variant universalCall(TContainer* a_container) {
        return Type<TContainer, ContainerAccessSpecificator>().call(a_container);
      }
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_SPECIFICATOR__CONTAINER_ACCESS_SPECIFICATOR_HPP___
