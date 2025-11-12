#ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__STORED_DATA_TYPE_SPECIFICATOR_HPP___
#define ___FCF_BASIS__BITS__PART_SPECIFICATOR__STORED_DATA_TYPE_SPECIFICATOR_HPP___

#include "../../bits/PartTypes/UniversalCall.hpp"
#include "SpecificatorRegistrar.hpp"
#include "../PartType/Type.hpp"
#include "../../Variant.hpp"

namespace fcf{

  struct StoredDataTypeSpecificator { };


  template <typename Ty, typename TSpecificator>
  struct TypeImpl;

  template <typename Ty>
  struct TypeImpl<Ty, StoredDataTypeSpecificator> {
    enum { enable = true };

    inline Variant universalCall(Ty* a_object, Variant* /*a_argv*/, size_t /*a_argc*/) const {
      return Type<Ty, StoredDataTypeSpecificator>().call(a_object);
    }

    inline unsigned int call(Ty* /*a_object*/) const {
      return Type< typename Type<Ty, StoredDataTypeSpecificator>::type >().index();
    }
  };

  template <typename Ty>
  struct Type<Ty, StoredDataTypeSpecificator> : public TypeImpl<Ty, StoredDataTypeSpecificator> {
    enum { enable = false };
    typedef Ty type;
  };

  template <>
  struct Type<const char*, StoredDataTypeSpecificator> : public TypeImpl<const char*, StoredDataTypeSpecificator> {
    enum { enable = true };
    typedef std::string type;
  };

  template <>
  struct Type<char*, StoredDataTypeSpecificator> : public TypeImpl<char*, StoredDataTypeSpecificator> {
    enum { enable = true };
    typedef std::string type;
  };

  template <size_t Size>
  struct Type<char[Size], StoredDataTypeSpecificator> : public TypeImpl<char[Size], StoredDataTypeSpecificator> {
    enum { enable = true };
    typedef std::string type;
  };

  template <size_t Size>
  struct Type<const char[Size], StoredDataTypeSpecificator> : public TypeImpl<const char[Size], StoredDataTypeSpecificator> {
    enum { enable = true };
    typedef std::string type;
  };


} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_SPECIFICATOR__STORED_DATA_TYPE_SPECIFICATOR_HPP___
