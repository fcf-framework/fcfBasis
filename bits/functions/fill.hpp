#ifndef ___FCF_BASIS__BITS__FUNCTIONS__FILL_HPP___
#define ___FCF_BASIS__BITS__FUNCTIONS__FILL_HPP___

#include "../../InvariantCaller.hpp"

namespace fcf {

    namespace Details {
      struct FillExecutor {
        template <typename TIterator, typename TValue>
        void call(TIterator a_begin, TIterator a_end, const TValue& a_value) {
          for(; a_begin != a_end; ++a_begin) {
            *a_begin = a_value;
          }
        }
        template <typename TContainer, typename TIterator>
        void callA(TContainer& a_container, TIterator a_begin, TIterator a_end) {
          InvariantCaller<FillExecutor>().rangeCall(a_begin, a_end, Type<TContainer, ValueSpecificator>().value(a_container));
        }
      };
    }

    template <typename TIterator, typename TValue>
    void fill(TIterator a_begin, TIterator a_end, const TValue& a_value) {
      InvariantCaller<Details::FillExecutor>().rangeCall(a_begin, a_end, a_value);
    }

    template <typename TContainer, typename TValue>
    void fill(TContainer& a_container, const TValue& a_value) {
      InvariantCaller<Details::FillExecutor>().call(a_container, a_value);
    }

    template <typename TContainer>
    void fill(TContainer& a_container) {
      InvariantCaller<Details::FillExecutor>().callA<ValueSpecificator>(a_container);
    }

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__FUNCTIONS__FILL_HPP___

