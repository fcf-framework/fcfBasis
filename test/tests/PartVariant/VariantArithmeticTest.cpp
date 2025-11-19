#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace FcfTest {
  namespace BasisTest {

    void variantArithmeticTest(){
      std::cout << "Start variantArithmeticTest()..." << std::endl;

      //
      // operator +=
      // 
      {
        fcf::Variant v1(1);
        fcf::Variant v2(2);
        v1 += v2;
        FCF_TEST(v1.get<int>() == 3, v1);
        FCF_TEST(v1 == 3, v1.get<int>());
      }
      {
        fcf::Variant v1(1);
        v1 += 2;
        FCF_TEST(v1.get<int>() == 3, v1);
        FCF_TEST(v1 == 3, v1);
      }
      {
        fcf::Variant v1(1);
        v1 += "2";
        FCF_TEST(v1.get<int>() == 3, v1);
        FCF_TEST(v1 == 3, v1);
      }
      {
        fcf::Variant v1("1");
        fcf::Variant v2(2);
        v1 += v2;
        FCF_TEST(v1.get<std::string>() == "12", v1);
        FCF_TEST(v1 == 12, v1);
        FCF_TEST(v1 == "12", v1);
      }
      {
        fcf::Variant v1;
        fcf::Variant v2(2);
        v1 += v2;
        FCF_TEST(v1.empty() == true);
      }

      //
      // operator +
      // 
      {
        fcf::Variant v1(1);
        fcf::Variant v2(2);
        fcf::Variant v3;
        v3 = v1 + v2;
        FCF_TEST(v1.get<int>() == 1, v1);
        FCF_TEST(v2.get<int>() == 2, v2);
        FCF_TEST(v3.get<int>() == 3, v3);
        FCF_TEST((v1 + v2).get<int>() == 3);
      }
      {
        fcf::Variant v1(1);
        fcf::Variant v3;
        v3 = v1 + 2;
        FCF_TEST(v1.get<int>() == 1, v1);
        FCF_TEST(v3.get<int>() == 3, v3);
        FCF_TEST((v1 + 2).get<int>() == 3);
      }
      {
        fcf::Variant v1("1");
        fcf::Variant v2(2);
        fcf::Variant v3;
        v3 = v1 + v2;
        FCF_TEST(v1.cast<int>() == 1, v1.cast<int>());
        FCF_TEST(v2.cast<int>() == 2, v2.cast<int>());
        FCF_TEST(v3.cast<int>() == 12, v3.cast<int>());
        FCF_TEST(v3.get<std::string>() == "12", v3.get<std::string>());
        FCF_TEST((v1 + v2).get<std::string>() == "12");
      }
      {
        fcf::Variant v1("1");
        fcf::Variant v3;
        v3 = v1 + 2;
        FCF_TEST(v1.cast<int>() == 1, v1);
        FCF_TEST(v3.cast<int>() == 12, v3);
        FCF_TEST(v3.get<std::string>() == "12", v3);
        FCF_TEST((v1 + 2).get<std::string>() == "12");
      }

      //
      // operator -=
      // 
      {
        fcf::Variant v1(1);
        fcf::Variant v2(2);
        v1 -= v2;
        FCF_TEST(v1.get<int>() == -1, v1);
        FCF_TEST(v1 == -1, v1.get<int>());
      }
      {
        fcf::Variant v1(3);
        v1 -= 2;
        FCF_TEST(v1.get<int>() == 1, v1);
        FCF_TEST(v1 == 1, v1);
      }
      {
        fcf::Variant v1(1);
        v1 -= "2";
        FCF_TEST(v1.get<int>() == -1, v1);
        FCF_TEST(v1 == -1, v1);
      }
      {
        fcf::Variant v1("1");
        fcf::Variant v2(2);
        v1 -= v2;
        FCF_TEST(v1.get<std::string>() == "1", v1);
        FCF_TEST(v1 == 1, v1);
        FCF_TEST(v1 == "1", v1);
      }
      {
        fcf::Variant v1;
        fcf::Variant v2(2);
        v1 -= v2;
        FCF_TEST(v1.empty() == true);
      }

      //
      // operator -
      //
      {
        fcf::Variant v1(3);
        fcf::Variant v2(2);
        fcf::Variant v3;
        v3 = v1 - v2;
        FCF_TEST(v1.get<int>() == 3, v1);
        FCF_TEST(v2.get<int>() == 2, v2);
        FCF_TEST(v3.get<int>() == 1, v3);
        FCF_TEST((v1 - v2).get<int>() == 1);
      }
      {
        fcf::Variant v1(5);
        fcf::Variant v3;
        v3 = v1 - 2;
        FCF_TEST(v1.get<int>() == 5, v1);
        FCF_TEST(v3.get<int>() == 3, v3);
        FCF_TEST((v1 - 2).get<int>() == 3);
      }
      {
        fcf::Variant v1("7");
        fcf::Variant v2(2);
        fcf::Variant v3;
        v3 = v1 - v2;
        FCF_TEST(v1.cast<int>() == 7, v1.cast<int>());
        FCF_TEST(v2.cast<int>() == 2, v2.cast<int>());
        FCF_TEST(v3.cast<int>() == 7, v3.cast<int>());
        FCF_TEST(v3.get<std::string>() == "7", v3.get<std::string>());
        FCF_TEST((v1 - v2).get<std::string>() == "7");
      }
      {
        fcf::Variant v1("8");
        fcf::Variant v3;
        v3 = v1 - 2;
        FCF_TEST(v1.cast<int>() == 8, v1);
        FCF_TEST(v3.cast<int>() == 8, v3);
        FCF_TEST(v3.get<std::string>() == "8", v3);
        FCF_TEST((v1 - 2).get<std::string>() == "8");
      }


      //
      // operator *=
      //
      {
        fcf::Variant v1(3);
        fcf::Variant v2(5);
        v1 *= v2;
        FCF_TEST(v1.get<int>() == 15, v1);
        FCF_TEST(v1 == 15, v1.get<int>());
      }
      {
        fcf::Variant v1(3);
        v1 *= 2;
        FCF_TEST(v1.get<int>() == 6, v1);
        FCF_TEST(v1 == 6, v1);
      }
      {
        fcf::Variant v1(3);
        v1 *= "2";
        FCF_TEST(v1.get<int>() == 6, v1);
        FCF_TEST(v1 == 6, v1);
      }
      {
        fcf::Variant v1("1");
        fcf::Variant v2(2);
        v1 *= v2;
        FCF_TEST(v1.get<std::string>() == "1", v1);
        FCF_TEST(v1 == 1, v1);
        FCF_TEST(v1 == "1", v1);
      }
      {
        fcf::Variant v1;
        fcf::Variant v2(2);
        v1 *= v2;
        FCF_TEST(v1.empty() == true);
      }


      //
      // operator *
      //
      {
        fcf::Variant v1(3);
        fcf::Variant v2(2);
        fcf::Variant v3;
        v3 = v1 * v2;
        FCF_TEST(v1.get<int>() == 3, v1);
        FCF_TEST(v2.get<int>() == 2, v2);
        FCF_TEST(v3.get<int>() == 6, v3);
        FCF_TEST((v1 * v2).get<int>() == 6);
      }
      {
        fcf::Variant v1(5);
        fcf::Variant v3;
        v3 = v1 * 2;
        FCF_TEST(v1.get<int>() == 5, v1);
        FCF_TEST(v3.get<int>() == 10, v3);
        FCF_TEST((v1 * 2).get<int>() == 10);
      }
      {
        fcf::Variant v1("7");
        fcf::Variant v2(2);
        fcf::Variant v3;
        v3 = v1 * v2;
        FCF_TEST(v1.cast<int>() == 7, v1.cast<int>());
        FCF_TEST(v2.cast<int>() == 2, v2.cast<int>());
        FCF_TEST(v3.cast<int>() == 7, v3.cast<int>());
        FCF_TEST(v3.get<std::string>() == "7", v3.get<std::string>());
        FCF_TEST((v1 * v2).get<std::string>() == "7");
      }
      {
        fcf::Variant v1("8");
        fcf::Variant v3;
        v3 = v1 * 2;
        FCF_TEST(v1.cast<int>() == 8, v1);
        FCF_TEST(v3.cast<int>() == 8, v3);
        FCF_TEST(v3.get<std::string>() == "8", v3);
        FCF_TEST((v1 * 2).get<std::string>() == "8");
      }



      //
      // operator /=
      //
      {
        fcf::Variant v1(21);
        fcf::Variant v2(3);
        v1 /= v2;
        FCF_TEST(v1.get<int>() == 7, v1);
        FCF_TEST(v1 == 7, v1.get<int>());
      }
      {
        fcf::Variant v1(27);
        v1 /= 9;
        FCF_TEST(v1.get<int>() == 3, v1);
        FCF_TEST(v1 == 3, v1);
      }
      {
        fcf::Variant v1(8);
        v1 /= "2";
        FCF_TEST(v1.get<int>() == 4, v1);
        FCF_TEST(v1 == 4, v1);
      }
      {
        fcf::Variant v1("1");
        fcf::Variant v2(2);
        v1 /= v2;
        FCF_TEST(v1.get<std::string>() == "1", v1);
        FCF_TEST(v1 == 1, v1);
        FCF_TEST(v1 == "1", v1);
      }
      {
        fcf::Variant v1;
        fcf::Variant v2(2);
        v1 /= v2;
        FCF_TEST(v1.empty() == true);
      }



      //
      // operator /
      //
      {
        fcf::Variant v1(8);
        fcf::Variant v2(2);
        fcf::Variant v3;
        v3 = v1 / v2;
        FCF_TEST(v1.get<int>() == 8, v1);
        FCF_TEST(v2.get<int>() == 2, v2);
        FCF_TEST(v3.get<int>() == 4, v3);
        FCF_TEST((v1 / v2).get<int>() == 4);
      }
      {
        fcf::Variant v1(6);
        fcf::Variant v3;
        v3 = v1 / 2;
        FCF_TEST(v1.get<int>() == 6, v1);
        FCF_TEST(v3.get<int>() == 3, v3);
        FCF_TEST((v1 / 2).get<int>() == 3);
      }
      {
        fcf::Variant v1("7");
        fcf::Variant v2(2);
        fcf::Variant v3;
        v3 = v1 / v2;
        FCF_TEST(v1.cast<int>() == 7, v1.cast<int>());
        FCF_TEST(v2.cast<int>() == 2, v2.cast<int>());
        FCF_TEST(v3.cast<int>() == 7, v3.cast<int>());
        FCF_TEST(v3.get<std::string>() == "7", v3.get<std::string>());
        FCF_TEST((v1 / v2).get<std::string>() == "7");
      }
      {
        fcf::Variant v1("8");
        fcf::Variant v3;
        v3 = v1 / 2;
        FCF_TEST(v1.cast<int>() == 8, v1);
        FCF_TEST(v3.cast<int>() == 8, v3);
        FCF_TEST(v3.get<std::string>() == "8", v3);
        FCF_TEST((v1 * 2).get<std::string>() == "8");
      }

    } // void variantArithmeticTest() end
  }
}
