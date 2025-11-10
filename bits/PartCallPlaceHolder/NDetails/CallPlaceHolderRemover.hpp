#ifndef ___FCF_BASIS__BITS__PART_CALL_PLACE_HOLDER__NDETAILS__CALL_PLACE_HOLDER_REMOVER_HPP___
#define ___FCF_BASIS__BITS__PART_CALL_PLACE_HOLDER__NDETAILS__CALL_PLACE_HOLDER_REMOVER_HPP___

#include "../../../bits/PartMetaType/MetaTypeTupleInsert.hpp"
#include "../../../bits/PartCall/NDetails/CallFunctionBuilderByTuple.hpp"
#include "CallPlaceHolderArgDetector.hpp"

namespace fcf::NDetails {

    template <typename TTuple, typename TResult, typename... TArgPack>
    struct CallPlaceHolderRemoverImpl;

    template <typename TTuple, bool IsPlaceHolder, typename TResult, typename TArg1, typename... TArgPack>
    struct CallPlaceHolderResolveRemoverImpl {
      typedef typename ::fcf::MetaTypeTupleInsert<TTuple, TArg1, std::tuple_size<TTuple>::value>::type  next_tuple_type;
      typedef CallPlaceHolderRemoverImpl<next_tuple_type, TResult, TArgPack...>                           next_remover_type;
      typedef typename next_remover_type::function_type function_type;
    };

    template <typename TTuple, typename TResult, typename TArg1, typename... TArgPack>
    struct CallPlaceHolderResolveRemoverImpl<TTuple, true, TResult, TArg1, TArgPack...> {
      typedef CallPlaceHolderRemoverImpl<TTuple, TResult, TArgPack...>      next_remover_type;
      typedef typename next_remover_type::function_type                     function_type;
    };

    template <typename TTuple, typename TResult, typename... TArgPack >
    struct CallPlaceHolderRemoverImpl {
      typedef typename CallFunctionBuilderByTuple<TResult, TTuple>::type function_type;
    };

    template <typename TTuple, typename TResult, typename TArg1, typename... TArgPack>
    struct CallPlaceHolderRemoverImpl<TTuple, TResult, TArg1, TArgPack...> {
      typedef typename CallPlaceHolderResolveRemoverImpl<TTuple, CallPlaceHolderArgDetector<TArg1>::value, TResult, TArg1, TArgPack...>::function_type function_type;
    };

    template <typename TResult, typename... TArgPack>
    struct CallPlaceHolderRemover {
      typedef typename CallPlaceHolderRemoverImpl<std::tuple<>, TResult, TArgPack...>::function_type function_type;
    };

    template <typename TResult, typename... TArgPack>
    struct CallPlaceHolderRemover<TResult (TArgPack...) > {
      typedef typename CallPlaceHolderRemoverImpl<std::tuple<>, TResult, TArgPack...>::function_type function_type;
    };

} // fcf::NDetails namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL_PLACE_HOLDER__NDETAILS__CALL_PLACE_HOLDER_REMOVER_HPP___
