#ifndef ___FCF_BASIS__BITS__REGISTRY_HPP___
#define ___FCF_BASIS__BITS__REGISTRY_HPP___

#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>

#include "../macro.hpp"
#include "../Nop.hpp"
#include "../nativeType.hpp"
#include "./TypeIdSource.hpp"
#include "./TypeInitializer.hpp"
#include "../Variant.hpp"

FCF_TYPEID_REGISTRY(char,               "char",               FCF_INT8_TYPE_INDEX);
FCF_TYPEID_REGISTRY(unsigned char,      "unsigned char",      FCF_UINT8_TYPE_INDEX);
FCF_TYPEID_REGISTRY(short,              "short",              FCF_INT16_TYPE_INDEX);
FCF_TYPEID_REGISTRY(unsigned short,     "unsigned short",     FCF_UINT16_TYPE_INDEX);
FCF_TYPEID_REGISTRY(int,                "int",                FCF_INT32_TYPE_INDEX);
FCF_TYPEID_REGISTRY(unsigned int,       "unsigned int",       FCF_UINT32_TYPE_INDEX);
FCF_TYPEID_REGISTRY(long long,          "long long",          FCF_INT64_TYPE_INDEX);
FCF_TYPEID_REGISTRY(unsigned long long, "unsigned long long", FCF_UINT64_TYPE_INDEX);
FCF_TYPEID_REGISTRY(float,              "float",              FCF_FLOAT32_TYPE_INDEX);
FCF_TYPEID_REGISTRY(double,             "double",             FCF_FLOAT64_TYPE_INDEX);
FCF_TYPEID_REGISTRY(long double,        "long double",        FCF_FLOAT128_TYPE_INDEX);
FCF_TYPEID_REGISTRY_SINGLE(void,        "void",               20);
FCF_TYPEID_REGISTRY(bool,               "bool",               21);
FCF_TYPEID_REGISTRY(std::string,        "std::string",        30);

namespace fcf {
  class Variant;
} // fcf namespace
FCF_TYPEID_REGISTRY(fcf::Variant,        "fcf::Variant",         31);

FCF_TYPEID_REGISTRY(fcf::Nop, "fcf::Nop", 0);

FCF_TYPEID_TEMPLATE1_REGISTRY(std::vector, "std::vector");
FCF_TYPEID_TEMPLATE1_REGISTRY(std::list, "std::list");
FCF_TYPEID_TEMPLATE1_REGISTRY(std::set, "std::set");
FCF_TYPEID_TEMPLATE2_REGISTRY(std::map, "std::map");

#endif // #ifndef ___FCF_BASIS__BITS__REGISTRY_HPP___
