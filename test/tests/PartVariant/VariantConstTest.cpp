#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace FcfTest {
  namespace BasisTest {

    void variantConstTest(){
      std::cout << "Start variantConstTest()..." << std::endl;
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
          fcf::Variant v(fcf::Type<std::vector<int> >(), vec, fcf::Variant::REFERENCE);
        } catch(std::exception&){
          error = true;
        }
        FCF_TEST(error == true);
      }
      {
        typedef std::map<std::string, fcf::Variant> MapType;
        MapType m;
        fcf::Variant v(fcf::Type<MapType>(), m, fcf::Variant::REFERENCE);
        m["1"] = "v-1";
        m["2"] = MapType();
        /*
        m["2"]["1"] = "v-2-1";

        for(auto it = m["2"].get<MapType>().begin(); it != m["2"].get<MapType>().end(); ++it){
          std::cout << "key: " << it->first << "; value:" << it->second << std::endl;
        }
        std::cout << m["2"].get<MapType>().size() << std::endl;
        std::cout << m["2"]["1"].typeIndex() << std::endl;
        FCF_TEST(v["1"] == "v-1", v[1]);
        FCF_TEST(v["2"]["1"] == "v-2-1", v["2"]["1"]);
        */
      }

    }

  } // BasisTest namespace
} // FcfTest namespace
