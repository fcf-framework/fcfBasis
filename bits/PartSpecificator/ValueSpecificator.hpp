#ifndef ___FCF__BASIS__BITS__PART_SPECIFICATOR__VALUE_SPECIFICATOR_HPP___
#define ___FCF__BASIS__BITS__PART_SPECIFICATOR__VALUE_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "SpecificatorRegistrarHandler.hpp"
#include "../PartType/Type.hpp"
#include "../../Variant.hpp"

namespace fcf {

  struct ValueSpecificator { 
  };

  template <typename Ty>
  struct Type<Ty, ValueSpecificator> {
    enum { enable = false };
  };


  template <typename Ty>
  struct TypeImpl<Ty, ValueSpecificator> {
    enum { enable = true };

    inline Variant universalCall(Ty* a_object, Variant* /*a_argv*/, size_t /*a_argc*/) const {
      return Type<Ty, ValueSpecificator>().call(a_object);
    }

    //
    // Example call mathod
    // 
    // inline auto call(Ty* a_container) -> decltype(a_container->value) const {
    //  return a_container->value;
    //}

  };


}

#endif // #ifndef ___FCF__BASIS__BITS__PART_SPECIFICATOR__VALUE_SPECIFICATOR_HPP___
