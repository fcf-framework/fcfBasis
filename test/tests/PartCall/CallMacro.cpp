#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

template <typename T1, typename T2>
T1 sum_test_macro(T1 a_left, T2 a_right){
  return a_left + a_right;
}

FCF_FUNCTION_REGISTRATION(
    (sum_test_macro<int, int>),
    "sum_test_macro<int>",
    "*",
    int(*)(int, int),
    (),
    false,
    (asdasdas dasda sdas)
    );

FCF_FUNCTION_REGISTRATION(
    (sum_test_macro_string),
    "sum_test_macro<std::string>",
    "*",
    std::string(*)(std::string, std::string),
    (),
    true,
    (
      std::string sum_test_macro_string(std::string a_left, std::string a_right){
        return a_left + a_right;
      }
    )
    );

template <typename TId, typename TUser>
struct DataTestMacro{
  TId   id;
  TUser user;
};

template <typename TId, typename TUser>
DataTestMacro<TId, TUser> data_test_macro(TId a_id, TUser a_user){
  return DataTestMacro<TId, TUser>{a_id, a_user};
}

FCF_TEMPLATE_TYPE_REGISTRATION(DataTestMacro, "DataTestMacro", (typename TId, typename TUser), (TId, TUser), (Type<TId>().name()+","+Type<TUser>().name()));

FCF_FUNCTION_REGISTRATION(
    (data_test_macro<int, std::string>),
    "data_test_macro<int,std::string>",
    "*",
    (DataTestMacro<int, std::string>(*)(int, std::string)),
    (),
    false,
    ()
    );

FCF_TEST_DECLARE("fcfBasis", "Call", "macro"){
  {
    fcf::Variant res = fcf::rcall("sum_test_macro<int>", 1, 2);
    FCF_TEST(res == 3, res);
  }
  {
    fcf::Variant res = fcf::rcall("sum_test_macro<std::string>", 1, 2);
    FCF_TEST(res == "12", res);
  }
  {
    std::string res = sum_test_macro_string("a", "b");
    FCF_TEST(res == "ab", res);
  }
  {
    typedef DataTestMacro<int, std::string> DataType;
    fcf::Variant res = fcf::rcall("data_test_macro<int,std::string>", 1, (const char*)"user");
    FCF_TEST(res.as<DataType>().id == 1, res.as<DataType>().id);
    FCF_TEST(res.as<DataType>().user == "user", res.as<DataType>().user);
  }
  {
    typedef int(*FunctionType)(int, int);
    unsigned int functionIndex = FCF_GET_FUNCTION_INDEX("sum_test_macro<int>", int(int, int));
    FCF_TEST(functionIndex != 0, functionIndex);
    FunctionType func = (FunctionType)FCF_GET_FUNCTION(functionIndex);
    int res = func(2, 6);
    FCF_TEST(res == 8, res);
  }
}
