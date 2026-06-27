#include <iostream>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../PartCall.hpp"
#include "../bits/functions.hpp"
#include "../../../PartType.hpp"
#include "../../../bits/registry.hpp"
#include "../../../basis.hpp"

#include "../../../bits/PartCall/NDetails/CallWrapper.hpp"

namespace FcfTest {
  namespace BasisTest {

    struct PHCTestDataItem{
      int value;
      int defaultValue;
      PHCTestDataItem()
        : value(0)
        , defaultValue(999){
      }
      PHCTestDataItem& operator=(int a_value){
        value = a_value;
        return *this;
      }
    };
  }
}

namespace fcf {
  template <>
  struct Type<FcfTest::BasisTest::PHCTestDataItem, ValueSpecifier> : public TypeImpl<FcfTest::BasisTest::PHCTestDataItem, ValueSpecifier> {
    inline auto operator()(FcfTest::BasisTest::PHCTestDataItem* a_container) -> decltype(a_container->defaultValue) {
      return a_container->defaultValue;
    }
  };
}

FCF_TYPE_REGISTRATION_FORCE(std::vector<FcfTest::BasisTest::PHCTestDataItem>, "std::vector<FcfTest::BasisTest::PHCTestDataItem>", 0);
FCF_TYPE_REGISTRATION_FORCE(FcfTest::BasisTest::PHCTestDataItem, "FcfTest::BasisTest::PHCTestDataItem",                           0);
FCF_SPECIFIER_REGISTRATION_FORCE(FcfTest::BasisTest::PHCTestDataItem, fcf::ValueSpecifier);


FCF_FUNCTION_REGISTRATION(
                   fcf::fill,
                   "fill",
                   "cpu",
                   void(*) (FcfTest::BasisTest::PHCTestDataItem*, FcfTest::BasisTest::PHCTestDataItem*, int),
                   (
                    (fcf::CallOptions, 1, fcf::CallArgumentOptions<fcf::CAO_RESOLVE_POINTER|fcf::CAO_PAIR_ITERATION_POINTER|fcf::CAO_PAIR_SEGMENTATION>),
                    (fcf::ValueSpecifier, 1, FcfTest::BasisTest::PHCTestDataItem*, FcfTest::BasisTest::PHCTestDataItem*, fcf::Arg1)
                   ),
                   false,
                  );

namespace FcfTest {
  namespace BasisTest {

    void function_test_1(int* a_a1, int a_a2, short /*a_a3*/){
      *a_a1 = a_a2;
    }
    void function_test_2(int* a_a1, int /*a_a2*/, short a_a3){
      *a_a1 = (int)a_a3;
    }

    FCF_TEST_DECLARE("fcfBasis", "Call", "placeholder call"){

      {
        FcfTest::BasisTest::PHCTestDataItem obj;
        obj.defaultValue = 789;
        int value = fcf::Type<FcfTest::BasisTest::PHCTestDataItem, fcf::ValueSpecifier>().call(&obj);
        FCF_TEST(value == 789, value);
      }
      {
        typedef void (function_type)(int*, int, short);
        fcf::NDetails::CallWrapper<function_type> c;
        void* cpa[4];
        int   a1data = 0;
        int*  a1 = &a1data;
        int   a2 = 2;
        short a3 = 3;
        cpa[0] = &a1;
        cpa[1] = &a2;
        cpa[2] = &a3;
        c.call(function_test_1, &cpa[0]);
        FCF_TEST(a1data == a2, a1data, a2);
        c.call(function_test_2, &cpa[0]);
        FCF_TEST(a1data == a3, a1data, a3);


      }
      /*
      {
        size_t val  = 999;
        size_t size = 10;
        std::vector<int> v(size);
        fcf::call("fill", v, val);
        FCF_TEST(v.size() == size, size, v.size());
        for(size_t i = 0; i < size; ++i){
          FCF_TEST(v[i] == val, i, val, v[i]);
        }
      }
    */
      /*
      {
        int val  = 999;
        size_t size = 10;
        std::vector<PHCTestDataItem> v(size);
        fcf::call("fill", v, val);
        for(auto itm : v){
          FCF_TEST(itm.value == val, itm.value, val);
        }
      }
      */

      {
        size_t size = 10;
        std::vector<int> v(size);
        std::fill(v.begin(), v.end(), 10);
        fcf::call("fill", v, 11);
        for(auto itm : v){
          FCF_TEST(itm == 11, itm);
        }
      }

      {
        size_t size = 10;
        std::vector<PHCTestDataItem> v(size);
        fcf::call("fill", v);
        for(auto itm : v){
          FCF_TEST(itm.value == itm.defaultValue, itm.value, itm.defaultValue);
        }
      }


    }

  } // BasisTest namespace
} // FcfTest namespace

