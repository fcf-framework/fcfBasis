#ifndef ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_SEQUENCE_HPP___
#define ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_SEQUENCE_HPP___

namespace fcf{

    template <int ... IndexPack>
    struct MetaTypeSequence;

    template <>
    struct MetaTypeSequence<>{
      typedef MetaTypeSequence<> type;
    };

    template <int Index>
    struct MetaTypeSequence<Index>{
      typedef MetaTypeSequence<Index> type;
    };

    template <int IndexStop, int StartIndex, int ... IndexPack>
    struct MetaTypeSequence<IndexStop, StartIndex, IndexPack...> {
      typedef typename MetaTypeSequence<IndexStop, StartIndex-1, StartIndex, IndexPack...>::type type;
    };

    template <int IndexStop, int StartIndex>
    struct MetaTypeSequence<IndexStop, StartIndex> {
      typedef typename MetaTypeSequence<IndexStop, StartIndex-2, StartIndex-1>::type type;
    };

    template <int IndexStop, int ... IndexPack>
    struct MetaTypeSequence<IndexStop, IndexStop, IndexPack...> {
      typedef MetaTypeSequence<IndexStop, IndexPack...> type;
    };

    template <int IndexStop>
    struct MetaTypeSequence<IndexStop, IndexStop> {
      typedef MetaTypeSequence<> type;
    };

    template <int IndexStop>
    struct MetaTypeSequence<IndexStop, IndexStop-1> {
      typedef MetaTypeSequence<> type;
    };

    template <int IndexStop>
    struct MetaTypeSequence<IndexStop, IndexStop-2> {
      typedef MetaTypeSequence<> type;
    };

    template <int IndexStop>
    struct MetaTypeSequence<IndexStop, IndexStop+1> {
      typedef MetaTypeSequence<IndexStop> type;
    };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_META_TYPE__META_TYPE_SEQUENCE_HPP___
