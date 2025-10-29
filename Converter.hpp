/*
#ifndef ___FCF_BASIS__CONVERTER_HPP___
#define ___FCF_BASIS__CONVERTER_HPP___

#include <algorithm>
#include <string>
#include <sstream>
#include "Variant.hpp"

namespace fcf {

  template <typename TDestination, typename TSource, typename TSpecificator = DefaultConvertSpecificator>
  class Converter{
    public:
      void operator()(TDestination& a_destination, const TSource& a_source, void* a_convertOptions = 0){
        a_destination = (TDestination)a_source;
      }
  };

  template <typename TSource>
  class Converter<std::string, TSource>{
    public:
      void operator()(std::string& a_destination, const TSource& a_source, void* a_convertOptions = 0){
        a_destination = std::to_string(a_source);
      }
  };

  template <typename TDestination>
  class Converter<TDestination, std::string>{
    public:
      void operator()(TDestination& a_destination, const std::string& a_source, void* a_convertOptions = 0){
        std::istringstream iss(a_source);
        char c = 0;
        TDestination result;
        iss >> result;
        if (iss.fail() || (iss.get(c)))  {
          throw std::runtime_error(std::string() + "Invaid string format for '" + Type<TDestination>().name() + "' type");
        }
        std::swap(a_destination, result);
      }
  };

  template <>
  class Converter<std::string, std::string>{
    public:
      void operator()(std::string& a_destination, const std::string& a_source, void* a_convertOptions = 0){
        a_destination = a_source;
      }
  };

  template <typename TSource>
  class Converter<Variant, TSource>{
    public:
      void operator()(Variant& a_destination, const TSource& a_source, void* a_convertOptions = 0){
        a_destination = a_source;
      }
  };

  template <typename TDestination>
  class Converter<TDestination, Variant>{
    public:
      void operator()(TDestination& a_destination, const Variant& a_source, void* a_convertOptions = 0){
        a_destination = a_source.cast<TDestination>();
      }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__CONVERTER_HPP___
*/
