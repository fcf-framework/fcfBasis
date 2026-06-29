#ifndef _FCF_BASIS__BITS__PART_SPECIFIER__SPECIFIER_REGISTRAR_GETTER_HPP___
#define _FCF_BASIS__BITS__PART_SPECIFIER__SPECIFIER_REGISTRAR_GETTER_HPP___

#include "SpecifierInfo.hpp"
#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../PartVariant.hpp"
namespace fcf{

  template <typename Ty, typename TSpecifier>
  struct SpecifierRegistrarGetter {
    enum { defaultImplementationMarker = 1 };

    SpecifierInfo operator()(){
      fcf::SpecifierInfo sti;
      sti.universalCall = (UniversalCall)universalCall;
      sti.call          = ::fcf::NDetails::SpecifierCallRegistrarGetter<Ty, TSpecifier>()();
      return sti;
    }

    static Variant universalCall(Ty* a_container, Variant* a_argv, size_t a_argc) {
      return ::fcf::Type<Ty, TSpecifier>().universalCall(a_container, a_argv, a_argc);
    }
  };
  
} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_SPECIFIER__SPECIFIER_REGISTRAR_GETTER_HPP___
