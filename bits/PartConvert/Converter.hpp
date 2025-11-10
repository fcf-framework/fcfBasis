#ifndef ___FCF_BASIS__BITS__PART_CONVERT__CONVERTER_HPP___
#define ___FCF_BASIS__BITS__PART_CONVERT__CONVERTER_HPP___

#include <algorithm>
#include <string>
#include <sstream>
#include "ConvertOptions.hpp"
#include "../PartType/Type.hpp"
#include "../PartConvert/DefaultConvertMode.hpp"

namespace fcf {

  template <typename TDestination, typename TSource, typename TSpecificator = DefaultConvertMode>
  class Converter{
    public:
      void operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        a_destination = (TDestination)a_source;
      }
  };

  template <typename TSource>
  class Converter<std::string, TSource>{
    public:
      void operator()(std::string& a_destination, const TSource& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        a_destination = std::to_string(a_source);
      }
  };

  template <typename TDestination>
  class Converter<TDestination, std::string>{
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
  class Converter<std::string, std::string>{
    public:
      void operator()(std::string& a_destination, const std::string& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        a_destination = a_source;
      }
  };
} // fcf namespace

#include "../../Variant.hpp"

namespace fcf {
  template <typename TSource>
  class Converter<Variant, TSource>{
    public:
      void operator()(Variant& a_destination, const TSource& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        a_destination = a_source;
      }
  };

  template <typename TDestination>
  class Converter<TDestination, Variant>{
    public:
      void operator()(TDestination& a_destination, const Variant& a_source, ConvertOptions* a_convertOptions = 0){
        (void)a_convertOptions;
        a_destination = a_source.cast<TDestination>();
      }
  };

} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CONVERT__CONVERTER_HPP___
