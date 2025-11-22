#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace FcfTest {
  namespace BasisTest {

    void variantContainerTest(){
      std::cout << "Start variantContainerTest()..." << std::endl;
      {
        std::vector<int> vec = {1, 2, 3};
        fcf::Variant v(vec);
        FCF_TEST(v[0] == 1);
        FCF_TEST(v[1] == 2);
        FCF_TEST(v[2] == 3);
        FCF_TEST(!v[3].empty());

        vec[0] *= 10;
        FCF_TEST(v[0] == 1);
        FCF_TEST(vec[0] == 10);
      }
      {
        std::vector<int> vec = {1, 2, 3};
        fcf::Variant v(vec, fcf::Variant::REFERENCE);
        FCF_TEST(v[0] == 1);
        FCF_TEST(v[1] == 2);
        FCF_TEST(v[2] == 3);

        v[0] *= 10;
        FCF_TEST(v[0] == 10);
        FCF_TEST(vec[0] == 10);

        v[0] = 99;
        FCF_TEST(v[0] == 99, v[0]);
        FCF_TEST(vec[0] == 99, v[0]);

        v[1] *= 10;
        FCF_TEST(v[1] == 20);
        FCF_TEST(vec[1] == 20);
        v[2] *= 10;
        FCF_TEST(v[2] == 30);
        FCF_TEST(vec[2] == 30);

        vec.push_back(40);

        FCF_TEST(v[3] == 40);
        FCF_TEST(vec[3] == 40);

        FCF_TEST(!v[4].empty());
      }
    }

  }
}


