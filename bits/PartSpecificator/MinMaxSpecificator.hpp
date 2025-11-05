#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__MIN_MAX_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__MIN_MAX_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "SpecificatorRegistrar.hpp"
#include "../PartType/Type.hpp"
#include "../../Variant.hpp"
#include "../../bits/PartTypes/UniversalArguments.hpp"
#include "FunctionSpecificator.hpp"

namespace fcf{

  struct MinMaxSpecificator { };

  template <typename Ty>
  struct Type<Ty, MinMaxSpecificator> {
    enum { enable = false };
  };


  template <typename Ty>
  struct TypeImpl<Ty, MinMaxSpecificator> {
    enum { enable = true };

    inline Variant universalCall(Ty* a_object, Variant* a_argv, size_t a_argc) const {
      Variant result(UniversalArguments(2));

      typedef decltype(&Type<Ty, MinMaxSpecificator>::call) call_type;
      typedef typename Type<call_type, FunctionSpecificator>::arguments_type arguments_type;
      typedef typename std::remove_pointer< typename std::tuple_element<1, arguments_type>::type >::type arg1_type;
      typedef typename std::remove_pointer< typename std::tuple_element<2, arguments_type>::type >::type arg2_type;

      arg1_type arg1;
      arg2_type arg2;

      Type<Ty, MinMaxSpecificator>().call(a_object, &arg1, &arg2);

      result.as<UniversalArguments>()[0] = arg1;
      result.as<UniversalArguments>()[1] = arg2;

      return result;
    }
  };


} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__MIN_MAX_SPECIFICATOR_HPP___
