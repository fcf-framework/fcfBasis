#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_CALL_REGISTRAR_CALLER_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_CALL_REGISTRAR_CALLER_HPP___

#include <tuple>
#include <type_traits>
#include "../../../bits/PartMetaType/MetaTypeFunction.hpp"
#include "../../../bits/PartMetaType/MetaTypeSequence.hpp"

namespace fcf{
  namespace NDetails {

    template <typename Ty, typename TSpecificator>
    struct SpecificatorCallRegistrarCaller{
      typedef typename MetaTypeFunction<typename TSpecificator::CallType>::ResultType ResultType;

      inline void* operator()(){
        return (void*)static_cast<typename TSpecificator::CallType>(call);
      }

      template <typename ...TPack>
      static inline ResultType call(TPack... a_argPack){
        typedef decltype(&Type<Ty, TSpecificator>::call)                  MethodType;
        typedef typename MetaTypeFunction<MethodType>::ArgumentsType      MethodArgumentsType;
        typedef typename MetaTypeSequence<0, sizeof...(a_argPack)>::type  SequenceType;
        return callWithConvert(MethodArgumentsType(), SequenceType(), a_argPack...);
      }

      template <typename TArguments, typename ...TMethodArgPack, int ...SequencePack, typename ...TPack>
      static inline ResultType callWithConvert(TArguments, MetaTypeSequence<SequencePack...>, TPack... a_argPack){
        return Type<Ty, TSpecificator>().call(
           (decltype(std::get<SequencePack>(TArguments())))std::get<SequencePack>(std::forward_as_tuple(std::forward<TPack>(a_argPack)...))...
        );
      }
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_CALL_REGISTRAR_CALLER_HPP___
