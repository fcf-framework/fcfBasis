#ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_OPTIONS_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__CALL_OPTIONS_HPP___

namespace fcf{

  enum CallOptionsFlags {
    CO_ITERATION_SELECT_QUIET = 1,
  };

  struct CallOptions {
    unsigned int flags;

    CallOptions()
      : flags(0){ }

    CallOptions(unsigned int a_flags)
      : flags(a_flags){ }

    CallOptions(const CallOptions& a_source)
      : flags(a_source.flags){ }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_OPTIONS_HPP___
