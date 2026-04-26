#ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_ARGUMENT_OPTIONS_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__CALL_ARGUMENT_OPTIONS_HPP___

namespace fcf{

  struct BasicCallArgumentOptions {
    int flagsValue;
    BasicCallArgumentOptions()
      : flagsValue(0)
    {}
    BasicCallArgumentOptions(int a_flagsValue)
      : flagsValue(a_flagsValue)
    {}
  };

  enum CallArgumentOptionsFlags {
    CAO_RESOLVE_POINTER        = 1,
    CAO_CONVERT_POINTER        = 2,
    CAO_PAIR_ITERATION_POINTER = 4,
    CAO_PAIR_SEGMENTATION      = 8,
  };

  template <unsigned int Flags>
  struct CallArgumentOptions : public BasicCallArgumentOptions {
    enum { flags = Flags };

    CallArgumentOptions()
      : BasicCallArgumentOptions(flags)
    {}
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__CALL_ARGUMENT_OPTIONS_HPP___
