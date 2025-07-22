#ifndef ___FCF_BASIS__TEMPLATE__SEQUENCE_HPP___
#define ___FCF_BASIS__TEMPLATE__SEQUENCE_HPP___

namespace fcf {
  namespace Template {

    template <int IndexStop, int ... IndexPack>
    struct Sequence;

    template <int IndexStop>
    struct Sequence<IndexStop>{
      typedef Sequence<IndexStop> type;
    };

    template <int IndexStop, int StartIndex, int ... IndexPack>
    struct Sequence<IndexStop, StartIndex, IndexPack...> {
      typedef typename Sequence<IndexStop, StartIndex-1, StartIndex, IndexPack...>::type type;
    };

    template <int IndexStop, int ... IndexPack>
    struct Sequence<IndexStop, IndexStop, IndexPack...> {
      typedef Sequence<IndexStop, IndexStop, IndexPack...> type;
    };

    template <int IndexStop>
    struct Sequence<IndexStop, -1> {
      typedef Sequence<IndexStop> type;
    };

    template <int IndexStop>
    struct Sequence<IndexStop, IndexStop-1> {
      typedef Sequence<IndexStop> type;
    };

  } // Template namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__TEMPLATE__SEQUENCE_HPP___
