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
#include "Type/TypeInitializer.hpp"
#include "./PartContainerAccess/ContainerAccess.hpp"
#include "Type/DynamicIteratorSpecificator/Type_DynamicIteratorSpecificator.hpp"
#include "../Variant.hpp"
#include "../bits/PartType/NDetails/TypeRegistrar.hpp"

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
FCF_TYPEID_REGISTRY(unsigned long int,  "unsigned long int",  0);
FCF_TYPEID_REGISTRY_SINGLE(void,        "void",               20);
FCF_TYPEID_REGISTRY(bool,               "bool",               21);
FCF_TYPEID_REGISTRY(std::string,        "std::string",        30);

FCF_TYPEID_REGISTRY(fcf::Variant,       "fcf::Variant",         31);
FCF_SPECIFICATOR_REGISTRY(fcf::Variant, fcf::RawDataSpecificator);

FCF_TYPEID_REGISTRY(fcf::Nop, "fcf::Nop", 0);

FCF_TEMPLATE_TYPEID_DECLARE(std::vector, "std::vector", (typename Ty), (Ty), (::fcf::Type<Ty>().name()));
FCF_TEMPLATE_SPECIFICATOR_REGISTRY(std::vector, DynamicIteratorSpecificator);

FCF_TEMPLATE_TYPEID_DECLARE(fcf::ContainerAccess, "fcf::ContainerAccess", (typename Ty), (Ty), (::fcf::Type<Ty>().name()));

FCF_TEMPLATE_TYPEID_DECLARE(std::list, "std::list", (typename Ty), (Ty), (Type<Ty>().name()));
FCF_TEMPLATE_TYPEID_DECLARE(std::set, "std::set", (typename Ty), (Ty), (Type<Ty>().name()));
FCF_TEMPLATE_TYPEID_DECLARE(std::map, "std::map", (typename TKey, typename TValue), (TKey, TValue), (Type<TKey>().name()+","+Type<TValue>().name()));


#endif // #ifndef ___FCF_BASIS__BITS__REGISTRY_HPP___
