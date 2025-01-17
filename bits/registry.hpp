#ifndef ___FCF_BASIS__REGISTRY_HPP___
#define ___FCF_BASIS__REGISTRY_HPP___

#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>

#include "../macro.hpp"
#include "../nativeType.hpp"
#include "./TypeIdSource.hpp"
#include "./TypeInitializer.hpp"

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
FCF_TYPEID_REGISTRY(bool,               "bool",               20);
FCF_TYPEID_REGISTRY(std::string,        "std::string",        30);

FCF_TYPEID_TEMPLATE1_REGISTRY(std::vector, (std::string() + "std::vector<" + fcf::Type<T1>::name() + ">"));
FCF_TYPEID_TEMPLATE1_REGISTRY(std::list, (std::string() +"std::list<" + fcf::Type<T1>::name() + ">"));
FCF_TYPEID_TEMPLATE1_REGISTRY(std::set, (std::string() +"std::set<" + fcf::Type<T1>::name() + ">"));
FCF_TYPEID_TEMPLATE2_REGISTRY(std::map, (std::string() +"std::map<" + fcf::Type<T1>::name() + "," + fcf::Type<T2>::name() + ">"));

#endif // #ifndef ___FCF_BASIS__REGISTRY_HPP___
