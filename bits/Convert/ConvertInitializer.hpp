#ifndef ___FCF_BASIS__BITS___CONVERT_CONVERT_INITIALIZER_HPP___
#define ___FCF_BASIS__BITS___CONVERT_CONVERT_INITIALIZER_HPP___

#include "Details/ConvertInitializer.hpp"

namespace fcf {
  template <typename... TypesPack>
  struct ConvertInitializer {
     ConvertInitializer(){
      Details::Basis::Convert::ConvertInitializerHandlerL2<TypesPack...> handler2;
      Details::Basis::Convert::ConvertInitializerHandlerL1<TypesPack...>::call(handler2);
    }
  };
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS___CONVERT_CONVERT_INITIALIZER_HPP___
