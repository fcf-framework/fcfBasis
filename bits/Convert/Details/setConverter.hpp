#ifndef ___FCF_BASIS__BITS__CONVERT__DETAILS__SET_CONVERTER_HPP___
#define ___FCF_BASIS__BITS__CONVERT__DETAILS__SET_CONVERTER_HPP___

#include "convertWrapper.hpp"
#include "../../../bits/PartType/Type.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace Convert {
        template <typename TSource, typename TDestination>
        inline void setConverter() {
          ::fcf::Type<TSource>()._info->converters[::fcf::Type<TDestination>().index()] = (ConvertFunction)Details::Basis::Convert::convertWrapper<TDestination, TSource>;
          ::fcf::Type<TDestination>()._info->backConverters[::fcf::Type<TSource>().index()] = (ConvertFunction)Details::Basis::Convert::convertWrapper<TDestination, TSource>;
        }
      } // Convert namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace


#endif // #ifndef ___FCF_BASIS__BITS__CONVERT__DETAILS__SET_CONVERTER_HPP___

