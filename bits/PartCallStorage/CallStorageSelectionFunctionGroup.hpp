#ifndef ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_SELECTION_FUNCTION_GROUP_HPP___
#define ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_SELECTION_FUNCTION_GROUP_HPP___

#include <vector>
#include <map>
#include <unordered_map>
#include "CallStorageSelectionFunctionInfo.hpp"

namespace fcf {

  typedef std::multimap<BaseFunctionSignature, CallStorageSelectionFunctionInfo>            CallStorageSelectionFunctionsMap;
  typedef std::unordered_multimap<unsigned int, CallStorageSelectionFunctionsMap>           CallStorageSelectionFunctionsByArgNumber;
  typedef std::unordered_multimap<BaseFunctionSignature, CallStorageSelectionFunctionInfo>  CallStorageSelectionFunctions;

  struct CallStorageSelectionFunctionGroup {
    std::vector< std::vector<unsigned int> >  specificatorsByArgIndex;
    CallStorageSelectionFunctions             callers;
    CallStorageSelectionFunctionsByArgNumber  callersTree;
    std::vector<unsigned int>                 argumentOptions;
    unsigned int                              maxArgumentCount;
    CallStorageSelectionFunctionGroup()
      : maxArgumentCount(0){}
  };

  typedef std::unordered_map<std::string, CallStorageSelectionFunctionGroup >               CallStorageSelectionFunctionGroups;

}

#endif // #ifndef ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_SELECTION_FUNCTION_GROUP_HPP___
