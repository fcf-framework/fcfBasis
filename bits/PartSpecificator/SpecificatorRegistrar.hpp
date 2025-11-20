#ifndef ___FCF__BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_HPP___
#define ___FCF__BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_HPP___

#include "../PartVariant/VariantPredefinition.hpp"
#include "../PartMetaType/MetaTypeSequence.hpp"
#include "NDetails/SpecificatorRefRegistrar.hpp"

namespace fcf{

  template <typename Ty>
  struct MetaTypeFunction;

  template <typename TResult, typename ...TPack>
  struct MetaTypeFunction<TResult(*)(TPack...)>{
    enum { argCount = sizeof...(TPack) };
    typedef TResult(*Type)(TPack...);
    typedef TResult               ResultType;
    typedef std::tuple<TPack...>  ArgumentsType;
    typedef TResult(*FunctionType)(TPack...);
  };

  template <typename TResult, typename ...TPack>
  struct MetaTypeFunction<TResult(TPack...)>{
    enum { argCount = sizeof...(TPack) };
    typedef TResult(*Type)(TPack...);
    typedef TResult               ResultType;
    typedef std::tuple<TPack...>  ArgumentsType;
    typedef TResult(*FunctionType)(TPack...);
  };

  template <typename TResult, typename TClass, typename ...TPack>
  struct MetaTypeFunction<TResult(TClass::*)(TPack...)>{
    enum { argCount = sizeof...(TPack) };
    typedef TResult(TClass::*Type)(TPack...);
    typedef TResult                         ResultType;
    typedef std::tuple<TPack...>            ArgumentsType;
    typedef TResult(*FunctionType)(TPack...);
    typedef TResult(TClass::*MethodType)(TPack...);
  };

  template <typename TResult, typename TClass, typename ...TPack>
  struct MetaTypeFunction<TResult(TClass::*)(TPack...) const>{
    enum { argCount = sizeof...(TPack) };
    typedef TResult(TClass::*Type)(TPack...);
    typedef TResult                         ResultType;
    typedef std::tuple<TPack...>            ArgumentsType;
    typedef TResult(*FunctionType)(TPack...);
    typedef TResult(TClass::*MethodType)(TPack...);
  };


  namespace NDetails {

    template <typename Ty, typename TSpecificator>
    struct SpecificatorCallRegistrarCaller{
      typedef typename MetaTypeFunction<typename TSpecificator::CallType>::ResultType ResultType;

      inline void operator()(fcf::SpecificatorInfo* a_si){
        typename TSpecificator::CallType func = static_cast<typename TSpecificator::CallType>(call);
        a_si->call = (void*)func;
      }

      template <typename ...TPack>
      static inline ResultType call(TPack... a_argPack){
        typedef decltype(&Type<Ty, TSpecificator>::call)                  MethodType;
        typedef typename MetaTypeFunction<MethodType>::ArgumentsType      MethodArgumentsType;
        typedef typename MetaTypeSequence<0, sizeof...(a_argPack)>::type  SequenceType;
        return callWithConvert(MethodArgumentsType(), SequenceType(), a_argPack...);
      }

      template <int ...SequencePack, typename ...TMethodArgPack, typename ...TPack,
                typename TArguments = std::tuple<TMethodArgPack...>
                >
      static inline ResultType callWithConvert(TArguments, MetaTypeSequence<SequencePack...>, TPack... a_argPack){
        return Type<Ty, TSpecificator>().call(
           (decltype(std::get<SequencePack>(TArguments())))std::get<SequencePack>(std::forward_as_tuple(std::forward<TPack>(a_argPack)...))...
        );
      }
    };

    template <typename Ty, typename TSpecificator, typename = void>
    struct SpecificatorCallRegistrar{
      inline void operator()(fcf::SpecificatorInfo*){
      }
    };

    template <typename Ty, typename TSpecificator>
    struct SpecificatorCallRegistrar<Ty, TSpecificator, decltype((void)typename TSpecificator::CallType())>{
      typedef typename MetaTypeFunction<typename TSpecificator::CallType>::ResultType ResultType;
      enum { argCount = MetaTypeFunction<typename TSpecificator::CallType>::argCount };

      inline void operator()(fcf::SpecificatorInfo* a_si){
        SpecificatorCallRegistrarCaller<Ty, TSpecificator>()(a_si);
      }

    };

  }

  template <typename TContainer, typename TSpecificator>
  class SpecificatorRegistrar {
    public:
      SpecificatorRegistrar() {
        unsigned int specificatorIndex = Type<TSpecificator>().index();
        fcf::SpecificatorInfo sti;
        sti.universalCall = (UniversalCall)SpecificatorRegistrar::universalCall;
        NDetails::SpecificatorCallRegistrar<TContainer, TSpecificator>()(&sti);
        Type<TContainer>()._info->specificators[specificatorIndex] = sti;
        NDetails::SpecificatorRefRegistrar<TContainer, std::is_reference<TContainer>::value>()(sti, specificatorIndex);
      }
    protected:
      static Variant universalCall(TContainer* a_container, Variant* a_argv, size_t a_argc);
  };

} // fcf namespace

#include "../../Variant.hpp"

namespace fcf {

  template <typename TContainer, typename TSpecificator>
  Variant SpecificatorRegistrar<TContainer, TSpecificator>::universalCall(TContainer* a_container, Variant* a_argv, size_t a_argc) {
    return ::fcf::Type<TContainer, TSpecificator>().universalCall(a_container, a_argv, a_argc);
  }


} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_HPP___
