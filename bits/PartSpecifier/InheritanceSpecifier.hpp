#ifndef _FCF_BASIS__BITS__PART_SPECIFIER__INHERITANCE_SPECIFIER_HPP___
#define _FCF_BASIS__BITS__PART_SPECIFIER__INHERITANCE_SPECIFIER_HPP___

#include <tuple>
#include "../PartType/PartType.hpp"
#include "../../PartStaticVector.hpp"

namespace fcf{

  struct InheritanceSpecifier {
    typedef StaticVector<const TypeInfo*, 4> InheritanceVector;
    typedef InheritanceVector (*CallType)();
    typedef InheritanceVector (*HandleType)();
  };

  template <typename Ty>
  struct Type<Ty, InheritanceSpecifier> {
    inline InheritanceSpecifier::InheritanceVector operator()() {
      return InheritanceSpecifier::InheritanceVector();
    }

    inline InheritanceSpecifier::InheritanceVector call() {
      return Type<Ty, InheritanceSpecifier>()();
    }

    inline Variant universalCall(const Ty* /*a_object*/, Variant* /*a_argv*/, size_t /*a_argc*/) {
      return Variant(InheritanceSpecifier::InheritanceVector());
    }

  };

  template <typename Ty, typename TBase>
  struct TypeImpl<Ty, InheritanceSpecifier, TBase> {
    struct ContainerValue {
      ContainerValue() {
        value.push_back(Type<TBase>().typeInfo());
        InheritanceSpecifier::InheritanceVector bases(Type<TBase, InheritanceSpecifier>().call());
        value.insert(value.end(), bases.begin(), bases.end());
      }
      InheritanceSpecifier::InheritanceVector value;
    };

    InheritanceSpecifier::InheritanceVector operator()(){
      static ContainerValue cv;
      return cv.value;
    }

    inline InheritanceSpecifier::InheritanceVector call() {
      return Type<Ty, InheritanceSpecifier>()();
    }

    inline Variant universalCall(const Ty* /*a_object*/, Variant* /*a_argv*/, size_t /*a_argc*/) {
      return Type<Ty, InheritanceSpecifier>().call();
    }

  };

} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_SPECIFIER__INHERITANCE_SPECIFIER_HPP___
