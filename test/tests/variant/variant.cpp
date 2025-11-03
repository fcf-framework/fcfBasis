#include <iostream>
#include <fcfTest/test.hpp>
#include "../macro.hpp"
#include "../../../convert.hpp"
#include "../../../Variant.hpp"
#include "../../../Type.hpp"

void variantTest(){
  std::cout << "Start variantTest..." << std::endl;
  {
    fcf::Variant v("123.1");
    fcf::Variant v2(v);
    fcf::Variant v3;
    v3 = v2;
    v2.clear();
    v2 = fcf::convert<fcf::Variant>("999");
    FCF_TEST(fcf::convert<double>(v2) == 999, v2.cast<std::string>());
    FCF_TEST(fcf::convert<double>(v3) == 123.1, v3.cast<std::string>());
  }
  {
    fcf::Variant v1((int)1);
    fcf::BasicVariant<128> v2(v1);
    FCF_TEST(v1.get<int>() == 1, v1.get<int>());
    FCF_TEST(v1.get<int>() == v2.get<int>(), v1.get<int>(), v2.get<int>());
  }
  {
    fcf::Variant v1((int)1);
    fcf::BasicVariant<128> v2;
    v2 = v1;
    FCF_TEST(v1.get<int>() == 1, v1.get<int>());
    FCF_TEST(v1.get<int>() == v2.get<int>(), v1.get<int>(), v2.get<int>());
  }

  {
    unsigned int intTypeIndex = fcf::Type<int>().index();
    fcf::Variant v1( fcf::DynamicType{intTypeIndex} );
    FCF_TEST(v1.typeIndex() == intTypeIndex, v1.typeIndex(), intTypeIndex);

    unsigned int charTypeIndex = fcf::Type<char>().index();
    v1.reset(fcf::DynamicType{charTypeIndex});
    FCF_TEST(v1.typeIndex() == charTypeIndex, v1.typeIndex(), charTypeIndex);

    v1.clear();

    FCF_TEST(v1.typeIndex() == 0, v1.typeIndex());
  }
  {
    fcf::Variant v1( fcf::Type<int>{} );
    FCF_TEST(v1.typeIndex() == fcf::Type<int>().index(), v1.typeIndex(), fcf::Type<int>().index());

    unsigned int charTypeIndex = fcf::Type<char>().index();
    v1.reset(fcf::Type<char>{});
    FCF_TEST(v1.typeIndex() == charTypeIndex, v1.typeIndex(), charTypeIndex);
  }

}
