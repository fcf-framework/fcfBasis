#ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_DETAILS_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__CALL_DETAILS_HPP___

#include <tuple>
#include "../../PartForeach.hpp"
#include "../../PartType.hpp"
#include "ArgNumber.hpp"
#include "FunctionSignature.hpp"
#include "../../bits/PartType/getTypeInfo.hpp"
#include "../../bits/PartCallPlaceHolder/NDetails/CallPlaceHolderRemover.hpp"
#include "../../bits/PartCallPlaceHolder/CallPlaceHolderInfo.hpp"

namespace fcf{

    template <typename TSpecificator, unsigned int SpecificatorSourceArgIndex = 0, typename... TArgPack>
    struct CallDetails {
      enum { enable  = true };
      enum { ArgIndex = SpecificatorSourceArgIndex };
      typedef CallDetails<TSpecificator, SpecificatorSourceArgIndex, TArgPack...> active_type;
      typedef TSpecificator                                                           specificator_type;
      typedef typename NDetails::CallPlaceHolderRemover<void, TArgPack...>::function_type       _short_function_type;
      typedef typename ::fcf::FunctionSignature<_short_function_type>::args_type      ShortTupleArgumentsType;

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
        template <typename TIndex, typename TValue>
        void operator()(TIndex a_index, TValue& /*a_value*/){
          if (ArgNumber<TValue>::value == 0){
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

    template <typename... TArgPack>
    struct CallDetails<Nop, 0, TArgPack...>{
      enum { enable  = false };
      enum { ArgIndex = 0 };
      typedef Nop active_type;
      typedef Nop                                     specificator_type;
      typedef void(*_short_function_type)();
      typedef typename ::fcf::FunctionSignature<_short_function_type>::args_type      ShortTupleArgumentsType;

      inline static CallPlaceHolderInfo getPlaceHolderInfo(){
        std::tuple<TArgPack...> tuple;
        CallPlaceHolderInfo cphi;
        cphi.argSourceIndex = 0;
        cphi.specificatorIndex = 0;
        return cphi;
      }

    };

    template <typename TSpecificator, typename... TArgPack>
    struct CallDetails<TSpecificator, 0, TArgPack...>{
      enum { enable  = false };
      enum { ArgIndex = 0 };
      typedef Nop active_type;
      typedef Nop                                     specificator_type;
      typedef void(*_short_function_type)();
      typedef typename ::fcf::FunctionSignature<_short_function_type>::args_type      ShortTupleArgumentsType;

      inline static CallPlaceHolderInfo getPlaceHolderInfo(){
        std::tuple<TArgPack...> tuple;
        CallPlaceHolderInfo cphi;
        cphi.argSourceIndex = 0;
        cphi.specificatorIndex = 0;
        return cphi;
      }
    };

} // fcf namespace

#include "CallDetailsPack.hpp"

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_DETAILS_HPP___
