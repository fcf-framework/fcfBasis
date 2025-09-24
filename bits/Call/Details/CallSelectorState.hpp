#ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_SELECTOR_STATE_HPP___
#define ___FCF__BASIS__BITS__CALL__DETAILS__CALL_SELECTOR_STATE_HPP___

#include "../../PartCallStorage/CallStorage.hpp"
#include "../../../StaticVector.hpp"
#include "../Call.hpp"

namespace fcf {
  namespace Details {

    struct CallSelectorState {
      const char*                                       name;
      Call*                                             result;
      CallStorageSelectionFunctionGroups::iterator      groupIterator;
      BaseFunctionSignature&                            functionSignature;
      BaseFunctionSignature*                            ptrFunctionSignature;
      StaticVector<void*, 8>*                           arguments;
      std::vector<unsigned int>                         placeHolderVec;
      std::vector<std::vector<unsigned int> >*          placeHolderSpecificators;
      bool                                              strictSource;
      bool                                              dynamicCaller;
    };

  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_SELECTOR_STATE_HPP___
