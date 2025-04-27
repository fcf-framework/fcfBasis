/*
#ifndef ___FCF_BASIS__DETAILS__CONVERT__CONVERT_INITIALIZER_HPP___
#define ___FCF_BASIS__DETAILS__CONVERT__CONVERT_INITIALIZER_HPP___

#include <map>
#include "ConvertIndex.hpp"
#include "../../Type.hpp"

namespace fcf {
  template <typename TResult, typename TSource>
  TResult convert(const TSource& a_source, void* a_options = 0);
} // fcf namespace

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace Convert {

        template <typename TDest, typename TSrc>
        void convertType(TDest* a_dst, const TSrc* a_src){
          *a_dst = ::fcf::convert<TDest>(*a_src);
        }
        typedef void (*ConverFunction)(void*, const void*);

        struct ConvertStorage {
          std::map<ConvertIndex, ConverFunction> functions;
        };

        template <typename TSource, typename TDestination>
        void setConverter(ConvertStorage* a_storage){
          ConvertIndex ci;
          ci.source = ::fcf::Type<TSource>().index();
          ci.destination = ::fcf::Type<TDestination>().index();
          a_storage->functions[ci] = (ConverFunction)convertType<TDestination, TSource>;
          Type<TSource>().typeId->_ti->converters[ci.destination] = (void*)convertType<TDestination, TSource>;
        }

        template <typename TType=Nop, typename... TTypesPack>
        struct ConvertInitializerHandlerL1 {
          template <typename THandler>
          static void call(THandler& a_handler2, ConvertStorage* a_converStorage){
            a_handler2.template call<TType>(a_converStorage);
            ConvertInitializerHandlerL1<TTypesPack...>::call(a_handler2, a_converStorage);
          }
        };

        template <typename TType>
        struct ConvertInitializerHandlerL1<TType> {
          template <typename THandler>
          static void call(THandler& a_handler2, ConvertStorage* a_converStorage){
            a_handler2.template call<TType>(a_converStorage);
          }
        };


        template <typename TType=Nop, typename... TTypesPack>
        struct ConvertInitializerHandlerL2 {
          template <typename TSource>
          void call(ConvertStorage* a_converStorage){
            setConverter<TSource, TType>(a_converStorage);
            ConvertInitializerHandlerL2<TTypesPack...>().template call<TSource> (a_converStorage);
          }
        };

        template <typename TType>
        struct ConvertInitializerHandlerL2<TType> {
          template <typename TSource>
          void call(ConvertStorage* a_converStorage){
            setConverter<TSource, TType>(a_converStorage);
          }
        };

        template <typename... TypesPack>
        struct ConvertInitializer {
          static void call(ConvertStorage* a_storage){
            ConvertInitializerHandlerL2<TypesPack...> handler2;
            ConvertInitializerHandlerL1<TypesPack...>::call(handler2, a_storage);
          }
        };

      } // Convert namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__DETAILS__CONVERT__CONVERT_INITIALIZER_HPP___
*/
