#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__RESOLVE_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__RESOLVE_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "SpecificatorRegistrar.hpp"
#include "../PartType/Type.hpp"
#include "../../Variant.hpp"
#include "ResolveSpecificatorDefinition.hpp"

namespace fcf{

  template <typename Ty>
  struct TypeImpl<Ty, ResolveSpecificator> {
    enum { enable = true };

    inline Variant universalCall(Ty* a_object, Variant* a_argv, size_t a_argc) const {
      return Variant(ResolveData(Type<Ty, ResolveSpecificator>().call(a_object)));
    }
  };

  template <typename TContainer>
  class SpecificatorRegistrar<TContainer, ResolveSpecificator> {
    public:
      SpecificatorRegistrar() {
        unsigned int specificatorIndex = Type<ResolveSpecificator>().index();
        fcf::SpecificatorTypeInfo sti;
        sti.resolve = (void*)universalCall;
        Type<TContainer>()._info->specificators[specificatorIndex] = sti;
        Type<TContainer>()._info->resolver = call;
      }

      static ResolveData call(void* a_container) {
        return Type<TContainer, ResolveSpecificator>().call((TContainer*)a_container);
      }

      static Variant universalCall(TContainer* a_container, Variant* a_argv, size_t a_argc) {
        return Type<TContainer, ResolveSpecificator>().universalCall(a_container, a_argv, a_argc);
      }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__RESOLVE_SPECIFICATOR_HPP___
