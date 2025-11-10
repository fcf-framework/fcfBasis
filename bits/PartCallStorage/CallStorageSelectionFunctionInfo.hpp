#ifndef ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_SELECTION_FUNCTION_INFO_HPP___
#define ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_SELECTION_FUNCTION_INFO_HPP___

#include "../../FunctionSignature.hpp"
#include "../../bits/PartCallPlaceHolder/CallPlaceHolderInfo.hpp"

namespace fcf {

  struct CallStorageSelectionFunctionInfo {
    BaseFunctionSignature                   callerSignature;
    unsigned int                            index;
    void                                    (*lcaller)(void*, void**);
    std::vector<::fcf::CallPlaceHolderInfo> placeHolder;
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_SELECTION_FUNCTION_INFO_HPP___

