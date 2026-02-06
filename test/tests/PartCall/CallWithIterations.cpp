#include <iostream>
#include <exception>
#include <chrono>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"


namespace FcfTest {
  namespace BasisTest {
    namespace CallIterationsTest {
      struct Item{
        int value;
        int defaultValue;
        Item& operator=(int a_value){
          value = a_value;
          return *this;
        }
      };
    }
  }
}

namespace fcf {
  template <>
  struct Type<FcfTest::BasisTest::CallIterationsTest::Item, ValueSpecificator> : public TypeImpl<FcfTest::BasisTest::CallIterationsTest::Item, ValueSpecificator> {
    inline auto call(FcfTest::BasisTest::CallIterationsTest::Item* a_container) const -> decltype(a_container->defaultValue) {
      return a_container->defaultValue;
    }
  };
}

FCF_TYPEID_REGISTRY_FORCE(FcfTest::BasisTest::CallIterationsTest::Item, "FcfTest::BasisTest::CallIterationsTest::Item",                           0);
FCF_SPECIFICATOR_REGISTRY_FORCE(FcfTest::BasisTest::CallIterationsTest::Item, fcf::ValueSpecificator);

FCF_DECLARE_FUNCTION(fill,
                   "engine_cpu",
                   fcf::fill,
                   void(*) (FcfTest::BasisTest::CallIterationsTest::Item*, FcfTest::BasisTest::CallIterationsTest::Item*, int),
                   (
                    (fcf::CallOptions, 1, fcf::CallArgumentOptions<fcf::CAO_RESOLVE_POINTER|fcf::CAO_PAIR_ITERATION_POINTER|fcf::CAO_PAIR_SEGMENTATION>),
                    (fcf::ValueSpecificator, 1, FcfTest::BasisTest::CallIterationsTest::Item*, FcfTest::BasisTest::CallIterationsTest::Item*, fcf::Arg1)
                   ),
                  );

namespace FcfTest {
  namespace BasisTest {


    void callIterationsTest (){
      std::cout << "Start callIterationsTest()..." << std::endl;
      {
        std::list<int> list;
        fcf::call("fill", list, 999);
        FCF_TEST(list.size() == 0, list.size());
      }
      {
        std::list<int> list(10, 0);
        fcf::call("fill", list, 999);
        FCF_TEST(list.size() == 10, list.size());
        for(int& item : list){
          FCF_TEST(item == 999, item);
        }
      }
      {
        std::list<unsigned int> list(10, 0);
        fcf::call("fill", list, (int)999);
        FCF_TEST(list.size() == 10, list.size());
        for(unsigned int& item : list){
          FCF_TEST(item == 999, item);
        }
      }
      {
        std::list<unsigned int> list;
        fcf::call("fill", list, (int)999);
        FCF_TEST(list.size() == 0, list.size());
      }
      {
        std::list<FcfTest::BasisTest::CallIterationsTest::Item> list;
        list.push_back({0, 1});
        list.push_back({0, 2});
        list.push_back({0, 3});
        list.push_back({0, 4});
        list.push_back({0, 5});
        fcf::call("fill", list);
        FCF_TEST(list.size() == 5, list.size());
        int expected = 1;
        for(FcfTest::BasisTest::CallIterationsTest::Item& item : list){
          FCF_TEST(item.value == expected, item.value);
          FCF_TEST(item.defaultValue == expected, item.value);
          ++expected;
        }
      }
      {
        std::vector<FcfTest::BasisTest::CallIterationsTest::Item> list;
        list.push_back({0, 1});
        list.push_back({0, 2});
        list.push_back({0, 3});
        list.push_back({0, 4});
        list.push_back({0, 5});
        fcf::call("fill", list);
        FCF_TEST(list.size() == 5, list.size());
        int expected = 1;
        for(FcfTest::BasisTest::CallIterationsTest::Item& item : list){
          FCF_TEST(item.value == expected, item.value);
          FCF_TEST(item.defaultValue == expected, item.value);
          ++expected;
        }
      }


    }

  } // BasisTest namespace
} // FcfTest namespace
