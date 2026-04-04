#include <iostream>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../PartCall.hpp"
#include "../bits/functions.hpp"

#define FCFTEST_STRINGIFY_2(...) #__VA_ARGS__
#define FCFTEST_STRINGIFY_1(...) FCFTEST_STRINGIFY_2(__VA_ARGS__)
#define FCFTEST_STRINGIFY_0(...) FCFTEST_STRINGIFY_1(__VA_ARGS__)
#define FCFTEST_STRINGIFY(...) FCFTEST_STRINGIFY_0(__VA_ARGS__)

FCF_TEST_DECLARE("fcfBasis", "Call", "declare call"){
  {
    std::string expected = "typename ::fcf::NDetails::CallPlaceHolderSignatureGetter<"
                                                                      "void(), "
                                                                      "::fcf::FunctionSignature<void()>::result_type, "
                                                                      "::fcf::Nop "
                                                                    ">::active_type, "
                           "typename ::fcf::NDetails::CallPlaceHolderSignatureGetter<"
                                                                      "void(), "
                                                                      "::fcf::FunctionSignature<void()>::result_type, "
                                                                      "::fcf::Nop "
                                                                    ">::active_type, "
                           "typename ::fcf::NDetails::CallPlaceHolderSignatureGetter<"
                                                                      "void(), "
                                                                      "::fcf::FunctionSignature<void()>::result_type, "
                                                                      "::fcf::Nop "
                                                                    ">::active_type";
    std::string str = FCFTEST_STRINGIFY(
                                        _FCF_DECLARE_FUNCTION__RESOLVE_SIGNATURES(void(),)
                                       );
    FCF_TEST(str == expected, str, expected);
  }
  {
    std::string expected = "typename ::fcf::NDetails::CallPlaceHolderSignatureGetter<"
                                                                      "void(), "
                                                                      "::fcf::FunctionSignature<void()>::result_type, "
                                                                      "::fcf::Nop "
                                                                    ">::active_type, "
                           "typename ::fcf::NDetails::CallPlaceHolderSignatureGetter<"
                                                                      "void(), "
                                                                      "::fcf::FunctionSignature<void()>::result_type, "
                                                                      "::fcf::Nop "
                                                                    ">::active_type, "
                           "typename ::fcf::NDetails::CallPlaceHolderSignatureGetter<"
                                                                      "void(), "
                                                                      "::fcf::FunctionSignature<void()>::result_type, "
                                                                      "::fcf::Nop "
                                                                    ">::active_type";
    std::string str = FCFTEST_STRINGIFY(
                                        _FCF_DECLARE_FUNCTION__RESOLVE_SIGNATURES(void(),())
                                       );
    FCF_TEST(str == expected, str, expected);
  }
  {
    std::string expected = "typename ::fcf::NDetails::CallPlaceHolderSignatureGetter<"
                                                                      "void(), "
                                                                      "::fcf::FunctionSignature<void()>::result_type, "
                                                                      "1-1, 1-2 "
                                                                    ">::active_type, "
                           "typename ::fcf::NDetails::CallPlaceHolderSignatureGetter<"
                                                                      "void(), "
                                                                      "::fcf::FunctionSignature<void()>::result_type, "
                                                                      "::fcf::Nop "
                                                                    ">::active_type, "
                           "typename ::fcf::NDetails::CallPlaceHolderSignatureGetter<"
                                                                      "void(), "
                                                                      "::fcf::FunctionSignature<void()>::result_type, "
                                                                      "::fcf::Nop "
                                                                    ">::active_type";
    std::string str = FCFTEST_STRINGIFY(
                                        _FCF_DECLARE_FUNCTION__RESOLVE_SIGNATURES(void(),((1-1, 1-2)))
                                       );
    FCF_TEST(str == expected, str, expected);
  }
  {
    std::string expected = "typename ::fcf::NDetails::CallPlaceHolderSignatureGetter<"
                                                                      "void(), "
                                                                      "::fcf::FunctionSignature<void()>::result_type, "
                                                                      "1-1, 1-2 "
                                                                    ">::active_type, "
                           "typename ::fcf::NDetails::CallPlaceHolderSignatureGetter<"
                                                                      "void(), "
                                                                      "::fcf::FunctionSignature<void()>::result_type, "
                                                                      "2 "
                                                                    ">::active_type, "
                           "typename ::fcf::NDetails::CallPlaceHolderSignatureGetter<"
                                                                      "void(), "
                                                                      "::fcf::FunctionSignature<void()>::result_type, "
                                                                      "::fcf::Nop "
                                                                    ">::active_type";
    std::string str = FCFTEST_STRINGIFY(
                                        _FCF_DECLARE_FUNCTION__RESOLVE_SIGNATURES(void(),((1-1, 1-2), (2)))
                                       );
    FCF_TEST(str == expected, str, expected);
  }
  {
    std::string expected = "typename ::fcf::NDetails::CallPlaceHolderSignatureGetter<"
                                                                      "void(), "
                                                                      "::fcf::FunctionSignature<void()>::result_type, "
                                                                      "1-1, 1-2 "
                                                                    ">::active_type, "
                           "typename ::fcf::NDetails::CallPlaceHolderSignatureGetter<"
                                                                      "void(), "
                                                                      "::fcf::FunctionSignature<void()>::result_type, "
                                                                      "2 "
                                                                    ">::active_type, "
                           "typename ::fcf::NDetails::CallPlaceHolderSignatureGetter<"
                                                                      "void(), "
                                                                      "::fcf::FunctionSignature<void()>::result_type, "
                                                                      "3 "
                                                                    ">::active_type";
    std::string str = FCFTEST_STRINGIFY(
                                        _FCF_DECLARE_FUNCTION__RESOLVE_SIGNATURES(void(),((1-1, 1-2), (2), (3)))
                                       );
    FCF_TEST(str == expected, str, expected);
  }
  {
    std::string expected = "typename ::fcf::NDetails::CallPlaceHolderSignatureGetter<"
                                                                      "void(), "
                                                                      "::fcf::FunctionSignature<void()>::result_type, "
                                                                      "1-1, 1-2 "
                                                                    ">::active_type, "
                           "typename ::fcf::NDetails::CallPlaceHolderSignatureGetter<"
                                                                      "void(), "
                                                                      "::fcf::FunctionSignature<void()>::result_type, "
                                                                      "2 "
                                                                    ">::active_type, "
                           "typename ::fcf::NDetails::CallPlaceHolderSignatureGetter<"
                                                                      "void(), "
                                                                      "::fcf::FunctionSignature<void()>::result_type, "
                                                                      "3 "
                                                                    ">::active_type";
    std::string str = FCFTEST_STRINGIFY(
                                        _FCF_DECLARE_FUNCTION__RESOLVE_SIGNATURES(void(),((1-1, 1-2), (2), (3), (4)))
                                       );
    FCF_TEST(str == expected, str, expected);
  }
}

