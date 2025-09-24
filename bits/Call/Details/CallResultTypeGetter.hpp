#ifndef ___FCF_BASIS__BITS__CALL__DETAILS__CALL_RESULT_TYPE_GETTER_HPP___
#define ___FCF_BASIS__BITS__CALL__DETAILS__CALL_RESULT_TYPE_GETTER_HPP___

#include "../../../Nop.hpp"

namespace fcf {
  namespace Details {
    template <typename TResult = Nop>
    struct CallResultTypeGetter {
      typedef TResult type;
    };

    template <typename TResult, typename... TPack>
    struct CallResultTypeGetter<TResult (TPack...)> {
      typedef TResult type;
    };

    template <typename TResult, typename... TPack>
    struct CallResultTypeGetter<TResult (*)(TPack...)> {
      typedef TResult type;
    };

  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__CALL__DETAILS__CALL_RESULT_TYPE_GETTER_HPP___
