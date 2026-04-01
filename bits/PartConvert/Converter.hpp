#ifndef ___FCF_BASIS__BITS__PART_CONVERT__CONVERTER_HPP___
#define ___FCF_BASIS__BITS__PART_CONVERT__CONVERTER_HPP___

#include <climits>
#include <algorithm>
#include <string>
#include <sstream>
#include "ConvertOptions.hpp"
#include "../PartType/Type.hpp"
#include "../PartConvert/DefaultConvertMode.hpp"
#include "../../PartVariant.hpp"
#include "../../bits/PartCall/FunctionSignature.hpp"
#include "../PartException/exceptions.hpp"

namespace fcf {

  template <int Mode, typename TDestination, typename TSource, typename TSpecificator = DefaultConvertMode>
  class Converter;

  template <typename TDestination, typename TSource, typename TSpecificator>
  class Converter<0, TDestination, TSource, TSpecificator>{
    public:
      void operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        a_destination = (TDestination)a_source;
      }
  };

  template <typename TSource>
  class Converter<1, std::string, TSource>{
    public:
      void operator()(std::string& a_destination, const TSource& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        a_destination = std::to_string(a_source);
      }
  };

  template <typename TDestination>
  class Converter<2, TDestination, std::string>{
    public:
      void operator()(TDestination& a_destination, const std::string& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        std::istringstream iss(a_source);
        char c = 0;
        TDestination result;
        iss >> result;
        if (iss.fail() || (iss.get(c)))  {
          throw fcf::ConvertFormatException(__FILE__, __LINE__, a_source, Type<TDestination>().name());
        }
        std::swap(a_destination, result);
      }
  };


  template <>
  class Converter<3, short, std::string>{
    public:
      void operator()(short& a_destination, const std::string& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        try {
            a_destination = std::stoi(a_source);
        } catch (const std::out_of_range&) {
          throw fcf::ConvertRangeExceededException(__FILE__, __LINE__, a_source, Type<short>().name());
        } catch (const std::invalid_argument&) {
          throw fcf::ConvertFormatException(__FILE__, __LINE__, a_source, Type<short>().name());
        }
        if (a_destination < SHRT_MIN){
           throw fcf::ConvertRangeExceededException(__FILE__, __LINE__, a_source, Type<short>().name());
        }
        if (a_destination > SHRT_MAX){
          throw fcf::ConvertRangeExceededException(__FILE__, __LINE__, a_source, Type<short>().name());
        }
      }
  };


  template <>
  class Converter<3, unsigned short, std::string>{
    public:
      void operator()(unsigned short& a_destination, const std::string& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        try {
            a_destination = (unsigned short)std::stoul(a_source);
        } catch (const std::out_of_range&) {
          throw fcf::ConvertRangeExceededException(__FILE__, __LINE__, a_source, Type<unsigned short>().name());
        } catch (const std::invalid_argument&) {
          throw fcf::ConvertFormatException(__FILE__, __LINE__, a_source, Type<unsigned short>().name());
        }
        if (a_destination > USHRT_MAX){
          throw fcf::ConvertRangeExceededException(__FILE__, __LINE__, a_source, Type<unsigned short>().name());
        }
      }
  };

  template <>
  class Converter<3, int, std::string>{
    public:
      void operator()(int& a_destination, const std::string& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        try {
            a_destination = std::stoi(a_source);
        } catch (const std::out_of_range&) {
          throw fcf::ConvertRangeExceededException(__FILE__, __LINE__, a_source, Type<int>().name());
        } catch (const std::invalid_argument&) {
          throw fcf::ConvertFormatException(__FILE__, __LINE__, a_source, Type<int>().name());
        }
      }
  };


  template <>
  class Converter<3, unsigned int, std::string>{
    public:
      void operator()(unsigned int& a_destination, const std::string& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        try {
            a_destination = std::stoul(a_source);
        } catch (const std::out_of_range&) {
          throw fcf::ConvertRangeExceededException(__FILE__, __LINE__, a_source, Type<unsigned int>().name());
        } catch (const std::invalid_argument&) {
          throw fcf::ConvertFormatException(__FILE__, __LINE__, a_source, Type<unsigned int>().name());
        }
        if (a_destination > UINT_MAX){
          throw fcf::ConvertRangeExceededException(__FILE__, __LINE__, a_source, Type<unsigned int>().name());
        }
      }
  };

  template <>
  class Converter<3, long, std::string>{
    public:
      void operator()(long& a_destination, const std::string& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        try {
            a_destination = std::stol(a_source);
        } catch (const std::out_of_range&) {
          throw fcf::ConvertRangeExceededException(__FILE__, __LINE__, a_source, Type<long>().name());
        } catch (const std::invalid_argument&) {
          throw fcf::ConvertFormatException(__FILE__, __LINE__, a_source, Type<long>().name());
        }
      }
  };

  template <>
  class Converter<3, unsigned long, std::string>{
    public:
      void operator()(unsigned long& a_destination, const std::string& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        try {
            a_destination = std::stoul(a_source);
        } catch (const std::out_of_range&) {
          throw fcf::ConvertRangeExceededException(__FILE__, __LINE__, a_source, Type<unsigned long>().name());
        } catch (const std::invalid_argument&) {
          throw fcf::ConvertFormatException(__FILE__, __LINE__, a_source, Type<unsigned long>().name());
        }
      }
  };

  template <>
  class Converter<3, long long, std::string>{
    public:
      void operator()(long long& a_destination, const std::string& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        try {
            a_destination = std::stoll(a_source);
        } catch (const std::out_of_range&) {
          throw fcf::ConvertRangeExceededException(__FILE__, __LINE__, a_source, Type<long long>().name());
        } catch (const std::invalid_argument&) {
          throw fcf::ConvertFormatException(__FILE__, __LINE__, a_source, Type<long long>().name());
        }
      }
  };

  template <>
  class Converter<3, unsigned long long, std::string>{
    public:
      void operator()(unsigned long long& a_destination, const std::string& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        try {
            a_destination = std::stoull(a_source);
        } catch (const std::out_of_range&) {
          throw fcf::ConvertRangeExceededException(__FILE__, __LINE__, a_source, Type<unsigned long long>().name());
        } catch (const std::invalid_argument&) {
          throw fcf::ConvertFormatException(__FILE__, __LINE__, a_source, Type<unsigned long long>().name());
        }
      }
  };

  template <>
  class Converter<3, std::string, std::string>{
    public:
      void operator()(std::string& a_destination, const std::string& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        a_destination = a_source;
      }
  };
