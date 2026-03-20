#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace FcfTest {
  namespace BasisTest {

    FCF_TEST_DECLARE("fcfBasis", "Variant", "const variant"){
      {
        bool error = false;
        int i = 1;
        fcf::Variant v(fcf::Type<const int>(), i, fcf::Variant::REFERENCE);
        FCF_TEST(v == 1, v);
        try {
          v = 2;
        } catch (std::exception&) {
          error = true;
        }
        FCF_TEST(error == true);
        FCF_TEST(v == 1, v);
        FCF_TEST(i == 1, i);
      }
      {
        bool error = false;
        fcf::Variant v(fcf::Type<const int>(), 1);
        try {
          v = 2;
        } catch (std::exception&) {
          error = true;
        }
        FCF_TEST(error == true);
        FCF_TEST(v == 1, v);
      }
      {
        bool error = false;
        fcf::Variant v(fcf::Type<const int>(), 2);
        try {
          v /= 2;
        } catch (std::exception&) {
          error = true;
        }
        FCF_TEST(error == true);
        FCF_TEST(v == 2, v);
      }
      {
        bool error = false;
        fcf::Variant v(fcf::Type<const int>(), 2);
        fcf::Variant v2(2);
        try {
          v /= v2;
        } catch (std::exception&) {
          error = true;
        }
        FCF_TEST(error == true);
        FCF_TEST(v == 2, v);
      }
      {
        bool error = false;
        fcf::Variant v(fcf::Type<const std::vector<int> >(), std::vector<int>({1,2,3}));
        try {
          v[0] = 2;
        } catch(std::exception&){
          error = true;
        }
        FCF_TEST(error == true);
        FCF_TEST(v[0] == 1, v[0]);
      }
      {
        bool error = false;
        std::vector<int> vec={1,2,3};
        fcf::Variant v(fcf::Type<const std::vector<int> >(), vec, fcf::Variant::REFERENCE);
        try {
          v[0] = 2;
        } catch(std::exception&){
          error = true;
        }
        FCF_TEST(error == true);
        FCF_TEST(v[0] == 1, v[0]);
        FCF_TEST(vec[0] == 1, vec[0]);
      }
      {
        bool error = false;
        const std::vector<int> vec={1,2,3};
        try {
          fcf::Variant v(fcf::Type< std::vector<int> >(), vec, fcf::Variant::REFERENCE);
        } catch(std::exception&){
          error = true;
        }
        FCF_TEST(error == true);
      }

      {
        bool error = false;
        std::vector<int> vec={1,2,3};
        fcf::Variant v1(vec, fcf::Variant::REFERENCE);
        fcf::Variant v2(v1, fcf::Variant::FORCE_REFERENCE);
        fcf::Variant v3(v2, fcf::Variant::FORCE_REFERENCE);
        fcf::Variant v4(v3, fcf::Variant::REFERENCE);
        fcf::Variant v(v4, fcf::Variant::FORCE_REFERENCE);
        try {
          v[0] = 1;
        } catch(std::exception&){
          error = true;
        }
        FCF_TEST(error == false);
      }
      {
        bool error = false;
        const std::vector<int> vec={1,2,3};
        fcf::Variant v1(vec, fcf::Variant::REFERENCE);
        fcf::Variant v2(v1, fcf::Variant::FORCE_REFERENCE);
        fcf::Variant v3(v2, fcf::Variant::FORCE_REFERENCE);
        fcf::Variant v4(v3, fcf::Variant::REFERENCE);
        fcf::Variant v(v4, fcf::Variant::FORCE_REFERENCE);
        try {
          v[0] = 1;
        } catch(std::exception&){
          error = true;
        }
        FCF_TEST(error == true);
      }

      {
        bool error = false;
        std::vector<int> vec={1,2,3};
        fcf::Variant v1;
        v1.set(vec, fcf::Variant::REFERENCE);
        fcf::Variant v2(v1, fcf::Variant::FORCE_REFERENCE);
        fcf::Variant v3(v2, fcf::Variant::FORCE_REFERENCE);
        fcf::Variant v4(v3, fcf::Variant::REFERENCE);
        fcf::Variant v(v4, fcf::Variant::FORCE_REFERENCE);
        try {
          v[0] = 1;
        } catch(std::exception&){
          error = true;
        }
        FCF_TEST(error == false);
      }
      {
        bool error = false;
        const std::vector<int> vec={1,2,3};
        fcf::Variant v1;
        v1.set(vec, fcf::Variant::REFERENCE);
        fcf::Variant v2(v1, fcf::Variant::FORCE_REFERENCE);
        fcf::Variant v3(v2, fcf::Variant::FORCE_REFERENCE);
        fcf::Variant v4(v3, fcf::Variant::REFERENCE);
        fcf::Variant v(v4, fcf::Variant::FORCE_REFERENCE);
        try {
          v[0] = 1;
        } catch(std::exception&){
          error = true;
        }
        FCF_TEST(error == true);
      }
      {
        bool error = false;
        int i = 1;
        fcf::Variant v11(i, fcf::Variant::REFERENCE);
        fcf::Variant v12(v11, fcf::Variant::FORCE_REFERENCE);
        fcf::Variant v13(v12, fcf::Variant::FORCE_REFERENCE);
        fcf::Variant v1(fcf::Type<const fcf::Variant>(), v13, fcf::Variant::FORCE_REFERENCE);
        try {
          v1 = 2;
        } catch(std::exception&){
          error = true;
        }
        FCF_TEST(v1 == 1, v1);
        FCF_TEST(error == true);

        try {
          v1 *= 2;
        } catch(std::exception&){
          error = true;
        }
        FCF_TEST(v1 == 1, v1);
        FCF_TEST(error == true);
      }
      {
        bool error = false;
        int i = 1;
        fcf::Variant v11(i, fcf::Variant::REFERENCE);
        fcf::Variant v12(v11, fcf::Variant::FORCE_REFERENCE);
        fcf::Variant v1(v12, fcf::Variant::FORCE_REFERENCE);

        fcf::Variant v2((const fcf::Variant&) v1, fcf::Variant::FORCE_REFERENCE);
        try {
          v2 = 2;
        } catch(std::exception&){
          error = true;
        }

        FCF_TEST(v2.get<fcf::Variant>().get<fcf::Variant>().get<fcf::Variant>().get<int>() == 1, v2.get<fcf::Variant>().get<fcf::Variant>().get<fcf::Variant>().get<int>());
        FCF_TEST(error == true);
        FCF_TEST(v1 == 1, v1);
        FCF_TEST(v2 == 1, v2);
      }
      {
        bool error = false;
        int i = 1;
        fcf::Variant v11(i, fcf::Variant::REFERENCE);
        fcf::Variant v12(v11, fcf::Variant::FORCE_REFERENCE);
        fcf::Variant v1(v12, fcf::Variant::FORCE_REFERENCE);

        fcf::Variant v2(fcf::Type<const fcf::Variant>(), v1, fcf::Variant::FORCE_REFERENCE);
        try {
          v2 = 2;
        } catch(std::exception&){
          error = true;
        }

        FCF_TEST(v2.get<const fcf::Variant>().get<fcf::Variant>().get<fcf::Variant>().get<int>() == 1, v2.get<fcf::Variant>().get<fcf::Variant>().get<fcf::Variant>().get<int>());
        FCF_TEST(error == true);
        FCF_TEST(v1 == 1, v1);
        FCF_TEST(v2 == 1, v2);
      }
      {
        bool error = false;
        int i = 1;
        fcf::Variant v11(i, fcf::Variant::REFERENCE);
        fcf::Variant v12(v11, fcf::Variant::FORCE_REFERENCE);
        fcf::Variant v1(v12, fcf::Variant::FORCE_REFERENCE);

        fcf::Variant v2((const fcf::Variant&) v1, fcf::Variant::REFERENCE);
        try {
          v2 = 2;
        } catch(std::exception&){
          error = true;
        }

        FCF_TEST(error == true);
        FCF_TEST(v2.get<const fcf::Variant>().get<fcf::Variant>().get<int>() == 1, v2.get<const fcf::Variant>().get<fcf::Variant>().get<int>());
        FCF_TEST(v1 == 1, v1);
        FCF_TEST(v2 == 1, v2);
      }
      {
        bool error = false;
        int i = 1;
        fcf::Variant v11(i, fcf::Variant::REFERENCE);
        fcf::Variant v12(v11, fcf::Variant::FORCE_REFERENCE);
        fcf::Variant v1(v12, fcf::Variant::FORCE_REFERENCE);

        fcf::Variant v2(fcf::Type<const fcf::Variant>(), v1, fcf::Variant::REFERENCE);
        try {
          v2 = 2;
        } catch(std::exception&){
          error = true;
        }

        FCF_TEST(v2.get<const fcf::Variant>().get<fcf::Variant>().get<int>() == 1, v2.get<const fcf::Variant>().get<fcf::Variant>().get<int>());
        FCF_TEST(error == true);
        FCF_TEST(v1 == 1, v1);
        FCF_TEST(v2 == 1, v2);
      }
      {
        std::vector<int> vector{1,2,3};
        fcf::Variant variant(fcf::Type< const std::vector<int> >(), vector, fcf::Variant::REFERENCE);
        FCF_TEST((*variant.cbegin()).getTypeInfo()->name == "const int&", (*variant.cbegin()).getTypeInfo()->name);
      }
      {
        const std::vector<int> vector{1,2,3};
        fcf::Variant variant(vector, fcf::Variant::REFERENCE);
        FCF_TEST((*variant.cbegin()).getTypeInfo()->name == "const int&", (*variant.cbegin()).getTypeInfo()->name);
      }
      {
        std::vector<int> vector{1,2,3};
        fcf::Variant variant(vector, fcf::Variant::REFERENCE);
        FCF_TEST((*variant.cbegin()).getTypeInfo()->name == "const int&", (*variant.cbegin()).getTypeInfo()->name);
        FCF_TEST((*variant.begin()).getTypeInfo()->name == "int&", (*variant.begin()).getTypeInfo()->name);
      }
      {
        std::vector<int> vector{1,2,3};
        fcf::Variant variant(fcf::Type< const std::vector<int> >(), vector, fcf::Variant::REFERENCE);
        fcf::Variant element = *variant.cbegin();
        FCF_TEST(element.getTypeInfo()->name == "const int&", element.getTypeInfo()->name);
        bool error = false;
        try {
          element = 2;
        } catch (...){
          error = true;
        }
        FCF_TEST(error == true, error);
        FCF_TEST(vector[0] == 1, vector[0]);
      }
      {
        std::map<int, std::string> obj{{1, "001"}, {2, "002"}};
        fcf::Variant variant(fcf::Type<std::map<int, std::string> >(), obj, fcf::Variant::REFERENCE);
        {
          bool error = false;
          fcf::Variant variantItem = *variant.cbegin();
          try {
            variantItem = "001-1";
          } catch(...){
            error = true;
          }
          FCF_TEST(error == true, error);
        }
        FCF_TEST((*variant.cbegin()).getTypeInfo()->name == "const std::string&", (*variant.cbegin()).getTypeInfo()->name);
        FCF_TEST((*variant.begin()).getTypeInfo()->name == "std::string&", (*variant.begin()).getTypeInfo()->name);
      }
      {
        std::map<int, std::string> obj{{1, "001"}, {2, "002"}};
        fcf::Variant variant(fcf::Type< const std::map<int, std::string> >(), obj, fcf::Variant::REFERENCE);
        FCF_TEST((*variant.cbegin()).getTypeInfo()->name == "const std::string&", (*variant.cbegin()).getTypeInfo()->name);
        FCF_TEST((*variant.begin()).getTypeInfo()->name == "const std::string&", (*variant.begin()).getTypeInfo()->name);
      }
      {
        std::map<int, std::string> obj{{1, "001"}, {2, "002"}};
        fcf::Variant variant(obj, fcf::Variant::REFERENCE);
        FCF_TEST((*variant.cbegin()).getTypeInfo()->name == "const std::string&", (*variant.cbegin()).getTypeInfo()->name);
        FCF_TEST((*variant.begin()).getTypeInfo()->name == "std::string&", (*variant.begin()).getTypeInfo()->name);
      }

    }

  } // BasisTest namespace
} // FcfTest namespace
