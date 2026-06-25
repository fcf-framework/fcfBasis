#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__MIN_MAX_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__MIN_MAX_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "SpecificatorRegistrar.hpp"
#include "../PartType/Type.hpp"
#include "../../PartVariant.hpp"
#include "../../bits/PartTypes/UniversalPack.hpp"
#include "FunctionSpecificator.hpp"

namespace fcf{

  struct MinMaxSpecificator { };

  template <typename Ty>
  struct TypeImpl<Ty, MinMaxSpecificator> {
    /*
     * Example of implementing operator() in a child class:
     *
     * inline std::pair<int, int> operator()(const Ty* a_object) {
     *   return std::pair<int, int>{a_object->min, a_object->max};
     * }
     */

    template <typename TArg>
    inline auto call(const TArg* a_object) -> decltype( Type<TArg, MinMaxSpecificator>()(a_object) ) {
      return Type<TArg, MinMaxSpecificator>()(a_object);
    }

    inline Variant universalCall(Ty* a_object, Variant* /*a_argv*/, size_t /*a_argc*/) {
      auto pair = Type<Ty, MinMaxSpecificator>()(a_object);
      Variant result(UniversalPack{pair.first, pair.second});
      return result;
    }
  };


} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__MIN_MAX_SPECIFICATOR_HPP___