/*
  template <>
  class Converter<const char*, char*>{
    public:
      void operator()(const char*& a_destination, char* a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        a_destination = a_source;
      }
  };
*/
  template <>
  class Converter<3, std::string, const char*>{
    public:
      void operator()(std::string& a_destination, const char* a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        a_destination = a_source;
      }
  };

  template <>
  class Converter<3, std::string, char*>{
    public:
      void operator()(std::string& a_destination, char* a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        a_destination = a_source;
      }
  };

  template <>
  class Converter<3, std::string, BaseFunctionSignature>{
    public:
      void operator()(std::string& a_destination, const BaseFunctionSignature& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        a_destination.clear();
        a_destination += getTypeInfo(a_source.rcode)->name;
        a_destination += " (";
        for(size_t i = 0; i < a_source.asize; ++i){
          if (i){
            a_destination += ", ";
          }
          a_destination += getTypeInfo(a_source.pacodes[i])->name;
        }
        a_destination += ")";
      }
  };

/*
  template <>
  class Converter<const char*, const char*>{
    public:
      void operator()(const char*& a_destination, const char* const& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        a_destination = a_source;
      }
  };

  template <>
  class Converter<char*, char*>{
    public:
      void operator()(char*& a_destination, char* const& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        a_destination = a_source;
      }
  };
*/
  template <typename TDestination>
  class Converter<2, TDestination, const char*>{
    public:
      void operator()(TDestination& a_destination, const char* a_source, ConvertOptions* a_convertOptions = 0);
  };

  template <typename TDestination>
  class Converter<2, TDestination, char*>{
    public:
      void operator()(TDestination& a_destination, char* a_source, ConvertOptions* a_convertOptions = 0);
  };

} // fcf namespace

#include "../../PartVariant.hpp"

namespace fcf {

 

  template <typename TSource>
  class Converter<1, Variant, TSource>{
    public:
      void operator()(Variant& a_destination, const TSource& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        a_destination = a_source;
      }
  };

  template <typename TDestination>
  class Converter<2, TDestination, Variant>{
    public:
      void operator()(TDestination& a_destination, const Variant& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        a_destination = a_source.cast<TDestination>();
      }
  };

} // fcf namespace


#include "ConvertSelector.hpp"

namespace fcf {

  template <typename TDestination>
  void Converter<2, TDestination, const char*>::operator()(TDestination& a_destination, const char* a_source, ConvertOptions* a_convertOptions){
    ConvertSelector<TDestination, std::string>()(a_destination, std::string(a_source), a_convertOptions);
  };

  template <typename TDestination>
  void Converter<2, TDestination, char*>::operator()(TDestination& a_destination, char* a_source, ConvertOptions* a_convertOptions){
    ConvertSelector<TDestination, std::string>()(a_destination, std::string(a_source), a_convertOptions);
  };

} // fcf namespace
#endif // #ifndef ___FCF_BASIS__BITS__PART_CONVERT__CONVERTER_HPP___

