#ifndef _FCF_BASIS__BITS__REGISTRY_HPP___
#define _FCF_BASIS__BITS__REGISTRY_HPP___

#include <string.h>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>

#include "../macro.hpp"
#include "../bits/PartTypes/Nop.hpp"
#include "../bits/PartTypes/GroupNativeTypes.hpp"
#include "../bits/PartType/TypeInitializer.hpp"
#include "./PartContainerAccess/ContainerAccess.hpp"
#include "./PartContainerAccess/DynamicContainerAccess.hpp"
#include "../PartVariant.hpp"
#include "../bits/PartType/NDetails/TypeRegistrar.hpp"
#include "../bits/PartTypes/UniversalPack.hpp"
#include "../bits/PartSpecifier/PartSpecifier.hpp"
#include "../bits/PartCall/CallOptions.hpp"
#include "../bits/PartCall/CallArgumentOptions.hpp"




FCF_TYPE_REGISTRATION(fcf::CallOptions, "fcf::CallOptions", 0);

FCF_TYPE_REGISTRATION(fcf::ContainerAccessSpecifier, "fcf::ContainerAccessSpecifier", 0);
FCF_TYPE_REGISTRATION(fcf::MinMaxSpecifier,          "fcf::MinMaxSpecifier", 0);
FCF_TYPE_REGISTRATION(fcf::ValueSpecifier,           "fcf::ValueSpecifier",  0);
FCF_TYPE_REGISTRATION(fcf::StoredDataTypeSpecifier,  "fcf::StoredDataTypeSpecifier",  0);
FCF_TYPE_REGISTRATION(fcf::ResolveData,                 "fcf::ResolveData",  0);
FCF_TYPE_REGISTRATION(fcf::ResolveSpecifier,         "fcf::ResolveSpecifier",  0);
FCF_TYPE_REGISTRATION(fcf::LessSpecifier,            "fcf::LessSpecifier",  0);
FCF_TYPE_REGISTRATION(fcf::EqualSpecifier,           "fcf::EqualSpecifier",  0);
FCF_TYPE_REGISTRATION(fcf::AddSpecifier,             "fcf::AddSpecifier",  0);
FCF_TYPE_REGISTRATION(fcf::SubSpecifier,             "fcf::SubSpecifier",  0);
FCF_TYPE_REGISTRATION(fcf::MulSpecifier,             "fcf::MulSpecifier",  0);
FCF_TYPE_REGISTRATION(fcf::DivSpecifier,             "fcf::DivSpecifier",  0);
FCF_TYPE_REGISTRATION(fcf::BoolSpecifier,            "fcf::BoolSpecifier",  0);
FCF_TYPE_REGISTRATION(fcf::InheritanceSpecifier,     "fcf::InheritanceSpecifier",  0);


FCF_TEMPLATE_TYPE_REGISTRATION((fcf, CallArgumentOptions), "fcf::CallArgumentOptions", (unsigned int Flags), (Flags), ( std::to_string(Flags) ));
namespace fcf {
  template<unsigned int Flags> 
  struct Type<CallArgumentOptions<Flags>, InheritanceSpecifier> : public TypeImpl<CallArgumentOptions<Flags>, InheritanceSpecifier, BasicCallArgumentOptions> {
  };
}
FCF_TEMPLATE_SPECIFIER_REGISTRATION((fcf, CallArgumentOptions), InheritanceSpecifier);

