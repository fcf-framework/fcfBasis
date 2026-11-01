#ifndef _FCF_BASIS__BITS__PART_CALL__CALL_SEEKER_HPP___
#define _FCF_BASIS__BITS__PART_CALL__CALL_SEEKER_HPP___

#include "CallSeekerBase.hpp"

#include "NDetails/CallPairArgumentNode.hpp"
#include "NDetails/CallArguments.hpp"
#include "NDetails/CallSelectorHandler.hpp"
#include "NDetails/CallPairArgumentNode.hpp"
#include "../../PartConvert.hpp"
#include "../../PartException.hpp"


namespace fcf{

  template <typename TRes, typename... TArgPack>
  class CallSeeker : public CallSeekerBase {
    public:
      CallSeeker() {
      }

      CallSeeker(const CallOptions& a_options)
        : CallSeekerBase(a_options) {
      }

      CallSeeker(const CallOptions* a_options)
        : CallSeekerBase(a_options) {
      }

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
  };

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_CALL__CALL_SEEKER_HPP___
