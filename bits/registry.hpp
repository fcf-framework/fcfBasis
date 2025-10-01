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
#include "../Variant.hpp"
#include "./PartIterator/DynamicIterator.hpp"

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

namespace fcf {
  class Variant;
} // fcf namespace
FCF_TYPEID_REGISTRY(fcf::Variant,       "fcf::Variant",         31);
FCF_SPECIFICATOR_REGISTRY(fcf::Variant, fcf::RawDataSpecificator);

FCF_TYPEID_REGISTRY(fcf::Nop, "fcf::Nop", 0);

FCF_TYPEID_TEMPLATE1_REGISTRY(std::vector, "std::vector");
FCF_TYPEID_SUBTEMPLATE1_REGISTRY(fcf::DynamicIterator<std::vector, "fcf::VectorDynamicIterator<std::vector");

namespace fcf {
  template <typename Ty>
  class TemplateSpecializationInitializer< std::vector<Ty> > {
    public:
      typedef std::vector<Ty> type;
      void operator()(){
        SpecificatorTypeRegistrator<type, DynamicIteratorSpecificator> regDIS;
      }
  };
} // fcf namespace

FCF_TYPEID_REGISTRY(std::vector<char>,            "std::vector<char>",            0);
FCF_TYPEID_REGISTRY(std::vector<unsigned char>,   "std::vector<unsigned char>",   0);
FCF_TYPEID_REGISTRY(std::vector<short>,           "std::vector<short>",           0);
FCF_TYPEID_REGISTRY(std::vector<unsigned short>,  "std::vector<unsigned short>",  0);
FCF_TYPEID_REGISTRY(std::vector<int>,             "std::vector<int>",             0);
FCF_TYPEID_REGISTRY(std::vector<unsigned int>,    "std::vector<unsigned int>",    0);
//FCF_TYPEID_REGISTRY(std::vector<char>::iterator, "fcf::vector<char>::iterator", 0);


//FCF_TYPEID_REGISTRY_IMPL_DECL_CLASS((std::vector<T1>::iterator), (typename T1), "it", 0, std::vector<T1>::iterator) \
//FCF_TYPEID_TEMPLATE1_SUBTYPE_REGISTRY(std::vector, iterator, "std::vector", "iterator");

FCF_TYPEID_TEMPLATE1_REGISTRY(std::list, "std::list");
FCF_TYPEID_TEMPLATE1_REGISTRY(std::set, "std::set");
FCF_TYPEID_TEMPLATE2_REGISTRY(std::map, "std::map");


#endif // #ifndef ___FCF_BASIS__BITS__REGISTRY_HPP___
