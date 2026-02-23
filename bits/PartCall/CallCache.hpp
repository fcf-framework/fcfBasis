#ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_CACHE_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__CALL_CACHE_HPP___

#include "NDetails/CallCacheHandler.hpp"

namespace fcf{

  template <typename ...TPackArg>
  class CallCache {
    public:
      enum { invariant_value = NDetails::CallCacheIsInvariant<TPackArg...>::invariant_value };

      template <typename ...TInputPackArg>
      CallCache(const char* a_functionName, TInputPackArg&&... a_packArg)
        : _handler(a_functionName, a_packArg...) {
      }

      template <typename ...TInputPackArg>
      inline void call(TInputPackArg&&... a_packArg){
        _handler.call(a_packArg...);
      }

      template <typename ...TInputPackArg>
      inline Variant rcall(TInputPackArg&&... a_packArg){
        return _handler.rcall(a_packArg...);
      }

    private:
      NDetails::CallCacheHandler< invariant_value, TPackArg... > _handler;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_CACHE_HPP___
