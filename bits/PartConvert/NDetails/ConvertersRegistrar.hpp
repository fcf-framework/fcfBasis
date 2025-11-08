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

  template <typename TCurrent, typename ... TPack>
  struct ConvertersRegistrar {
    typedef std::tuple<TPack...> tuple_type;

    void operator()(){
      tuple_type tuple;
      fcf::foreach(tuple, *this);
    }

    template <typename TItem>
    void operator()(const tuple_type&, size_t, const TItem&){
      if (std::is_same<TCurrent, TItem>::value){
        return;
      }
      setConverter<TCurrent, TItem>();
      setConverter<TItem, TCurrent>();
    }
  };

  template <int Index, int Size, typename TCurrent, typename ... TPack>
  struct ConvertersRegistrarWalker {
    void operator()(){
      ConvertersRegistrarWalker<Index+1, Size, TCurrent,  TPack..., typename ConvertersRegistrarMarker<Index>::type>()();
    }
  };

  template <int Size, typename TCurrent, typename ... TPack>
  struct ConvertersRegistrarWalker<Size, Size, TCurrent, TPack...> {
    void operator()(){
      ConvertersRegistrar<TCurrent, TPack...>()();
    }
  };

  template <int UnstaticCounter, typename TCurrent, int Size>
  struct ConvertersRegistrarInitializer {
    ConvertersRegistrarInitializer(){
      ConvertersRegistrarWalker<
        0,
        Size,
        TCurrent
        >()();
    }
  };

} // fcf::NDetails namespace

#endif // #ifndef ___FCF_BASIS__BITS__PART_CONVERT__NDETAILS__CONVERTERS_REGISTRAR_HPP___
