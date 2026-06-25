#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

#include "../bits/functions.hpp"

namespace FcfTest {
  namespace BasisTest {
    FCF_TEST_DECLARE("fcfBasis", "Specifier", "arithmetic specifiers"){
      {
        fcf::Variant args[2] = {3, "2"};
        int result = 0;
        fcf::Type<int>().specifierUniversalCall<fcf::SubSpecifier>()(&result, &args[0], sizeof(args) / sizeof(args[0]));
        FCF_TEST(result == 1, result);
      }
      {
        fcf::Variant args[2] = {3, 1};
        int result = 0;
        fcf::Type<int>().specifierUniversalCall<fcf::SubSpecifier>()(&result, &args[0], sizeof(args) / sizeof(args[0]));
        FCF_TEST(result == 2, result);
      }
      {
        fcf::Variant args[2] = {3, "2"};
        int result = 0;
        fcf::Type<int>().specifierUniversalCall<fcf::AddSpecifier>()(&result, &args[0], sizeof(args) / sizeof(args[0]));
        FCF_TEST(result == 5, result);
      }
      {
        fcf::Variant args[2] = {3, 1};
        int result = 0;
        fcf::Type<int>().specifierUniversalCall<fcf::AddSpecifier>()(&result, &args[0], sizeof(args) / sizeof(args[0]));
        FCF_TEST(result == 4, result);
      }
      {
        fcf::Variant args[2] = {3, "2"};
        int result = 0;
        fcf::Type<int>().specifierUniversalCall<fcf::MulSpecifier>()(&result, &args[0], sizeof(args) / sizeof(args[0]));
        FCF_TEST(result == 6, result);
      }
      {
        fcf::Variant args[2] = {3, 5};
        int result = 0;
        fcf::Type<int>().specifierUniversalCall<fcf::MulSpecifier>()(&result, &args[0], sizeof(args) / sizeof(args[0]));
        FCF_TEST(result == 15, result);
      }
    }
  } // BasisTest namespace
} // FcfTest namespace
