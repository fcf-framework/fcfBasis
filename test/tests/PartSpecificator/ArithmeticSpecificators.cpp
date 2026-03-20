#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"
#include "../../../bits/functions/random.hpp"


namespace FcfTest {
  namespace BasisTest {
    FCF_TEST_DECLARE("fcfBasis", "Specificator", "arithmetic specificators"){
      {
        fcf::Variant args[2] = {3, "2"};
        int result = 0;
        fcf::Type<int>().getSpecificator<fcf::SubSpecificator>()(&result, &args[0], sizeof(args) / sizeof(args[0]));
        FCF_TEST(result == 1, result);
      }
      {
        fcf::Variant args[2] = {3, 1};
        int result = 0;
        fcf::Type<int>().getSpecificator<fcf::SubSpecificator>()(&result, &args[0], sizeof(args) / sizeof(args[0]));
        FCF_TEST(result == 2, result);
      }
      {
        fcf::Variant args[2] = {3, "2"};
        int result = 0;
        fcf::Type<int>().getSpecificator<fcf::AddSpecificator>()(&result, &args[0], sizeof(args) / sizeof(args[0]));
        FCF_TEST(result == 5, result);
      }
      {
        fcf::Variant args[2] = {3, 1};
        int result = 0;
        fcf::Type<int>().getSpecificator<fcf::AddSpecificator>()(&result, &args[0], sizeof(args) / sizeof(args[0]));
        FCF_TEST(result == 4, result);
      }
      {
        fcf::Variant args[2] = {3, "2"};
        int result = 0;
        fcf::Type<int>().getSpecificator<fcf::MulSpecificator>()(&result, &args[0], sizeof(args) / sizeof(args[0]));
        FCF_TEST(result == 6, result);
      }
      {
        fcf::Variant args[2] = {3, 5};
        int result = 0;
        fcf::Type<int>().getSpecificator<fcf::MulSpecificator>()(&result, &args[0], sizeof(args) / sizeof(args[0]));
        FCF_TEST(result == 15, result);
      }
    }
  } // BasisTest namespace
} // FcfTest namespace
