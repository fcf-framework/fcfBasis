#ifndef _FCF_BASIS__BITS__PART_SPECIFIER__NDETAILS__SPECIFIER_REF_REGISTRAR_DEFINITION_HPP___
#define _FCF_BASIS__BITS__PART_SPECIFIER__NDETAILS__SPECIFIER_REF_REGISTRAR_DEFINITION_HPP___

namespace fcf{

  namespace NDetails {

    template <typename Ty, typename TSpecifier, typename = void>
    struct SpecifierRefRegistrarImpl;

    template <typename RegTy, typename Ty, typename TSpecifier, typename = void>
    struct SpecifierRegistrarIfTypeDeclaredImpl;

    template <typename Ty, typename TSpecifier, bool Ignore>
    struct SpecifierRefRegistrar;

  }

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_SPECIFIER__NDETAILS__SPECIFIER_REF_REGISTRAR_DEFINITION_HPP___
