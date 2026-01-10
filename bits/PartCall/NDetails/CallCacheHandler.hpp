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
    struct CallCacheIsInvariantItem {
      enum { value = false };
    };

    template <typename Ty>
    struct CallCacheIsInvariantItem<Ty, decltype((void)::fcf::Type<Ty, ::fcf::ResolveSpecificator>::invariant_value )> {
      enum { value = ::fcf::Type<Ty, ::fcf::ResolveSpecificator>::invariant_value };
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
        inline void operator()(TInputPackArg&&... a_argPack){
          NDetails::Caller().call(_call, a_argPack...);
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
        inline void operator()(TInputPackArg&&... a_argPack){
          bool complete = false;
          Caller().call(complete, _graph, a_argPack...);

          if (!complete) {
            fcf::Call dc;
            fcf::CallSeeker<void, TPackArg...>()(_functionName.c_str(), &dc, a_argPack...);
            _addToGraph(dc, _graph);
            NDetails::Caller().call(dc, a_argPack...);
          }
        }
      private:

        void _addToGraph(const Call& a_call, Caller::CallGraph& a_graph){
          Caller::ConversionsNode* node = &a_graph.conversions;
          Call* lastDstCall  = &a_graph.conversions.call;
          for(const CallConversion& conversion : a_call.conversions){
            Caller::KeyNode ca{conversion.index, conversion.sourceIndex, conversion.mode};
            auto insertIt = node->conversions.insert({ca, Caller::ConversionInfoNode()});
            Caller::ConversionInfoNode* typesConversion = &insertIt.first->second;
            typesConversion->conversion =  conversion;
            auto insertTypeIt = typesConversion->types.insert({conversion.type, Caller::ConversionsNode()});
            lastDstCall = &insertTypeIt.first->second.call;
            node = &insertTypeIt.first->second;
          }
          *lastDstCall = a_call;
        }
        Caller::CallGraph _graph;
        std::string _functionName;
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_CACHE_HANDLER_HPP___
