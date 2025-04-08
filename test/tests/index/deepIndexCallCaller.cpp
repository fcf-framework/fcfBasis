#include <iostream>

#include "../../libraries/fcfTest/test.hpp"

#include "../../../Details/IndexableFunction/SimpleCaller.hpp"

namespace NTestCaller {

  int test1(int a_arg1){
    return a_arg1 + 1;
  }

  int test2(int* a_arg1){
    return *a_arg1 + 1;
  }

}

void deepIndexCallCaller() {
  std::cout << "Start deepIndexCallCaller..." << std::endl;
  {
    int res = 0;
    auto ptrFunc = NTestCaller::test1;
    auto caller =  fcf::Details::IndexableFunction::getSimpleCaller(ptrFunc);
    res = caller(ptrFunc, 1);
    FCF_TEST(res == 2, res);
    int val = 2;
    res = caller(ptrFunc, val);
    FCF_TEST(res == val + 1, res, val + 1);
  }
  {
    int res = 0;
    auto ptrFunc = NTestCaller::test2;
    auto caller =  fcf::Details::IndexableFunction::getSimpleCaller(ptrFunc);
    int val = 2;
    res = caller(ptrFunc, &val);
    FCF_TEST(res == val + 1, res, val + 1);
  }
}
