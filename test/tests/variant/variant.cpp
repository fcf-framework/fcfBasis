#include <iostream>
#include <fcfTest/test.hpp>
#include "../macro.hpp"
#include "../../../convert.hpp"
#include "../../../Variant.hpp"
void variantTest(){
  std::cout << "Start variantTest..." << std::endl;
  {
    fcf::Variant v("123.1");
    fcf::Variant v2(v);
    fcf::Variant v3;
    v3 = v2;
    v2.clear();
    v2 = fcf::convert<fcf::Variant>("999");
    FCF_TEST(fcf::convert<double>(v2) == 999, v2.as<std::string>());
    FCF_TEST(fcf::convert<double>(v3) == 123.1, v3.as<std::string>());
  }
}
