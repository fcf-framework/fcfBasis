#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_CALL_REGISTRAR_GETTER_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_CALL_REGISTRAR_GETTER_HPP___

#include "SpecificatorCallRegistrarCaller.hpp"

namespace fcf{
  namespace NDetails {

    template <typename Ty, typename TSpecificator, typename = void>
    struct SpecificatorCallRegistrarGetter{
      inline void* operator()(){
        return 0;
      }
    };

    template <typename Ty, typename TSpecificator>
    struct SpecificatorCallRegistrarGetter<Ty, TSpecificator, decltype((void)typename TSpecificator::CallType())>{
      typedef typename MetaTypeFunction<typename TSpecificator::CallType>::ResultType ResultType;
      enum { argCount = MetaTypeFunction<typename TSpecificator::CallType>::argCount };

      inline void* operator()(){
        return SpecificatorCallRegistrarCaller<Ty, TSpecificator>()();
      }
    };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__NDETAILS__SPECIFICATOR_CALL_REGISTRAR_GETTER_HPP___
