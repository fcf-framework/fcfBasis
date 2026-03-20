#include <iostream>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

FCF_TEST_DECLARE("fcfBasis", "Type", "type index"){
  {
    unsigned int index = FCF_INT8_TYPE_INDEX;
    unsigned int expected = index;
    FCF_TEST(fcf::Type<char>().index() == expected, fcf::Type<char>().index(), expected);

    expected = index | (0x0a << 24);
    FCF_TEST(
        fcf::Type<const char&>().index() == expected,
        fcf::Type<const char&>().index(),
        expected
        );

    expected = index | (0x02 << 24);
    FCF_TEST(
        fcf::Type<char&>().index() == expected,
        fcf::Type<char&>().index(),
        expected
        );

    expected = index | (0x10 << 24);
    FCF_TEST(
        fcf::Type<char*>().index() == expected,
        fcf::Type<char*>().index(),
        expected
        );

    expected = index | (0x20 << 24);
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
      FCF_TEST(
          fcf::Type< std::vector<unsigned int> >().index() != fcf::Type< std::vector<int> >().index(),
          fcf::Type< std::vector<unsigned int> >().index(),
           fcf::Type< std::vector<int> >().index()
          );
      FCF_TEST(
          fcf::Type< std::vector<int> >().name() == "std::vector<int>",
          fcf::Type< std::vector<unsigned int> >().name()
          );
      FCF_TEST(
          fcf::Type< std::vector<int>* >().name() == "std::vector<int>*",
          fcf::Type< std::vector<int>* >().name()
          );
      FCF_TEST(
          fcf::Type< std::vector<unsigned int> >().name() == "std::vector<unsigned int>",
          fcf::Type< std::vector<unsigned int> >().name()
          );
    }
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
      expected = index | (0x10 << 24) | (0x01 << 24);
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
      expected = index | (0x20 << 24) | (0x01 << 24);
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
      expected = index | (0x28 << 24) | (0x01 << 24);
      FCF_TEST(
          fcf::Type<type>().index() == expected,
          fcf::Type<type>().index(),
          expected
          );
    }



  }
}
