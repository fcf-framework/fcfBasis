#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__FUNCTION_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__FUNCTION_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "SpecificatorRegistrar.hpp"
#include "../PartType/Type.hpp"
#include "../../PartVariant.hpp"
#include "../../bits/PartTypes/UniversalPack.hpp"
#include "../../PartForeach.hpp"

namespace fcf{

  struct FunctionSpecificator { };

  template <typename Ty>
  struct Type<Ty, FunctionSpecificator> {
    typedef UniversalPack (*CallType)(void* a_container);
    typedef UniversalPack (*HandleType)(void* a_container);
  };

  template <typename TResult, typename ... TArgPack>
  struct TypeImpl<TResult (TArgPack...), FunctionSpecificator> {

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
      return Type<TResult (TArgPack...), FunctionSpecificator>()(a_container);
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
