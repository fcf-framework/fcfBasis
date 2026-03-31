#ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_SEEKER_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__CALL_SEEKER_HPP___

#include "NDetails/CallSelector.hpp"
#include "NDetails/CallPairArgumentNode.hpp"
#include "NDetails/CallArguments.hpp"
#include "../../PartConvert.hpp"
#include "../../PartException.hpp"

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
        NDetails::CallArguments ca(Nop(), a_argPack...);
        return (*this)(a_functionName, (BaseFunctionSignature*)0, (BaseFunctionSignature*)0, a_result, ca);
      }

      void operator()(const char* a_functionName, Call* a_result){
        std::tuple<TArgPack*...> tuple={((TArgPack*)0)...};
        NDetails::CallArguments ca(tuple);
        return (*this)(a_functionName, (BaseFunctionSignature*)0, (BaseFunctionSignature*)0, a_result, ca);
      }

      void operator()(const char* a_functionName, BaseFunctionSignature* a_functionSignature, BaseFunctionSignature* a_resultFunctionSignature, Call* a_result, NDetails::CallArguments& a_arguments, bool a_quiet = false){
        State state;
        state.init = true;
        state.strictSource = true;
        this->_call(a_functionName, a_functionSignature, a_resultFunctionSignature, a_result, state, a_arguments, a_quiet);
      }

      void packSearch(const char* a_functionName,
                      BaseFunctionSignature* a_functionSignature,
                      BaseFunctionSignature* a_resultFunctionSignature,
                      Call* a_result,
                      NDetails::CallArguments& a_arguments){
        State state;
        state.init = true;
        state.strictSource = true;
        this->_call(a_functionName, a_functionSignature, a_resultFunctionSignature, a_result, state, a_arguments);
      }

    protected:
      void _call(const char* a_functionName, BaseFunctionSignature* a_functionSignature, BaseFunctionSignature* a_resultFunctionSignature, Call* a_result, State& a_state, NDetails::CallArguments& a_callArguments, bool a_quiet = false){
        BaseFunctionSignature functionSignature(a_callArguments.size());
        BaseFunctionSignature* currentFunctionSignature;
        if (!a_functionSignature){
          functionSignature.rcode = Type<void>().index();
          for(unsigned int i = 0; i < a_callArguments.size() ; ++i){
            functionSignature.pacodes[i] = a_callArguments.getTypeIndex(i);
          }
          functionSignature.applySimpleCallSignature();
          currentFunctionSignature = &functionSignature;
        } else {
          currentFunctionSignature = a_functionSignature;
        }

        CallStorageSelectionFunctionGroups::iterator groupIt = getCallStorage().groups.find(a_functionName);
        if (groupIt == getCallStorage().groups.end()) {
          throw CallNotFoundException(__FILE__, __LINE__, a_functionName, convert<std::string>((const BaseFunctionSignature&)*currentFunctionSignature));
        }

        if (a_state.init) {
          a_state.init = false;
          a_result->complete = false;
          a_result->dynamicCaller = false;
          a_result->caller = 0;
          a_result->function = 0;
          a_result->conversions.clear();
        }

        ::fcf::NDetails::CallSelectorState iasd = {a_functionName, a_resultFunctionSignature, a_result, groupIt, *currentFunctionSignature, currentFunctionSignature, {}, &groupIt->second.specificatorsByArgIndex, a_state.strictSource, false, {}, {}, false};
        {
          NDetails::CallSelectorHandler csh(iasd);
          csh.initialize(a_callArguments);
          csh(0, 0, 0, 0, false);
          if (iasd.result->caller){
            return;
          }
        }

        if (!a_result->complete && !a_quiet) {
          throw CallNotFoundException(__FILE__, __LINE__, a_functionName, convert<std::string>((const BaseFunctionSignature&)*currentFunctionSignature));
        }
      }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_SEEKER_HPP___
