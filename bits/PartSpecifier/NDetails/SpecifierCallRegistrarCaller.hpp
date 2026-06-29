#ifndef _FCF_BASIS__BITS__PART_SPECIFIER__NDETAILS__SPECIFIER_CALL_REGISTRAR_CALLER_HPP___
#define _FCF_BASIS__BITS__PART_SPECIFIER__NDETAILS__SPECIFIER_CALL_REGISTRAR_CALLER_HPP___

#include <tuple>
#include <type_traits>
#include "../../../bits/PartMetaType/MetaTypeRemoveRightReference.hpp"
#include "../../../bits/PartMetaType/MetaTypeFunction.hpp"
#include "../../../bits/PartMetaType/MetaTypeSequence.hpp"

namespace fcf{
  namespace NDetails {

    template <typename Ty, typename TSpecifier>
    struct SpecifierCallRegistrarCaller{
      typedef typename MetaTypeFunction<typename TSpecifier::CallType>::ResultType ResultType;

      inline void* operator()(){
        return (void*)static_cast<typename TSpecifier::CallType>(call);
      }

      template <typename ...TPack>
      static inline ResultType call(TPack... a_argPack){
        typedef decltype(&Type<Ty, TSpecifier>::call)                  MethodType;
        typedef typename MetaTypeFunction<MethodType>::ArgumentsType      MethodArgumentsType;
        typedef typename MetaTypeSequence<0, sizeof...(a_argPack)>::type  SequenceType;
        return callWithConvert(MethodArgumentsType(), SequenceType(), a_argPack...);
      }

      template <typename TArguments, typename ...TMethodArgPack, int ...SequencePack, typename ...TPack>
      static inline ResultType callWithConvert(TArguments, MetaTypeSequence<SequencePack...>, TPack... a_argPack){
        return Type<Ty, TSpecifier>().call(
           (
             typename MetaTypeRemoveRightReference<
                decltype( 
                  std::get<SequencePack>(TArguments())
                )
             >::type
           )
           std::get<SequencePack>(
            std::forward_as_tuple(
              std::forward<TPack>(a_argPack)...
            )
           )...
        );
      }
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_SPECIFIER__NDETAILS__SPECIFIER_CALL_REGISTRAR_CALLER_HPP___
