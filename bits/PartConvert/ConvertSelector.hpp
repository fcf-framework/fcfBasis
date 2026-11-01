#ifndef _FCF_BASIS__BITS__PART_CONVERT__CONVERT_SELECTOR_HPP___
#define _FCF_BASIS__BITS__PART_CONVERT__CONVERT_SELECTOR_HPP___

#include "Converter.hpp"

namespace fcf {

  namespace NDetails {

    // Search order 3 -> 1 -> 2 -> 0

    template <typename TDestination, typename TSource>
    struct ConverSelectorMode0{
      inline void operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions* a_convertOptions, Error& a_error); /*{
        return Converter<0, TDestination, TSource>()(a_destination, a_source, a_convertOptions, a_error);
      }
      */
    };

    template <typename TDestination, typename TSource, typename = void>
    struct ConverSelectorMode2{
      inline void operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions* a_convertOptions, Error& a_error){
        return ConverSelectorMode0<TDestination, TSource>()(a_destination, a_source, a_convertOptions, a_error);
      }
    };

    template <typename TDestination, typename TSource>
    struct ConverSelectorMode2<TDestination, TSource, decltype((void)Converter<2, TDestination, TSource>()) >{
      inline void operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions* a_convertOptions, Error& a_error); /*{
        return Converter<2, TDestination, TSource>()(a_destination, a_source, a_convertOptions, a_error);
      }
      */
    };

    template <typename TDestination, typename TSource, typename = void>
    struct ConverSelectorMode1{
      inline void operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions* a_convertOptions, Error& a_error){
        return ConverSelectorMode2<TDestination, TSource>()(a_destination, a_source, a_convertOptions, a_error);
      }
    };

    template <typename TDestination, typename TSource>
    struct ConverSelectorMode1<TDestination, TSource, decltype((void)Converter<1, TDestination, TSource>())>{
      inline void operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions* a_convertOptions, Error& a_error); /*{
        return Converter<1, TDestination, TSource>()(a_destination, a_source, a_convertOptions, a_error);
      }
      */
    };

    template <typename TDestination, typename TSource, typename = void>
    struct ConverSelectorMode3{
      inline void operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions* a_convertOptions, Error& a_error){
        return ConverSelectorMode1<TDestination, TSource>()(a_destination, a_source, a_convertOptions, a_error);
      }
    };

    template <typename TDestination, typename TSource>
    struct ConverSelectorMode3<TDestination, TSource, decltype((void)Converter<3, TDestination, TSource>())>{
      inline void operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions* a_convertOptions, Error& a_error); /*{
        return Converter<3, TDestination, TSource>()(a_destination, a_source, a_convertOptions, a_error);
      }
      */
    };

  } // NDetails namespace

  template <typename TDestination, typename TSource>
  struct ConvertSelector {
    inline void operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions* a_convertOptions, Error& a_error){
      return NDetails::ConverSelectorMode3<TDestination, TSource>()(a_destination, a_source, a_convertOptions, a_error);
    }
    inline void operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions* a_convertOptions, Error&& a_error = Error{true}){
      return NDetails::ConverSelectorMode3<TDestination, TSource>()(a_destination, a_source, a_convertOptions, a_error);
    }
  };
} // fcf namespace

#include "Converter.hpp"

namespace fcf {
  namespace NDetails {

    template <typename TDestination, typename TSource>
    void ConverSelectorMode0<TDestination, TSource>::operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions* a_convertOptions, Error& a_error){
      return Converter<0, TDestination, TSource>()(a_destination, a_source, a_convertOptions, a_error);
    }

    template <typename TDestination, typename TSource>
    inline void ConverSelectorMode2<TDestination, TSource, decltype((void)Converter<2, TDestination, TSource>()) >::operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions* a_convertOptions, Error& a_error){
      return Converter<2, TDestination, TSource>()(a_destination, a_source, a_convertOptions, a_error);
    };

    template <typename TDestination, typename TSource>
    inline void ConverSelectorMode1<TDestination, TSource, decltype((void)Converter<1, TDestination, TSource>())>::operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions* a_convertOptions, Error& a_error){
      return Converter<1, TDestination, TSource>()(a_destination, a_source, a_convertOptions, a_error);
    }

    template <typename TDestination, typename TSource>
    inline void ConverSelectorMode3<TDestination, TSource, decltype((void)Converter<3, TDestination, TSource>())>::operator()(TDestination& a_destination, const TSource& a_source, ConvertOptions* a_convertOptions, Error& a_error){
      return Converter<3, TDestination, TSource>()(a_destination, a_source, a_convertOptions, a_error);
    };


  } // NDetails namespace
} // fcf namespace

#endif // #ifndef _FCF_BASIS__BITS__PART_CONVERT__CONVERT_SELECTOR_HPP___
