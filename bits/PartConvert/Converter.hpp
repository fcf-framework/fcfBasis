#ifndef ___FCF_BASIS__BITS__PART_CONVERT__CONVERTER_HPP___
#define ___FCF_BASIS__BITS__PART_CONVERT__CONVERTER_HPP___

#include <algorithm>
#include <string>
#include <sstream>
#include "ConvertOptions.hpp"
#include "../PartType/Type.hpp"
#include "../PartConvert/DefaultConvertMode.hpp"
#include "../../Variant.hpp"

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
          throw std::runtime_error(std::string() + "Ne ne string format for '" + Type<TDestination>().name() + "' type");
        }
        std::swap(a_destination, result);
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

#include "../../Variant.hpp"

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
