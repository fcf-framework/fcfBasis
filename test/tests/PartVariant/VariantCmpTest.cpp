#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace FcfTest::BasisTest {

  void variantCmpTest(){
    std::cout << "Start variantCmpTest()..." << std::endl;
    {
      fcf::Variant v1;
      fcf::Variant v2(2);
      FCF_TEST((v1 < v2) == true);
      FCF_TEST((v2 < v1) == false);
    }
    {
      fcf::Variant v1;
      fcf::Variant v2;
      FCF_TEST((v1 < v2) == false);
      FCF_TEST((v2 < v1) == false);
    }

    {
      fcf::Variant v1(1);
      fcf::Variant v2(2);
      FCF_TEST((v1 < v2) == true);
      FCF_TEST((v2 < v1) == false);
    }
    {
      fcf::Variant v1(2);
      fcf::Variant v2(2);
      FCF_TEST((v1 < v2) == false);
      FCF_TEST((v2 < v1) == false);
    }
    {
      fcf::Variant v1((unsigned int)1);
      fcf::Variant v2((int)2);
      FCF_TEST((v1 < v2) == true);
      FCF_TEST((v2 < v1) == false);
    }
    {
      fcf::Variant v1((unsigned int)1);
      fcf::Variant v2(std::string("2"));
      FCF_TEST((v1 < v2) == true);
      FCF_TEST((v2 < v1) == false);
    }
    {
      fcf::Variant v1(std::string("-1"));
      fcf::Variant v2(2);
      FCF_TEST((v1 < v2) == true);
      FCF_TEST((v2 < v1) == false);
    }
    {
      fcf::Variant v1(std::string("-1"));
      fcf::Variant v2(-1);
      FCF_TEST((v1 < v2) == false);
      FCF_TEST((v2 < v1) == false);
    }
    {
      fcf::Variant v1(9999999);
      fcf::Variant v2(std::vector<int>{1});
      FCF_TEST((v1 < v2) == true);
      FCF_TEST((v2 < v1) == false);
    }
    {
      fcf::Variant v1(2);
      FCF_TEST((v1 < 3) == true);
      FCF_TEST((v1 < 2) == false);
      FCF_TEST((v1 < "3") == true);
      FCF_TEST((v1 < "2") == false);
    }
    {
      fcf::Variant v1(2);
      int cv1 = 3;
      FCF_TEST((v1 < cv1) == true);
      int cv2 = 2;
      FCF_TEST((v1 < cv2) == false);
      const char* cv3 = "3";
      FCF_TEST((v1 < cv3) == true);
      std::string cv4 = "2";
      FCF_TEST((v1 < cv4) == false);
    }
    {
      fcf::Variant v1;
      FCF_TEST((v1 < 3) == true);
      FCF_TEST((v1 < -1) == true);
    }
    {
      fcf::Variant v1;
      int cv1 = 3;
      int cv2 = -1;
      FCF_TEST((v1 < cv1) == true);
      FCF_TEST((v1 < cv2) == true);
    }
    //
    // operator ==
    //
    {
      fcf::Variant v1;
      fcf::Variant v2(2);
      FCF_TEST((v1 == v2) == false);
      FCF_TEST((v2 == v1) == false);
      FCF_TEST((v1 != v2) == true);
      FCF_TEST((v2 != v1) == true);
      FCF_TEST((v1 != 2) == true);
      FCF_TEST((v2 != 2) == false);
      FCF_TEST((v2 != "2") == false);
      FCF_TEST((v2 != "3") == true);
    }
    {
      fcf::Variant v1;
      fcf::Variant v2;
      FCF_TEST((v1 == v2) == true);
      FCF_TEST((v2 == v1) == true);
    }
    {
      fcf::Variant v1(1);
      fcf::Variant v2(2);
      FCF_TEST((v1 == v2) == false);
      FCF_TEST((v2 == v1) == false);
    }
    {
      fcf::Variant v1(2);
      fcf::Variant v2(2);
      FCF_TEST((v1 == v2) == true);
      FCF_TEST((v2 == v1) == true);
    }
    {
      fcf::Variant v1(2);
      fcf::Variant v2("2");
      FCF_TEST((v1 == v2) == true);
      FCF_TEST((v2 == v1) == true);
    }
    {
      fcf::Variant v1(1);
      fcf::Variant v2("2");
      FCF_TEST((v1 == v2) == false);
      FCF_TEST((v2 == v1) == false);
    }
    {
      fcf::Variant v1(9999999);
      fcf::Variant v2(std::vector<int>{1});
      FCF_TEST((v1 == v2) == false);
      FCF_TEST((v2 == v1) == false);
    }
    //
    // operator <=
    //
    {
      fcf::Variant v1;
      fcf::Variant v2(2);
      FCF_TEST((v1 <= v2) == true);
      FCF_TEST((v2 <= v1) == false);
    }
    {
      fcf::Variant v1;
      fcf::Variant v2;
      FCF_TEST((v1 <= v2) == true);
      FCF_TEST((v2 <= v1) == true);
    }

    {
      fcf::Variant v1(1);
      fcf::Variant v2(2);
      FCF_TEST((v1 <= v2) == true);
      FCF_TEST((v2 <= v1) == false);
    }
    {
      fcf::Variant v1(2);
      fcf::Variant v2(2);
      FCF_TEST((v1 <= v2) == true);
      FCF_TEST((v2 <= v1) == true);
    }
    {
      fcf::Variant v1((unsigned int)1);
      fcf::Variant v2((int)2);
      FCF_TEST((v1 <= v2) == true);
      FCF_TEST((v2 <= v1) == false);
    }
    {
      fcf::Variant v1((unsigned int)1);
      fcf::Variant v2(std::string("2"));
      FCF_TEST((v1 <= v2) == true);
      FCF_TEST((v2 <= v1) == false);
    }
    {
      fcf::Variant v1(std::string("-1"));
      fcf::Variant v2(2);
      FCF_TEST((v1 <= v2) == true);
      FCF_TEST((v2 <= v1) == false);
    }
    {
      fcf::Variant v1(std::string("-1"));
      fcf::Variant v2(-1);
      FCF_TEST((v1 <= v2) == true);
      FCF_TEST((v2 <= v1) == true);
    }
    {
      fcf::Variant v1(9999999);
      fcf::Variant v2(std::vector<int>{1});
      FCF_TEST((v1 <= v2) == true);
      FCF_TEST((v2 <= v1) == false);
    }
    {
      fcf::Variant v1(1);
      FCF_TEST((v1 <= 1) == true);
      FCF_TEST((v1 <= 2) == true);
      FCF_TEST((v1 <= 0) == false);
      FCF_TEST((v1 <= "0") == false);
      FCF_TEST((v1 <= "1") == true);
      FCF_TEST((v1 <= "3") == true);
    }

    //
    // operator other
    //
    {
      fcf::Variant v1(1);
      FCF_TEST((v1 >= 2) == false);
      FCF_TEST((v1 >= 1) == true);
      FCF_TEST((v1 >= 0) == true);
    }
    {
      fcf::Variant v1("1");
      FCF_TEST((v1 >= 2) == false);
      FCF_TEST((v1 >= 1) == true);
      FCF_TEST((v1 >= 0) == true);
    }
    {
      fcf::Variant v1(1);
      FCF_TEST((v1 > 2) == false);
      FCF_TEST((v1 > 1) == false);
      FCF_TEST((v1 > 0) == true);
    }
    {
      fcf::Variant v1("1");
      FCF_TEST((v1 > 2) == false);
      FCF_TEST((v1 > 1) == false);
      FCF_TEST((v1 > 0) == true);
    }
    {
      fcf::Variant v1(std::string("1"));
      fcf::Variant v2(2);
      FCF_TEST((v1 >= v2) == false);
      FCF_TEST((v2 >= v1) == true);
    }
    {
      fcf::Variant v1(std::string("2"));
      fcf::Variant v2(2);
      FCF_TEST((v1 >= v2) == true);
      FCF_TEST((v2 >= v1) == true);
    }
    {
      fcf::Variant v1(std::string("3"));
      fcf::Variant v2(2);
      FCF_TEST((v1 >= v2) == true);
      FCF_TEST((v2 >= v1) == false);
    }
    {
      fcf::Variant v1(std::string("1"));
      fcf::Variant v2(2);
      FCF_TEST((v1 > v2) == false);
      FCF_TEST((v2 > v1) == true);
    }
    {
      fcf::Variant v1(std::string("2"));
      fcf::Variant v2(2);
      FCF_TEST((v1 > v2) == false);
      FCF_TEST((v2 > v1) == false);
    }
    {
      fcf::Variant v1(std::string("3"));
      fcf::Variant v2(2);
      FCF_TEST((v1 > v2) == true);
      FCF_TEST((v2 > v1) == false);
    }

    //
    // operator !
    //
    /*
    {
      fcf::Variant v1 = 1;
      bool b1 = !!v1;
      FCF_TEST(b1 == true)
      if(v1){
      }
    }
    */
  }

} // FcfTest::BasisTest namespace
