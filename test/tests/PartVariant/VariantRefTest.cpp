#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace FcfTest {
  namespace BasisTest {
    namespace VariantRefTest {
      struct Item{
        std::string value;
        bool operator==(const Item& a_value) const{
          return value == a_value.value;
        }
      };
    }
  }
}


FCF_TYPEID_REGISTRY_FORCE(FcfTest::BasisTest::VariantRefTest::Item, "FcfTest::BasisTest::VariantRefTest::Item", 0);
namespace fcf { template<> struct Type<FcfTest::BasisTest::VariantRefTest::Item, EqualSpecificator> : public TypeImpl<FcfTest::BasisTest::VariantRefTest::Item, EqualSpecificator> {}; }
FCF_SPECIFICATOR_REGISTRY_FORCE(FcfTest::BasisTest::VariantRefTest::Item,  fcf::EqualSpecificator);


namespace FcfTest {
  namespace BasisTest {

    void variantRefTest(){
      std::cout << "Start variantRefTest()..." << std::endl;
      {
        int i = 1;
        fcf::Variant v(i, fcf::Variant::REFERENCE);
        FCF_TEST(v.ptr() == &i);
        FCF_TEST(v == i, v, i);

        v.get<int>() = 2;
        FCF_TEST(v == 2, v);
        FCF_TEST(i == 2, i);
        FCF_TEST(v == i, v, i);

        v += 1;
        FCF_TEST(v == 3, v);
        FCF_TEST(i == 3, i);
        FCF_TEST(v == i, v, i);
      }
      {
        int i1 = 1;
        fcf::Variant v1(i1, fcf::Variant::REFERENCE);
        fcf::Variant v2(v1, fcf::Variant::REFERENCE);

        FCF_TEST(i1 == 1, i1);
        FCF_TEST(v1 == 1, v1);
        FCF_TEST(v2 == 1, v2);

        i1 = 2;
        FCF_TEST(i1 == 2, i1);
        FCF_TEST(v1 == 2, v1);
        FCF_TEST(v2 == 2, v2);

        v1 = 3;
        FCF_TEST(i1 == 3, i1);
        FCF_TEST(v1 == 3, v1);
        FCF_TEST(v2 == 3, v2);

        v2 = 4;
        FCF_TEST(i1 == 4, i1);
        FCF_TEST(v1 == 4, v1);
        FCF_TEST(v2 == 4, v2);
      }
      {
        fcf::Variant v1(1);
        fcf::Variant v2(v1, fcf::Variant::REFERENCE);
        FCF_TEST(v1 == 1, v1);
        FCF_TEST(v2 == 1, v2);

        v1 = 2;
        FCF_TEST(v1 == 2, v1);
        FCF_TEST(v2 == 2, v2);

        v2 = 3;
        FCF_TEST(v1 == 3, v1);
        FCF_TEST(v2 == 3, v2);

        v2.set(1, fcf::Variant::RESET);
        FCF_TEST(v1 == 3, v1);
        FCF_TEST(v2 == 1, v2);

        v2.set(v1, fcf::Variant::REFERENCE);
        FCF_TEST(v1 == 3, v1);
        FCF_TEST(v2 == 3, v2);

        v2.set(9, fcf::Variant::WRITE);
        FCF_TEST(v1 == 9, v1);
        FCF_TEST(v2 == 9, v2);

        v2.set(1, fcf::Variant::RESET);
        FCF_TEST(v1 == 9, v1);
        FCF_TEST(v2 == 1, v2);
      }
      {
        fcf::Variant v1;
        fcf::Variant v2(v1, fcf::Variant::FORCE_REFERENCE);
        v1 = 1;
        FCF_TEST(v1 == 1);
        FCF_TEST(v2 == 1);
        v2 = 3;
        FCF_TEST(v1 == 3);
        FCF_TEST(v2 == 3);
        v2.set(4, fcf::Variant::RESET);
        FCF_TEST(v1 == 3);
        FCF_TEST(v2 == 4);
        v2 = 5;
        FCF_TEST(v1 == 3);
        FCF_TEST(v2 == 5);
        v1 = 33;
        FCF_TEST(v1 == 33);
        FCF_TEST(v2 == 5);
      }
      {
        typedef std::map<std::string, fcf::Variant> MapType;
        MapType m;
        fcf::Variant v(fcf::Type<MapType>(), m, fcf::Variant::REFERENCE);
        m["1"] = "v-1";
        m["2"] = MapType();
        m["2"]["1"] = "v-2-1";
        fcf::Variant vref = v["2"];
        FCF_TEST(v["1"] == "v-1", v[1]);
        FCF_TEST(v["2"]["1"] == "v-2-1", v["2"]["1"]);
        v["2"]["2"] = "v-2-2";
        FCF_TEST(v["2"]["2"] == "v-2-2", v["2"]["2"]);
        FCF_TEST(m["2"]["2"] == "v-2-2", m["2"]["2"]);
        v["2"]["2"] = "v-2-2-new";
        FCF_TEST(v["2"]["2"] == "v-2-2-new", v["2"]["2"]);
        FCF_TEST(m["2"]["2"] == "v-2-2-new", m["2"]["2"]);
        v["3"] = MapType();
        v["3"]["1"] = MapType();
        v["3"]["1"]["1"] = "3-1-1";
        FCF_TEST(v["3"]["1"]["1"] == "3-1-1", v["3"]["1"]["1"]);
        FCF_TEST(m["3"]["1"]["1"] == "3-1-1", m["3"]["1"]["1"]);
      }
      {
        typedef std::map<std::string, fcf::Variant> MapType;
        MapType m1;
        fcf::Variant v1(fcf::Type<MapType>(), m1, fcf::Variant::REFERENCE);
        v1["m1-1"] = 1;
        MapType m2;
        fcf::Variant v2(fcf::Type<MapType>(), m2, fcf::Variant::REFERENCE);
        v2["m2-1"] = 1;

        fcf::Variant v3 = VariantRefTest::Item{"v3-1"};
        v2["m2-2"] = v3;
        FCF_TEST(v2["m2-2"].cast<VariantRefTest::Item>().value == "v3-1", v2["m2-2"].cast<VariantRefTest::Item>().value);
        FCF_TEST(m2["m2-2"].cast<VariantRefTest::Item>().value == "v3-1", m2["m2-2"].cast<VariantRefTest::Item>().value);

        v2["m2-2"] = "v3-1-new";
        FCF_TEST(v2["m2-2"].cast<std::string>() == "v3-1-new", v2["m2-2"].cast<std::string>());
        FCF_TEST(m2["m2-2"].cast<std::string>() == "v3-1-new", m2["m2-2"].cast<std::string>());
        FCF_TEST(v3.cast<VariantRefTest::Item>().value == "v3-1", v3.cast<VariantRefTest::Item>().value);

        {
          VariantRefTest::Item item = VariantRefTest::Item{"v4-1"};
          fcf::Variant v(item, fcf::Variant::REFERENCE);
          v2["m2-3"] = v;
          FCF_TEST(v2["m2-3"].cast<VariantRefTest::Item>().value == "v4-1", v2["m2-3"].cast<VariantRefTest::Item>().value);
          FCF_TEST(m2["m2-3"].cast<VariantRefTest::Item>().value == "v4-1", m2["m2-3"].cast<VariantRefTest::Item>().value);

          v2["m2-3"] = "v4-1-new";
          FCF_TEST(v2["m2-3"].cast<std::string>() == "v4-1-new", v2["m2-3"].cast<std::string>());
          FCF_TEST(m2["m2-3"].cast<std::string>() == "v4-1-new", m2["m2-3"].cast<std::string>());
          FCF_TEST(v.cast<VariantRefTest::Item>().value == "v4-1", v.cast<VariantRefTest::Item>().value);
        }
        {
          int          i   = 1;
          fcf::Variant vs1(i, fcf::Variant::REFERENCE);
          fcf::Variant vs2(vs1, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant vs3(vs2, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant vs4(vs3, fcf::Variant::REFERENCE);
          {
            fcf::Variant v = vs4;
            FCF_TEST(v == 1, v);
            FCF_TEST(v.getTypeInfo()->name == "int", v.getTypeInfo()->name);
          }
        }
        {
          int          i1   = 1;
          fcf::Variant v1s1(i1, fcf::Variant::REFERENCE);
          fcf::Variant v1s2(v1s1, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s3(v1s2, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s4(v1s3, fcf::Variant::REFERENCE);

          int          i2   = 1;
          fcf::Variant v2s1(i2, fcf::Variant::REFERENCE);
          fcf::Variant v2s2(v2s1, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v2s3(v2s2, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v2s4(v2s3, fcf::Variant::REFERENCE);

          FCF_TEST(v1s4 == v2s4, v1s4, v2s4);
          FCF_TEST(!(v1s4 < v2s4), v1s4, v2s4);
          i2 = 2;
          FCF_TEST(v1s4 != v2s4, v1s4, v2s4);
          FCF_TEST(v1s4 < v2s4, v1s4, v2s4);
        }
        {
          VariantRefTest::Item i1{"1"};
          fcf::Variant v1s1(i1, fcf::Variant::REFERENCE);
          fcf::Variant v1s2(v1s1, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s3(v1s2, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s4(v1s3, fcf::Variant::REFERENCE);

          VariantRefTest::Item i2{"1"};
          fcf::Variant v2s1(i2, fcf::Variant::REFERENCE);
          fcf::Variant v2s2(v2s1, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v2s3(v2s2, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v2s4(v2s3, fcf::Variant::REFERENCE);

          FCF_TEST(v1s4 == v2s4, v1s4, v2s4);
          i2.value = "2";
          FCF_TEST(v1s4 != v2s4, v1s4, v2s4);
          i1.value = "2";
          FCF_TEST(v1s4 == v2s4, v1s4, v2s4);

          FCF_TEST(v1s4.cast<VariantRefTest::Item>().value == "2", v1s4);

          v1s4 = VariantRefTest::Item{"3"};
          FCF_TEST(i1.value == "3", i1.value);

          //FCF_TEST(v1s4 < v2s4, v1s4, v2s4);
        }
        {
          VariantRefTest::Item i1{"1"};
          fcf::Variant v1s1(i1, fcf::Variant::REFERENCE);
          fcf::Variant v1s2(v1s1, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s3(v1s2, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s4(v1s3, fcf::Variant::REFERENCE);

          VariantRefTest::Item i2{"1"};
          fcf::Variant v2s1(i2, fcf::Variant::REFERENCE);
          fcf::Variant v2s3(v2s1, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v2s4(v2s3, fcf::Variant::REFERENCE);

          FCF_TEST(v1s4 == v2s4, v1s4.cast<VariantRefTest::Item>().value, v2s4.cast<VariantRefTest::Item>().value);
          i2.value = "2";
          FCF_TEST(v1s4 != v2s4, v1s4.cast<VariantRefTest::Item>().value, v2s4.cast<VariantRefTest::Item>().value);
          i1.value = "2";
          FCF_TEST(v1s4 == v2s4, v1s4.cast<VariantRefTest::Item>().value, v2s4.cast<VariantRefTest::Item>().value);

          FCF_TEST(v1s4.cast<VariantRefTest::Item>().value == "2", v1s4.cast<VariantRefTest::Item>().value);
        }
        {
          VariantRefTest::Item i1{"1"};
          fcf::Variant v1s1(i1, fcf::Variant::REFERENCE);
          fcf::Variant v1s2(v1s1, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s3(v1s2, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s4(v1s3, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s5(v1s4, fcf::Variant::REFERENCE);

          VariantRefTest::Item i2{"2"};
          fcf::Variant v2s1(i2, fcf::Variant::REFERENCE);
          fcf::Variant v2s3(v2s1, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v2s4(v2s3, fcf::Variant::REFERENCE);

          v2s4 = v1s5;
          FCF_TEST(i1.value == "1", i1.value);
          FCF_TEST(i2.value == "1", i2.value);
          FCF_TEST(v1s5.cast<VariantRefTest::Item>().value == "1", v1s5.cast<VariantRefTest::Item>().value);
          FCF_TEST(v2s4.cast<VariantRefTest::Item>().value == "1", v2s4.cast<VariantRefTest::Item>().value);
        }
        {
          VariantRefTest::Item i1{"1"};
          fcf::Variant v1s1(i1, fcf::Variant::REFERENCE);
          fcf::Variant v1s2(v1s1, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s3(v1s2, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s4(v1s3, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s5(v1s4, fcf::Variant::REFERENCE);

          VariantRefTest::Item i2{"2"};
          fcf::Variant v2s1(i2, fcf::Variant::REFERENCE);
          fcf::Variant v2s3(v2s1, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v2s4(v2s3, fcf::Variant::REFERENCE);

          v1s5 = v2s4;
          FCF_TEST(i1.value == "2", i1.value);
          FCF_TEST(i2.value == "2", i2.value);
          FCF_TEST(v1s5.cast<VariantRefTest::Item>().value == "2", v1s5.cast<VariantRefTest::Item>().value);
          FCF_TEST(v2s4.cast<VariantRefTest::Item>().value == "2", v2s4.cast<VariantRefTest::Item>().value);
        }
        {
          VariantRefTest::Item i1{"1"};
          fcf::Variant v1s1(i1, fcf::Variant::REFERENCE);
          fcf::Variant v1s2(v1s1, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s3(v1s2, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s4(v1s3, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1(v1s4, fcf::Variant::REFERENCE);

          fcf::Variant v2(v1);
          FCF_TEST(v2.getTypeInfo()->name == "FcfTest::BasisTest::VariantRefTest::Item", v2.getTypeInfo()->name);
        }
        {
          VariantRefTest::Item i1{"1"};
          fcf::Variant v1s1(i1, fcf::Variant::REFERENCE);
          fcf::Variant v1s2(v1s1, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s3(v1s2, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s4(v1s3, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1(v1s4, fcf::Variant::REFERENCE);

          fcf::Variant v2;
          v2 = v1;
          FCF_TEST(v2.getTypeInfo()->name == "FcfTest::BasisTest::VariantRefTest::Item", v2.getTypeInfo()->name);
        }
        {
          VariantRefTest::Item i1{"1"};
          fcf::Variant v1s1(i1, fcf::Variant::REFERENCE);
          fcf::Variant v1s2(v1s1, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s3(v1s2, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s4(v1s3, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1(v1s4, fcf::Variant::REFERENCE);

          fcf::Variant v2(v1, fcf::Variant::RESET);
          FCF_TEST(v2.getTypeInfo()->name == "FcfTest::BasisTest::VariantRefTest::Item", v2.getTypeInfo()->name);
        }
        {
          VariantRefTest::Item i1{"1"};
          fcf::Variant v1s1(i1, fcf::Variant::REFERENCE);
          fcf::Variant v1s2(v1s1, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s3(v1s2, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1s4(v1s3, fcf::Variant::FORCE_REFERENCE);
          fcf::Variant v1(v1s4, fcf::Variant::REFERENCE);

          fcf::Variant v2;
          v2 = v1;
          FCF_TEST(v2.getTypeInfo()->name == "FcfTest::BasisTest::VariantRefTest::Item", v2.getTypeInfo()->name);
        }

      }
    }

  }
}

