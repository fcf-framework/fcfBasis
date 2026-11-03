#ifndef _FCF_BASIS__BITS__PART_TYPE__TYPE_TRIAL_INITIALIZER_HPP___
#define _FCF_BASIS__BITS__PART_TYPE__TYPE_TRIAL_INITIALIZER_HPP___

#include "../../macro.hpp"
#include "../../bits/PartType/Type.hpp"
#include <iostream>

namespace fcf{

  template <typename Ty, typename>
  struct TypeTrialInitializer {
    TypeTrialInitializer() {
    }
  };

  template <typename Ty>
  struct TypeTrialInitializer<Ty, decltype((void)TypeId<Ty>().index())> {
    TypeTrialInitializer() {
      ::fcf::Type<Ty>::_classInitialize();
    }
  };



} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_TYPE__TYPE_TRIAL_INITIALIZER_HPP___
