#ifndef ___FCF_BASIS__BITS__PART_CALL_PLACE_HOLDER__CALL_PLACE_HOLDER_INFO_HPP___
#define ___FCF_BASIS__BITS__PART_CALL_PLACE_HOLDER__CALL_PLACE_HOLDER_INFO_HPP___

#include <vector>
#include "CallPlaceHolderArg.hpp"
#include "CallPlaceHolderArgEx.hpp"

namespace fcf{

  struct CallPlaceHolderInfo {
    unsigned int                    specificatorIndex;
    int                             argSourceIndex;
    std::vector<CallPlaceHolderArg> placeHolders;
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL_PLACE_HOLDER__CALL_PLACE_HOLDER_INFO_HPP___
