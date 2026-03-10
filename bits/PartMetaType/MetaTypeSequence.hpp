#ifndef ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_SEQUENCE_HPP___
#define ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_SEQUENCE_HPP___

#include "MetaTypeSequencePredefinition.hpp"
#include "NDetails/MetaTypeSequenceSelector.hpp"

namespace fcf {

    template <>
    struct MetaTypeSequence<>{
      typedef MetaTypeSequence<> type;
    };

    template <int Index>
    struct MetaTypeSequence<Index>{
      typedef MetaTypeSequence<Index> type;
    };

    template <int IndexStop, int StartIndex>
    struct MetaTypeSequence<IndexStop, StartIndex> {
      typedef typename NDetails::MetaTypeSequenceSelector<IndexStop, StartIndex>::type type;
    };

    template <int BeginIndex, int NextIndex, int ... IndexPack>
    struct MetaTypeSequence<BeginIndex, BeginIndex, NextIndex, IndexPack...> {
      typedef MetaTypeSequence<BeginIndex, NextIndex, IndexPack...> type;
    };

    template <int BeginIndex, int CurrentIndex, int NextIndex, int ... IndexPack>
    struct MetaTypeSequence<BeginIndex, CurrentIndex, NextIndex, IndexPack...> {
      typedef typename MetaTypeSequence<BeginIndex, CurrentIndex-1, CurrentIndex, NextIndex, IndexPack...>::type type;
    };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_SEQUENCE_HPP___
