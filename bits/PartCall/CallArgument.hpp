#ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_ARGUMENT_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__CALL_ARGUMENT_HPP___

namespace fcf{

  enum CallArgumentFlags {
    CAF_POINTER_RESOLVE = 1,
  };

  struct CallArgument {
    unsigned int flags;

    CallArgument()
      :flags(0)
    {}

    CallArgument(const CallArgument& a_source)
      : flags(a_source.flags){
    }

    CallArgument(unsigned int a_flags)
      :flags(a_flags)
    {}

  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_ARGUMENT_HPP___
