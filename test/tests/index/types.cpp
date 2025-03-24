#include <iostream>

#include "../../libraries/fcfTest/test.hpp"

#include "../../../basis.hpp"

void indexTypesTest(){
  std::cout << "Start indexTypesTest..." << std::endl;

  {
    unsigned int index = FCF_INT8_TYPE_INDEX;
    unsigned int expected = index;
    FCF_TEST(fcf::Type<char>().index() == expected, fcf::Type<char>().index(), expected);

    expected = index | (0x0e << 24);
    FCF_TEST(
        fcf::Type<const char&>().index() == expected,
        fcf::Type<const char&>().index(),
        expected
        );

    expected = index | (0x06 << 24);
    FCF_TEST(
        fcf::Type<char&>().index() == expected,
        fcf::Type<char&>().index(),
        expected
        );

    expected = index | (0x02 << 24);
    FCF_TEST(
        fcf::Type<char*>().index() == expected,
        fcf::Type<char*>().index(),
        expected
        );

    expected = index | (0x04 << 24);
    FCF_TEST(
        fcf::Type<char**>().index() == expected,
        fcf::Type<char**>().index(),
        expected
        );
  }

  {
    unsigned int index = fcf::Type< std::vector<int> >().index();
    unsigned int expected = index;
    {
      typedef std::vector<int> type;
      FCF_TEST(fcf::Type<type>().index() == expected, fcf::Type<type>().index(), expected);
      std::string expectedName = "std::vector<int>";
      FCF_TEST(fcf::Type<type>().name() == expectedName, fcf::Type<type>().name(), expectedName);
    }
    {
      typedef std::vector<int>* type;
      std::string expectedName = "std::vector<int>*";
      FCF_TEST(fcf::Type<type>().name() == expectedName, fcf::Type<type>().name(), expectedName);
      expected = index | (0x02 << 24) | (0x01 << 24);
      FCF_TEST(
          fcf::Type<type>().index() == expected,
          fcf::Type<type>().index(),
          expected
          );
    }
    {
      typedef std::vector<int>** type;
      std::string expectedName = "std::vector<int>**";
      FCF_TEST(fcf::Type<type>().name() == expectedName, fcf::Type<type>().name(), expectedName);
      expected = index | (0x04 << 24) | (0x01 << 24);
      FCF_TEST(
          fcf::Type<type>().index() == expected,
          fcf::Type<type>().index(),
          expected
          );
    }
    {
      typedef const std::vector<int>** type;
      std::string expectedName = "const std::vector<int>**";
      FCF_TEST(fcf::Type<type>().name() == expectedName, fcf::Type<type>().name(), expectedName);
      expected = index | (0x0d << 24) | (0x01 << 24);
      FCF_TEST(
          fcf::Type<type>().index() == expected,
          fcf::Type<type>().index(),
          expected
          );
    }



  }

}
