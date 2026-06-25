#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__STORED_DATA_TYPE_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__STORED_DATA_TYPE_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "SpecificatorRegistrar.hpp"
#include "../PartType/Type.hpp"
#include "../../PartVariant.hpp"

namespace fcf{

  struct StoredDataTypeSpecificator { 
    typedef unsigned int (*CallType)();
    typedef unsigned int (*HandleType)();
  };


  template <typename Ty, typename TSpecificator, typename TArg1 = Nop>
  struct TypeImpl;

  template <typename Ty>
  struct TypeImpl<Ty, StoredDataTypeSpecificator> {

    inline unsigned int operator()() {
      return Type< typename Type<Ty, StoredDataTypeSpecificator>::type >().index();
    }

    inline unsigned int call() {
      return Type<Ty, StoredDataTypeSpecificator>()();
    }

    inline Variant universalCall(Ty* /*a_object*/, Variant* /*a_argv*/, size_t /*a_argc*/) {
      return Type<Ty, StoredDataTypeSpecificator>().call();
    }

  };

  template <typename Ty>
  struct Type<Ty, StoredDataTypeSpecificator> : public TypeImpl<Ty, StoredDataTypeSpecificator> {
    typedef Ty type;
  };

  template <>
  struct Type<const char*, StoredDataTypeSpecificator> : public TypeImpl<const char*, StoredDataTypeSpecificator> {
    typedef std::string type;
  };

  template <>
  struct Type<char*, StoredDataTypeSpecificator> : public TypeImpl<char*, StoredDataTypeSpecificator> {
    typedef std::string type;
  };

  template <size_t Size>
  struct Type<char[Size], StoredDataTypeSpecificator> : public TypeImpl<char[Size], StoredDataTypeSpecificator> {
    typedef std::string type;
  };

  template <size_t Size>
  struct Type<const char[Size], StoredDataTypeSpecificator> : public TypeImpl<const char[Size], StoredDataTypeSpecificator> {
    typedef std::string type;
  };


} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__STORED_DATA_TYPE_SPECIFICATOR_HPP___
