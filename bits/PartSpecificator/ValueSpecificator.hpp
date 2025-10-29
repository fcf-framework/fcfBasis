#ifndef ___FCF__BASIS__BITS__PART_SPECIFICATOR__VALUE_SPECIFICATOR_HPP___
#define ___FCF__BASIS__BITS__PART_SPECIFICATOR__VALUE_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "SpecificatorRegistrar.hpp"
#include "../Type/Type.hpp"
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

    inline Variant universalCall(Ty* a_object, Variant* a_argv, size_t a_argc) const {
      return Type<Ty, ValueSpecificator>().call(a_object);
    }

    //
    // Example call mathod
    // 
    // inline auto call(Ty* a_container) -> decltype(a_container->value) const {
    //  return a_container->value;
    //}

  };

  template <typename TContainer>
  class SpecificatorRegistrar<TContainer, ValueSpecificator> {
    public:
      SpecificatorRegistrar() {
        unsigned int specificatorIndex = Type<ValueSpecificator>().index();
        fcf::SpecificatorTypeInfo sti;
        sti.argc = 1;
        sti.resolve = (void*)universalCall;
        Type<TContainer>()._info->specificators[specificatorIndex] = sti;
      }

      static Variant universalCall(TContainer* a_container) {
        return Type<TContainer, ValueSpecificator>().universalCall(a_container, 0, 0);
      }
  };

}

#endif // #ifndef ___FCF__BASIS__BITS__PART_SPECIFICATOR__VALUE_SPECIFICATOR_HPP___
