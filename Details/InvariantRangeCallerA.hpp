#ifndef ___FCF_BASIS__DETAILS__INVARIANT_RANGE_CALLER_A___
#define ___FCF_BASIS__DETAILS__INVARIANT_RANGE_CALLER_A___

namespace fcf {  
  namespace Details {

    template <typename TSpecificator, typename TExecutor, typename TItem, bool IsContainerItem, bool EnableValue = false>
    struct InvariantRangeCallerA;

    template <typename TSpecificator, typename TExecutor, typename TItem, bool IsContainerItem>
    struct InvariantRangeCallerA<TSpecificator, TExecutor, TItem, IsContainerItem, true> {
      template <typename TContainer, typename TIterator, typename... TArgPack>
      void operator()(TContainer& a_container, TIterator a_begin, TIterator a_end, TArgPack... a_argPack){
        TExecutor().callA(a_container, a_begin, a_end, a_argPack...);
      }
    };

    template <typename TSpecificator, typename TExecutor, typename TItem>
    struct InvariantRangeCallerA<TSpecificator, TExecutor, TItem, true, false> {
      template <typename TContainer, typename TIterator, typename... TArgPack>
      void operator()(TContainer& a_container, TIterator a_begin, TIterator a_end, TArgPack... a_argPack) {
        typedef typename Type<TIterator, IterativeSpecificator>::value_type value_type;
        typedef typename Type<value_type>::value_type item_value_type;
        for(; a_begin != a_end; ++a_begin) {
          Details::InvariantRangeCallerA<
                TSpecificator, 
                TExecutor, 
                item_value_type, 
                Type<item_value_type>::container, 
                Type<value_type, TSpecificator>::enable 
                >()(
                    *a_begin, 
                    std::begin(*a_begin), 
                    std::end(*a_begin), 
                    a_argPack...
                );
        }
      }
    };

  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__INVARIANT_RANGE_CALLER_A___
