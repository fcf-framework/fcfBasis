#ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_WRAPPER_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_WRAPPER_HPP___

#include <tuple>
#include <type_traits>
#include "../../../bits/PartMetaType/MetaTypeSequence.hpp"
#include "../../../Variant.hpp"

namespace fcf { 
  namespace NDetails {

    template <typename TResult, typename ...TArgPack>
    struct CallWrapper;

    template <typename TResult, typename ...TArgPack>
    struct CallWrapper<TResult (TArgPack...)> {
      public:
        typedef void (*wrapper_type)(void*, void**);
        typedef Variant (*rwrapper_type)(void*, void**);
        typedef TResult (*function_type)(TArgPack...);

        static void call(function_type a_function, void** a_args){
          typedef typename MetaTypeSequence<0, sizeof...(TArgPack)>::type sequence_type;
          _call(a_function, a_args, sequence_type());
        }

        static Variant rcall(function_type a_function, void** a_args){
          typedef typename MetaTypeSequence<0, sizeof...(TArgPack)>::type sequence_type;
          return _rcall(a_function, a_args, sequence_type());
        }

        static inline wrapper_type getWrapper(){
          void (*ptr)(function_type, void**) = CallWrapper::call;
          return (wrapper_type)ptr;
        }

        static inline rwrapper_type getRWrapper(){
          Variant (*ptr)(function_type, void**) = CallWrapper::rcall;
          return (rwrapper_type)ptr;
        }

      protected:
        template <int... SequencePack>
        static inline void _call(function_type a_function, void** a_args, MetaTypeSequence<SequencePack...> /*a_sequence*/){
          typedef std::tuple<TArgPack...> tuple_type;
          a_function(*(typename std::remove_cv< typename std::remove_reference< typename std::tuple_element<SequencePack, tuple_type>::type >::type >::type  *)a_args[SequencePack]...);
        }

        template <int... SequencePack>
        static inline Variant _rcall(function_type a_function, void** a_args, MetaTypeSequence<SequencePack...> /*a_sequence*/){
          typedef std::tuple<TArgPack...> tuple_type;
          Variant result(a_function(*(typename std::remove_cv< typename std::remove_reference< typename std::tuple_element<SequencePack, tuple_type>::type >::type >::type  *)a_args[SequencePack]...));
          return result;
        }

    };

    template <typename ...TArgPack>
    struct CallWrapper<void (TArgPack...)> {
      public:
        typedef void (*wrapper_type)(void*, void**);
        typedef Variant (*rwrapper_type)(void*, void**);
        typedef void (*function_type)(TArgPack...);

        static void call(function_type a_function, void** a_args){
          typedef typename MetaTypeSequence<0, sizeof...(TArgPack)>::type sequence_type;
          _call(a_function, a_args, sequence_type());
        }

        static Variant rcall(function_type a_function, void** a_args){
          typedef typename MetaTypeSequence<0, sizeof...(TArgPack)>::type sequence_type;
          return _rcall(a_function, a_args, sequence_type());
        }

        static inline wrapper_type getWrapper(){
          void (*ptr)(function_type, void**) = CallWrapper::call;
          return (wrapper_type)ptr;
        }

        static inline rwrapper_type getRWrapper(){
          Variant (*ptr)(function_type, void**) = CallWrapper::rcall;
          return (rwrapper_type)ptr;
        }

      protected:
        template <int... SequencePack>
        static inline void _call(function_type a_function, void** a_args, MetaTypeSequence<SequencePack...> /*a_sequence*/){
          typedef std::tuple<TArgPack...> tuple_type;
          a_function(*(typename std::remove_cv< typename std::remove_reference< typename std::tuple_element<SequencePack, tuple_type>::type >::type >::type  *)a_args[SequencePack]...);
        }

        template <int... SequencePack>
        static inline Variant _rcall(function_type a_function, void** a_args, MetaTypeSequence<SequencePack...> /*a_sequence*/){
          typedef std::tuple<TArgPack...> tuple_type;
          a_function(*(typename std::remove_cv< typename std::remove_reference< typename std::tuple_element<SequencePack, tuple_type>::type >::type >::type  *)a_args[SequencePack]...);
          return Variant();
        }

    };

    template <typename TResult, typename ...TArgPack>
    struct CallWrapper<TResult (*)(TArgPack...)> : public CallWrapper<TResult (TArgPack...)> {
      typedef CallWrapper<TResult (TArgPack...)> base_type;
      using typename base_type::wrapper_type;
      using typename base_type::function_type;
    };

    template <typename ...TArgPack>
    struct CallWrapper<void (*)(TArgPack...)> : public CallWrapper<void (TArgPack...)> {
      typedef CallWrapper<void (TArgPack...)> base_type;
      using typename base_type::wrapper_type;
      using typename base_type::function_type;
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_WRAPPER_HPP___
