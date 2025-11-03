#ifndef ___FCF__BASIS__BITS__CALL__PART_PLACE_HOLDER__DETAILS__CALL_PLACE_HOLDER_SIGNATURE_GETTER_HPP___
#define ___FCF__BASIS__BITS__CALL__PART_PLACE_HOLDER__DETAILS__CALL_PLACE_HOLDER_SIGNATURE_GETTER_HPP___

#include <tuple>
#include "../../foreach.hpp"
#include "../../Type.hpp"

#include "../../ArgNumber.hpp"
#include "../../../../FunctionSignature.hpp"
#include "CallPlaceHolderRemover.hpp"
#include "../CallPlaceHolderInfo.hpp"

#include "../../../PartType/getTypeInfo.hpp"

namespace fcf {
  namespace Details {

    template <typename TFullFunctionType, typename TResult, typename TSpecificator, unsigned int SpecificatorSourceArgIndex = 0, typename... TArgPack>
    struct CallPlaceHolderSignatureGetter {
      enum { enable  = true };
      enum { ArgIndex = SpecificatorSourceArgIndex };
      typedef CallPlaceHolderSignatureGetter<TFullFunctionType, TResult, TSpecificator, SpecificatorSourceArgIndex, TArgPack...> active_type;
      typedef TSpecificator                                                   specificator_type;
      typedef typename CallPlaceHolderRemover<TResult, TArgPack...>::function_type short_function_type;
      typedef ::fcf::FunctionSignature<short_function_type>                   short_function_signature_type;

      inline static CallPlaceHolderInfo getPlaceHolderInfo(){
        std::tuple<TArgPack...> tuple;
        CallPlaceHolderInfo cphi;
        cphi.argSourceIndex = SpecificatorSourceArgIndex;
        cphi.specificatorIndex = Type<TSpecificator>().index();
        SignatureDataFiller sdf = {cphi};
        fcf::foreach(tuple, sdf);
        return cphi;
      }

      struct SignatureDataFiller {
        template <typename TContainer, typename TIndex, typename TValue>
        void operator()(TContainer& a_container, TIndex a_index, TValue& a_value){
          if (!ArgNumber<TValue>::value){
            return;
          }
          CallPlaceHolderArg pha;
          pha.argument = a_index;
          pha.placeHolderArgument = ArgNumber<TValue>::value;
          placeHolderInfo.placeHolders.push_back(pha);
        }
        CallPlaceHolderInfo& placeHolderInfo;
      };

    };

    template <typename TFullFunctionType, typename TResult, typename... TArgPack>
    struct CallPlaceHolderSignatureGetter<TFullFunctionType, TResult, Nop, 0, TArgPack...>{
      enum { enable  = false };
      enum { ArgIndex = 0 };
      typedef Nop active_type;
      typedef Nop                                     specificator_type;
      typedef void(*short_function_type)();
      typedef ::fcf::FunctionSignature<short_function_type>  short_function_signature_type;

      inline static CallPlaceHolderInfo getPlaceHolderInfo(){
        std::tuple<TArgPack...> tuple;
        CallPlaceHolderInfo cphi;
        cphi.argSourceIndex = 0;
        cphi.specificatorIndex = 0;
        return cphi;
      }

    };

    template <typename TResult, typename TSpecificator, typename... TArgPack>
    struct CallPlaceHolderSignatureGetter<Nop, TResult, TSpecificator, 0, TArgPack...>{
      enum { enable  = false };
      enum { ArgIndex = 0 };
      typedef Nop active_type;
      typedef Nop                                     specificator_type;
      typedef void(*short_function_type)();
      typedef ::fcf::FunctionSignature<short_function_type>  short_function_signature_type;

      inline static CallPlaceHolderInfo getPlaceHolderInfo(){
        std::tuple<TArgPack...> tuple;
        CallPlaceHolderInfo cphi;
        cphi.argSourceIndex = 0;
        cphi.specificatorIndex = 0;
        return cphi;
      }
    };


  } // Details namespace
} // fcf namespace


#include "../../Details/CallPlaceHolderSignatures.hpp"

#endif // #ifndef ___FCF__BASIS__BITS__CALL__PART_PLACE_HOLDER__DETAILS__CALL_PLACE_HOLDER_SIGNATURE_GETTER_HPP___
