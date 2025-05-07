#ifndef ___FCF_BASIS__BITS__CONVERT__DETAILS__CONVERT_INITIALIZER_HPP___
#define ___FCF_BASIS__BITS__CONVERT__DETAILS__CONVERT_INITIALIZER_HPP___

#include "setConverter.hpp"
#include "../Converter.hpp"
#include "../../../bits/Type/Type.hpp"

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace Convert {

        template <typename TType=Nop, typename... TTypesPack>
        struct ConvertInitializerHandlerL1 {
          template <typename THandler>
          static void call(THandler& a_handler2){
            a_handler2.template call<TType>();
            ConvertInitializerHandlerL1<TTypesPack...>::call(a_handler2);
          }
        };

        template <typename TType>
        struct ConvertInitializerHandlerL1<TType> {
          template <typename THandler>
          static void call(THandler& a_handler2){
            a_handler2.template call<TType>();
          }
        };

        template <typename TType=Nop, typename... TTypesPack>
        struct ConvertInitializerHandlerL2 {
          template <typename TSource>
          void call(){
            setConverter<TSource, TType>();
            ConvertInitializerHandlerL2<TTypesPack...>().template call<TSource>();
          }
        };

        template <typename TType>
        struct ConvertInitializerHandlerL2<TType> {
          template <typename TSource>
          void call(){
            setConverter<TSource, TType>();
          }
        };

      } // Convert namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace

#endif // #ifndef ___FCF_BASIS__BITS__CONVERT__DETAILS__CONVERT_INITIALIZER_HPP___
