#ifndef ___FCF_BASIS__DETAILS__INVARIANT_SINGLE_CALLER___
#define ___FCF_BASIS__DETAILS__INVARIANT_SINGLE_CALLER___

namespace fcf {  
  namespace Details {

    template <typename TExecutor, typename TItem, bool IsContainerItem>
    struct InvariantRangeCaller;

    template <typename TExecutor, bool IsContainer = false>
    struct InvariantSingleCaller {
      template <typename TContainer, typename... TArgPack>
      void operator()(TContainer& a_container, TArgPack... a_argPack){
        TExecutor().call(&a_container, &a_container + 1, a_argPack...);
      }
    };

    template <typename TExecutor>
    struct InvariantSingleCaller<TExecutor, true> {
      template <typename TContainer, typename... TArgPack>
      void operator()(TContainer& a_container, TArgPack... a_argPack) {
        typedef typename Type<TContainer>::value_type value_type;
        InvariantRangeCaller<TExecutor, value_type, Type<value_type>::container>()(std::begin(a_container), std::end(a_container), a_argPack...);
      }
    };

  } // Details namespace
} // fcf namespace 

#endif // #ifndef ___FCF_BASIS__DETAILS__INVARIANT_SINGLE_CALLER___
