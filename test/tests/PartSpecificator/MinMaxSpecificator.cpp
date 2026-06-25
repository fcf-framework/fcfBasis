#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

#include "../bits/functions.hpp"

namespace FcfTest{
  namespace BasisTest{
    namespace MinMaxSpecificatorTest{

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

        Item& operator=(const Item& a_value){
          value = a_value.value;
          return *this;
        }

      };

}}}

namespace fcf {

  template<>
  struct Type<FcfTest::BasisTest::MinMaxSpecificatorTest::Item, MinMaxSpecificator> : public TypeImpl<FcfTest::BasisTest::MinMaxSpecificatorTest::Item, MinMaxSpecificator>{
    typedef FcfTest::BasisTest::MinMaxSpecificatorTest::Item type;

    typedef std::pair<int, int> result_type;
    inline std::pair<int, int> operator()(const type* a_object){
      return std::pair<int, int>{a_object->min, a_object->max};
    }
  };

} // fcf namespace

FCF_TYPE_REGISTRATION_FORCE(FcfTest::BasisTest::MinMaxSpecificatorTest::Item, "FcfTest::BasisTest::MinMaxSpecificatorTest::Item", 0);
FCF_SPECIFICATOR_REGISTRATION_FORCE(FcfTest::BasisTest::MinMaxSpecificatorTest::Item, fcf::MinMaxSpecificator);

FCF_FUNCTION_REGISTRATION(random,
                     "cpu",
                     fcf::random,
                     void(*) (int*, int*, const int&, const int&),
                     (
                      (fcf::CallOptions, 1, fcf::CallArgumentOptions<fcf::CAO_RESOLVE_POINTER|fcf::CAO_PAIR_ITERATION_POINTER|fcf::CAO_PAIR_SEGMENTATION>),
                      (fcf::MinMaxSpecificator, 1, int*, int*, fcf::Arg1, fcf::Arg2)
                     ),
                    );

typedef FcfTest::BasisTest::MinMaxSpecificatorTest::Item Item;

FCF_FUNCTION_REGISTRATION(random,
                     "cpu",
                     fcf::random,
                     void(*) (Item*, Item*, const int&, const int&),
                     (
                       (fcf::CallOptions, 1, fcf::CallArgumentOptions<fcf::CAO_RESOLVE_POINTER|fcf::CAO_PAIR_ITERATION_POINTER|fcf::CAO_PAIR_SEGMENTATION>),
                       (fcf::MinMaxSpecificator, 1, Item*, Item*, fcf::Arg1, fcf::Arg2)
                     ),
                    );

namespace FcfTest {
  namespace BasisTest {
    FCF_TEST_DECLARE("fcfBasis", "Specificator", "MinMaxSpecificator"){
      std::vector<FcfTest::BasisTest::MinMaxSpecificatorTest::Item> vector(100);
      fcf::call("random", vector);
      for(Item& itm : vector){
        FCF_TEST(itm.value >= 1, itm.value);
        FCF_TEST(itm.value < 10, itm.value);
      }
    }
  } // BasisTest namespace
} // FcfTest namespace
