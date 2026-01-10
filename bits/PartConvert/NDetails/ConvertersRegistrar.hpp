#ifndef ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__CONVERTERS_REGISTRAR_HPP___
#define ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__CONVERTERS_REGISTRAR_HPP___

#include <tuple>
#include "../../../Type.hpp"
#include "../../../bits/PartConvert/NDetails/setConverter.hpp"

namespace fcf {
  namespace NDetails {

  template <typename TCrossConvert, int Index>
  struct ConvertersRegistrarMarker;

  template <typename TCrossConvert, int UnstaticCounter, int Index, typename = void>
  struct ConvertersRegistrarMarkerExists{
    enum { value = false };
  };

  template <typename TCrossConvert, int UnstaticCounter, int Index>
  struct ConvertersRegistrarMarkerExists<TCrossConvert, UnstaticCounter, Index, decltype(void(ConvertersRegistrarMarker<TCrossConvert, Index>()))>{
    enum { value = true };
  };

  template <typename TCrossConvert, int UnstaticCounter, int Index = -1, bool Exists = true>
  struct ConvertersRegistrarMarkerEnd {
    enum { value = ConvertersRegistrarMarkerEnd<TCrossConvert, UnstaticCounter, Index + 1, ConvertersRegistrarMarkerExists<TCrossConvert, UnstaticCounter, Index+1>::value  >::value } ;
  };

  template <typename TCrossConvert, int UnstaticCounter, int Index>
  struct ConvertersRegistrarMarkerEnd<TCrossConvert, UnstaticCounter, Index, false> {
    enum { value = Index } ;
  };

  template <typename TCrossConvert, typename TCurrent, bool EnableToConvertion, bool EnableFromConversion>
  struct ConvertersRegistrarItem;

  template <typename TCrossConvert, typename TCurrent>
  struct ConvertersRegistrarItem<TCrossConvert, TCurrent, true, true> {
    void operator()(const TCurrent&){
    }

    template <typename TItem>
    void operator()(const TItem&){
      setConverter<TCurrent, TItem>();
      setConverter<TItem, TCurrent>();
    }
  };

  template <typename TCrossConvert, typename TCurrent>
  struct ConvertersRegistrarItem<TCrossConvert, TCurrent, true, false> {
    void operator()(const TCurrent&){
    }
    template <typename TItem>
    void operator()(const TItem&){
      setConverter<TItem, TCurrent>();
    }
  };

  template <typename TCrossConvert, typename TCurrent>
  struct ConvertersRegistrarItem<TCrossConvert, TCurrent, false, true> {
    void operator()(const TCurrent&){
    }
    template <typename TItem>
    void operator()(const TItem&){
      setConverter<TCurrent, TItem>();
    }
  };

  template <typename TCrossConvert, typename TCurrent>
  struct ConvertersRegistrarItem<TCrossConvert, TCurrent, false, false> {
    void operator()(const TCurrent&){
    }
    template <typename TItem>
    void operator()(const TItem&){
    }
  };


  template <typename TCrossConvert, int Index, int Size, typename TCurrent, bool EnableFront, bool EnableBack, typename ... TPack>
  struct ConvertersRegistrarWalker {
    void operator()(){
      enum { toConvertion = EnableFront && ConvertersRegistrarMarker<TCrossConvert, Index>::fromConversion };
      enum { fromConvertion = EnableBack && ConvertersRegistrarMarker<TCrossConvert, Index>::toConversion };
      ConvertersRegistrarItem<TCrossConvert, TCurrent, toConvertion, fromConvertion>()( *((typename ConvertersRegistrarMarker<TCrossConvert, Index>::type*)0xffffffff/*stub address*/)  );
      ConvertersRegistrarWalker<TCrossConvert, Index+1, Size, TCurrent, EnableFront, EnableBack,  TPack..., typename ConvertersRegistrarMarker<TCrossConvert, Index>::type>()();
    }
  };

  template <typename TCrossConvert, int Size, typename TCurrent, bool EnableFront, bool EnableBack, typename ... TPack>
  struct ConvertersRegistrarWalker<TCrossConvert, Size, Size, TCurrent, EnableFront, EnableBack, TPack...> {
    void operator()(){
      //ConvertersRegistrar<TCurrent, EnableFront, EnableBack, TPack...>()();
    }
  };

  template <typename TCrossConvert, int UnstaticCounter, typename TCurrent, int Size, bool EnableFront, bool EnableBack>
  struct ConvertersRegistrarInitializer {
    ConvertersRegistrarInitializer(){
      ConvertersRegistrarWalker<
        TCrossConvert,
        0,
        Size,
        TCurrent,
        EnableFront,
        EnableBack
        >()();
    }
  };

  } // NDetails namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__CONVERTERS_REGISTRAR_HPP___