FCF_TYPE_REGISTRATION(char,               "char",               FCF_INT8_TYPE_INDEX);
namespace fcf { template<> struct Type<char, LessSpecifier> : public TypeImpl<char, LessSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(char,  fcf::LessSpecifier);
namespace fcf { template<> struct Type<char, EqualSpecifier> : public TypeImpl<char, EqualSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(char,  fcf::EqualSpecifier);
namespace fcf { template<> struct Type<char, AddSpecifier> : public TypeImpl<char, AddSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(char,  fcf::AddSpecifier);
namespace fcf { template<> struct Type<char, SubSpecifier> : public TypeImpl<char, SubSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(char,  fcf::SubSpecifier);
namespace fcf { template<> struct Type<char, BoolSpecifier> : public TypeImpl<char, BoolSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(char,  fcf::BoolSpecifier);
namespace fcf { template<> struct Type<char, MulSpecifier> : public TypeImpl<char, MulSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(char,  fcf::MulSpecifier);
namespace fcf { template<> struct Type<char, DivSpecifier> : public TypeImpl<char, DivSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(char,  fcf::DivSpecifier);


FCF_SPECIFIER_REGISTRATION(char*,        fcf::StoredDataTypeSpecifier);
namespace fcf {
  template<> struct Type<char*, LessSpecifier> : public TypeImpl<char*, LessSpecifier> {
    inline bool call(char* const* a_left, char* const* a_right) const {
      return strcmp(*a_left, *a_right) < 0;
    }
  };
}
FCF_SPECIFIER_REGISTRATION(char*,  fcf::LessSpecifier);
namespace fcf {
  template<> struct Type<char*, EqualSpecifier> : public TypeImpl<char*, EqualSpecifier> {
    inline bool call(char* const* a_left, char* const* a_right) const {
      return strcmp(*a_left, *a_right) == 0;
    }
  };
}
FCF_SPECIFIER_REGISTRATION(char*,  fcf::EqualSpecifier);
namespace fcf { template<> struct Type<char*, BoolSpecifier> : public TypeImpl<char*, BoolSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(char*,  fcf::BoolSpecifier);


FCF_SPECIFIER_REGISTRATION(const char*,  fcf::StoredDataTypeSpecifier);
namespace fcf {
  template<> struct Type<const char*, LessSpecifier> : public TypeImpl<const char*, LessSpecifier> {
    inline bool call(const char* const* a_left, const char* const* a_right) const {
      return strcmp(*a_left, *a_right) < 0;
    }
  };
}
FCF_SPECIFIER_REGISTRATION(const char*,  fcf::LessSpecifier);
namespace fcf {
  template<> struct Type<const char*, EqualSpecifier> : public TypeImpl<const char*, EqualSpecifier> {
    inline bool call(const char* const* a_left, const char* const* a_right) const {
      return strcmp(*a_left, *a_right) == 0;
    }
  };
}
FCF_SPECIFIER_REGISTRATION(const char*,  fcf::EqualSpecifier);
namespace fcf { template<> struct Type<const char*, BoolSpecifier> : public TypeImpl<const char*, BoolSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(const char*,  fcf::BoolSpecifier);


FCF_TYPE_REGISTRATION(unsigned char,      "unsigned char",      FCF_UINT8_TYPE_INDEX);
namespace fcf { template<> struct Type<unsigned char, LessSpecifier> : public TypeImpl<unsigned char, LessSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned char,  fcf::LessSpecifier);
namespace fcf { template<> struct Type<unsigned char, EqualSpecifier> : public TypeImpl<unsigned char, EqualSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned char,  fcf::EqualSpecifier);
namespace fcf { template<> struct Type<unsigned char, AddSpecifier> : public TypeImpl<unsigned char, AddSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned char,  fcf::AddSpecifier);
namespace fcf { template<> struct Type<unsigned char, SubSpecifier> : public TypeImpl<unsigned char, SubSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned char,  fcf::SubSpecifier);
namespace fcf { template<> struct Type<unsigned char, BoolSpecifier> : public TypeImpl<unsigned char, BoolSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned char,  fcf::BoolSpecifier);
namespace fcf { template<> struct Type<unsigned char, MulSpecifier> : public TypeImpl<unsigned char, MulSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned char,  fcf::MulSpecifier);
namespace fcf { template<> struct Type<unsigned char, DivSpecifier> : public TypeImpl<unsigned char, DivSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned char,  fcf::DivSpecifier);


FCF_TYPE_REGISTRATION(short,              "short",              FCF_INT16_TYPE_INDEX);
namespace fcf { template<> struct Type<short, LessSpecifier> : public TypeImpl<short, LessSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(short,  fcf::LessSpecifier);
namespace fcf { template<> struct Type<short, EqualSpecifier> : public TypeImpl<short, EqualSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(short,  fcf::EqualSpecifier);
namespace fcf { template<> struct Type<short, AddSpecifier> : public TypeImpl<short, AddSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(short,  fcf::AddSpecifier);
namespace fcf { template<> struct Type<short, SubSpecifier> : public TypeImpl<short, SubSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(short,  fcf::SubSpecifier);
namespace fcf { template<> struct Type<short, BoolSpecifier> : public TypeImpl<short, BoolSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(short,  fcf::BoolSpecifier);
namespace fcf { template<> struct Type<short, MulSpecifier> : public TypeImpl<short, MulSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(short,  fcf::MulSpecifier);
namespace fcf { template<> struct Type<short, DivSpecifier> : public TypeImpl<short, DivSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(short,  fcf::DivSpecifier);


FCF_TYPE_REGISTRATION(unsigned short,     "unsigned short",     FCF_UINT16_TYPE_INDEX);
namespace fcf { template<> struct Type<unsigned short, LessSpecifier> : public TypeImpl<unsigned short, LessSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(short,  fcf::LessSpecifier);
namespace fcf { template<> struct Type<unsigned short, EqualSpecifier> : public TypeImpl<unsigned short, EqualSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(short,  fcf::EqualSpecifier);
namespace fcf { template<> struct Type<unsigned short, AddSpecifier> : public TypeImpl<unsigned short, AddSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(short,  fcf::AddSpecifier);
namespace fcf { template<> struct Type<unsigned short, SubSpecifier> : public TypeImpl<unsigned short, SubSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(short,  fcf::SubSpecifier);
namespace fcf { template<> struct Type<unsigned short, MulSpecifier> : public TypeImpl<unsigned short, MulSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(short,  fcf::MulSpecifier);
namespace fcf { template<> struct Type<unsigned short, DivSpecifier> : public TypeImpl<unsigned short, DivSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(short,  fcf::DivSpecifier);


FCF_TYPE_REGISTRATION(int,                "int",                FCF_INT32_TYPE_INDEX);
namespace fcf { template<> struct Type<int, LessSpecifier> : public TypeImpl<int, LessSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(int,  fcf::LessSpecifier);
namespace fcf { template<> struct Type<int, EqualSpecifier> : public TypeImpl<int, EqualSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(int,  fcf::EqualSpecifier);
namespace fcf { template<> struct Type<int, AddSpecifier> : public TypeImpl<int, AddSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(int,  fcf::AddSpecifier);
namespace fcf { template<> struct Type<int, SubSpecifier> : public TypeImpl<int, SubSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(int,  fcf::SubSpecifier);
namespace fcf { template<> struct Type<int, BoolSpecifier> : public TypeImpl<int, BoolSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(int,  fcf::BoolSpecifier);
namespace fcf { template<> struct Type<int, MulSpecifier> : public TypeImpl<int, MulSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(int,  fcf::MulSpecifier);
namespace fcf { template<> struct Type<int, DivSpecifier> : public TypeImpl<int, DivSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(int,  fcf::DivSpecifier);


FCF_TYPE_REGISTRATION(unsigned int,       "unsigned int",       FCF_UINT32_TYPE_INDEX);
namespace fcf { template<> struct Type<unsigned int, LessSpecifier> : public TypeImpl<unsigned int, LessSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned int,  fcf::LessSpecifier);
namespace fcf { template<> struct Type<unsigned int, EqualSpecifier> : public TypeImpl<unsigned int, EqualSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned int,  fcf::EqualSpecifier);
namespace fcf { template<> struct Type<unsigned int, AddSpecifier> : public TypeImpl<unsigned int, AddSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned int,  fcf::AddSpecifier);
namespace fcf { template<> struct Type<unsigned int, SubSpecifier> : public TypeImpl<unsigned int, SubSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned int,  fcf::SubSpecifier);
namespace fcf { template<> struct Type<unsigned int, BoolSpecifier> : public TypeImpl<unsigned int, BoolSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned int,  fcf::BoolSpecifier);
namespace fcf { template<> struct Type<unsigned int, MulSpecifier> : public TypeImpl<unsigned int, MulSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned int,  fcf::MulSpecifier);
namespace fcf { template<> struct Type<unsigned int, DivSpecifier> : public TypeImpl<unsigned int, DivSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned int,  fcf::DivSpecifier);


FCF_TYPE_REGISTRATION(long long,          "long long",          FCF_INT64_TYPE_INDEX);
namespace fcf { template<> struct Type<long long, LessSpecifier> : public TypeImpl<long long, LessSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long long,  fcf::LessSpecifier);
namespace fcf { template<> struct Type<long long, EqualSpecifier> : public TypeImpl<long long, EqualSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long long,  fcf::EqualSpecifier);
namespace fcf { template<> struct Type<long long, AddSpecifier> : public TypeImpl<long long, AddSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long long,  fcf::AddSpecifier);
namespace fcf { template<> struct Type<long long, SubSpecifier> : public TypeImpl<long long, SubSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long long,  fcf::SubSpecifier);
namespace fcf { template<> struct Type<long long, BoolSpecifier> : public TypeImpl<long long, BoolSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long long,  fcf::BoolSpecifier);
namespace fcf { template<> struct Type<long long, MulSpecifier> : public TypeImpl<long long, MulSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long long,  fcf::MulSpecifier);
namespace fcf { template<> struct Type<long long, DivSpecifier> : public TypeImpl<long long, DivSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long long,  fcf::DivSpecifier);


FCF_TYPE_REGISTRATION(unsigned long long, "unsigned long long", FCF_UINT64_TYPE_INDEX);
namespace fcf { template<> struct Type<unsigned long long, LessSpecifier> : public TypeImpl<unsigned long long, LessSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned long long,  fcf::LessSpecifier);
namespace fcf { template<> struct Type<unsigned long long, EqualSpecifier> : public TypeImpl<unsigned long long, EqualSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned long long,  fcf::EqualSpecifier);
namespace fcf { template<> struct Type<unsigned long long, AddSpecifier> : public TypeImpl<unsigned long long, AddSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned long long,  fcf::AddSpecifier);
namespace fcf { template<> struct Type<unsigned long long, SubSpecifier> : public TypeImpl<unsigned long long, SubSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned long long,  fcf::SubSpecifier);
namespace fcf { template<> struct Type<unsigned long long, BoolSpecifier> : public TypeImpl<unsigned long long, BoolSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned long long,  fcf::BoolSpecifier);
namespace fcf { template<> struct Type<unsigned long long, MulSpecifier> : public TypeImpl<unsigned long long, MulSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned long long,  fcf::MulSpecifier);
namespace fcf { template<> struct Type<unsigned long long, DivSpecifier> : public TypeImpl<unsigned long long, DivSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned long long,  fcf::DivSpecifier);


FCF_TYPE_REGISTRATION(float,              "float",              FCF_FLOAT32_TYPE_INDEX);
namespace fcf { template<> struct Type<float, LessSpecifier> : public TypeImpl<float, LessSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(float,  fcf::LessSpecifier);
namespace fcf { template<> struct Type<float, EqualSpecifier> : public TypeImpl<float, EqualSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(float,  fcf::EqualSpecifier);
namespace fcf { template<> struct Type<float, AddSpecifier> : public TypeImpl<float, AddSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(float,  fcf::AddSpecifier);
namespace fcf { template<> struct Type<float, SubSpecifier> : public TypeImpl<float, SubSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(float,  fcf::SubSpecifier);
namespace fcf { template<> struct Type<float, BoolSpecifier> : public TypeImpl<float, BoolSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(float,  fcf::BoolSpecifier);
namespace fcf { template<> struct Type<float, MulSpecifier> : public TypeImpl<float, MulSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(float,  fcf::MulSpecifier);
namespace fcf { template<> struct Type<float, DivSpecifier> : public TypeImpl<float, DivSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(float,  fcf::DivSpecifier);


FCF_TYPE_REGISTRATION(double,             "double",             FCF_FLOAT64_TYPE_INDEX);
namespace fcf { template<> struct Type<double, LessSpecifier> : public TypeImpl<double, LessSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(double,  fcf::LessSpecifier);
namespace fcf { template<> struct Type<double, EqualSpecifier> : public TypeImpl<double, EqualSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(double,  fcf::EqualSpecifier);
namespace fcf { template<> struct Type<double, AddSpecifier> : public TypeImpl<double, AddSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(double,  fcf::AddSpecifier);
namespace fcf { template<> struct Type<double, SubSpecifier> : public TypeImpl<double, SubSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(double,  fcf::SubSpecifier);
namespace fcf { template<> struct Type<double, BoolSpecifier> : public TypeImpl<double, BoolSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(double,  fcf::BoolSpecifier);
namespace fcf { template<> struct Type<double, MulSpecifier> : public TypeImpl<double, MulSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(double,  fcf::MulSpecifier);
namespace fcf { template<> struct Type<double, DivSpecifier> : public TypeImpl<double, DivSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(double,  fcf::DivSpecifier);


FCF_TYPE_REGISTRATION(long double,        "long double",        FCF_FLOAT128_TYPE_INDEX);
namespace fcf { template<> struct Type<long double, LessSpecifier> : public TypeImpl<long double, LessSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long double,  fcf::LessSpecifier);
namespace fcf { template<> struct Type<long double, EqualSpecifier> : public TypeImpl<long double, EqualSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long double,  fcf::EqualSpecifier);
namespace fcf { template<> struct Type<long double, AddSpecifier> : public TypeImpl<long double, AddSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long double,  fcf::AddSpecifier);
namespace fcf { template<> struct Type<long double, SubSpecifier> : public TypeImpl<long double, SubSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long double,  fcf::SubSpecifier);
namespace fcf { template<> struct Type<long double, BoolSpecifier> : public TypeImpl<long double, BoolSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long double,  fcf::BoolSpecifier);
namespace fcf { template<> struct Type<long double, MulSpecifier> : public TypeImpl<long double, MulSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long double,  fcf::MulSpecifier);
namespace fcf { template<> struct Type<long double, DivSpecifier> : public TypeImpl<long double, DivSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long double,  fcf::DivSpecifier);


FCF_TYPE_REGISTRATION(long int,           "long int",  0);
namespace fcf { template<> struct Type<long int, LessSpecifier> : public TypeImpl<long int, LessSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long int,  fcf::LessSpecifier);
namespace fcf { template<> struct Type<long int, EqualSpecifier> : public TypeImpl<long int, EqualSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long int,  fcf::EqualSpecifier);
namespace fcf { template<> struct Type<long int, AddSpecifier> : public TypeImpl<long int, AddSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long int,  fcf::AddSpecifier);
namespace fcf { template<> struct Type<long int, SubSpecifier> : public TypeImpl<long int, SubSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long int,  fcf::SubSpecifier);
namespace fcf { template<> struct Type<long int, BoolSpecifier> : public TypeImpl<long int, BoolSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long int,  fcf::BoolSpecifier);
namespace fcf { template<> struct Type<long int, MulSpecifier> : public TypeImpl<long int, MulSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long int,  fcf::MulSpecifier);
namespace fcf { template<> struct Type<long int, DivSpecifier> : public TypeImpl<long int, DivSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(long int,  fcf::DivSpecifier);


FCF_TYPE_REGISTRATION(unsigned long int,  "unsigned long int",  0);
namespace fcf { template<> struct Type<unsigned long int, LessSpecifier> : public TypeImpl<unsigned long int, LessSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned long int,  fcf::LessSpecifier);
namespace fcf { template<> struct Type<unsigned long int, EqualSpecifier> : public TypeImpl<unsigned long int, EqualSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned long int,  fcf::EqualSpecifier);
namespace fcf { template<> struct Type<unsigned long int, AddSpecifier> : public TypeImpl<unsigned long int, AddSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned long int,  fcf::AddSpecifier);
namespace fcf { template<> struct Type<unsigned long int, SubSpecifier> : public TypeImpl<unsigned long int, SubSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned long int,  fcf::SubSpecifier);
namespace fcf { template<> struct Type<unsigned long int, BoolSpecifier> : public TypeImpl<unsigned long int, BoolSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned long int,  fcf::BoolSpecifier);
namespace fcf { template<> struct Type<unsigned long int, MulSpecifier> : public TypeImpl<unsigned long int, MulSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned long int,  fcf::MulSpecifier);
namespace fcf { template<> struct Type<unsigned long int, DivSpecifier> : public TypeImpl<unsigned long int, DivSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(unsigned long int,  fcf::DivSpecifier);


FCF_TYPE_REGISTRATION_SINGLE(void,        "void",               20);

FCF_TYPE_REGISTRATION(bool,               "bool",               21);
namespace fcf { template<> struct Type<bool, LessSpecifier> : public TypeImpl<bool, LessSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(bool,  fcf::LessSpecifier);
namespace fcf { template<> struct Type<bool, EqualSpecifier> : public TypeImpl<bool, EqualSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(bool,  fcf::EqualSpecifier);
namespace fcf { template<> struct Type<bool, AddSpecifier> : public TypeImpl<bool, AddSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(bool,  fcf::AddSpecifier);
namespace fcf { template<> struct Type<bool, SubSpecifier> : public TypeImpl<bool, SubSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(bool,  fcf::SubSpecifier);
namespace fcf { template<> struct Type<bool, BoolSpecifier> : public TypeImpl<bool, BoolSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(bool,  fcf::BoolSpecifier);
namespace fcf { template<> struct Type<bool, MulSpecifier> : public TypeImpl<bool, MulSpecifier> {
  void call(bool* a_destination, const bool* a_left, const bool* a_right){
    *a_destination = *a_left && *a_right;
  }
}; }
FCF_SPECIFIER_REGISTRATION(bool,  fcf::MulSpecifier);
namespace fcf { template<> struct Type<bool, DivSpecifier> : public TypeImpl<bool, DivSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(bool,  fcf::DivSpecifier);


FCF_TYPE_REGISTRATION(std::string,        "std::string",        30);
namespace fcf { template<> struct Type<std::string, LessSpecifier> : public TypeImpl<std::string, LessSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(std::string,  fcf::LessSpecifier);
namespace fcf { template<> struct Type<std::string, EqualSpecifier> : public TypeImpl<std::string, EqualSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(std::string,  fcf::EqualSpecifier);
namespace fcf { template<> struct Type<std::string, AddSpecifier> : public TypeImpl<std::string, AddSpecifier> {}; }
FCF_SPECIFIER_REGISTRATION(std::string,  fcf::AddSpecifier);
namespace fcf { template<> struct Type<std::string, BoolSpecifier> : public TypeImpl<std::string, BoolSpecifier> {
  bool call(const std::string* a_value){
    return !a_value->empty();
  }
}; }
FCF_SPECIFIER_REGISTRATION(std::string,  fcf::BoolSpecifier);


FCF_TEMPLATE_TYPE_REGISTRATION((fcf, BasicVariant),
                            "fcf::BasicVariant",
                            (size_t InnerBufferSize),
                            (InnerBufferSize),
                            (std::to_string(InnerBufferSize))
                            );

FCF_TEMPLATE_SPECIFIER_REGISTRATION((fcf, BasicVariant), ResolveSpecifier);
namespace fcf { template<size_t InnerBufferSize> struct Type<fcf::BasicVariant<InnerBufferSize>, LessSpecifier> : public TypeImpl<fcf::BasicVariant<InnerBufferSize>, LessSpecifier> {}; }
FCF_TEMPLATE_SPECIFIER_REGISTRATION((fcf, BasicVariant), LessSpecifier);
namespace fcf { template<size_t InnerBufferSize> struct Type<fcf::BasicVariant<InnerBufferSize>, EqualSpecifier> : public TypeImpl<fcf::BasicVariant<InnerBufferSize>, EqualSpecifier> {}; }
FCF_TEMPLATE_SPECIFIER_REGISTRATION((fcf, BasicVariant), EqualSpecifier);
namespace fcf { template<size_t InnerBufferSize> struct Type<fcf::BasicVariant<InnerBufferSize>, AddSpecifier> : public TypeImpl<fcf::BasicVariant<InnerBufferSize>, AddSpecifier> {}; }
FCF_TEMPLATE_SPECIFIER_REGISTRATION((fcf, BasicVariant),  AddSpecifier);
namespace fcf { template<size_t InnerBufferSize> struct Type<fcf::BasicVariant<InnerBufferSize>, SubSpecifier> : public TypeImpl<fcf::BasicVariant<InnerBufferSize>, SubSpecifier> {}; }
FCF_TEMPLATE_SPECIFIER_REGISTRATION((fcf, BasicVariant),  SubSpecifier);
namespace fcf { template<size_t InnerBufferSize> struct Type<fcf::BasicVariant<InnerBufferSize>, BoolSpecifier> : public TypeImpl<fcf::BasicVariant<InnerBufferSize>, BoolSpecifier> {}; }
FCF_TEMPLATE_SPECIFIER_REGISTRATION((fcf, BasicVariant),  BoolSpecifier);
namespace fcf { template<size_t InnerBufferSize> struct Type<fcf::BasicVariant<InnerBufferSize>, MulSpecifier> : public TypeImpl<fcf::BasicVariant<InnerBufferSize>, MulSpecifier> {}; }
FCF_TEMPLATE_SPECIFIER_REGISTRATION((fcf, BasicVariant),  MulSpecifier);
namespace fcf { template<size_t InnerBufferSize> struct Type<fcf::BasicVariant<InnerBufferSize>, DivSpecifier> : public TypeImpl<fcf::BasicVariant<InnerBufferSize>, DivSpecifier> {}; }
FCF_TEMPLATE_SPECIFIER_REGISTRATION((fcf, BasicVariant),  DivSpecifier);

namespace fcf {

