#ifndef ___FCF_BASIS__INVARIANT_CALLER___
#define ___FCF_BASIS__INVARIANT_CALLER___

#include "./Type.hpp"
#include "./Details/InvariantSingleCaller.hpp"
#include "./Details/InvariantRangeCaller.hpp"
#include "./Details/InvariantRangeCallerA.hpp"

namespace fcf {  

  template <typename TExecutor>
  struct InvariantCaller {
    template <typename TContainer, typename... TArgPack>
    void call(TContainer& a_container, TArgPack... a_argPack){
      Details::InvariantSingleCaller<TExecutor, Type<TContainer>::container>()(a_container, a_argPack...);
    }
    template <typename TSpecificator, typename TContainer, typename... TArgPack>
    void callA(TContainer& a_container, TArgPack... a_argPack){
      typedef typename Type<TContainer>::value_type item_value_type;
      Details::InvariantRangeCallerA<
        TSpecificator, 
        TExecutor, 
        item_value_type,
        Type<TContainer>::container,
        Type<TContainer, TSpecificator>::enable
        >()(a_container, std::begin(a_container), std::end(a_container), a_argPack...);
    }
    template <typename TIterator, typename... TArgPack>
    void rangeCall(TIterator a_begin, TIterator a_end, TArgPack... a_argPack){
      typedef typename Type<TIterator, IteratorSpecificator>::value_type item_value_type;
      Details::InvariantRangeCaller<TExecutor, item_value_type, Type<item_value_type>::container>()(a_begin, a_end, a_argPack...);
    }
    template <typename TSpecificator, typename TIterator, typename... TArgPack>
    void rangeCallA(TIterator a_begin, TIterator a_end, TArgPack... a_argPack){
      typedef typename Type<TIterator, IteratorSpecificator>::value_type item_value_type;
      Nop nop;
      Details::InvariantRangeCallerA<
        TSpecificator, 
        TExecutor, 
        item_value_type,
        true,
        false
        >()(nop, a_begin, a_end, a_argPack...);
    }
  };
  
} // fcf namespace


#endif // #ifndef ___FCF_BASIS__INVARIANT_CALLER___
