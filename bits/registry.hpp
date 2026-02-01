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
#include "../bits/PartCall/CallOptions.hpp"
#include "../bits/PartCall/CallArgumentOptions.hpp"




FCF_TYPEID_REGISTRY(fcf::CallOptions, "fcf::CallOptions", 0);

FCF_TYPEID_REGISTRY(fcf::ContainerAccessSpecificator, "fcf::ContainerAccessSpecificator", 0);
FCF_TYPEID_REGISTRY(fcf::MinMaxSpecificator,          "fcf::MinMaxSpecificator", 0);
FCF_TYPEID_REGISTRY(fcf::ValueSpecificator,           "fcf::ValueSpecificator",  0);
FCF_TYPEID_REGISTRY(fcf::StoredDataTypeSpecificator,  "fcf::StoredDataTypeSpecificator",  0);
FCF_TYPEID_REGISTRY(fcf::ResolveData,                 "fcf::ResolveData",  0);
FCF_TYPEID_REGISTRY(fcf::ResolveSpecificator,         "fcf::ResolveSpecificator",  0);
FCF_TYPEID_REGISTRY(fcf::LessSpecificator,            "fcf::LessSpecificator",  0);
FCF_TYPEID_REGISTRY(fcf::EqualSpecificator,           "fcf::EqualSpecificator",  0);
FCF_TYPEID_REGISTRY(fcf::AddSpecificator,             "fcf::AddSpecificator",  0);
FCF_TYPEID_REGISTRY(fcf::SubSpecificator,             "fcf::SubSpecificator",  0);
FCF_TYPEID_REGISTRY(fcf::MulSpecificator,             "fcf::MulSpecificator",  0);
FCF_TYPEID_REGISTRY(fcf::DivSpecificator,             "fcf::DivSpecificator",  0);
FCF_TYPEID_REGISTRY(fcf::BoolSpecificator,            "fcf::BoolSpecificator",  0);
FCF_TYPEID_REGISTRY(fcf::InheritanceSpecificator,     "fcf::InheritanceSpecificator",  0);


FCF_TEMPLATE_TYPEID_DECLARE((fcf, CallArgumentOptions), "fcf::CallArgumentOptions", (unsigned int Flags), (Flags), ( std::to_string(Flags) ));
namespace fcf {
  template<unsigned int Flags> 
  struct Type<CallArgumentOptions<Flags>, InheritanceSpecificator> : public TypeImpl<CallArgumentOptions<Flags>, InheritanceSpecificator, BaseCallArgumentOptions> {
  };
}
FCF_TEMPLATE_SPECIFICATOR_REGISTRY((fcf, CallArgumentOptions), InheritanceSpecificator);

