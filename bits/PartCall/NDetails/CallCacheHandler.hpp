#ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_CACHE_HANDLER_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_CACHE_HANDLER_HPP___

#include <string>
#include "../../../Type.hpp"
#include "../Call.hpp"
#include "../CallSeeker.hpp"
#include "Caller.hpp"

namespace fcf{
  namespace NDetails {

    template <typename Ty, typename = void>
    struct CallCacheIsInvariantType {
      enum { value = false };
    };

    template <typename Ty>
    struct CallCacheIsInvariantType<Ty, decltype((void)::fcf::Type<Ty, ::fcf::ResolveSpecificator>::invariant_value )> {
      enum { value = ::fcf::Type<Ty, ::fcf::ResolveSpecificator>::invariant_value };
    };

    template <typename Ty, typename = void>
    struct CallCacheIsInvariantContainer {
      enum { value = false };
    };

    template <typename Ty>
    struct CallCacheIsInvariantContainer<Ty, decltype((void)typename ::fcf::Type<Ty, ::fcf::ContainerAccessSpecificator>::KeyType() )> {
      enum { 
        value = CallCacheIsInvariantType<typename ::fcf::Type<Ty, ::fcf::ContainerAccessSpecificator>::KeyType >::value ||
                CallCacheIsInvariantType<typename ::fcf::Type<Ty, ::fcf::ContainerAccessSpecificator>::ValueType >::value,
      };
    };

    template <typename Ty>
    struct CallCacheIsInvariantItem {
      enum { 
        value = CallCacheIsInvariantType<Ty>::value ||
                CallCacheIsInvariantContainer<Ty>::value
      };
    };


    template <typename ...TPackArg>
    struct CallCacheIsInvariant {
      enum { invariant_value = false };
    };

    template <typename TArg, typename ...TPackArg>
    struct CallCacheIsInvariant<TArg, TPackArg...> {
      typedef typename std::remove_const< typename std::remove_reference< TArg>::type >::type type;
      enum { invariant_value = CallCacheIsInvariantItem<type>::value | CallCacheIsInvariant<TPackArg...>::invariant_value  };
    };

    template <bool IsInvariant, typename ...TPackArg>
    class CallCacheHandler{
      public:
        template <typename ...TInputPackArg>
        CallCacheHandler(const char* a_functionName, TInputPackArg&&... a_argPack) {
          fcf::CallSeeker<void, TPackArg...>()(a_functionName, &_call, a_argPack...);
        }

        template <typename ...TInputPackArg>
        inline void call(TInputPackArg&&... a_argPack){
          NDetails::Caller().call(_call, a_argPack...);
        }

        template <typename ...TInputPackArg>
        inline Variant rcall(TInputPackArg&&... a_argPack){
          return NDetails::Caller().rcall(_call, a_argPack...);
        }

      private:
        fcf::Call _call;
    };

    template <typename ...TPackArg>
    struct CallCacheHandler<true, TPackArg...>{
      public:
        template <typename ...TInputPackArg>
        CallCacheHandler(const char* a_functionName, TInputPackArg&&... /*a_argPack*/)
          : _functionName(a_functionName){
        }

        template <typename ...TInputPackArg>
        inline void call(TInputPackArg&&... a_argPack){
          bool complete = false;
          Caller caller;
          caller.call(complete, _graph, a_argPack...);

          if (!complete) {
            fcf::Call dc;
            fcf::CallSeeker<void, TPackArg...>()(_functionName.c_str(), &dc, a_argPack...);
            _graph.add(dc);
            caller.call(dc, a_argPack...);
          }
        }

        template <typename ...TInputPackArg>
        inline Variant rcall(TInputPackArg&&... a_argPack){
          bool complete = false;
          Caller caller;
          Variant res = caller.rcall(complete, _graph, a_argPack...);

          if (!complete) {
            fcf::Call dc;
            fcf::CallSeeker<void, TPackArg...>()(_functionName.c_str(), &dc, a_argPack...);
            _graph.add(dc);
            res = caller.rcall(dc, a_argPack...);
          }

          return res;
        }

        Caller::CallGraph _graph;
        std::string _functionName;
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_CACHE_HANDLER_HPP___