  template <size_t InnerBufferSize>
  struct Cursor< BasicVariant<InnerBufferSize> > : public VariantCursor< BasicVariant<InnerBufferSize> >{
    typedef VariantCursor< BasicVariant<InnerBufferSize> > BaseType;
    using VariantCursor< BasicVariant<InnerBufferSize> >::VariantCursor;
  };

  template <size_t InnerBufferSize>
  struct Type<BasicVariant<InnerBufferSize>, ContainerAccessSpecifier>: public TypeImpl<BasicVariant<InnerBufferSize>, ContainerAccessSpecifier>{
  };


} // fcf namespace
FCF_SPECIFIER_REGISTRATION(fcf::Variant,  fcf::ContainerAccessSpecifier);


FCF_TYPE_REGISTRATION(fcf::UniversalPack,       "fcf::UniversalPack",         0);


FCF_TYPE_REGISTRATION(fcf::Nop, "fcf::Nop", 0);

FCF_TEMPLATE_TYPE_REGISTRATION((fcf, ContainerAccess),
                            "fcf::ContainerAccess",
                            (typename Ty),
                            (Ty),
                            (::fcf::Type<Ty>().name())
                            );

FCF_TEMPLATE_TYPE_REGISTRATION((fcf, DynamicContainerAccess),
                            "fcf::DynamicContainerAccess",
                            (typename Ty),
                            (Ty),
                            (::fcf::Type<Ty>().name())
                            );


FCF_TEMPLATE_TYPE_REGISTRATION((std, vector), "std::vector", (typename Ty), (Ty), (::fcf::Type<Ty>().name()));
namespace fcf {
  template <typename Ty>
  struct Type<std::vector<Ty>, ContainerAccessSpecifier>: public TypeImpl<std::vector<Ty>, ContainerAccessSpecifier>{
  };
} // fcf namespace
namespace fcf {
  template <typename Ty>
  struct Type<const std::vector<Ty>, ContainerAccessSpecifier>: public TypeImpl<const std::vector<Ty>, ContainerAccessSpecifier>{
  };
} // fcf namespace
FCF_TEMPLATE_SPECIFIER_REGISTRATION((std, vector), ContainerAccessSpecifier);


FCF_TEMPLATE_TYPE_REGISTRATION((std, list), "std::list", (typename Ty), (Ty), (Type<Ty>().name()));
namespace fcf {
  template <typename Ty>
  struct Type<std::list<Ty>, ContainerAccessSpecifier>: public TypeImpl<std::list<Ty>, ContainerAccessSpecifier>{
  };
} // fcf namespace
FCF_TEMPLATE_SPECIFIER_REGISTRATION((std, list), ContainerAccessSpecifier);



FCF_TEMPLATE_TYPE_REGISTRATION((std, set), "std::set", (typename Ty), (Ty), (Type<Ty>().name()));
namespace fcf {
  template <typename Ty>
  struct Type<std::set<Ty>, ContainerAccessSpecifier>: public TypeImpl<std::set<Ty>, ContainerAccessSpecifier>{
  };
} // fcf namespace
FCF_TEMPLATE_SPECIFIER_REGISTRATION((std, set), ContainerAccessSpecifier);



FCF_TEMPLATE_TYPE_REGISTRATION((std, map), "std::map", (typename TKey, typename TValue), (TKey, TValue), (Type<TKey>().name()+","+Type<TValue>().name()));
namespace fcf {
  template <typename TKey, typename TValue>
  struct Type<std::map<TKey, TValue>, ContainerAccessSpecifier>: public TypeImpl<std::map<TKey, TValue>, ContainerAccessSpecifier>{
  };
} // fcf namespace
FCF_TEMPLATE_SPECIFIER_REGISTRATION((std, map), ContainerAccessSpecifier);

#endif // #ifndef _FCF_BASIS__BITS__REGISTRY_HPP___
