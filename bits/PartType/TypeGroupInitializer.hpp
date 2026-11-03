#ifndef _FCF_BASIS__BITS__PART_TYPE__TYPE_GROUP_INITIALIZER_HPP___
#define _FCF_BASIS__BITS__PART_TYPE__TYPE_GROUP_INITIALIZER_HPP___

#include <type_traits>
#include "TypeTrialInitializer.hpp"
#include "../PartMetaType/MetaTypeClearType.hpp"

namespace fcf{

  template <bool IsTemplate, typename Ty>
  struct TypeGroupInitializer{
    typedef typename MetaTypeClearType<Ty>::Type raw_type;
    TypeGroupInitializer();
  };

  template <bool IsTemplate, typename Ty>
  TypeGroupInitializer<IsTemplate, Ty>::TypeGroupInitializer() {
    { fcf::TypeTrialInitializer<raw_type> var; }
    { fcf::TypeTrialInitializer<raw_type*> var; }
    { fcf::TypeTrialInitializer<raw_type**> var; }
    { fcf::TypeTrialInitializer<raw_type&> var; }
    { fcf::TypeTrialInitializer<raw_type&&> var; }
    { fcf::TypeTrialInitializer<const raw_type*> var; }
    { fcf::TypeTrialInitializer<const raw_type*&> var; }
    { fcf::TypeTrialInitializer<const raw_type**> var; }
    { fcf::TypeTrialInitializer<const raw_type**&> var; }
    { fcf::TypeTrialInitializer<const raw_type&> var; }
    { fcf::TypeTrialInitializer<const raw_type&&> var; }
  }

  template <typename Ty>
  struct TypeGroupInitializer<false, Ty>{
  };

  template <>
  struct TypeGroupInitializer<true, void>{
  };

  template <>
  struct TypeGroupInitializer<false, void>{
  };

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_TYPE__TYPE_GROUP_INITIALIZER_HPP___
