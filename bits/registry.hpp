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



FCF_TYPEID_REGISTRY(char,               "char",               FCF_INT8_TYPE_INDEX);
FCF_SPECIFICATOR_REGISTRY(char*,        fcf::StoredDataTypeSpecificator);
FCF_SPECIFICATOR_REGISTRY(const char*,  fcf::StoredDataTypeSpecificator);

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
FCF_SPECIFICATOR_REGISTRY(fcf::Variant, fcf::ResolveSpecificator);

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
