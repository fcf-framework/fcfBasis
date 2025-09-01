#ifndef ___FCF_BASIS__BITS__TYPE_INITIALIZER_HPP___
#define ___FCF_BASIS__BITS__TYPE_INITIALIZER_HPP___

#include "../../macro.hpp"
#include "../../Details/Variant/NobodyWrapper.hpp"
#include "../../Details/Variant/Storage.hpp"
#include "../../Details/Variant/NobodyWrapperRegistrator.hpp"
#include "../../bits/TemplateSpecializationInitializer.hpp"
#include "Type.hpp"
#include <iostream>
namespace fcf {
  
  
  namespace NDetails {
    
    template <typename Ty, bool IsRef>
    struct TypeInitializerHandler {
      inline void operator()(unsigned int a_typeIndex){
        typedef typename std::decay<typename std::decay<Ty>::type>::type simple_type;
        ::fcf::Details::Basis::Variant::NobodyWrapperRegistrator<Ty>();
        TemplateSpecializationInitializer<Ty>()();
      }
    };

    template <typename Ty>
    struct TypeInitializerHandler<Ty, true> {
      inline void operator()(unsigned int a_typeIndex){
      }
    };


  };
  
  template <typename Ty>
  struct TypeInitializer {
    TypeInitializer() {
      unsigned int index = ::fcf::Type<Ty>().index();
      if ((index & 0xce000000) == 0) { // if not ref and not const
        typedef typename std::decay<typename std::decay<Ty>::type>::type simple_type;
        NDetails::TypeInitializerHandler<simple_type, std::is_reference<simple_type>::value>()(index);
      }
    }
  };
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__TYPE_INITIALIZER_HPP___

