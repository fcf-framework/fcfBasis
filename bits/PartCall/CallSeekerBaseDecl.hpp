#ifndef _FCF_BASIS__BITS__PART_CALL__CALL_SEEKER_BASE_DECL_HPP___
#define _FCF_BASIS__BITS__PART_CALL__CALL_SEEKER_BASE_DECL_HPP___

#include "FunctionSignature.hpp"
#include "Call.hpp"
#include "CallConversion.hpp"
#include "CallOptions.hpp"
#include "NDetails/CallArguments.hpp"
#include "../../bits/PartStaticVector/PartStaticVector.hpp"

namespace fcf{

  class FCF_BASIS_DECL_EXPORT CallSeekerBase {
    protected:
      struct State {
        typedef StaticVector<CallConversion, 8> conversions_type;
        bool             init;
        conversions_type conversions;
        bool             strictSource;
      };

      CallSeekerBase()
        : _options(0) {}

      CallSeekerBase(const CallOptions& a_options)
        : _options(&a_options){
      }

      CallSeekerBase(const CallOptions* a_options)
        : _options(a_options){
      }

      void _call(const char* a_functionName, 
                 BaseFunctionSignature* a_functionSignature, 
                 BaseFunctionSignature* a_resultFunctionSignature, 
                 Call* a_result, 
                 State& a_state, 
                 NDetails::CallArguments& a_callArguments, 
                 bool a_quiet = false);

      const CallOptions* _options;
  };

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_CALL__CALL_SEEKER_BASE_DECL_HPP___
