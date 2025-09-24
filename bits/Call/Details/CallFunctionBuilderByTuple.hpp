#ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_FUNCTION_BUILDER_BY_TUPLE_HPP___
#define ___FCF__BASIS__BITS__CALL__DETAILS__CALL_FUNCTION_BUILDER_BY_TUPLE_HPP___

#include <tuple>

namespace fcf {
  namespace Details {

    template <typename TResult, typename TTuple>
    struct CallFunctionBuilderByTuple;

    template <typename TResult, typename ... TPack>
    struct CallFunctionBuilderByTuple<TResult, std::tuple<TPack...> > {
      typedef TResult (*type)(TPack...);
    };

  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_FUNCTION_BUILDER_BY_TUPLE_HPP___
