#ifndef ___FCF_BASIS__DETAILS__VARIANT__NOBODY_WRAPPER_STORAGE_HPP___
#define ___FCF_BASIS__DETAILS__VARIANT__NOBODY_WRAPPER_STORAGE_HPP___

#include <map>
#include <memory>
#include "BaseNobodyWrapper.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace Variant {

        typedef std::map< unsigned int, std::shared_ptr<BaseNobodyWrapper> > NobodyWrapperStorage;

      } // Variant namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace


#endif // #ifndef ___FCF_BASIS__DETAILS__VARIANT__NOBODY_WRAPPER_STORAGE_HPP___
