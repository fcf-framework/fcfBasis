#ifndef ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_HPP___
#define ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_HPP___

#include "CallStorageFunctionIndexes.hpp"
#include "CallStorageFunctionInfoVector.hpp"
#include "CallStorageSelectionFunctionGroup.hpp"

namespace fcf {

  struct CallStorage {
    CallStorageFunctionIndexes         indexes;
    CallStorageFunctionInfoVector      functions;
    CallStorageSelectionFunctionGroups groups;
  };

  CallStorage& getCallStorage();

  #ifdef FCF_BASIS_IMPLEMENTATION
  CallStorage& getCallStorage(){
    static CallStorage storage;
    return storage;
  }
  #endif

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_HPP___
