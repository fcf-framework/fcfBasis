#ifndef ___FCF__BASIS__BITS__PART_SPECIFICATOR__CONTAINER_ACCESS_SPECIFICATOR_HPP___
#define ___FCF__BASIS__BITS__PART_SPECIFICATOR__CONTAINER_ACCESS_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "SpecificatorRegistrar.hpp"
#include "../PartType/Type.hpp"
#include "../../PartVariant.hpp"
#include "../PartContainerAccess/ContainerAccess.hpp"
#include "../PartContainerAccess/DynamicContainerAccess.hpp"

namespace fcf {

  struct ContainerAccessSpecificator{
  };

  template <typename Ty>
  struct Type<Ty, ContainerAccessSpecificator>;

  template <typename Ty>
  struct TypeImpl<Ty, ContainerAccessSpecificator> {
    enum { enable = true };

    typedef typename ContainerAccess<Ty>::key_type        KeyType;
    typedef typename ContainerAccess<Ty>::value_type      ValueType;
    typedef DynamicContainerAccess< ContainerAccess<Ty> > DynamicContainerAccessType;

    inline Variant universalCall(Ty* a_object, Variant* /*a_argv*/, size_t /*a_argc*/) const {
      return Variant(Type<Ty, ContainerAccessSpecificator>().call(a_object));
    }

    inline DynamicContainerAccessType call(Ty* a_container) const {
      return !a_container ? DynamicContainerAccessType()
                          : DynamicContainerAccessType(*a_container);
    }

  };

  template <typename Ty>
  struct SpecificatorRegistrarGetter<const Ty, ContainerAccessSpecificator> {
    typedef DynamicContainerAccess< ContainerAccess<const Ty> > DynamicContainerAccessType;

    SpecificatorInfo operator()(){
      fcf::SpecificatorInfo sti;
      sti.universalCall = (UniversalCall)universalCall;
      sti.call          = (void*)call;
      return sti;
    }

    static DynamicContainerAccessType call(Ty* a_container) {
      return !a_container ? DynamicContainerAccessType()
                          : DynamicContainerAccessType(*a_container);
    }

    static Variant universalCall(Ty* a_container, Variant* /*a_argv*/, size_t /*a_argc*/) {
      return Variant(call(a_container));
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_SPECIFICATOR__CONTAINER_ACCESS_SPECIFICATOR_HPP___
