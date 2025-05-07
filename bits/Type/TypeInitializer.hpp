#ifndef ___FCF_BASIS__BITS__TYPE_INITIALIZER_HPP___
#define ___FCF_BASIS__BITS__TYPE_INITIALIZER_HPP___

#include "../../macro.hpp"
#include "../../Details/Variant/NobodyWrapper.hpp"
#include "../../Details/Variant/Storage.hpp"
#include "../../Details/Variant/NobodyWrapperRegistrator.hpp"
#include "../../bits/TemplateSpecializationInitializer.hpp"
#include "Type.hpp"

namespace fcf {
  template <typename Ty>
  struct TypeInitializer {
    TypeInitializer() {
      unsigned int index = ::fcf::Type<Ty>().index();
      if ((index & 0xfe000000) == 0) { // if not ref, not ptr and not const
        typedef typename std::decay<typename std::remove_pointer<typename std::remove_pointer<typename std::decay<Ty>::type>::type>::type>::type simple_type;
        ::fcf::Details::Basis::Variant::NobodyWrapperRegistrator<simple_type>();
        TemplateSpecializationInitializer<Ty>()();
      }
    }
  };
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__TYPE_INITIALIZER_HPP___

