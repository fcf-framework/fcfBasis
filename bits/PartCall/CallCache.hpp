#ifndef _FCF_BASIS__BITS__PART_CALL__CALL_CACHE_HPP___
#define _FCF_BASIS__BITS__PART_CALL__CALL_CACHE_HPP___

#include "NDetails/CallCacheHandler.hpp"
#include "CallOptions.hpp"

namespace fcf{

  template <typename ...TPackArg>
  class CallCache {
    public:
      enum { invariantValue = NDetails::CallCacheIsInvariant<TPackArg...>::invariantValue };

      template <typename ...TInputPackArg>
      CallCache(const char* a_functionName, TInputPackArg&&... a_packArg)
        : _handler(a_functionName, a_packArg...) {
      }

      template <typename ...TInputPackArg>
      inline void call(TInputPackArg&&... a_packArg){
        _handler.call(a_packArg...);
      }

      template <typename ...TInputPackArg>
      inline void call(const CallOptions& a_callOptions, TInputPackArg&&... a_packArg){
        _handler.call(a_callOptions, a_packArg...);
      }

      template <typename ...TInputPackArg>
      inline void call(CallOptions& a_callOptions, TInputPackArg&&... a_packArg){
        _handler.call((const CallOptions&)a_callOptions, a_packArg...);
      }

      template <typename ...TInputPackArg>
      inline Variant rcall(TInputPackArg&&... a_packArg){
        return _handler.rcall(a_packArg...);
      }

      template <typename ...TInputPackArg>
      inline Variant rcall(const CallOptions& a_callOptions, TInputPackArg&&... a_packArg){
        return _handler.rcall(a_callOptions, a_packArg...);
      }

      template <typename ...TInputPackArg>
      inline Variant rcall(CallOptions& a_callOptions, TInputPackArg&&... a_packArg){
        return _handler.rcall((const CallOptions&)a_callOptions, a_packArg...);
      }

    private:
      NDetails::CallCacheHandler< invariantValue, TPackArg... > _handler;
  };

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_CALL__CALL_CACHE_HPP___
