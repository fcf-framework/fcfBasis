#ifndef _FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_FUNCTION_BUILDER_BY_TUPLE_HPP___
#define _FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_FUNCTION_BUILDER_BY_TUPLE_HPP___

#include <tuple>

namespace fcf {
  namespace NDetails {

    template <typename TResult, typename TTuple>
    struct CallFunctionBuilderByTuple;

    template <typename TResult, typename ... TPack>
    struct CallFunctionBuilderByTuple<TResult, std::tuple<TPack...> > {
      typedef TResult (*type)(TPack...);
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_FUNCTION_BUILDER_BY_TUPLE_HPP___
