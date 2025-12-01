#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_REF_REGISTRAR_DEFINITION_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_REF_REGISTRAR_DEFINITION_HPP___

namespace fcf{

  namespace NDetails {

    template <typename Ty, typename TSpecificator, typename = void>
    struct SpecificatorRefRegistrarImpl;

    template <typename RegTy, typename Ty, typename TSpecificator, typename = void>
    struct SpecificatorConstRefRegistrarImpl;

    template <typename Ty, typename TSpecificator, bool Ignore>
    struct SpecificatorRefRegistrar;

  }

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_REF_REGISTRAR_DEFINITION_HPP___
