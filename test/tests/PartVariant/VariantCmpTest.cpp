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
    //
    // operator ==
    //
    {
      fcf::Variant v1;
      fcf::Variant v2(2);
      FCF_TEST((v1 == v2) == false);
      FCF_TEST((v2 == v1) == false);
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

    //
    // operator other
    //
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

  }

} // FcfTest::BasisTest namespace
