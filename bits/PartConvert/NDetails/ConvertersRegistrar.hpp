#ifndef ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__CONVERTERS_REGISTRAR_HPP___
#define ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__CONVERTERS_REGISTRAR_HPP___

#include <tuple>
#include "../../../Type.hpp"
#include "../../../bits/PartConvert/NDetails/setConverter.hpp"

namespace fcf::NDetails {

  template <int Index>
  struct ConvertersRegistrarMarker;

  template <int UnstaticCounter, int Index, typename = void>
  struct ConvertersRegistrarMarkerExists{
    enum { value = false };
  };

  template <int UnstaticCounter, int Index>
  struct ConvertersRegistrarMarkerExists<UnstaticCounter, Index, decltype(void(ConvertersRegistrarMarker<Index>()))>{
    enum { value = true };
  };

  template <int UnstaticCounter, int Index = -1, bool Exists = true>
  struct ConvertersRegistrarMarkerEnd {
    enum { value = ConvertersRegistrarMarkerEnd<UnstaticCounter, Index + 1, ConvertersRegistrarMarkerExists<UnstaticCounter, Index+1>::value  >::value } ;
  };

  template <int UnstaticCounter, int Index>
  struct ConvertersRegistrarMarkerEnd<UnstaticCounter, Index, false> {
    enum { value = Index } ;
  };

  template <typename TCurrent, bool EnableToConvertion, bool EnableFromConversion>
  struct ConvertersRegistrarItem;

  template <typename TCurrent>
  struct ConvertersRegistrarItem<TCurrent, true, true> {
    void operator()(const TCurrent&){
    }

    template <typename TItem>
    void operator()(const TItem&){
      setConverter<TCurrent, TItem>();
      setConverter<TItem, TCurrent>();
    }
  };

  template <typename TCurrent>
  struct ConvertersRegistrarItem<TCurrent, true, false> {
    void operator()(const TCurrent&){
    }
    template <typename TItem>
    void operator()(const TItem&){
      setConverter<TItem, TCurrent>();
    }
  };

  template <typename TCurrent>
  struct ConvertersRegistrarItem<TCurrent, false, true> {
    void operator()(const TCurrent&){
    }
    template <typename TItem>
    void operator()(const TItem&){
      setConverter<TCurrent, TItem>();
    }
  };

  template <typename TCurrent>
  struct ConvertersRegistrarItem<TCurrent, false, false> {
    void operator()(const TCurrent&){
    }
    template <typename TItem>
    void operator()(const TItem&){
    }
  };

  template <int Index, int Size, typename TCurrent, bool EnableFront, bool EnableBack, typename ... TPack>
  struct ConvertersRegistrarWalker {
    void operator()(){
      enum { toConvertion = EnableFront && ConvertersRegistrarMarker<Index>::fromConversion };
      enum { fromConvertion = EnableBack && ConvertersRegistrarMarker<Index>::toConversion };
      ConvertersRegistrarItem<TCurrent, toConvertion, fromConvertion>()( *((typename ConvertersRegistrarMarker<Index>::type*)0)  );
      ConvertersRegistrarWalker<Index+1, Size, TCurrent, EnableFront, EnableBack,  TPack..., typename ConvertersRegistrarMarker<Index>::type>()();
    }
  };

  template <int Size, typename TCurrent, bool EnableFront, bool EnableBack, typename ... TPack>
  struct ConvertersRegistrarWalker<Size, Size, TCurrent, EnableFront, EnableBack, TPack...> {
    void operator()(){
      //ConvertersRegistrar<TCurrent, EnableFront, EnableBack, TPack...>()();
    }
  };

  template <int UnstaticCounter, typename TCurrent, int Size, bool EnableFront, bool EnableBack>
  struct ConvertersRegistrarInitializer {
    ConvertersRegistrarInitializer(){
      ConvertersRegistrarWalker<
        0,
        Size,
        TCurrent,
        EnableFront,
        EnableBack
        >()();
    }
  };

} // fcf::NDetails namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__CONVERTERS_REGISTRAR_HPP___
