#ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_ARGUMENTS_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_ARGUMENTS_HPP___

#include <tuple>
#include "../../../StaticVector.hpp"
#include "../../../Type.hpp"
#include "../../../foreach.hpp"

namespace fcf{
  namespace NDetails {

    struct CallArguments {

      StaticVector<void*, 8>           arguments;
      StaticVector<const TypeInfo*, 8> types;

      template <typename ...TArgPack>
      CallArguments(const TArgPack&... a_argPack)
        : arguments(sizeof...(TArgPack))
        , types(sizeof...(TArgPack)) {
        std::tuple<TArgPack*...>  tuple{(TArgPack*)&a_argPack...};
        foreach(tuple, ArgFiller(this));
      }

      template <typename ...TArgPack>
      CallArguments(std::tuple<TArgPack*...>& a_tuple)
        : arguments(sizeof...(TArgPack))
        , types(sizeof...(TArgPack)) {
        foreach(a_tuple, ArgFiller(this));
      }

      inline const TypeInfo* getTypeInfo(size_t a_index){
        return types[a_index];
      }

      inline void* getArgument(size_t a_index){
        return arguments[a_index];
      }

      inline void setArgument(size_t a_index, void* a_value){
        arguments[a_index] = a_value;
      }

    protected:
      FCF_FOREACH_METHOD_WRAPPER(ArgFiller, CallArguments, _argFiller);
      template <typename TTuple, typename TArg>
      void _argFiller(const TTuple&, size_t a_index, TArg* a_arg) {
        types[a_index] = Type<TArg>().getTypeInfo();
        arguments[a_index] = (void*)a_arg;
      }
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_ARGUMENTS_HPP___
