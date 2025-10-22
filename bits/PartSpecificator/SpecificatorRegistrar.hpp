#ifndef ___FCF__BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_HPP___
#define ___FCF__BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_HPP___

namespace fcf{

  template <typename TContainer, typename TSpecificator>
  class SpecificatorRegistrar {
    public:
      SpecificatorRegistrar() {
        unsigned int specificatorIndex = Type<TSpecificator>().index();
        fcf::SpecificatorTypeInfo sti;
        sti.argc = _getArgCount(
                              Type<TContainer, TSpecificator>::resolve) - 1;
        sti.resolve = (void*)Type<TContainer, TSpecificator>::resolve;
        Type<TContainer>()._info->specificators[specificatorIndex] = sti;
      }
    protected:
      template <typename... TArgPack>
      unsigned int _getArgCount(void (*a_func)(TArgPack... a_argPack)){
        return sizeof...(TArgPack);
      }
  };

} // fcf namespace

#endif // #ifndef ___FCF__BASIS__BITS__PART_SPECIFICATOR__SPECIFICATOR_REGISTRAR_HPP___
