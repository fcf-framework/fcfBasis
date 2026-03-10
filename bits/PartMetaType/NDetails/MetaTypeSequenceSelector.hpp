#ifndef ___FCF_BASIS__BITS__PART_META_TYPE__NDETAILS__META_TYPE_SEQUENCE_SELECTOR_HPP___
#define ___FCF_BASIS__BITS__PART_META_TYPE__NDETAILS__META_TYPE_SEQUENCE_SELECTOR_HPP___

#include "../MetaTypeSequencePredefinition.hpp"

namespace fcf{
  namespace NDetails{

    template <int LeftIndex, int RigthIndex>
    struct MetaTypeSequenceSelectorInc3 {
      typedef typename MetaTypeSequence<LeftIndex, RigthIndex - 2 - 2, RigthIndex - 1 - 2>::type type;
    };

    template <int LeftIndex> // <0, -2>
    struct MetaTypeSequenceSelectorInc3<LeftIndex, LeftIndex> {
      typedef MetaTypeSequence<> type;

    };



    template <int LeftIndex, int RigthIndex>
    struct MetaTypeSequenceSelectorInc2 {
      typedef typename MetaTypeSequenceSelectorInc3<LeftIndex, RigthIndex + 1>::type type;
    };

    template <int LeftIndex> // <0, -1>
    struct MetaTypeSequenceSelectorInc2<LeftIndex, LeftIndex> {
      typedef MetaTypeSequence<> type;

    };



    template <int LeftIndex, int RigthIndex>
    struct MetaTypeSequenceSelectorInc1 {
      typedef typename MetaTypeSequenceSelectorInc2<LeftIndex, RigthIndex + 2>::type type;
    };

    template <int LeftIndex> // <0, 1>
    struct MetaTypeSequenceSelectorInc1<LeftIndex, LeftIndex> {
      typedef MetaTypeSequence<LeftIndex> type;
    };



    template <int LeftIndex, int RigthIndex>
    struct MetaTypeSequenceSelector {
      typedef typename MetaTypeSequenceSelectorInc1<LeftIndex, RigthIndex-1>::type type;
    };

    template <int LeftIndex> // <0, 0>
    struct MetaTypeSequenceSelector<LeftIndex, LeftIndex> {
      typedef MetaTypeSequence<> type;
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_META_TYPE__NDETAILS__META_TYPE_SEQUENCE_SELECTOR_HPP___
