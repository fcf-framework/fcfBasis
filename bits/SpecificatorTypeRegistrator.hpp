#ifndef ___FCF_BASIS__BITS__SPECIFICATOR_TYPE_REGISTRATOR_HPP___
#define ___FCF_BASIS__BITS__SPECIFICATOR_TYPE_REGISTRATOR_HPP___

#include "../Type.hpp"
namespace fcf {

  namespace Details {
    namespace SpecificatorTypeRegistrator {

      template <typename... TArgPack>
      unsigned int getArgCount(void (*a_func)(TArgPack... a_argPack)){
        return sizeof...(TArgPack);
      }

    }
  }

  template <typename TContainer, typename TSpecificator>
  class SpecificatorTypeRegistrator {
    public:
      SpecificatorTypeRegistrator() {
        unsigned int specificatorIndex = Type<TSpecificator>::index();
        fcf::SpecificatorTypeInfo sti;
        sti.argc = Details::SpecificatorTypeRegistrator::getArgCount(
                              Type<TContainer, TSpecificator>::resolve) - 1;
        Type<TContainer>::tryInit();
        Type<TContainer>::typeId->_typeSpecificators[specificatorIndex] = sti;
      }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__SPECIFICATOR_TYPE_REGISTRATOR_HPP___
