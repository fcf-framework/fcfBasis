#ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_RESULT_TYPE_GETTER_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_RESULT_TYPE_GETTER_HPP___

#include "../../../Nop.hpp"

namespace fcf::NDetails {

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

} // fcf::NDetails namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_RESULT_TYPE_GETTER_HPP___
