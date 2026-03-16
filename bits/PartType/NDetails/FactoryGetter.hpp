#ifndef ___FCF_BASIS__BITS__PART_TYPE__NDETAILS__FACTORY_GETTER_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__NDETAILS__FACTORY_GETTER_HPP___

#include "../../bits/PartType/TypeFactory.hpp"

namespace fcf{
  namespace NDetails {

    template <bool IsPointer, typename Ty>
    struct FactoryGetter2{
      inline static BaseTypeFactory* get(){
        return getTypeFactory< Ty >();
      }
    };

    template <typename Ty>
    struct FactoryGetter2<true, Ty>{
      inline static BaseTypeFactory* get(){
        return getTypeFactory< void*& >();
      }
    };

    template <bool IsReference, typename Ty>
    struct FactoryGetter{
      inline static BaseTypeFactory* get(){
        typedef typename std::remove_reference<Ty>::type UnrefType;
        return FactoryGetter2< std::is_pointer<UnrefType>::value && std::is_reference<Ty>::value, Ty >::get();
      }
    };

    template <typename Ty>
    struct FactoryGetter<true, Ty>{
      inline static BaseTypeFactory* get(){
        return getTypeFactory< int*  >();
      }
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__NDETAILS__FACTORY_GETTER_HPP___
