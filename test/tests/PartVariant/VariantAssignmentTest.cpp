#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace FcfTest {
  namespace BasisTest {

    void variantAssignmentTest(){
      std::cout << "Start variantAssignmentTest()..." << std::endl;
      {
        fcf::Variant v(fcf::Type<std::string>(), 1);
        FCF_TEST(v == "1", v);
        FCF_TEST(v.getTypeInfo()->name == "std::string", v.getTypeInfo()->name);
      }
      {
        fcf::Variant v1(fcf::Type<std::string>(), 1);
        fcf::Variant v2(fcf::Type<std::string>(), v1);
        FCF_TEST(v1 == "1", v1);
        FCF_TEST(v2 == "1", v2);
      }
      {
        fcf::Variant v1(fcf::Type<std::string>(), 1);
        fcf::Variant v2(fcf::Type<std::string>(), v1, fcf::Variant::RESET);
        FCF_TEST(v1 == "1", v1);
        FCF_TEST(v2 == "1", v2);
      }
      {
        fcf::Variant v11(fcf::Type<std::string>(), 1);
        fcf::Variant v12(v11, fcf::Variant::FORCE_REFERENCE);
        fcf::Variant v1(v12, fcf::Variant::FORCE_REFERENCE);
        fcf::Variant v2(fcf::Type<std::string>(), v1, fcf::Variant::RESET);
        FCF_TEST(v1 == "1", v1);
        FCF_TEST(v2 == "1", v2);
      }
      {
        fcf::Variant v11(fcf::Type<std::string>(), 1);
        fcf::Variant v12(v11, fcf::Variant::FORCE_REFERENCE);
        fcf::Variant v1(v12, fcf::Variant::FORCE_REFERENCE);
        fcf::Variant v2(fcf::Type<std::string>(), v1, fcf::Variant::WRITE);
        FCF_TEST(v1 == "1", v1);
        FCF_TEST(v2 == "1", v2);
      }
      {
        std::string str = "1";
        fcf::Variant v1(fcf::Type<std::string>(), str, fcf::Variant::REFERENCE);
        fcf::Variant v2(fcf::Type<std::string>(), v1, fcf::Variant::REFERENCE);
        FCF_TEST(v1 == "1", v1);
        FCF_TEST(v2 == "1", v2);

        v2 = "2";
        FCF_TEST(v1 == "2", v1);
        FCF_TEST(v2 == "2", v2);
        FCF_TEST(str == "2", str);
      }
      {
        bool error = false;
        std::string str = "1";
        fcf::Variant v1(fcf::Type<std::string>(), str, fcf::Variant::REFERENCE);
        try { 
          fcf::Variant v2(fcf::Type<std::string>(), v1, fcf::Variant::FORCE_REFERENCE);
        } catch(...){
          error = true;
        }
        FCF_TEST(error == true, error);
        FCF_TEST(v1 == "1", v1);
        FCF_TEST(str == "1", str);
      }

    } // void variantAssignmentTest(){
  } // BasisTest namespace
} // FcfTest namespace
