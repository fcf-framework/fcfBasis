#ifndef ___FCF__BASIS__BITS__PART_SPECIFIER__CONTAINER_ACCESS_SPECIFIER_HPP___
#define ___FCF__BASIS__BITS__PART_SPECIFIER__CONTAINER_ACCESS_SPECIFIER_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "SpecifierRegistrar.hpp"
#include "../PartType/Type.hpp"
#include "../../PartVariant.hpp"
#include "../PartContainerAccess/ContainerAccess.hpp"
#include "../PartContainerAccess/DynamicContainerAccess.hpp"

namespace fcf {

  struct ContainerAccessSpecifier {
    /*
      typedef DynamicContainerAccess< ContainerAccess<Ty> > (*CallType)(void* a_container);
      typedef DynamicContainerAccess< ContainerAccess<Ty> > (*HandleType)(void* a_container);
    */
  };

  template <typename Ty>
  struct Type<Ty, ContainerAccessSpecifier>;

  template <typename Ty>
  struct TypeImpl<Ty, ContainerAccessSpecifier> {
    typedef typename ContainerAccess<Ty>::key_type        KeyType;
    typedef typename ContainerAccess<Ty>::value_type      ValueType;
    typedef DynamicContainerAccess< ContainerAccess<Ty> > DynamicContainerAccessType;

    inline DynamicContainerAccessType operator()(Ty* a_container) {
      return !a_container ? DynamicContainerAccessType()
                          : DynamicContainerAccessType(*a_container);
    }

    inline DynamicContainerAccessType call(Ty* a_container) {
      return Type<Ty, ContainerAccessSpecifier>()(a_container);
    }

    inline Variant universalCall(Ty* a_object, Variant* /*a_argv*/, size_t /*a_argc*/) const {
      return Variant(Type<Ty, ContainerAccessSpecifier>().call(a_object));
    }

  };

  template <typename Ty>
  struct SpecifierRegistrarGetter<const Ty, ContainerAccessSpecifier> {
    typedef DynamicContainerAccess< ContainerAccess<const Ty> > DynamicContainerAccessType;

    SpecifierInfo operator()(){
      fcf::SpecifierInfo sti;
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
  struct SpecifierRegistrar<Ty, ContainerAccessSpecifier> {
    void operator()(const SpecifierInfo& a_si){
      unsigned int specifierIndex = Type<ContainerAccessSpecifier>().index();
      Type<Ty>()._info->specifiers[specifierIndex] = a_si;
      Type<Ty>()._info->containerAccessUniversalCall = a_si.universalCall;
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_SPECIFIER__CONTAINER_ACCESS_SPECIFIER_HPP___
