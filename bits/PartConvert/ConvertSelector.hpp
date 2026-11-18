#ifndef _FCF_BASIS__BITS__PART_CONVERT__CONVERT_SELECTOR_HPP___
#define _FCF_BASIS__BITS__PART_CONVERT__CONVERT_SELECTOR_HPP___

#include "Converter.hpp"

namespace fcf {

  namespace NDetails {

    // Search order 7 -> ... ->3 -> 2 -> 1 -> 0

    template <int ConverterLevelValue, typename TDestination, typename TSource, typename TFormat>
    struct ConverSelectorNext{
      inline void operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions& a_convertOptions, Error& a_error);
    };

    template <typename TDestination, typename TSource, typename TFormat>
    struct ConverSelectorNext<0, TDestination, TSource, TFormat>{
      inline void operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions& a_convertOptions, Error& a_error);
    };



    template <int ConverterLevelValue, typename TDestination, typename TSource, typename TFormat, typename = void>
    struct ConverSelectorMode {
      inline void operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions& a_convertOptions, Error& a_error){
        return ConverSelectorNext<(int)ConverterLevelValue-1, TDestination, TSource, TFormat>()(a_destination, a_source, a_convertOptions, a_error);
      }
    };

    template <int ConverterLevelValue, typename TDestination, typename TSource, typename TFormat>
    struct ConverSelectorMode<ConverterLevelValue, TDestination, TSource, TFormat, decltype((void)Converter<(ConverterLevel)ConverterLevelValue, TDestination, TSource, TFormat>())>{
      inline void operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions& a_convertOptions, Error& a_error);
    };

  } // NDetails namespace

  template <typename TDestination, typename TSource, typename TFormat = DefaultConvertMode>
  struct ConvertSelector {
    inline void operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions& a_convertOptions, Error& a_error){
      return NDetails::ConverSelectorMode<CL_DIRECT, TDestination, TSource, TFormat>()(a_destination, a_source, a_convertOptions, a_error);
    }
    inline void operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions& a_convertOptions, Error&& a_error = Error{true}){
      return NDetails::ConverSelectorMode<CL_DIRECT, TDestination, TSource, TFormat>()(a_destination, a_source, a_convertOptions, a_error);
    }
  };

} // fcf namespace

#include "Converter.hpp"

namespace fcf {
  namespace NDetails {

    template <int ConverterLevelValue, typename TDestination, typename TSource, typename TFormat>
    void ConverSelectorNext<ConverterLevelValue, TDestination, TSource, TFormat>::operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions& a_convertOptions, Error& a_error){
      return ConverSelectorMode<ConverterLevelValue, TDestination, TSource, TFormat>()(a_destination, a_source, a_convertOptions, a_error);
    }

    template <typename TDestination, typename TSource, typename TFormat>
    void ConverSelectorNext<0, TDestination, TSource, TFormat>::operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions& a_convertOptions, Error& a_error){
      return Converter<CL_ALL_LOW, TDestination, TSource, TFormat>()(a_destination, a_source, a_convertOptions, a_error);
    }



    template <int ConverterLevelValue, typename TDestination, typename TSource, typename TFormat>
    void ConverSelectorMode<ConverterLevelValue, TDestination, TSource, TFormat, decltype((void)Converter<(ConverterLevel)ConverterLevelValue, TDestination, TSource, TFormat>())>::operator()(TDestination& a_destination, 
                                                                                                                                                   const TSource& a_source, 
                                                                                                                                                   ConvertOptions& a_convertOptions, 
                                                                                                                                                   Error& a_error){
      return Converter<(ConverterLevel)ConverterLevelValue, TDestination, TSource, TFormat>()(a_destination, a_source, a_convertOptions, a_error);
    }


  } // NDetails namespace
} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_CONVERT__CONVERT_SELECTOR_HPP___
