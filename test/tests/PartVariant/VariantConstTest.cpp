#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace FcfTest {
  namespace BasisTest {

    void variantConstTest(){
      std::cout << "Start variantConstTest()..." << std::endl;
      {
        bool error = false;
        int i = 1;
        fcf::Variant v(fcf::Type<const int>(), i, fcf::Variant::REFERENCE);
        FCF_TEST(v == 1, v);
        try {
          v = 2;
        } catch (std::exception&) {
          error = true;
        }
        FCF_TEST(error == true);
        FCF_TEST(v == 1, v);
        FCF_TEST(i == 1, i);
      }
      {
        bool error = false;
        fcf::Variant v(fcf::Type<const int>(), 1);
        try {
          v = 2;
        } catch (std::exception&) {
          error = true;
        }
        FCF_TEST(error == true);
        FCF_TEST(v == 1, v);
      }
      {
        bool error = false;
        fcf::Variant v(fcf::Type<const int>(), 2);
        try {
          v /= 2;
        } catch (std::exception&) {
          error = true;
        }
        FCF_TEST(error == true);
        FCF_TEST(v == 2, v);
      }
      {
        bool error = false;
        fcf::Variant v(fcf::Type<const int>(), 2);
        fcf::Variant v2(2);
        try {
          v /= v2;
        } catch (std::exception&) {
          error = true;
        }
        FCF_TEST(error == true);
        FCF_TEST(v == 2, v);
      }

    }

  } // BasisTest namespace
} // FcfTest namespace
