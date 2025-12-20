#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_GETTER_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_GETTER_HPP___

#include "SpecificatorInfo.hpp"
#include "../../bits/PartTypes/UniversalCall.hpp"
#include "../../Variant.hpp"
namespace fcf{

  template <typename Ty, typename TSpecificator>
  struct SpecificatorRegistrarGetter {
    enum { defaultImplementationMarker = 1 };

    SpecificatorInfo operator()(){
      fcf::SpecificatorInfo sti;
      sti.universalCall = (UniversalCall)universalCall;
      sti.call          = ::fcf::NDetails::SpecificatorCallRegistrarGetter<Ty, TSpecificator>()();
      return sti;
    }

    static Variant universalCall(Ty* a_container, Variant* a_argv, size_t a_argc) {
      return ::fcf::Type<Ty, TSpecificator>().universalCall(a_container, a_argv, a_argc);
    }
  };
  
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_GETTER_HPP___
