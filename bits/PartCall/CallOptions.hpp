#ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_OPTIONS_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__CALL_OPTIONS_HPP___

#include "../../bits/PartCallStorage/CallStorageDefinition.hpp"

namespace fcf{

  enum CallOptionsFlags {
    CO_ITERATION_SELECT_QUIET = 1,
  };

  struct CallOptions {
    unsigned int       flags;
    const CallStorage* storage;

    CallOptions()
      : flags(0)
      , storage(&getCallStorage()) {
    }

    CallOptions(unsigned int a_flags)
      : flags(a_flags)
      , storage(&getCallStorage()) {
    }

    CallOptions(unsigned int a_flags, const CallStorage& a_storage)
      : flags(a_flags)
      , storage(&a_storage) {
    }

    CallOptions(const CallOptions& a_source)
      : flags(a_source.flags)
      , storage(a_source.storage) {
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_OPTIONS_HPP___
