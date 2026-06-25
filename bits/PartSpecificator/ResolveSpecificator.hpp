#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__RESOLVE_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__RESOLVE_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "SpecificatorRegistrar.hpp"
#include "../PartType/PartType.hpp"
#include "../../PartVariant.hpp"
#include "ResolveSpecificatorDefinition.hpp"

namespace fcf{

  template <typename Ty>
  struct TypeImpl<Ty, ResolveSpecificator> {
    enum { invariantValue = true };

    inline ResolveData call(Ty* a_object) {
      ResolveData rd;
      rd.invariant = Type<Ty, ResolveSpecificator>::invariantValue;
      if (a_object) {
        Type<Ty, ResolveSpecificator>()(a_object, &rd.data, &rd.typeIndex);
      } else {
        rd.data = 0;
        rd.typeIndex = 0;
      }
      return rd;
    }

    inline Variant universalCall(Ty* a_object, Variant* /*a_argv*/, size_t /*a_argc*/) const {
      return Variant(ResolveData(Type<Ty, ResolveSpecificator>().call(a_object)));
    }
  };

  template <typename TContainer>
  struct SpecificatorRegistrar<TContainer, ResolveSpecificator> {
    void operator()(const SpecificatorInfo& a_si){
      unsigned int specificatorIndex = Type<ResolveSpecificator>().index();
      Type<TContainer>()._info->specificators[specificatorIndex] = a_si;
      Type<TContainer>()._info->resolveCall = (ResolveSpecificator::CallType)a_si.call;
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__RESOLVE_SPECIFICATOR_HPP___
