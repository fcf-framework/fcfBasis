#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__INHERITANCE_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__INHERITANCE_SPECIFICATOR_HPP___

#include <tuple>
#include "../PartType/PartType.hpp"
#include "../../PartStaticVector.hpp"

namespace fcf{

  struct InheritanceSpecificator {
    typedef StaticVector<const TypeInfo*, 4> InheritanceVector;
    typedef InheritanceVector (*CallType)();
    typedef InheritanceVector (*HandleType)();
  };

  template <typename Ty>
  struct Type<Ty, InheritanceSpecificator> {
    inline InheritanceSpecificator::InheritanceVector operator()() {
      return InheritanceSpecificator::InheritanceVector();
    }

    inline InheritanceSpecificator::InheritanceVector call() {
      return Type<Ty, InheritanceSpecificator>()();
    }

    inline Variant universalCall(const Ty* /*a_object*/, Variant* /*a_argv*/, size_t /*a_argc*/) {
      return Variant(InheritanceSpecificator::InheritanceVector());
    }

  };

  template <typename Ty, typename TBase>
  struct TypeImpl<Ty, InheritanceSpecificator, TBase> {
    struct ContainerValue {
      ContainerValue() {
        value.push_back(Type<TBase>().typeInfo());
        InheritanceSpecificator::InheritanceVector bases(Type<TBase, InheritanceSpecificator>().call());
        value.insert(value.end(), bases.begin(), bases.end());
      }
      InheritanceSpecificator::InheritanceVector value;
    };

    InheritanceSpecificator::InheritanceVector operator()(){
      static ContainerValue cv;
      return cv.value;
    }

    inline InheritanceSpecificator::InheritanceVector call() {
      return Type<Ty, InheritanceSpecificator>()();
    }

    inline Variant universalCall(const Ty* /*a_object*/, Variant* /*a_argv*/, size_t /*a_argc*/) {
      return Type<Ty, InheritanceSpecificator>().call();
    }

  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__INHERITANCE_SPECIFICATOR_HPP___
