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

    inline Variant universalCall(Ty* a_object, Variant* /*a_argv*/, size_t /*a_argc*/) const {
      return Variant(ResolveData(Type<Ty, ResolveSpecificator>().call(a_object)));
    }
  };

  template <typename TContainer>
  struct SpecificatorRegistrar<TContainer, ResolveSpecificator> {
    void operator()(const SpecificatorInfo& a_si){
      unsigned int specificatorIndex = Type<ResolveSpecificator>().index();
      Type<TContainer>()._info->specificators[specificatorIndex] = a_si;
      Type<TContainer>()._info->resolver = (ResolveSpecificator::CallType)a_si.call;
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__RESOLVE_SPECIFICATOR_HPP___
