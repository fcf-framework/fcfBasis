#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace FcfTest {
  namespace BasisTest {

    void callInvariantArgumentsTest (){
      std::cout << "Start callInvariantArgumentsTest()..." << std::endl;
      {
        std::vector<int> v = {1,2,3,4};
        fcf::fill(v, 999.1);
        FCF_TEST(v.size() == 4, v.size());
        FCF_TEST(v[0] == 999, v[0]);
        FCF_TEST(v[1] == 999, v[1]);
        FCF_TEST(v[2] == 999, v[2]);
        FCF_TEST(v[3] == 999, v[3]);
      }

      {
        std::vector<int> v = {1,2,3,4};
        fcf::Variant variant(v, fcf::Variant::REFERENCE);
        fcf::fill(variant, 999.1);
        FCF_TEST(v.size() == 4, v.size());
        FCF_TEST(v[0] == 999, v[0]);
        FCF_TEST(v[1] == 999, v[1]);
        FCF_TEST(v[2] == 999, v[2]);
        FCF_TEST(v[3] == 999, v[3]);
      }

    } // void callInvariantArgumentsTest() end

  }
}
