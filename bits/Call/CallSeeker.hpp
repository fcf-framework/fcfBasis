#ifndef ___FCF__BASIS__BITS__CALL__CALL_SEEKER_HPP___
#define ___FCF__BASIS__BITS__CALL__CALL_SEEKER_HPP___

#include "Details/CallSelector.hpp"

namespace fcf {

  template <typename TRes, typename... TArgPack>
  class CallSeeker {
    protected:

      struct State {
        typedef StaticVector<CallConversion, 8> conversions_type;

        bool             init;
        conversions_type conversions;
        bool             strictSource;
      };

    public:
      template <typename... TCurrentArgPack>
      void operator()(const char* a_functionName, Call* a_result, const TCurrentArgPack&... a_argPack){
        State state;
        state.init = true;
        state.strictSource = !!sizeof...(TCurrentArgPack);
        this->call(a_functionName, a_result, state, a_argPack...);
      }

    protected:
      template <typename... TCurrentArgPack>
      void call(const char* a_functionName, Call* a_result, State& a_state, const TCurrentArgPack&... a_argPack){
        fcf::Details::IndexableFunction::CallFunctionGroups::iterator groupIt = fcf::Details::IndexableFunction::getStorage().groups.find(a_functionName);
        if (groupIt == Details::IndexableFunction::getStorage().groups.end()) {
          throw std::runtime_error("Function not found.");
        }

        FunctionSignature<TRes (TArgPack...)> functionSignature;
        functionSignature.applySimpleCallSignature();

        if (a_state.init) {
          a_state.init = false;
          a_result->complete = false;
          a_result->dynamicCaller = false;
          a_result->caller = 0;
          a_result->function = 0;
          a_result->conversions.clear();
        }

        fcf::Details::IndexableFunction::CallFunctions::iterator callerInfoIt =
          groupIt->second.callers.find(functionSignature);

        typedef std::tuple<const typename std::remove_cv< typename std::remove_reference<TArgPack>::type >::type *...> ptr_tuple_type;
        StaticVector<void*, 8> arguments = {(void*)&a_argPack...};
        ::fcf::Details::CallSelectorState iasd = {a_functionName, a_result, groupIt, functionSignature, &arguments, {}, &groupIt->second.specificatorsByArgIndex, a_state.strictSource};
        {
          typedef ::fcf::Details::CallSelector<sizeof...(a_argPack), sizeof...(a_argPack), ptr_tuple_type> selector_type;
          selector_type()(0, iasd, false, false);
          if (iasd.result->caller){
            return;
          }
        }
        {
          typedef ::fcf::Details::CallSelector<0, sizeof...(TArgPack), ptr_tuple_type> selector_type;
          selector_type()(0, iasd, true, false);
        }

        if (!a_result->complete) {
          throw std::runtime_error("Function not found. No signature found.");
        }
      }
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__CALL__CALL_SEEKER_HPP___

