#ifndef _FCF_BASIS__BITS__PART_CALL__CALL_SEEKER_BASE_IPP___
#define _FCF_BASIS__BITS__PART_CALL__CALL_SEEKER_BASE_IPP___

#include "NDetails/CallPairArgumentNode.hpp"
#include "NDetails/CallArguments.hpp"
#include "NDetails/CallSelectorHandler.hpp"
#include "NDetails/CallPairArgumentNode.hpp"
#include "CallOptions.hpp"

#include "../../PartConvert.hpp"
#include "../../PartException.hpp"
#include "../../bits/PartCallStorage/CallStorage.hpp"

#include "CallSeekerBaseDecl.hpp"

namespace fcf{

  #ifdef FCF_BASIS_IMPLEMENTATION
    void CallSeekerBase::_call(const char* a_functionName, BaseFunctionSignature* a_functionSignature, BaseFunctionSignature* a_resultFunctionSignature, Call* a_result, State& a_state, NDetails::CallArguments& a_callArguments, bool a_quiet){
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

      const CallStorage* storage = _options && _options->storage ? _options->storage : & getCallStorage();
      CallStorageSelectionFunctionGroups::const_iterator groupIt = storage->groups.find(a_functionName);
      if (groupIt == storage->groups.cend()) {
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

      ::fcf::NDetails::CallSelectorState iasd = {
                                                  storage,
                                                  _options,
                                                  a_functionName, 
                                                  a_resultFunctionSignature, 
                                                  a_result, 
                                                  groupIt, 
                                                  *currentFunctionSignature, 
                                                  currentFunctionSignature, 
                                                  {}, 
                                                  &groupIt->second.specifiersByArgIndex,
                                                  a_state.strictSource, 
                                                  false, 
                                                  {}, 
                                                  {}, 
                                                  false
                                                };
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
  #endif
} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_CALL__CALL_SEEKER_BASE_IPP___
