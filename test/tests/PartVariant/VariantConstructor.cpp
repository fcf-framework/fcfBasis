#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace FcfTest {
  namespace BasisTest {
    namespace ConstructorTest {
      struct BigItem{
        char data[512];
      };
}}}

FCF_TYPEID_REGISTRY(FcfTest::BasisTest::ConstructorTest::BigItem, "FcfTest::BasisTest::ConstructorTest::BigItem", 0);

namespace FcfTest {
  namespace BasisTest {

    void variantConstructorTest(){
      std::cout << "Start variantConstructorTest()..." << std::endl;

      {
        typedef int type;
        fcf::Variant v(fcf::DynamicType(fcf::Type<type>().index()));
        FCF_TEST(v.typeIndex() == fcf::Type<type>().index(), v.typeIndex(), fcf::Type<type>().index());
        FCF_TEST(v.isInnerMemory() == true);
      }
      {
        typedef ConstructorTest::BigItem type;
        fcf::Variant v(fcf::DynamicType(fcf::Type<type>().index()));
        FCF_TEST(v.typeIndex() == fcf::Type<type>().index(), v.typeIndex(), fcf::Type<type>().index());
        FCF_TEST(v.isInnerMemory() == false);
      }
      {
        typedef int type;
        fcf::Variant v{fcf::Type<type>()};
        FCF_TEST(v.typeIndex() == fcf::Type<type>().index(), v.typeIndex(), fcf::Type<type>().index());
        FCF_TEST(v.isInnerMemory() == true);
      }
      {
        typedef ConstructorTest::BigItem type;
        fcf::Variant v{fcf::Type<type>()};
        FCF_TEST(v.typeIndex() == fcf::Type<type>().index(), v.typeIndex(), fcf::Type<type>().index());
        FCF_TEST(v.isInnerMemory() == false);
      }
      {
        typedef int type;
        fcf::Variant v(fcf::Type<type>().getTypeInfo());
        FCF_TEST(v.typeIndex() == fcf::Type<type>().index(), v.typeIndex(), fcf::Type<type>().index());
        FCF_TEST(v.isInnerMemory() == true);
      }
      {
        typedef ConstructorTest::BigItem type;
        fcf::Variant v(fcf::Type<type>().getTypeInfo());
        FCF_TEST(v.typeIndex() == fcf::Type<type>().index(), v.typeIndex(), fcf::Type<type>().index());
        FCF_TEST(v.isInnerMemory() == false);
      }

      // reset
      {
        typedef int type;
        fcf::Variant v = "asd";
        v.reset(fcf::DynamicType(fcf::Type<type>().index()));
        FCF_TEST(v.typeIndex() == fcf::Type<type>().index(), v.typeIndex(), fcf::Type<type>().index());
        FCF_TEST(v.isInnerMemory() == true);
      }
      {
        typedef ConstructorTest::BigItem type;
        fcf::Variant v = "asd";
        v.reset(fcf::DynamicType(fcf::Type<type>().index()));
        FCF_TEST(v.typeIndex() == fcf::Type<type>().index(), v.typeIndex(), fcf::Type<type>().index());
        FCF_TEST(v.isInnerMemory() == false);
      }
      {
        typedef int type;
        fcf::Variant v{fcf::Type<type>()};
        FCF_TEST(v.typeIndex() == fcf::Type<type>().index(), v.typeIndex(), fcf::Type<type>().index());
        FCF_TEST(v.isInnerMemory() == true);
      }
      {
        typedef ConstructorTest::BigItem type;
        fcf::Variant v = "asd";
        v.reset(fcf::Type<type>());
        FCF_TEST(v.typeIndex() == fcf::Type<type>().index(), v.typeIndex(), fcf::Type<type>().index());
        FCF_TEST(v.isInnerMemory() == false);
      }
      {
        typedef int type;
        fcf::Variant v = "asd";
        v.reset(fcf::Type<type>().getTypeInfo());
        FCF_TEST(v.typeIndex() == fcf::Type<type>().index(), v.typeIndex(), fcf::Type<type>().index());
        FCF_TEST(v.isInnerMemory() == true);
      }
      {
        typedef ConstructorTest::BigItem type;
        fcf::Variant v = "asd";
        v.reset(fcf::Type<type>().getTypeInfo());
        FCF_TEST(v.typeIndex() == fcf::Type<type>().index(), v.typeIndex(), fcf::Type<type>().index());
        FCF_TEST(v.isInnerMemory() == false);
      }

    }
  }

} // FcfTest::BasisTest
