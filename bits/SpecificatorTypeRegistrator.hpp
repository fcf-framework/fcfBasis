#ifndef ___FCF_BASIS__BITS__SPECIFICATOR_TYPE_REGISTRATOR_HPP___
#define ___FCF_BASIS__BITS__SPECIFICATOR_TYPE_REGISTRATOR_HPP___
#include <iostream>
#include "../Type.hpp"
#include "PartSpecificator/SpecificatorRegistrar.hpp"

namespace fcf {

  namespace Details {
    namespace SpecificatorRegistrar {

      template <typename... TArgPack>
      unsigned int getArgCount(void (*a_func)(TArgPack... a_argPack)){
        return sizeof...(TArgPack);
      }

    }
  }

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

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__SPECIFICATOR_TYPE_REGISTRATOR_HPP___
