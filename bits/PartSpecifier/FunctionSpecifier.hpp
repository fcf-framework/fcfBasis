#ifndef _FCF_BASIS__BITS__PART_SPECIFIER__FUNCTION_SPECIFIER_HPP___
#define _FCF_BASIS__BITS__PART_SPECIFIER__FUNCTION_SPECIFIER_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "SpecifierRegistrar.hpp"
#include "../PartType/Type.hpp"
#include "../../PartVariant.hpp"
#include "../../bits/PartTypes/UniversalPack.hpp"
#include "../../PartForeach.hpp"

namespace fcf{

  struct FunctionSpecifier { };

  template <typename Ty>
  struct Type<Ty, FunctionSpecifier> {
    typedef UniversalPack (*CallType)(void* a_container);
    typedef UniversalPack (*HandleType)(void* a_container);
  };

  template <typename TResult, typename ... TArgPack>
  struct TypeImpl<TResult (TArgPack...), FunctionSpecifier> {

    typedef TResult(*type)(TArgPack...);
    typedef std::tuple<TArgPack...> arguments_type;
    typedef TResult                 result_type;

    inline UniversalPack operator()(type* /*a_container*/) {
      UniversalPack result(sizeof...(TArgPack) + 1);
      result[0] = Type<TResult>().index();

      std::tuple<TArgPack...> tuple;
      Filler filler = { result };
      fcf::foreach(tuple, filler);

      return result;
    }

    inline UniversalPack call(type* a_container) {
      return Type<TResult (TArgPack...), FunctionSpecifier>()(a_container);
    }

    inline Variant universalCall(type* a_object, Variant* /*a_argv*/, size_t /*a_argc*/) const {
      return Variant(Type<type>().call(a_object));
    }

    struct Filler{
      template <typename TTuple, typename Ty>
      inline void operator()(const TTuple&, size_t a_index, const Ty& /*a_item*/){
        ua[a_index + 1] = Type<Ty>().index();
      }
      UniversalPack& ua;
    };
  };

  template <typename TClass, typename TResult, typename ... TArgPack>
  struct Type<TResult (TClass::*)(TArgPack...), FunctionSpecifier> : public TypeImpl<TResult(TArgPack...), FunctionSpecifier> {
    typedef TypeImpl<TResult(TArgPack...), FunctionSpecifier> base_type;
    typedef typename base_type::type type;
    typedef typename base_type::arguments_type arguments_type;
    typedef typename base_type::result_type result_type;
  };


  template <typename TResult, typename ... TArgPack>
  struct Type<TResult (TArgPack...), FunctionSpecifier> : public TypeImpl<TResult (TArgPack...), FunctionSpecifier> {
    typedef TypeImpl<TResult (TArgPack...), FunctionSpecifier> base_type;
    typedef typename base_type::type type;
    typedef typename base_type::arguments_type arguments_type;
    typedef typename base_type::result_type result_type;
  };

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_SPECIFIER__FUNCTION_SPECIFIER_HPP___
