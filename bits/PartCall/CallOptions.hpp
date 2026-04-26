#ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_OPTIONS_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__CALL_OPTIONS_HPP___

#include "CallArgumentOptions.hpp"
#include "CallArgument.hpp"
#include "../../bits/PartCallStorage/CallStorageDefinition.hpp"

namespace fcf{

  enum CallOptionsFlags {
    CO_ITERATION_SELECT_QUIET = 1,
  };

  struct CallOptions {
    unsigned int                    flags;
    const CallStorage*              storage;
    const CallArgument* argumentOptions;
    size_t                          argumentOptionsCount;

    CallOptions()
      : flags(0)
      , storage(&getCallStorage())
      , argumentOptionsCount(0) {
    }

    CallOptions(const CallArgument* a_argumentOptions, size_t a_argumentOptionsCount)
      : flags(0)
      , storage(&getCallStorage())
      , argumentOptions(a_argumentOptions)
      , argumentOptionsCount(a_argumentOptionsCount) {
    }

    CallOptions(unsigned int a_flags, const CallArgument* a_argumentOptions = 0, size_t a_argumentOptionsCount = 0)
      : flags(a_flags)
      , storage(&getCallStorage())
      , argumentOptions(a_argumentOptions)
      , argumentOptionsCount(a_argumentOptionsCount) {
    }

    CallOptions(unsigned int a_flags, const CallStorage& a_storage, const CallArgument* a_argumentOptions = 0, size_t a_argumentOptionsCount = 0)
      : flags(a_flags)
      , storage(&a_storage)
      , argumentOptions(a_argumentOptions)
      , argumentOptionsCount(a_argumentOptionsCount) {
    }

    CallOptions(const CallOptions& a_source, const CallArgument* a_argumentOptions = 0, size_t a_argumentOptionsCount = 0)
      : flags(a_source.flags)
      , storage(a_source.storage)
      , argumentOptions(a_argumentOptions)
      , argumentOptionsCount(a_argumentOptionsCount) {
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_OPTIONS_HPP___
