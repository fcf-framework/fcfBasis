#ifndef ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__SIGNATURE_HPP___
#define ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__SIGNATURE_HPP___

#include <tuple>
#include "ArgNumber.hpp"
#include "Arguments.hpp"
#include "../../FunctionSignature.hpp"
#include "RemovePlaceHolder.hpp"
#include "SignatureData.hpp"
#include "../../foreach.hpp"
#include "../../Type.hpp"

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
/*
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

*/


namespace fcf {
  namespace ArgPlaceHolder {

    template <typename TFullFunctionType, typename TResult, typename TSpecificator, unsigned int SpecificatorSourceArgIndex = 0, typename... TArgPack>
    struct Signature {
      enum { enable  = true };
      enum { ArgIndex = SpecificatorSourceArgIndex };
      typedef Signature<TFullFunctionType, TResult, TSpecificator, SpecificatorSourceArgIndex, TArgPack...> active_type;
      typedef TSpecificator                                                   specificator_type;
      typedef Arguments<TArgPack...>                                          arguments_type;
      typedef typename RemovePlaceHolder<TResult, TArgPack...>::function_type short_function_type;
      typedef FunctionSignature<short_function_type>                          short_function_signature_type;

      inline static SignatureData getSignatureData(){
        std::tuple<TArgPack...> tuple;
        SignatureData sd;
        sd.argSourceIndex = SpecificatorSourceArgIndex;
        sd.specificatorIndex = Type<TSpecificator>().index();
        SignatureDataFiller sdf = {sd};
        fcf::foreach(tuple, sdf);
        return sd;
      }

      struct SignatureDataFiller {
        template <typename TContainer, typename TIndex, typename TValue>
        void operator()(TContainer& a_container, TIndex a_index, TValue& a_value){
          if (!ArgNumber<TValue>::value){
            return;
          }
          ArgPlaceHolder::PlaceHolderArg pha;
          pha.argument = a_index;
          pha.placeHolderArgument = ArgNumber<TValue>::value;
          signatureData.placeHolders.push_back(pha);
        }
        SignatureData& signatureData;
      };

    };

    template <typename TFullFunctionType, typename TResult, typename... TArgPack>
    struct Signature<TFullFunctionType, TResult, Nop, 0, TArgPack...>{
      enum { enable  = false };
      enum { ArgIndex = 0 };
      typedef Nop active_type;
      typedef Nop                                     specificator_type;
      typedef Nop                                     arguments_type;
      typedef void(*short_function_type)();
      typedef FunctionSignature<short_function_type>  short_function_signature_type;

      inline static SignatureData getSignatureData(){
        std::tuple<TArgPack...> tuple;
        SignatureData sd;
        sd.argSourceIndex = 0;
        sd.specificatorIndex = 0;
        return sd;
      }

    };

    template <typename TResult, typename TSpecificator, typename... TArgPack>
    struct Signature<Nop, TResult, TSpecificator, 0, TArgPack...>{
      enum { enable  = false };
      enum { ArgIndex = 0 };
      typedef Nop active_type;
      typedef Nop                                     specificator_type;
      typedef Nop                                     arguments_type;
      typedef void(*short_function_type)();
      typedef FunctionSignature<short_function_type>  short_function_signature_type;

      inline static SignatureData getSignatureData(){
        std::tuple<TArgPack...> tuple;
        SignatureData sd;
        sd.argSourceIndex = 0;
        sd.specificatorIndex = 0;
        return sd;
      }
    };


  } // ArgPlaceHolder namespace
} // fcf namespace


#include "../Call/Details/CallPlaceHolderSignatures.hpp"

#endif // #ifndef ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__SIGNATURE_HPP___
