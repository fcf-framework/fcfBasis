#ifndef ___FCF_BASIS__BITS__REGISTRY_HPP___
#define ___FCF_BASIS__BITS__REGISTRY_HPP___

#include <string.h>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>

#include "../macro.hpp"
#include "../Nop.hpp"
#include "../nativeType.hpp"
#include "../bits/PartType/TypeInitializer.hpp"
#include "./PartContainerAccess/ContainerAccess.hpp"
#include "./PartContainerAccess/DynamicContainerAccess.hpp"
#include "../Variant.hpp"
#include "../bits/PartType/NDetails/TypeRegistrar.hpp"
#include "../bits/PartTypes/UniversalArguments.hpp"
#include "../bits/PartSpecificator/PartSpecificator.hpp"

FCF_TYPEID_REGISTRY(fcf::ContainerAccessSpecificator, "fcf::ContainerAccessSpecificator", 0);
FCF_TYPEID_REGISTRY(fcf::MinMaxSpecificator,          "fcf::MinMaxSpecificator", 0);
FCF_TYPEID_REGISTRY(fcf::ValueSpecificator,           "fcf::ValueSpecificator",  0);
FCF_TYPEID_REGISTRY(fcf::StoredDataTypeSpecificator,  "fcf::StoredDataTypeSpecificator",  0);
FCF_TYPEID_REGISTRY(fcf::ResolveData,                 "fcf::ResolveData",  0);
FCF_TYPEID_REGISTRY(fcf::ResolveSpecificator,         "fcf::ResolveSpecificator",  0);
FCF_TYPEID_REGISTRY(fcf::LessSpecificator,            "fcf::LessSpecificator",  0);
FCF_TYPEID_REGISTRY(fcf::EqualSpecificator,            "fcf::EqualSpecificator",  0);


