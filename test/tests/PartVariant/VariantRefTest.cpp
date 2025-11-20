#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace FcfTest {
  namespace BasisTest {

    void variantRefTest(){
      std::cout << "Start variantRefTest()..." << std::endl;
      {
        int i = 1;
        fcf::Variant v(i, fcf::Variant::REF);
        FCF_TEST(v.ptr() == &i);
        FCF_TEST(v == i, v, i);

        v.get<int>() = 2;
        FCF_TEST(v == 2, v);
        FCF_TEST(i == 2, i);
        FCF_TEST(v == i, v, i);

        v += 1;
        FCF_TEST(v == 3, v);
        FCF_TEST(i == 3, i);
        FCF_TEST(v == i, v, i);

      }
    }

  }
}

