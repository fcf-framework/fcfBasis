#ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__FUNCTION_TYPE_BUILDER_HPP___
#define ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__FUNCTION_TYPE_BUILDER_HPP___

namespace fcf {
  namespace Details {
    namespace Basis {
      namespace ArgPlaceHolder {

        template <typename TResult,
                  typename T1 = Nop, typename T2 = Nop, typename T3 = Nop, typename T4 = Nop, typename T5 = Nop,
                  typename T6 = Nop, typename T7 = Nop, typename T8 = Nop, typename T9 = Nop, typename T10 = Nop>
        struct FunctionTypeBuilder {
          typedef TResult (*type)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10);
          typedef TResult (*caller_type)(T1, T2, T3&&, T4&&, T5&&, T6&&, T7&&, T8&&, T9&&, T10&&);
        };

        template <typename TResult,
                  typename T1, typename T2, typename T3, typename T4, typename T5,
                  typename T6, typename T7, typename T8, typename T9>
        struct FunctionTypeBuilder<TResult, T1, T2, T3, T4, T5, T6, T7, T8, T9> {
          typedef TResult (*type)(T1, T2, T3, T4, T5, T6, T7, T8, T9);
          typedef TResult (*caller_type)(T1, T2, T3&&, T4&&, T5&&, T6&&, T7&&, T8&&, T9&&);
        };

        template <typename TResult,
                  typename T1, typename T2, typename T3, typename T4, typename T5,
                  typename T6, typename T7, typename T8>
        struct FunctionTypeBuilder<TResult, T1, T2, T3, T4, T5, T6, T7, T8> {
          typedef TResult (*type)(T1, T2, T3, T4, T5, T6, T7, T8);
          typedef TResult (*caller_type)(T1, T2, T3&&, T4&&, T5&&, T6&&, T7&&, T8&&);
        };

        template <typename TResult,
                  typename T1, typename T2, typename T3, typename T4, typename T5,
                  typename T6, typename T7>
        struct FunctionTypeBuilder<TResult, T1, T2, T3, T4, T5, T6, T7> {
          typedef TResult (*type)(T1, T2, T3, T4, T5, T6, T7);
          typedef TResult (*caller_type)(T1, T2, T3&&, T4&&, T5&&, T6&&, T7&&);
        };

        template <typename TResult,
                  typename T1, typename T2, typename T3, typename T4, typename T5,
                  typename T6>
        struct FunctionTypeBuilder<TResult, T1, T2, T3, T4, T5, T6> {
          typedef TResult (*type)(T1, T2, T3, T4, T5, T6);
          typedef TResult (*caller_type)(T1, T2, T3&&, T4&&, T5&&, T6&&);
        };

        template <typename TResult,
                  typename T1, typename T2, typename T3, typename T4, typename T5>
        struct FunctionTypeBuilder<TResult, T1, T2, T3, T4, T5> {
          typedef TResult (*type)(T1, T2, T3, T4, T5);
          typedef TResult (*caller_type)(T1, T2, T3&&, T4&&, T5&&);
        };

        template <typename TResult,
                  typename T1, typename T2, typename T3, typename T4>
        struct FunctionTypeBuilder<TResult, T1, T2, T3, T4> {
          typedef TResult (*type)(T1, T2, T3, T4);
          typedef TResult (*caller_type)(T1, T2, T3&&, T4&&);
        };

        template <typename TResult,
                  typename T1, typename T2, typename T3>
        struct FunctionTypeBuilder<TResult, T1, T2, T3> {
          typedef TResult (*type)(T1, T2, T3);
          typedef TResult (*caller_type)(T1, T2, T3&&);
        };

        template <typename TResult,
                  typename T1, typename T2>
        struct FunctionTypeBuilder<TResult, T1, T2> {
          typedef TResult (*type)(T1, T2);
          typedef TResult (*caller_type)(T1, T2);
        };

        template <typename TResult,
                  typename T1>
        struct FunctionTypeBuilder<TResult, T1> {
          typedef TResult (*type)(T1);
          typedef TResult (*caller_type)(T1);
        };

        template <typename TResult>
        struct FunctionTypeBuilder<TResult> {
          typedef TResult (*type)();
          typedef TResult (*caller_type());
        };

      } // ArgPlaceHolder namespace
    } // Basis namespace
  } // Details namespace
} // fcf namespace


#endif // #ifndef ___FCF_BASIS__DETAILS__ARG_PLACE_HOLDER__FUNCTION_TYPE_BUILDER_HPP___
