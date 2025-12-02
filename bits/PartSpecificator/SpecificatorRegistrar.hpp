#ifndef ___FCF__BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_HPP___
#define ___FCF__BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_HPP___

#include "SpecificatorInfo.hpp"

namespace fcf{

  template <typename TContainer, typename TSpecificator>
  class SpecificatorRegistrar {
    public:
      void operator()(const fcf::SpecificatorInfo& a_si);
  };

} // fcf namespace


#include "SpecificatorRegistrarHandler.hpp"

namespace fcf {

  template <typename TContainer, typename TSpecificator>
  void SpecificatorRegistrar<TContainer, TSpecificator>::operator()(const fcf::SpecificatorInfo& a_si){
    unsigned int specificatorIndex = Type<TSpecificator>().index();
    Type<TContainer>()._info->specificators[specificatorIndex] = a_si;
  }

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_HPP___
