#ifndef _FCF_BASIS__BITS__PART_SPECIFIER__STORED_DATA_TYPE_SPECIFIER_HPP___
#define _FCF_BASIS__BITS__PART_SPECIFIER__STORED_DATA_TYPE_SPECIFIER_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "SpecifierRegistrar.hpp"
#include "../PartType/Type.hpp"
#include "../../PartVariant.hpp"

namespace fcf{

  struct StoredDataTypeSpecifier { 
    typedef TypeIndex (*CallType)();
    typedef TypeIndex (*HandleType)();
  };


  template <typename Ty, typename TSpecifier, typename TArg1 = Nop>
  struct TypeImpl;

  template <typename Ty>
  struct TypeImpl<Ty, StoredDataTypeSpecifier> {

    inline TypeIndex operator()() {
      return Type< typename Type<Ty, StoredDataTypeSpecifier>::type >().index();
    }

    inline TypeIndex call() {
      return Type<Ty, StoredDataTypeSpecifier>()();
    }

    inline Variant universalCall(Ty* /*a_object*/, Variant* /*a_argv*/, size_t /*a_argc*/) {
      return Type<Ty, StoredDataTypeSpecifier>().call();
    }

  };

  template <typename Ty>
  struct Type<Ty, StoredDataTypeSpecifier> : public TypeImpl<Ty, StoredDataTypeSpecifier> {
    typedef Ty type;
  };

  template <>
  struct Type<const char*, StoredDataTypeSpecifier> : public TypeImpl<const char*, StoredDataTypeSpecifier> {
    typedef std::string type;
  };

  template <>
  struct Type<char*, StoredDataTypeSpecifier> : public TypeImpl<char*, StoredDataTypeSpecifier> {
    typedef std::string type;
  };

  template <size_t Size>
  struct Type<char[Size], StoredDataTypeSpecifier> : public TypeImpl<char[Size], StoredDataTypeSpecifier> {
    typedef std::string type;
  };

  template <size_t Size>
  struct Type<const char[Size], StoredDataTypeSpecifier> : public TypeImpl<const char[Size], StoredDataTypeSpecifier> {
    typedef std::string type;
  };


} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_SPECIFIER__STORED_DATA_TYPE_SPECIFIER_HPP___
