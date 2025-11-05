#ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_WRAPPER_HPP___
#define ___FCF__BASIS__BITS__CALL__DETAILS__CALL_WRAPPER_HPP___

#include <tuple>
#include <type_traits>
#include "../../../bits/PartMetaType/MetaTypeSequence.hpp"

namespace fcf {
  namespace Details {

    template <typename TResult, typename ...TArgPack>
    struct CallWrapper;

    template <typename TResult, typename ...TArgPack>
    struct CallWrapper<TResult (TArgPack...)> {
      public:
        typedef void (*wrapper_type)(void*, void**);
        typedef TResult (*function_type)(TArgPack...);

        static void call(function_type a_function, void** a_args){
          typedef typename MetaTypeSequence<0, sizeof...(TArgPack)>::type sequence_type;
          _call(a_function, a_args, sequence_type());
        }

        static inline wrapper_type getWrapper(){
          void (*ptr)(function_type, void**) = CallWrapper::call;
          return (wrapper_type)ptr;
        }

      protected:
        template <int... SequencePack>
        static inline void _call(function_type a_function, void** a_args, MetaTypeSequence<SequencePack...> a_sequence){
          typedef std::tuple<TArgPack...> tuple_type;
          a_function(*(typename std::remove_cv< typename std::remove_reference< typename std::tuple_element<SequencePack, tuple_type>::type >::type >::type  *)a_args[SequencePack]...);
        }
    };

    template <typename TResult, typename ...TArgPack>
    struct CallWrapper<TResult (*)(TArgPack...)> : public CallWrapper<TResult (TArgPack...)> {
      typedef CallWrapper<TResult (TArgPack...)> base_type;
      using base_type::wrapper_type;
      using base_type::function_type;
    };

  } // Details namespace
} // fcf namespac

#endif // #ifndef ___FCF__BASIS__BITS__CALL__DETAILS__CALL_WRAPPER_HPP___

