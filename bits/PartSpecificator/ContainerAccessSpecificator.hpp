#ifndef ___FCF__BASIS__BITS__PART_SPECIFICATOR__CONTAINER_ACCESS_SPECIFICATOR_HPP___
#define ___FCF__BASIS__BITS__PART_SPECIFICATOR__CONTAINER_ACCESS_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "SpecificatorRegistrar.hpp"
#include "../PartType/Type.hpp"
#include "../../PartVariant.hpp"
#include "../PartContainerAccess/ContainerAccess.hpp"
#include "../PartContainerAccess/DynamicContainerAccess.hpp"

namespace fcf {

  struct ContainerAccessSpecificator {
    /*
      typedef DynamicContainerAccess< ContainerAccess<Ty> > (*CallType)(void* a_container);
      typedef DynamicContainerAccess< ContainerAccess<Ty> > (*HandleType)(void* a_container);
    */
  };

  template <typename Ty>
  struct Type<Ty, ContainerAccessSpecificator>;

  template <typename Ty>
  struct TypeImpl<Ty, ContainerAccessSpecificator> {
    typedef typename ContainerAccess<Ty>::key_type        KeyType;
    typedef typename ContainerAccess<Ty>::value_type      ValueType;
    typedef DynamicContainerAccess< ContainerAccess<Ty> > DynamicContainerAccessType;

    inline DynamicContainerAccessType operator()(Ty* a_container) {
      return !a_container ? DynamicContainerAccessType()
                          : DynamicContainerAccessType(*a_container);
    }

    inline DynamicContainerAccessType call(Ty* a_container) {
      return Type<Ty, ContainerAccessSpecificator>()(a_container);
    }

    inline Variant universalCall(Ty* a_object, Variant* /*a_argv*/, size_t /*a_argc*/) const {
      return Variant(Type<Ty, ContainerAccessSpecificator>().call(a_object));
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

  template <typename Ty>
  struct SpecificatorRegistrar<Ty, ContainerAccessSpecificator> {
    void operator()(const SpecificatorInfo& a_si){
      unsigned int specificatorIndex = Type<ContainerAccessSpecificator>().index();
      Type<Ty>()._info->specificators[specificatorIndex] = a_si;
      Type<Ty>()._info->containerAccessUniversalCall = a_si.universalCall;
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_SPECIFICATOR__CONTAINER_ACCESS_SPECIFICATOR_HPP___
