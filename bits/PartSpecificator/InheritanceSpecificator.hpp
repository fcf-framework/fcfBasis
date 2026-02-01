#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__INHERITANCE_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__INHERITANCE_SPECIFICATOR_HPP___

#include <tuple>
#include "../PartType/Type.hpp"
#include "../../StaticVector.hpp"

namespace fcf{

  struct InheritanceSpecificator {
    typedef StaticVector<const TypeInfo*, 4> InheritanceVector;
    typedef InheritanceVector (*CallType)(const void*);
  };

  template <typename Ty>
  struct Type<Ty, InheritanceSpecificator> {
    typedef Nop BaseType;

    inline Variant universalCall(const Ty* /*a_object*/, Variant* /*a_argv*/, size_t /*a_argc*/) const {
      return Variant(InheritanceSpecificator::InheritanceVector());
    }

    inline InheritanceSpecificator::InheritanceVector call() const {
      return InheritanceSpecificator::InheritanceVector();
    }
  };

  template <typename Ty, typename TBase>
  struct TypeImpl<Ty, InheritanceSpecificator, TBase> {
    typedef TBase BaseType;

    struct ContainerValue {
      ContainerValue() {
        value.push_back(Type<TBase>().getTypeInfo());
        InheritanceSpecificator::InheritanceVector bases(Type<TBase, InheritanceSpecificator>().call());
        value.insert(value.end(), bases.begin(), bases.end());
      }
      InheritanceSpecificator::InheritanceVector value;
    };

    inline Variant universalCall(const Ty* /*a_object*/, Variant* /*a_argv*/, size_t /*a_argc*/) const {
      return Type<Ty, InheritanceSpecificator>().call();
    }

    inline InheritanceSpecificator::InheritanceVector call() const {
      static ContainerValue cv;
      return cv.value;
    }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__INHERITANCE_SPECIFICATOR_HPP___
