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
        fcf::Variant v(i, fcf::Variant::REFERENCE);
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
      {
        int i1 = 1;
        fcf::Variant v1(i1, fcf::Variant::REFERENCE);
        fcf::Variant v2(v1, fcf::Variant::REFERENCE);

        FCF_TEST(i1 == 1, i1);
        FCF_TEST(v1 == 1, v1);
        FCF_TEST(v2 == 1, v2);

        i1 = 2;
        FCF_TEST(i1 == 2, i1);
        FCF_TEST(v1 == 2, v1);
        FCF_TEST(v2 == 2, v2);

        v1 = 3;
        FCF_TEST(i1 == 3, i1);
        FCF_TEST(v1 == 3, v1);
        FCF_TEST(v2 == 3, v2);

        v2 = 4;
        FCF_TEST(i1 == 4, i1);
        FCF_TEST(v1 == 4, v1);
        FCF_TEST(v2 == 4, v2);
      }
      {
        fcf::Variant v1(1);
        fcf::Variant v2(v1, fcf::Variant::REFERENCE);
        FCF_TEST(v1 == 1, v1);
        FCF_TEST(v2 == 1, v2);

        v1 = 2;
        FCF_TEST(v1 == 2, v1);
        FCF_TEST(v2 == 2, v2);

        v2 = 3;
        FCF_TEST(v1 == 3, v1);
        FCF_TEST(v2 == 3, v2);

        v2.set(1, fcf::Variant::RESET);
        FCF_TEST(v1 == 3, v1);
        FCF_TEST(v2 == 1, v2);

        v2.set(v1, fcf::Variant::REFERENCE);
        FCF_TEST(v1 == 3, v1);
        FCF_TEST(v2 == 3, v2);

        v2.set(9, fcf::Variant::WRITE);
        FCF_TEST(v1 == 9, v1);
        FCF_TEST(v2 == 9, v2);

        v2.set(1, fcf::Variant::RESET);
        FCF_TEST(v1 == 9, v1);
        FCF_TEST(v2 == 1, v2);
      }
    }

  }
}

