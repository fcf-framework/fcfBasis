#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

#include "../bits/functions.hpp"

namespace FcfTest{
  namespace BasisTest{
    namespace MinMaxSpecifierTest{

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
  struct Type<FcfTest::BasisTest::MinMaxSpecifierTest::Item, MinMaxSpecifier> : public TypeImpl<FcfTest::BasisTest::MinMaxSpecifierTest::Item, MinMaxSpecifier>{
    typedef FcfTest::BasisTest::MinMaxSpecifierTest::Item type;

    typedef std::pair<int, int> result_type;
    inline std::pair<int, int> operator()(const type* a_object){
      return std::pair<int, int>{a_object->min, a_object->max};
    }
  };

} // fcf namespace

FCF_TYPE_REGISTRATION_FORCE(FcfTest::BasisTest::MinMaxSpecifierTest::Item, "FcfTest::BasisTest::MinMaxSpecifierTest::Item", 0);
FCF_SPECIFIER_REGISTRATION_FORCE(FcfTest::BasisTest::MinMaxSpecifierTest::Item, fcf::MinMaxSpecifier);

FCF_FUNCTION_REGISTRATION(
                     fcf::random,
                     "random",
                     "cpu",
                     void(*) (int*, int*, const int&, const int&),
                     (
                      (fcf::CallOptions, 1, fcf::CallArgumentOptions<fcf::CAO_RESOLVE_POINTER|fcf::CAO_PAIR_ITERATION_POINTER|fcf::CAO_PAIR_SEGMENTATION>),
                      (fcf::MinMaxSpecifier, 1, int*, int*, fcf::Arg1, fcf::Arg2)
                     ),
                     false,
                    );

typedef FcfTest::BasisTest::MinMaxSpecifierTest::Item Item;

FCF_FUNCTION_REGISTRATION(
                     fcf::random,
                     "random",
                     "cpu",
                     void(*) (Item*, Item*, const int&, const int&),
                     (
                       (fcf::CallOptions, 1, fcf::CallArgumentOptions<fcf::CAO_RESOLVE_POINTER|fcf::CAO_PAIR_ITERATION_POINTER|fcf::CAO_PAIR_SEGMENTATION>),
                       (fcf::MinMaxSpecifier, 1, Item*, Item*, fcf::Arg1, fcf::Arg2)
                     ),
                     false,
                    );

namespace FcfTest {
  namespace BasisTest {
    FCF_TEST_DECLARE("fcfBasis", "Specifier", "MinMaxSpecifier"){
      std::vector<FcfTest::BasisTest::MinMaxSpecifierTest::Item> vector(100);
      fcf::call("random", vector);
      for(Item& itm : vector){
        FCF_TEST(itm.value >= 1, itm.value);
        FCF_TEST(itm.value < 10, itm.value);
      }
    }
  } // BasisTest namespace
} // FcfTest namespace
