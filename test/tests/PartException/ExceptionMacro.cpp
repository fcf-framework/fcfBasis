#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

#define STR1(x) #x
#define STR0(x) STR1(x)
#define STR(x) STR0(x)

FCF_TEST_DECLARE("fcfBasis", "Exception", "exception macro"){
  {
    std::string string = STR((FCF_INVARIANT_EXCEPTION_CALL(func, false, a_error)));
    FCF_TEST(string == "(((false) ? func()) : func(a_error))", string)
  }
  {
    std::string string = STR((FCF_INVARIANT_EXCEPTION_CALL(func, false, a_error, 1)));
    FCF_TEST(string == "(((false) ? func(1)) : func(1, a_error))", string)
  }
  {
    std::string string = STR((FCF_INVARIANT_EXCEPTION_CALL(func, false, a_error, 1, 2)));
    FCF_TEST(string == "(((false) ? func(1, 2)) : func(1, 2, a_error))", string)
  }
}

