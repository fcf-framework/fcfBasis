#ifndef _FCF_BASIS__BITS__PART_SPECIFIER__RESOLVE_SPECIFIER_HPP___
#define _FCF_BASIS__BITS__PART_SPECIFIER__RESOLVE_SPECIFIER_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "SpecifierRegistrar.hpp"
#include "../PartType/PartType.hpp"
#include "../../PartVariant.hpp"
#include "ResolveSpecifierDefinition.hpp"

namespace fcf{

  template <typename Ty>
  struct TypeImpl<Ty, ResolveSpecifier> {
    enum { invariantValue = true };

    inline ResolveData call(Ty* a_object) {
      ResolveData rd;
      rd.invariant = Type<Ty, ResolveSpecifier>::invariantValue;
      if (a_object) {
        Type<Ty, ResolveSpecifier>()(a_object, &rd.data, &rd.typeIndex);
      } else {
        rd.data = 0;
        rd.typeIndex = 0;
      }
      return rd;
    }

    inline Variant universalCall(Ty* a_object, Variant* /*a_argv*/, size_t /*a_argc*/) const {
      return Variant(ResolveData(Type<Ty, ResolveSpecifier>().call(a_object)));
    }
  };

  template <typename TContainer>
  struct SpecifierRegistrar<TContainer, ResolveSpecifier> {
    void operator()(const SpecifierInfo& a_si){
      TypeIndex specifierIndex = Type<ResolveSpecifier>().index();
      Type<TContainer>()._info->specifiers[specifierIndex] = a_si;
      Type<TContainer>()._info->resolveCall = (ResolveSpecifier::CallType)a_si.call;
    }
  };

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_SPECIFIER__RESOLVE_SPECIFIER_HPP___
