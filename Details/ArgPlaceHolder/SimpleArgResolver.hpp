#ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__SIMPLE_ARG_RESOLVER_HPP___
#define ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__SIMPLE_ARG_RESOLVER_HPP___

#include <cstddef>

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace ArgPlaceHolder {

        template <size_t Index = 0>
        struct SimpleArgResolver{
          template <typename T1, typename... TPack>
          inline static T1& call(T1& a_arg1, TPack... a_pack) {
            return a_arg1;
          }
        };

        template <>
        struct SimpleArgResolver<1>{
          template <typename T1, typename T2,
                    typename... TPack>
          inline static T2& call(T1& a_arg1, T2& a_arg2,
                                 TPack... a_pack) {
            return a_arg2;
          }
        };

        template <>
        struct SimpleArgResolver<2>{
          template <typename T1, typename T2, typename T3,
                    typename... TPack>
          inline static T3& call(T1& a_arg1, T2& a_arg2, T3& a_arg3,
                                 TPack... a_pack) {
            return a_arg3;
          }
        };

        template <>
        struct SimpleArgResolver<3>{
          template <typename T1, typename T2, typename T3, typename T4,
                    typename... TPack>
          inline static T4& call(T1& a_arg1, T2& a_arg2, T3& a_arg3, T4& a_arg4,
                                 TPack... a_pack) {
            return a_arg4;
          }
        };

        template <>
        struct SimpleArgResolver<4>{
          template <typename T1, typename T2, typename T3, typename T4, typename T5,
                    typename... TPack>
          inline static T5& call(T1& a_arg1, T2& a_arg2, T3& a_arg3, T4& a_arg4, T5& a_arg5,
                                 TPack... a_pack) {
            return a_arg5;
          }
        };

        template <>
        struct SimpleArgResolver<5>{
          template <typename T1, typename T2, typename T3, typename T4, typename T5,
                    typename T6,
                    typename... TPack>
          inline static T6& call(T1& a_arg1, T2& a_arg2, T3& a_arg3, T4& a_arg4, T5& a_arg5,
                                 T6& a_arg6,
                                 TPack... a_pack) {
            return a_arg6;
          }
        };

        template <>
        struct SimpleArgResolver<6>{
          template <typename T1, typename T2, typename T3, typename T4, typename T5,
                    typename T6, typename T7,
                    typename... TPack>
          inline static T7& call(T1& a_arg1, T2& a_arg2, T3& a_arg3, T4& a_arg4, T5& a_arg5,
                                 T6& a_arg6, T7& a_arg7,
                                 TPack... a_pack) {
            return a_arg7;
          }
        };

        template <>
        struct SimpleArgResolver<7>{
          template <typename T1, typename T2, typename T3, typename T4, typename T5,
                    typename T6, typename T7, typename T8,
                    typename... TPack>
          inline static T8& call(T1& a_arg1, T2& a_arg2, T3& a_arg3, T4& a_arg4, T5& a_arg5,
                                 T6& a_arg6, T7& a_arg7, T8& a_arg8,
                                 TPack... a_pack) {
            return a_arg8;
          }
        };

        template <>
        struct SimpleArgResolver<8>{
          template <typename T1, typename T2, typename T3, typename T4, typename T5,
                    typename T6, typename T7, typename T8, typename T9,
                    typename... TPack>
          inline static T9& call(T1& a_arg1, T2& a_arg2, T3& a_arg3, T4& a_arg4, T5& a_arg5,
                                 T6& a_arg6, T7& a_arg7, T8& a_arg8, T9& a_arg9,
                                 TPack... a_pack) {
            return a_arg9;
          }
        };

        template <>
        struct SimpleArgResolver<9>{
          template <typename T1, typename T2, typename T3, typename T4, typename T5,
                    typename T6, typename T7, typename T8, typename T9, typename T10,
                    typename... TPack>
          inline static T10& call(T1& a_arg1, T2& a_arg2, T3& a_arg3, T4& a_arg4, T5& a_arg5,
                                 T6& a_arg6, T7& a_arg7, T8& a_arg8, T9& a_arg9, T10& a_arg10,
                                 TPack... a_pack) {
            return a_arg10;
          }
        };

      } // ArgPlaceHolder namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace
 
#endif // #ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__SIMPLE_ARG_RESOLVER_HPP___
