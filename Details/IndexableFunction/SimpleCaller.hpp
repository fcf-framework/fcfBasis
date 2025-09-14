#ifndef ___FCF_BASIS__DETAILS__INDEXABLE_FUNCTION__SIMPLE_CALLER_HPP___
#define ___FCF_BASIS__DETAILS__INDEXABLE_FUNCTION__SIMPLE_CALLER_HPP___

#include <type_traits>

namespace fcf {
  namespace Details {
    namespace IndexableFunction {

      template <typename TRes, typename... TArgPack>
      struct SimpleCaller;

      template <typename TRes, typename... TArgPack>
      struct SimpleCaller<TRes (*)(TArgPack...)>{
        typedef TRes (*function_type)(TArgPack...);
        static TRes call(function_type a_function, const typename std::remove_cv< typename std::remove_reference<TArgPack>::type >::type&... a_argPack){
          return a_function(a_argPack...);
        }
      };

      template <typename TFunc>
      auto getSimpleCaller(TFunc a_func) -> decltype(&SimpleCaller<TFunc>::call) {
        return &SimpleCaller<TFunc>::call;
      }

      template <typename TFunc>
      void* getListCaller(TFunc a_func) {
        void* ptr;
        return ptr;
      }

    } // namespace IndexableFunction
  } // namespace Details
} // namespace fcf

#endif // #ifndef ___FCF_BASIS__BITS__INDEXABLE_FUNCTION__SIMPLE_CALLER_HPP___
