#ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_ARGUMENTS_HPP___
#define ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_ARGUMENTS_HPP___

#include <tuple>
#include "../../../StaticVector.hpp"
#include "../../../Type.hpp"
#include "../../../foreach.hpp"

namespace fcf{
  namespace NDetails {

    struct CallArguments {

      struct ArgumentInfo {
        unsigned int    typeIndex;
        const TypeInfo* typeInfo;
      };

      StaticVector<void*, 8*3> _arguments;
      ArgumentInfo*            _info;
      size_t                   _size;

      template <typename ...TArgPack>
      CallArguments(const TArgPack&... a_argPack)
        : _arguments(sizeof...(TArgPack)*3)
        , _info((ArgumentInfo*)&_arguments[sizeof...(TArgPack)])
        , _size(sizeof...(TArgPack)) {
        std::tuple<TArgPack*...>  tuple{(TArgPack*)&a_argPack...};
        foreach(tuple, ArgFiller(this));
      }

      template <typename ...TArgPack>
      CallArguments(std::tuple<TArgPack*...>& a_tuple)
        : _arguments(sizeof...(TArgPack)*3)
        , _info((ArgumentInfo*)&_arguments[sizeof...(TArgPack)])
        , _size(sizeof...(TArgPack)) {
        foreach(a_tuple, ArgFiller(this));
      }

      inline size_t size() const{
        return _size;
      }

      inline unsigned int getTypeIndex(size_t a_index) const{
        return _info[a_index].typeIndex;
      }

      inline const TypeInfo* getTypeInfo(size_t a_index){
        ArgumentInfo& arg = _info[a_index];
        if (arg.typeInfo->index != arg.typeIndex) {
          arg.typeInfo = fcf::getTypeInfo(arg.typeIndex);
        }
        return arg.typeInfo;
      }

      inline void* getArgument(size_t a_index){
        return _arguments[a_index];
      }

      inline void** getArguments(){
        return &_arguments[0];
      }


    protected:
      FCF_FOREACH_METHOD_WRAPPER(ArgFiller, CallArguments, _argFiller);
      template <typename TTuple, typename TArg>
      void _argFiller(const TTuple&, size_t a_index, TArg* a_arg) {
        _arguments[a_index] = (void*)a_arg;
        ArgumentInfo& ai = _info[a_index];
        ai.typeInfo = Type<TArg>().getTypeInfo();
        ai.typeIndex = ai.typeInfo->index;
      }
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CALL__NDETAILS__CALL_ARGUMENTS_HPP___
