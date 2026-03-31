#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__FUNCTION_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__FUNCTION_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "SpecificatorRegistrar.hpp"
#include "../PartType/Type.hpp"
#include "../../Variant.hpp"
#include "../../bits/PartTypes/UniversalArguments.hpp"
#include "../../PartForeach.hpp"

namespace fcf{

  struct FunctionSpecificator { };

  template <typename Ty>
  struct Type<Ty, FunctionSpecificator> {
    enum { enable = false };
  };

  template <typename TResult, typename ... TArgPack>
  struct TypeImpl<TResult (TArgPack...), FunctionSpecificator> {
    enum { enable = true };

    typedef TResult(*type)(TArgPack...);
    typedef std::tuple<TArgPack...> arguments_type;
    typedef TResult                 result_type;

    inline Variant universalCall(type* a_object, Variant* /*a_argv*/, size_t /*a_argc*/) const {
      return Variant(Type<type>().call(a_object));
    }

    inline UniversalArguments call(type* /*a_container*/) const {
      UniversalArguments result(sizeof...(TArgPack) + 1);
      result[0] = Type<TResult>().index();

      std::tuple<TArgPack...> tuple;
      Filler filler = { result };
      fcf::foreach(tuple, filler);

      return result;
    }

    struct Filler{
      template <typename TTuple, typename Ty>
      inline void operator()(const TTuple&, size_t a_index, const Ty& /*a_item*/){
        ua[a_index + 1] = Type<Ty>().index();
      }
      UniversalArguments& ua;
    };
  };

  template <typename TClass, typename TResult, typename ... TArgPack>
  struct Type<TResult (TClass::*)(TArgPack...), FunctionSpecificator> : public TypeImpl<TResult(TArgPack...), FunctionSpecificator> {
    typedef TypeImpl<TResult(TArgPack...), FunctionSpecificator> base_type;
    typedef typename base_type::type type;
    typedef typename base_type::arguments_type arguments_type;
    typedef typename base_type::result_type result_type;
  };


  template <typename TResult, typename ... TArgPack>
  struct Type<TResult (TArgPack...), FunctionSpecificator> : public TypeImpl<TResult (TArgPack...), FunctionSpecificator> {
    typedef TypeImpl<TResult (TArgPack...), FunctionSpecificator> base_type;
    typedef typename base_type::type type;
    typedef typename base_type::arguments_type arguments_type;
    typedef typename base_type::result_type result_type;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__FUNCTION_SPECIFICATOR_HPP___
