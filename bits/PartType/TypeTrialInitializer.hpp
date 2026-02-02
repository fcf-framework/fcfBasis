#ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_TRIAL_INITIALIZER_HPP___
#define ___FCF_BASIS__BITS__PART_TYPE__TYPE_TRIAL_INITIALIZER_HPP___


#include "../../macro.hpp"
#include "../../bits/PartType/Type.hpp"
#include <iostream>

namespace fcf{

  template <typename TSelf, typename Ty, typename = void>
  struct TypeTrialInitializer {
    TypeTrialInitializer() {
    }
  };

  template <typename Ty>
  struct TypeTrialInitializer<Ty, Ty, decltype((void)TypeId<Ty>().index())> {
    TypeTrialInitializer() {
    }
  };

  template <typename TSelf, typename Ty>
  struct TypeTrialInitializer<TSelf, Ty, decltype((void)TypeId<Ty>().index())> {
    TypeTrialInitializer() {
      ::fcf::Type<Ty>().index();
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_TYPE__TYPE_TRIAL_INITIALIZER_HPP___
