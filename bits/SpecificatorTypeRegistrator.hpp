#ifndef ___FCF_BASIS__BITS__SPECIFICATOR_TYPE_REGISTRATOR_HPP___
#define ___FCF_BASIS__BITS__SPECIFICATOR_TYPE_REGISTRATOR_HPP___
#include <iostream>
#include "../Type.hpp"

namespace fcf {
// Specificator registrar
// SpecificatorRegistrar
// // SpecificatorRegistrarCaller
 
  namespace Details {
    namespace SpecificatorRegistrar {

      template <typename... TArgPack>
      unsigned int getArgCount(void (*a_func)(TArgPack... a_argPack)){
        return sizeof...(TArgPack);
      }

    }
  }

  template <typename TContainer, typename TSpecificator>
  class SpecificatorRegistrar {
    public:
      SpecificatorRegistrar() {
        unsigned int specificatorIndex = Type<TSpecificator>().index();
        fcf::SpecificatorTypeInfo sti;
        sti.argc = Details::SpecificatorRegistrar::getArgCount(
                              Type<TContainer, TSpecificator>::resolve) - 1;
        sti.resolve = (void*)Type<TContainer, TSpecificator>::resolve;
        Type<TContainer>()._info->specificators[specificatorIndex] = sti;
      }
  };

  template <typename TContainer>
  class SpecificatorRegistrar<TContainer, RawDataSpecificator> {
    public:
      SpecificatorRegistrar() {
        Type<TContainer>()._info->rawDataResolver = (RawDataSpecificator::function_type)resolver;
      }

      static const void* resolver(const void* a_value = 0, unsigned int* a_type = 0, bool* a_invariantType = 0, bool* a_mayBeUnintialized = 0){
        return Type<TContainer, RawDataSpecificator>()((TContainer*)a_value, a_type, a_invariantType, a_mayBeUnintialized);
      }
  };


  template <typename TContainer>
  class SpecificatorRegistrar<TContainer, DynamicIteratorSpecificator> {
    public:
      SpecificatorRegistrar() {
        Type<TContainer>()._info->dynamicIteratorResolver = (DynamicIteratorSpecificator::function_type)resolver;
      }

      static bool resolver(void* a_container, DynamicIteratorInfo* a_dynamicIteratorInfo){
        return Type<TContainer, DynamicIteratorSpecificator>()((TContainer*)a_container, a_dynamicIteratorInfo);
      }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__SPECIFICATOR_TYPE_REGISTRATOR_HPP___
