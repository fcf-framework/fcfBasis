#ifndef ___FCF_BASIS__DETAILS__INVARIANT_RANGE_CALLER___
#define ___FCF_BASIS__DETAILS__INVARIANT_RANGE_CALLER___


namespace fcf {  
  namespace Details {

    template <typename TExecutor, typename TItem, bool IsContainerItem>
    struct InvariantRangeCaller {
      template <typename TIterator, typename... TArgPack>
      void operator()(TIterator a_begin, TIterator a_end, TArgPack... a_argPack){
        TExecutor().call(a_begin, a_end, a_argPack...);
      }
    };

    template <typename TExecutor, typename TItem>
    struct InvariantRangeCaller<TExecutor, TItem, true> {
      template <typename TIterator, typename... TArgPack>
      void operator()(TIterator a_begin, TIterator a_end, TArgPack... a_argPack) {
        typedef typename Type<TIterator, IterativeSpecificator>::value_type value_type;
        typedef typename Type<value_type>::value_type item_value_type;
        for(; a_begin != a_end; ++a_begin) {
          Details::InvariantRangeCaller<TExecutor, item_value_type, Type<item_value_type>::container >()(std::begin(*a_begin), std::end(*a_begin), a_argPack...);
        }
      }
    };

  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__INVARIANT_RANGE_CALLER___