FCF_TYPEID_REGISTRY(char,               "char",               FCF_INT8_TYPE_INDEX);
namespace fcf { template<> struct Type<char, LessSpecificator> : public TypeImpl<char, LessSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(char,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<char, EqualSpecificator> : public TypeImpl<char, EqualSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(char,  fcf::EqualSpecificator);
namespace fcf { template<> struct Type<char, AddSpecificator> : public TypeImpl<char, AddSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(char,  fcf::AddSpecificator);
namespace fcf { template<> struct Type<char, SubSpecificator> : public TypeImpl<char, SubSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(char,  fcf::SubSpecificator);
namespace fcf { template<> struct Type<char, BoolSpecificator> : public TypeImpl<char, BoolSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(char,  fcf::BoolSpecificator);
namespace fcf { template<> struct Type<char, MulSpecificator> : public TypeImpl<char, MulSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(char,  fcf::MulSpecificator);
namespace fcf { template<> struct Type<char, DivSpecificator> : public TypeImpl<char, DivSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(char,  fcf::DivSpecificator);


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
namespace fcf { template<> struct Type<char*, BoolSpecificator> : public TypeImpl<char*, BoolSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(char*,  fcf::BoolSpecificator);


FCF_SPECIFICATOR_REGISTRY(const char*,  fcf::StoredDataTypeSpecificator);
namespace fcf {
  template<> struct Type<const char*, LessSpecificator> : public TypeImpl<const char*, LessSpecificator> {
    inline bool call(const char* const* a_left, const char* const* a_right) const {
      return strcmp(*a_left, *a_right) < 0;
    }
  };
}
FCF_SPECIFICATOR_REGISTRY(const char*,  fcf::LessSpecificator);
namespace fcf {
  template<> struct Type<const char*, EqualSpecificator> : public TypeImpl<const char*, EqualSpecificator> {
    inline bool call(const char* const* a_left, const char* const* a_right) const {
      return strcmp(*a_left, *a_right) == 0;
    }
  };
}
FCF_SPECIFICATOR_REGISTRY(const char*,  fcf::EqualSpecificator);
namespace fcf { template<> struct Type<const char*, BoolSpecificator> : public TypeImpl<const char*, BoolSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(const char*,  fcf::BoolSpecificator);


FCF_TYPEID_REGISTRY(unsigned char,      "unsigned char",      FCF_UINT8_TYPE_INDEX);
namespace fcf { template<> struct Type<unsigned char, LessSpecificator> : public TypeImpl<unsigned char, LessSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned char,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<unsigned char, EqualSpecificator> : public TypeImpl<unsigned char, EqualSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned char,  fcf::EqualSpecificator);
namespace fcf { template<> struct Type<unsigned char, AddSpecificator> : public TypeImpl<unsigned char, AddSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned char,  fcf::AddSpecificator);
namespace fcf { template<> struct Type<unsigned char, SubSpecificator> : public TypeImpl<unsigned char, SubSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned char,  fcf::SubSpecificator);
namespace fcf { template<> struct Type<unsigned char, BoolSpecificator> : public TypeImpl<unsigned char, BoolSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned char,  fcf::BoolSpecificator);
namespace fcf { template<> struct Type<unsigned char, MulSpecificator> : public TypeImpl<unsigned char, MulSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned char,  fcf::MulSpecificator);
namespace fcf { template<> struct Type<unsigned char, DivSpecificator> : public TypeImpl<unsigned char, DivSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned char,  fcf::DivSpecificator);


FCF_TYPEID_REGISTRY(short,              "short",              FCF_INT16_TYPE_INDEX);
namespace fcf { template<> struct Type<short, LessSpecificator> : public TypeImpl<short, LessSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(short,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<short, EqualSpecificator> : public TypeImpl<short, EqualSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(short,  fcf::EqualSpecificator);
namespace fcf { template<> struct Type<short, AddSpecificator> : public TypeImpl<short, AddSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(short,  fcf::AddSpecificator);
namespace fcf { template<> struct Type<short, SubSpecificator> : public TypeImpl<short, SubSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(short,  fcf::SubSpecificator);
namespace fcf { template<> struct Type<short, BoolSpecificator> : public TypeImpl<short, BoolSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(short,  fcf::BoolSpecificator);
namespace fcf { template<> struct Type<short, MulSpecificator> : public TypeImpl<short, MulSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(short,  fcf::MulSpecificator);
namespace fcf { template<> struct Type<short, DivSpecificator> : public TypeImpl<short, DivSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(short,  fcf::DivSpecificator);


FCF_TYPEID_REGISTRY(unsigned short,     "unsigned short",     FCF_UINT16_TYPE_INDEX);
namespace fcf { template<> struct Type<unsigned short, LessSpecificator> : public TypeImpl<unsigned short, LessSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(short,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<unsigned short, EqualSpecificator> : public TypeImpl<unsigned short, EqualSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(short,  fcf::EqualSpecificator);
namespace fcf { template<> struct Type<unsigned short, AddSpecificator> : public TypeImpl<unsigned short, AddSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(short,  fcf::AddSpecificator);
namespace fcf { template<> struct Type<unsigned short, SubSpecificator> : public TypeImpl<unsigned short, SubSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(short,  fcf::SubSpecificator);
namespace fcf { template<> struct Type<unsigned short, MulSpecificator> : public TypeImpl<unsigned short, MulSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(short,  fcf::MulSpecificator);
namespace fcf { template<> struct Type<unsigned short, DivSpecificator> : public TypeImpl<unsigned short, DivSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(short,  fcf::DivSpecificator);


FCF_TYPEID_REGISTRY(int,                "int",                FCF_INT32_TYPE_INDEX);
namespace fcf { template<> struct Type<int, LessSpecificator> : public TypeImpl<int, LessSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(int,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<int, EqualSpecificator> : public TypeImpl<int, EqualSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(int,  fcf::EqualSpecificator);
namespace fcf { template<> struct Type<int, AddSpecificator> : public TypeImpl<int, AddSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(int,  fcf::AddSpecificator);
namespace fcf { template<> struct Type<int, SubSpecificator> : public TypeImpl<int, SubSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(int,  fcf::SubSpecificator);
namespace fcf { template<> struct Type<int, BoolSpecificator> : public TypeImpl<int, BoolSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(int,  fcf::BoolSpecificator);
namespace fcf { template<> struct Type<int, MulSpecificator> : public TypeImpl<int, MulSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(int,  fcf::MulSpecificator);
namespace fcf { template<> struct Type<int, DivSpecificator> : public TypeImpl<int, DivSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(int,  fcf::DivSpecificator);


FCF_TYPEID_REGISTRY(unsigned int,       "unsigned int",       FCF_UINT32_TYPE_INDEX);
namespace fcf { template<> struct Type<unsigned int, LessSpecificator> : public TypeImpl<unsigned int, LessSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned int,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<unsigned int, EqualSpecificator> : public TypeImpl<unsigned int, EqualSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned int,  fcf::EqualSpecificator);
namespace fcf { template<> struct Type<unsigned int, AddSpecificator> : public TypeImpl<unsigned int, AddSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned int,  fcf::AddSpecificator);
namespace fcf { template<> struct Type<unsigned int, SubSpecificator> : public TypeImpl<unsigned int, SubSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned int,  fcf::SubSpecificator);
namespace fcf { template<> struct Type<unsigned int, BoolSpecificator> : public TypeImpl<unsigned int, BoolSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned int,  fcf::BoolSpecificator);
namespace fcf { template<> struct Type<unsigned int, MulSpecificator> : public TypeImpl<unsigned int, MulSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned int,  fcf::MulSpecificator);
namespace fcf { template<> struct Type<unsigned int, DivSpecificator> : public TypeImpl<unsigned int, DivSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned int,  fcf::DivSpecificator);


FCF_TYPEID_REGISTRY(long long,          "long long",          FCF_INT64_TYPE_INDEX);
namespace fcf { template<> struct Type<long long, LessSpecificator> : public TypeImpl<long long, LessSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long long,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<long long, EqualSpecificator> : public TypeImpl<long long, EqualSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long long,  fcf::EqualSpecificator);
namespace fcf { template<> struct Type<long long, AddSpecificator> : public TypeImpl<long long, AddSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long long,  fcf::AddSpecificator);
namespace fcf { template<> struct Type<long long, SubSpecificator> : public TypeImpl<long long, SubSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long long,  fcf::SubSpecificator);
namespace fcf { template<> struct Type<long long, BoolSpecificator> : public TypeImpl<long long, BoolSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long long,  fcf::BoolSpecificator);
namespace fcf { template<> struct Type<long long, MulSpecificator> : public TypeImpl<long long, MulSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long long,  fcf::MulSpecificator);
namespace fcf { template<> struct Type<long long, DivSpecificator> : public TypeImpl<long long, DivSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long long,  fcf::DivSpecificator);


FCF_TYPEID_REGISTRY(unsigned long long, "unsigned long long", FCF_UINT64_TYPE_INDEX);
namespace fcf { template<> struct Type<unsigned long long, LessSpecificator> : public TypeImpl<unsigned long long, LessSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned long long,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<unsigned long long, EqualSpecificator> : public TypeImpl<unsigned long long, EqualSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned long long,  fcf::EqualSpecificator);
namespace fcf { template<> struct Type<unsigned long long, AddSpecificator> : public TypeImpl<unsigned long long, AddSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned long long,  fcf::AddSpecificator);
namespace fcf { template<> struct Type<unsigned long long, SubSpecificator> : public TypeImpl<unsigned long long, SubSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned long long,  fcf::SubSpecificator);
namespace fcf { template<> struct Type<unsigned long long, BoolSpecificator> : public TypeImpl<unsigned long long, BoolSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned long long,  fcf::BoolSpecificator);
namespace fcf { template<> struct Type<unsigned long long, MulSpecificator> : public TypeImpl<unsigned long long, MulSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned long long,  fcf::MulSpecificator);
namespace fcf { template<> struct Type<unsigned long long, DivSpecificator> : public TypeImpl<unsigned long long, DivSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned long long,  fcf::DivSpecificator);


FCF_TYPEID_REGISTRY(float,              "float",              FCF_FLOAT32_TYPE_INDEX);
namespace fcf { template<> struct Type<float, LessSpecificator> : public TypeImpl<float, LessSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(float,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<float, EqualSpecificator> : public TypeImpl<float, EqualSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(float,  fcf::EqualSpecificator);
namespace fcf { template<> struct Type<float, AddSpecificator> : public TypeImpl<float, AddSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(float,  fcf::AddSpecificator);
namespace fcf { template<> struct Type<float, SubSpecificator> : public TypeImpl<float, SubSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(float,  fcf::SubSpecificator);
namespace fcf { template<> struct Type<float, BoolSpecificator> : public TypeImpl<float, BoolSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(float,  fcf::BoolSpecificator);
namespace fcf { template<> struct Type<float, MulSpecificator> : public TypeImpl<float, MulSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(float,  fcf::MulSpecificator);
namespace fcf { template<> struct Type<float, DivSpecificator> : public TypeImpl<float, DivSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(float,  fcf::DivSpecificator);


FCF_TYPEID_REGISTRY(double,             "double",             FCF_FLOAT64_TYPE_INDEX);
namespace fcf { template<> struct Type<double, LessSpecificator> : public TypeImpl<double, LessSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(double,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<double, EqualSpecificator> : public TypeImpl<double, EqualSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(double,  fcf::EqualSpecificator);
namespace fcf { template<> struct Type<double, AddSpecificator> : public TypeImpl<double, AddSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(double,  fcf::AddSpecificator);
namespace fcf { template<> struct Type<double, SubSpecificator> : public TypeImpl<double, SubSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(double,  fcf::SubSpecificator);
namespace fcf { template<> struct Type<double, BoolSpecificator> : public TypeImpl<double, BoolSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(double,  fcf::BoolSpecificator);
namespace fcf { template<> struct Type<double, MulSpecificator> : public TypeImpl<double, MulSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(double,  fcf::MulSpecificator);
namespace fcf { template<> struct Type<double, DivSpecificator> : public TypeImpl<double, DivSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(double,  fcf::DivSpecificator);


FCF_TYPEID_REGISTRY(long double,        "long double",        FCF_FLOAT128_TYPE_INDEX);
namespace fcf { template<> struct Type<long double, LessSpecificator> : public TypeImpl<long double, LessSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long double,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<long double, EqualSpecificator> : public TypeImpl<long double, EqualSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long double,  fcf::EqualSpecificator);
namespace fcf { template<> struct Type<long double, AddSpecificator> : public TypeImpl<long double, AddSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long double,  fcf::AddSpecificator);
namespace fcf { template<> struct Type<long double, SubSpecificator> : public TypeImpl<long double, SubSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long double,  fcf::SubSpecificator);
namespace fcf { template<> struct Type<long double, BoolSpecificator> : public TypeImpl<long double, BoolSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long double,  fcf::BoolSpecificator);
namespace fcf { template<> struct Type<long double, MulSpecificator> : public TypeImpl<long double, MulSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long double,  fcf::MulSpecificator);
namespace fcf { template<> struct Type<long double, DivSpecificator> : public TypeImpl<long double, DivSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long double,  fcf::DivSpecificator);


FCF_TYPEID_REGISTRY(long int,           "long int",  0);
namespace fcf { template<> struct Type<long int, LessSpecificator> : public TypeImpl<long int, LessSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long int,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<long int, EqualSpecificator> : public TypeImpl<long int, EqualSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long int,  fcf::EqualSpecificator);
namespace fcf { template<> struct Type<long int, AddSpecificator> : public TypeImpl<long int, AddSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long int,  fcf::AddSpecificator);
namespace fcf { template<> struct Type<long int, SubSpecificator> : public TypeImpl<long int, SubSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long int,  fcf::SubSpecificator);
namespace fcf { template<> struct Type<long int, BoolSpecificator> : public TypeImpl<long int, BoolSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long int,  fcf::BoolSpecificator);
namespace fcf { template<> struct Type<long int, MulSpecificator> : public TypeImpl<long int, MulSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long int,  fcf::MulSpecificator);
namespace fcf { template<> struct Type<long int, DivSpecificator> : public TypeImpl<long int, DivSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(long int,  fcf::DivSpecificator);


FCF_TYPEID_REGISTRY(unsigned long int,  "unsigned long int",  0);
namespace fcf { template<> struct Type<unsigned long int, LessSpecificator> : public TypeImpl<unsigned long int, LessSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned long int,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<unsigned long int, EqualSpecificator> : public TypeImpl<unsigned long int, EqualSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned long int,  fcf::EqualSpecificator);
namespace fcf { template<> struct Type<unsigned long int, AddSpecificator> : public TypeImpl<unsigned long int, AddSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned long int,  fcf::AddSpecificator);
namespace fcf { template<> struct Type<unsigned long int, SubSpecificator> : public TypeImpl<unsigned long int, SubSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned long int,  fcf::SubSpecificator);
namespace fcf { template<> struct Type<unsigned long int, BoolSpecificator> : public TypeImpl<unsigned long int, BoolSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned long int,  fcf::BoolSpecificator);
namespace fcf { template<> struct Type<unsigned long int, MulSpecificator> : public TypeImpl<unsigned long int, MulSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned long int,  fcf::MulSpecificator);
namespace fcf { template<> struct Type<unsigned long int, DivSpecificator> : public TypeImpl<unsigned long int, DivSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(unsigned long int,  fcf::DivSpecificator);


FCF_TYPEID_REGISTRY_SINGLE(void,        "void",               20);

FCF_TYPEID_REGISTRY(bool,               "bool",               21);
namespace fcf { template<> struct Type<bool, LessSpecificator> : public TypeImpl<bool, LessSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(bool,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<bool, EqualSpecificator> : public TypeImpl<bool, EqualSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(bool,  fcf::EqualSpecificator);
namespace fcf { template<> struct Type<bool, AddSpecificator> : public TypeImpl<bool, AddSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(bool,  fcf::AddSpecificator);
namespace fcf { template<> struct Type<bool, SubSpecificator> : public TypeImpl<bool, SubSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(bool,  fcf::SubSpecificator);
namespace fcf { template<> struct Type<bool, BoolSpecificator> : public TypeImpl<bool, BoolSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(bool,  fcf::BoolSpecificator);
namespace fcf { template<> struct Type<bool, MulSpecificator> : public TypeImpl<bool, MulSpecificator> {
  void call(bool* a_destination, const bool* a_left, const bool* a_right){
    *a_destination = *a_left && *a_right;
  }
}; }
FCF_SPECIFICATOR_REGISTRY(bool,  fcf::MulSpecificator);
namespace fcf { template<> struct Type<bool, DivSpecificator> : public TypeImpl<bool, DivSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(bool,  fcf::DivSpecificator);


FCF_TYPEID_REGISTRY(std::string,        "std::string",        30);
namespace fcf { template<> struct Type<std::string, LessSpecificator> : public TypeImpl<std::string, LessSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(std::string,  fcf::LessSpecificator);
namespace fcf { template<> struct Type<std::string, EqualSpecificator> : public TypeImpl<std::string, EqualSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(std::string,  fcf::EqualSpecificator);
namespace fcf { template<> struct Type<std::string, AddSpecificator> : public TypeImpl<std::string, AddSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY(std::string,  fcf::AddSpecificator);
namespace fcf { template<> struct Type<std::string, BoolSpecificator> : public TypeImpl<std::string, BoolSpecificator> {
  bool call(const std::string* a_value){
    return !a_value->empty();
  }
}; }
FCF_SPECIFICATOR_REGISTRY(std::string,  fcf::BoolSpecificator);


FCF_TEMPLATE_TYPEID_DECLARE((fcf, BasicVariant),
                            "fcf::BasicVariant",
                            (size_t InnerBufferSize),
                            (InnerBufferSize),
                            (std::to_string(InnerBufferSize))
                            );

FCF_TEMPLATE_SPECIFICATOR_REGISTRY((fcf, BasicVariant), ResolveSpecificator);
namespace fcf { template<size_t InnerBufferSize> struct Type<fcf::BasicVariant<InnerBufferSize>, LessSpecificator> : public TypeImpl<fcf::BasicVariant<InnerBufferSize>, LessSpecificator> {}; }
FCF_TEMPLATE_SPECIFICATOR_REGISTRY((fcf, BasicVariant), LessSpecificator);
namespace fcf { template<size_t InnerBufferSize> struct Type<fcf::BasicVariant<InnerBufferSize>, EqualSpecificator> : public TypeImpl<fcf::BasicVariant<InnerBufferSize>, EqualSpecificator> {}; }
FCF_TEMPLATE_SPECIFICATOR_REGISTRY((fcf, BasicVariant), EqualSpecificator);
namespace fcf { template<size_t InnerBufferSize> struct Type<fcf::BasicVariant<InnerBufferSize>, AddSpecificator> : public TypeImpl<fcf::BasicVariant<InnerBufferSize>, AddSpecificator> {}; }
FCF_TEMPLATE_SPECIFICATOR_REGISTRY((fcf, BasicVariant),  AddSpecificator);
namespace fcf { template<size_t InnerBufferSize> struct Type<fcf::BasicVariant<InnerBufferSize>, SubSpecificator> : public TypeImpl<fcf::BasicVariant<InnerBufferSize>, SubSpecificator> {}; }
FCF_TEMPLATE_SPECIFICATOR_REGISTRY((fcf, BasicVariant),  SubSpecificator);
namespace fcf { template<size_t InnerBufferSize> struct Type<fcf::BasicVariant<InnerBufferSize>, BoolSpecificator> : public TypeImpl<fcf::BasicVariant<InnerBufferSize>, BoolSpecificator> {}; }
FCF_TEMPLATE_SPECIFICATOR_REGISTRY((fcf, BasicVariant),  BoolSpecificator);
namespace fcf { template<size_t InnerBufferSize> struct Type<fcf::BasicVariant<InnerBufferSize>, MulSpecificator> : public TypeImpl<fcf::BasicVariant<InnerBufferSize>, MulSpecificator> {}; }
FCF_TEMPLATE_SPECIFICATOR_REGISTRY((fcf, BasicVariant),  MulSpecificator);
namespace fcf { template<size_t InnerBufferSize> struct Type<fcf::BasicVariant<InnerBufferSize>, DivSpecificator> : public TypeImpl<fcf::BasicVariant<InnerBufferSize>, DivSpecificator> {}; }
FCF_TEMPLATE_SPECIFICATOR_REGISTRY((fcf, BasicVariant),  DivSpecificator);

namespace fcf {

  template <size_t InnerBufferSize>
  struct Cursor< BasicVariant<InnerBufferSize> > : public VariantCursor< BasicVariant<InnerBufferSize> >{
    typedef VariantCursor< BasicVariant<InnerBufferSize> > BaseType;
    using VariantCursor< BasicVariant<InnerBufferSize> >::VariantCursor;
  };

  template <size_t InnerBufferSize>
  struct Type<BasicVariant<InnerBufferSize>, ContainerAccessSpecificator>: public TypeImpl<BasicVariant<InnerBufferSize>, ContainerAccessSpecificator>{
  };


} // fcf namespace
FCF_SPECIFICATOR_REGISTRY(fcf::Variant,  fcf::ContainerAccessSpecificator);


FCF_TYPEID_REGISTRY(fcf::UniversalArguments,       "fcf::UniversalArguments",         0);


FCF_TYPEID_REGISTRY(fcf::Nop, "fcf::Nop", 0);

FCF_TEMPLATE_TYPEID_DECLARE((fcf, ContainerAccess),
                            "fcf::ContainerAccess",
                            (typename Ty),
                            (Ty),
                            (::fcf::Type<Ty>().name())
                            );

FCF_TEMPLATE_TYPEID_DECLARE((fcf, DynamicContainerAccess),
                            "fcf::DynamicContainerAccess",
                            (typename Ty),
                            (Ty),
                            (::fcf::Type<Ty>().name())
                            );


FCF_TEMPLATE_TYPEID_DECLARE((std, vector), "std::vector", (typename Ty), (Ty), (::fcf::Type<Ty>().name()));
namespace fcf {
  template <typename Ty>
  struct Type<std::vector<Ty>, ContainerAccessSpecificator>: public TypeImpl<std::vector<Ty>, ContainerAccessSpecificator>{
  };
} // fcf namespace
namespace fcf {
  template <typename Ty>
  struct Type<const std::vector<Ty>, ContainerAccessSpecificator>: public TypeImpl<const std::vector<Ty>, ContainerAccessSpecificator>{
  };
} // fcf namespace
FCF_TEMPLATE_SPECIFICATOR_REGISTRY((std, vector), ContainerAccessSpecificator);


FCF_TEMPLATE_TYPEID_DECLARE((std, list), "std::list", (typename Ty), (Ty), (Type<Ty>().name()));
namespace fcf {
  template <typename Ty>
  struct Type<std::list<Ty>, ContainerAccessSpecificator>: public TypeImpl<std::list<Ty>, ContainerAccessSpecificator>{
  };
} // fcf namespace
FCF_TEMPLATE_SPECIFICATOR_REGISTRY((std, list), ContainerAccessSpecificator);



FCF_TEMPLATE_TYPEID_DECLARE((std, set), "std::set", (typename Ty), (Ty), (Type<Ty>().name()));
namespace fcf {
  template <typename Ty>
  struct Type<std::set<Ty>, ContainerAccessSpecificator>: public TypeImpl<std::set<Ty>, ContainerAccessSpecificator>{
  };
} // fcf namespace
FCF_TEMPLATE_SPECIFICATOR_REGISTRY((std, set), ContainerAccessSpecificator);



FCF_TEMPLATE_TYPEID_DECLARE((std, map), "std::map", (typename TKey, typename TValue), (TKey, TValue), (Type<TKey>().name()+","+Type<TValue>().name()));
namespace fcf {
  template <typename TKey, typename TValue>
  struct Type<std::map<TKey, TValue>, ContainerAccessSpecificator>: public TypeImpl<std::map<TKey, TValue>, ContainerAccessSpecificator>{
  };
} // fcf namespace
FCF_TEMPLATE_SPECIFICATOR_REGISTRY((std, map), ContainerAccessSpecificator);

#endif // #ifndef ___FCF_BASIS__BITS__REGISTRY_HPP___
