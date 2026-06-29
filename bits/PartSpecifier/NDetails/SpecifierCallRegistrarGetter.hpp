#ifndef _FCF_BASIS__BITS__PART_SPECIFIER__NDETAILS__SPECIFIER_CALL_REGISTRAR_GETTER_HPP___
#define _FCF_BASIS__BITS__PART_SPECIFIER__NDETAILS__SPECIFIER_CALL_REGISTRAR_GETTER_HPP___

#include "SpecifierCallRegistrarCaller.hpp"

namespace fcf{
  namespace NDetails {

    template <typename Ty, typename TSpecifier, typename = void>
    struct SpecifierCallRegistrarGetter{
      inline void* operator()(){
        return 0;
      }
    };

    template <typename Ty, typename TSpecifier>
    struct SpecifierCallRegistrarGetter<Ty, TSpecifier, decltype((void)typename TSpecifier::CallType())>{
      typedef typename MetaTypeFunction<typename TSpecifier::CallType>::ResultType ResultType;
      enum { argCount = MetaTypeFunction<typename TSpecifier::CallType>::argCount };

      inline void* operator()(){
        return SpecifierCallRegistrarCaller<Ty, TSpecifier>()();
      }
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_SPECIFIER__NDETAILS__SPECIFIER_CALL_REGISTRAR_GETTER_HPP___
