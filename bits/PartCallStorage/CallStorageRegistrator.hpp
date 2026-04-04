#ifndef ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_REGISTRATOR_HPP___
#define ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_REGISTRATOR_HPP___

#include "NDetails/CallStoragePlaceHolderRegistrator.hpp"
#include <algorithm>
#include "../../PartForeach.hpp"
#include "CallStorageSpace.hpp"
#include "../../bits/PartType/TypeIndexConverter.hpp"
#include "../../bits/PartCallPlaceHolder/NDetails/CallPlaceHolderSignatureGetter.hpp"
#include "../../bits/PartCall/CallOptions.hpp"
#include "../../bits/PartCall/CallArgumentOptions.hpp"
#include "../PartCall/NDetails/CallWrapper.hpp"
#include "CallStorageFunctionInfo.hpp"
#include "CallStorage.hpp"

namespace fcf {

    struct CallStorageRegistrator {

      template <typename TPlaceHolderSignatures, typename TFunctionResult, typename... TArgPack>
      CallStorageRegistrator(      std::string a_name,
                                   const std::string& a_space,
                                   const std::string& a_sourceName,
                                   TFunctionResult (*a_function)(TArgPack...),
                                   TPlaceHolderSignatures a_phs,
                                   std::string a_sourceCode = std::string()){
        getCallStorage().add(a_name, a_space, a_sourceName, a_function, a_phs, a_sourceCode);
      }

    };

} // fcf namespace


#endif // #ifndef ___FCF__BASIS__BITS__CALL_STORAGE__CALL_STORAGE_REGISTRATOR_HPP___
