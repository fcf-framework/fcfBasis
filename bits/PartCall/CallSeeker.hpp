#ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_SEEKER_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__CALL_SEEKER_HPP___

#include "NDetails/CallSelector.hpp"
#include "NDetails/CallPairArgumentNode.hpp"

namespace fcf{

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
        this->call(a_functionName, 0, 0, a_result, state, a_argPack...);
      }

      template <typename... TCurrentArgPack>
      void operator()(const char* a_functionName, NDetails::CallPairArgumentNode* a_pairNode, BaseFunctionSignature* a_functionSignature, Call* a_result, const TCurrentArgPack&... a_argPack){
        State state;
        state.init = true;
        state.strictSource = !!sizeof...(TCurrentArgPack);
        this->call(a_functionName, a_pairNode, a_functionSignature, a_result, state, a_argPack...);
      }

    protected:
      template <typename... TCurrentArgPack>
      void call(const char* a_functionName, NDetails::CallPairArgumentNode* a_pairNode, BaseFunctionSignature* a_functionSignature, Call* a_result, State& a_state, const TCurrentArgPack&... a_argPack){
        CallStorageSelectionFunctionGroups::iterator groupIt = getCallStorage().groups.find(a_functionName);
        if (groupIt == getCallStorage().groups.end()) {
          throw std::runtime_error("Function not found.");
        }

        FunctionSignature<TRes (TArgPack...)> functionSignature;
        functionSignature.applySimpleCallSignature();

        BaseFunctionSignature* currentFunctionSignature = a_functionSignature ? a_functionSignature : &functionSignature;

        if (a_state.init) {
          a_state.init = false;
          a_result->complete = false;
          a_result->dynamicCaller = false;
          a_result->caller = 0;
          a_result->function = 0;
          a_result->conversions.clear();
        }

        typedef std::tuple<const typename std::remove_cv< typename std::remove_reference<TArgPack>::type >::type *...> ptr_tuple_type;
        StaticVector<void*, 8> arguments = {(void*)&a_argPack...};
        ::fcf::NDetails::CallSelectorState iasd = {a_functionName, a_result, groupIt, *currentFunctionSignature, currentFunctionSignature, &arguments, {}, &groupIt->second.specificatorsByArgIndex, a_state.strictSource, false, {}, false};
        {
          typedef ::fcf::NDetails::CallSelector<sizeof...(a_argPack), sizeof...(a_argPack), ptr_tuple_type> selector_type;
          selector_type()(iasd, a_pairNode);
          if (iasd.result->caller){
            return;
          }
        }

        if (!a_result->complete) {
          throw std::runtime_error("Function not found. No signature found.");
        }
      }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_SEEKER_HPP___
