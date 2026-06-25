#ifndef ___FCF__BASIS__BITS__PART_SPECIFIER__SPECIFIER_REGISTRAR_HPP___
#define ___FCF__BASIS__BITS__PART_SPECIFIER__SPECIFIER_REGISTRAR_HPP___

#include "SpecifierInfo.hpp"

namespace fcf{

  template <typename TContainer, typename TSpecifier>
  class SpecifierRegistrar {
    public:
      void operator()(const fcf::SpecifierInfo& a_si);
  };

} // fcf namespace


#include "SpecifierRegistrarHandler.hpp"

namespace fcf {

  template <typename TContainer, typename TSpecifier>
  void SpecifierRegistrar<TContainer, TSpecifier>::operator()(const fcf::SpecifierInfo& a_si){
    unsigned int specifierIndex = Type<TSpecifier>().index();
    Type<TContainer>()._info->specifiers[specifierIndex] = a_si;
  }

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_SPECIFIER__SPECIFIER_REGISTRAR_HPP___
