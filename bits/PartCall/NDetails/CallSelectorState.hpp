#ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_SELECTOR_STATE_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_SELECTOR_STATE_HPP___

#include "../../PartCallStorage/CallStorage.hpp"
#include "../../../StaticVector.hpp"
#include "../Call.hpp"

namespace fcf { 
  namespace NDetails {

    struct CallSelectorState {
      struct PlaceHolderSource{
        unsigned int specificatorIndex;
        unsigned int argumentNumber;
      };
      const char*                                       name;
      BaseFunctionSignature*                            resultFunctionSignature;
      Call*                                             result;
      CallStorageSelectionFunctionGroups::iterator      groupIterator;
      BaseFunctionSignature&                            functionSignature;
      BaseFunctionSignature*                            ptrFunctionSignature;
      /*StaticVector<void*, 8>*                           arguments;*/
      std::vector<PlaceHolderSource>                    placeHolderVec;
      std::vector<std::vector<unsigned int> >*          placeHolderSpecificators;
      bool                                              strictSource;
      bool                                              dynamicCaller;
      StaticVector<unsigned int, 4>                     ptrResolveVector;
      StaticVector<std::pair<unsigned int, unsigned int>, 4> requiredArgumentsFlags;
      bool                                              invariantIteration;
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_SELECTOR_STATE_HPP___
