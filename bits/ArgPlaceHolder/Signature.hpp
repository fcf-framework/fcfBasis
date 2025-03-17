#ifndef ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__SIGNATURE_HPP___
#define ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__SIGNATURE_HPP___

#include "Arguments.hpp"
#include "../../FunctionSignature.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {

        template <typename TResult = Nop>
        struct FunctionResultType {
          typedef TResult type;
        };

        template <typename TResult, typename... TPack>
        struct FunctionResultType<TResult (TPack...)> {
          typedef TResult type;
        };

        template <typename TResult, typename... TPack>
        struct FunctionResultType<TResult (*)(TPack...)> {
          typedef TResult type;
        };

    }
  }
}
namespace fcf {
  namespace ArgPlaceHolder {
    
    
    

    template <typename TSpecificator = Nop, typename TFullFunctionType = Nop, typename TResult = Nop, typename... TArgPack>
    struct Signature {
      enum { enable  = false };
      typedef Nop                                     specificator_type;
      typedef Nop                                     arguments_type;
      typedef void(*short_function_type)();
      typedef FunctionSignature<short_function_type>  short_function_signature_type;
      typedef Caller<
                    ::fcf::ArgPlaceHolder::Arguments<void()>,
                    void ()
                    > caller_type;
      typedef typename caller_type::caller_type caller_function_type;
    };

    template <typename TSpecificator, typename TFullFunctionType, typename TResult, typename... TArgPack>
    struct Signature<TFullFunctionType, TResult (TSpecificator, TArgPack...)> {
      enum { enable  = true };
      typedef TSpecificator                                                   specificator_type;
      typedef Arguments<TArgPack...>                                          arguments_type;
      typedef typename RemovePlaceHolder<TResult, TArgPack...>::function_type short_function_type;
      typedef FunctionSignature<short_function_type>                          short_function_signature_type;
      typedef Caller<
                    ::fcf::ArgPlaceHolder::Arguments<TResult(TArgPack...)>,
                    TFullFunctionType
                    > caller_type;
      typedef typename caller_type::caller_type caller_function_type;
    };

    template <typename TSpecificator, typename TFullFunctionType, typename TResult, typename... TArgPack>
    struct Signature<TFullFunctionType, TResult (*)(TSpecificator, TArgPack...)> {
      enum { enable  = true };
      typedef TSpecificator                                                   specificator_type;
      typedef Arguments<TArgPack...>                                          arguments_type;
      typedef typename RemovePlaceHolder<TResult, TArgPack...>::function_type short_function_type;
      typedef FunctionSignature<short_function_type>                          short_function_signature_type;
      typedef Caller<
                    ::fcf::ArgPlaceHolder::Arguments<TResult(TArgPack...)>,
                    TFullFunctionType
                    > caller_type;
      typedef typename caller_type::caller_type caller_function_type;
    };

  } // ArgPlaceHolder namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__SIGNATURE_HPP___