FCF_TYPEID_REGISTRY(char,               "char",               FCF_INT8_TYPE_INDEX);
namespace fcf { template<> struct Type<char, LessSpecificator> : public TypeImpl<char, LessSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(char,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<char, EqualSpecificator> : public TypeImpl<char, EqualSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(char,  fcf::EqualSpecificator);


FCF_SPECIFICATOR_REGISTRY(char*,        fcf::StoredDataTypeSpecificator);
namespace fcf { 
  template<> struct Type<char*, LessSpecificator> : public TypeImpl<char*, LessSpecificator> {
    inline bool call(char* const* a_left, char* const* a_right) const {
      return strcmp(*a_left, *a_right) < 0;
    }
  }; 
}
FCF_SPECIFICATOR_REGISTRY(char*,  fcf::LessSpecificator);
namespace fcf { 
  template<> struct Type<char*, EqualSpecificator> : public TypeImpl<char*, EqualSpecificator> {
    inline bool call(char* const* a_left, char* const* a_right) const {
      return strcmp(*a_left, *a_right) == 0;
    }
  }; 
}
FCF_SPECIFICATOR_REGISTRY(char*,  fcf::EqualSpecificator);


FCF_SPECIFICATOR_REGISTRY(const char*,  fcf::StoredDataTypeSpecificator);
namespace fcf { 
  template<> struct Type<const char*, LessSpecificator> : public TypeImpl<const char*, LessSpecificator> {
    inline bool call(const char* const* a_left, const char* const* a_right) const {
      return strcmp(*a_left, *a_right) < 0;
    }
  }; 
}
FCF_SPECIFICATOR_REGISTRY(char*,  fcf::LessSpecificator);
namespace fcf { 
  template<> struct Type<const char*, EqualSpecificator> : public TypeImpl<const char*, EqualSpecificator> {
    inline bool call(const char* const* a_left, const char* const* a_right) const {
      return strcmp(*a_left, *a_right) == 0;
    }
  }; 
}
FCF_SPECIFICATOR_REGISTRY(char*,  fcf::EqualSpecificator);


FCF_TYPEID_REGISTRY(unsigned char,      "unsigned char",      FCF_UINT8_TYPE_INDEX);
namespace fcf { template<> struct Type<unsigned char, LessSpecificator> : public TypeImpl<unsigned char, LessSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(unsigned char,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<unsigned char, EqualSpecificator> : public TypeImpl<unsigned char, EqualSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(unsigned char,  fcf::EqualSpecificator);


FCF_TYPEID_REGISTRY(short,              "short",              FCF_INT16_TYPE_INDEX);
namespace fcf { template<> struct Type<short, LessSpecificator> : public TypeImpl<short, LessSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(short,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<short, EqualSpecificator> : public TypeImpl<short, EqualSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(short,  fcf::EqualSpecificator);


FCF_TYPEID_REGISTRY(unsigned short,     "unsigned short",     FCF_UINT16_TYPE_INDEX);
namespace fcf { template<> struct Type<unsigned short, LessSpecificator> : public TypeImpl<unsigned short, LessSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(short,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<unsigned short, EqualSpecificator> : public TypeImpl<unsigned short, EqualSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(short,  fcf::EqualSpecificator);


FCF_TYPEID_REGISTRY(int,                "int",                FCF_INT32_TYPE_INDEX);
namespace fcf { template<> struct Type<int, LessSpecificator> : public TypeImpl<int, LessSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(int,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<int, EqualSpecificator> : public TypeImpl<int, EqualSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(int,  fcf::EqualSpecificator);


FCF_TYPEID_REGISTRY(unsigned int,       "unsigned int",       FCF_UINT32_TYPE_INDEX);
namespace fcf { template<> struct Type<unsigned int, LessSpecificator> : public TypeImpl<unsigned int, LessSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(unsigned int,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<unsigned int, EqualSpecificator> : public TypeImpl<unsigned int, EqualSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(unsigned int,  fcf::EqualSpecificator);


FCF_TYPEID_REGISTRY(long long,          "long long",          FCF_INT64_TYPE_INDEX);
namespace fcf { template<> struct Type<long long, LessSpecificator> : public TypeImpl<long long, LessSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(long long,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<long long, EqualSpecificator> : public TypeImpl<long long, EqualSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(long long,  fcf::EqualSpecificator);


FCF_TYPEID_REGISTRY(unsigned long long, "unsigned long long", FCF_UINT64_TYPE_INDEX);
namespace fcf { template<> struct Type<unsigned long long, LessSpecificator> : public TypeImpl<unsigned long long, LessSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(unsigned long long,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<unsigned long long, EqualSpecificator> : public TypeImpl<unsigned long long, EqualSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(unsigned long long,  fcf::EqualSpecificator);


FCF_TYPEID_REGISTRY(float,              "float",              FCF_FLOAT32_TYPE_INDEX);
namespace fcf { template<> struct Type<float, LessSpecificator> : public TypeImpl<float, LessSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(float,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<float, EqualSpecificator> : public TypeImpl<float, EqualSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(float,  fcf::EqualSpecificator);


FCF_TYPEID_REGISTRY(double,             "double",             FCF_FLOAT64_TYPE_INDEX);
namespace fcf { template<> struct Type<double, LessSpecificator> : public TypeImpl<double, LessSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(double,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<double, EqualSpecificator> : public TypeImpl<double, EqualSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(double,  fcf::EqualSpecificator);


FCF_TYPEID_REGISTRY(long double,        "long double",        FCF_FLOAT128_TYPE_INDEX);
namespace fcf { template<> struct Type<long double, LessSpecificator> : public TypeImpl<long double, LessSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(long double,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<long double, EqualSpecificator> : public TypeImpl<long double, EqualSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(long double,  fcf::EqualSpecificator);


FCF_TYPEID_REGISTRY(long int,           "long int",  0);
namespace fcf { template<> struct Type<long int, LessSpecificator> : public TypeImpl<long int, LessSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(long int,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<long int, EqualSpecificator> : public TypeImpl<long int, EqualSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(long int,  fcf::EqualSpecificator);


FCF_TYPEID_REGISTRY(unsigned long int,  "unsigned long int",  0);
namespace fcf { template<> struct Type<unsigned long int, LessSpecificator> : public TypeImpl<unsigned long int, LessSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(unsigned long int,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<unsigned long int, EqualSpecificator> : public TypeImpl<unsigned long int, EqualSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(unsigned long int,  fcf::EqualSpecificator);


FCF_TYPEID_REGISTRY_SINGLE(void,        "void",               20);

FCF_TYPEID_REGISTRY(bool,               "bool",               21);
namespace fcf { template<> struct Type<bool, LessSpecificator> : public TypeImpl<bool, LessSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(bool,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<bool, EqualSpecificator> : public TypeImpl<bool, EqualSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(bool,  fcf::EqualSpecificator);


FCF_TYPEID_REGISTRY(std::string,        "std::string",        30);
namespace fcf { template<> struct Type<std::string, LessSpecificator> : public TypeImpl<std::string, LessSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(std::string,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<std::string, EqualSpecificator> : public TypeImpl<std::string, EqualSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(std::string,  fcf::EqualSpecificator);


FCF_TYPEID_REGISTRY(fcf::Variant,       "fcf::Variant",         31);
FCF_SPECIFICATOR_REGISTRY(fcf::Variant, fcf::ResolveSpecificator);
namespace fcf { template<> struct Type<fcf::Variant, LessSpecificator> : public TypeImpl<fcf::Variant, LessSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(fcf::Variant,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<fcf::Variant, EqualSpecificator> : public TypeImpl<fcf::Variant, EqualSpecificator> {}; } 
FCF_SPECIFICATOR_REGISTRY(fcf::Variant,  fcf::EqualSpecificator);


FCF_TYPEID_REGISTRY(fcf::UniversalArguments,       "fcf::UniversalArguments",         0);


FCF_TYPEID_REGISTRY(fcf::Nop, "fcf::Nop", 0);

FCF_TEMPLATE_TYPEID_DECLARE(fcf::ContainerAccess, 
                            "fcf::ContainerAccess", 
                            (typename Ty, bool ConstMode), 
                            (Ty, ConstMode), 
                            (::fcf::Type<Ty>().name() +","+ (ConstMode ? "true" : "false"))
                            );

FCF_TEMPLATE_TYPEID_DECLARE(fcf::DynamicContainerAccess, 
                            "fcf::DynamicContainerAccess", 
                            (typename Ty), 
                            (Ty), 
                            (::fcf::Type<Ty>().name())
                            );


FCF_TEMPLATE_TYPEID_DECLARE(std::vector, "std::vector", (typename Ty), (Ty), (::fcf::Type<Ty>().name()));
namespace fcf {
  template <typename Ty>
  struct Type<std::vector<Ty>, ContainerAccessSpecificator>: public TypeImpl<std::vector<Ty>, ContainerAccessSpecificator>{
  };
} // fcf namespace
FCF_TEMPLATE_SPECIFICATOR_REGISTRY(std::vector, ContainerAccessSpecificator);


FCF_TEMPLATE_TYPEID_DECLARE(std::list, "std::list", (typename Ty), (Ty), (Type<Ty>().name()));
namespace fcf {
  template <typename Ty>
  struct Type<std::list<Ty>, ContainerAccessSpecificator>: public TypeImpl<std::list<Ty>, ContainerAccessSpecificator>{
  };
} // fcf namespace
FCF_TEMPLATE_SPECIFICATOR_REGISTRY(std::list, ContainerAccessSpecificator);



FCF_TEMPLATE_TYPEID_DECLARE(std::set, "std::set", (typename Ty), (Ty), (Type<Ty>().name()));
namespace fcf {
  template <typename Ty>
  struct Type<std::set<Ty>, ContainerAccessSpecificator>: public TypeImpl<std::set<Ty>, ContainerAccessSpecificator>{
  };
} // fcf namespace
FCF_TEMPLATE_SPECIFICATOR_REGISTRY(std::set, ContainerAccessSpecificator);



FCF_TEMPLATE_TYPEID_DECLARE(std::map, "std::map", (typename TKey, typename TValue), (TKey, TValue), (Type<TKey>().name()+","+Type<TValue>().name()));
namespace fcf {
  template <typename TKey, typename TValue>
  struct Type<std::map<TKey, TValue>, ContainerAccessSpecificator>: public TypeImpl<std::map<TKey, TValue>, ContainerAccessSpecificator>{
  };
} // fcf namespace
FCF_TEMPLATE_SPECIFICATOR_REGISTRY(std::map, ContainerAccessSpecificator);

#endif // #ifndef ___FCF_BASIS__BITS__REGISTRY_HPP___
