#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"
#include "../../../bits/functions/random.hpp"


namespace FcfTest::BasisTest::MinMaxSpecificatorTest{

  struct Item{
    int value;
    int min;
    int max;

    Item()
      : value(0)
      , min(1)
      , max(10) {
    }
    Item(const Item& a_item)
      : value(a_item.value)
      , min(a_item.min)
      , max(a_item.max) {
    }

    Item(int a_value)
      : value(a_value)
      , min(1)
      , max(10) {
    }

    Item& operator=(int a_value){
      value = a_value;
      return *this;
    }

  };

}

namespace fcf {

  template<>
  struct Type<FcfTest::BasisTest::MinMaxSpecificatorTest::Item, MinMaxSpecificator> : public TypeImpl<FcfTest::BasisTest::MinMaxSpecificatorTest::Item, MinMaxSpecificator>{
    typedef FcfTest::BasisTest::MinMaxSpecificatorTest::Item type;
    inline void call(type* a_object, int* a_min, int* a_max){
      *a_min = a_object->min;
      *a_max = a_object->max;
    }
  };

} // fcf namespace

FCF_TYPEID_REGISTRY_FORCE(FcfTest::BasisTest::MinMaxSpecificatorTest::Item, "FcfTest::BasisTest::MinMaxSpecificatorTest::Item", 0);
FCF_SPECIFICATOR_REGISTRY_FORCE(FcfTest::BasisTest::MinMaxSpecificatorTest::Item, fcf::MinMaxSpecificator);

FCF_DECLARE_FUNCTION(random,
                     "engine_cpu",
                     fcf::random,
                     void(*) (int*, int*, const int&, const int&),
                     ((fcf::MinMaxSpecificator, 1, int*, int*, fcf::Arg1, fcf::Arg2)),
                    );

typedef FcfTest::BasisTest::MinMaxSpecificatorTest::Item Item;

FCF_DECLARE_FUNCTION(random,
                     "engine_cpu",
                     fcf::random,
                     void(*) (Item*, Item*, const int&, const int&),
                     ((fcf::MinMaxSpecificator, 1, Item*, Item*, fcf::Arg1, fcf::Arg2)),
                    );

namespace FcfTest::BasisTest {




  void minMaxSpecificatorTest(){
    std::cout << "Start minMaxSpecificatorTest()..." << std::endl;
    std::vector<FcfTest::BasisTest::MinMaxSpecificatorTest::Item> vector(100);
    fcf::call("random", vector);
    for(Item& itm : vector){
      FCF_TEST(itm.value >= 1, itm.value);
      FCF_TEST(itm.value < 10, itm.value);
    }

  }

} // FcfTest::BasisTest namespace
