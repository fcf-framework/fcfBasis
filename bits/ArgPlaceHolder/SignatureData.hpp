#ifndef ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__SIGNATURE_DATA_HPP___
#define ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__SIGNATURE_DATA_HPP___

#include <vector>

namespace fcf {
  namespace ArgPlaceHolder {

    struct PlaceHolderArg {
      unsigned int argument;
      unsigned int placeHolderArgument;
    };

    struct PlaceHolderArgEx : public PlaceHolderArg {
      unsigned int type;
    };

    struct SignatureData {
      unsigned int                specificatorIndex;
      int                         argSourceIndex;
      std::vector<PlaceHolderArg> placeHolders;
    };

  } // ArgPlaceHolder namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__ARG_PLACE_HOLDER__SIGNATURE_DATA_HPP___
