#include <iostream>
#include <exception>
#include <chrono>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"


namespace FcfTest {
  namespace BasisTest {

    int sum(int a_left, int a_right){
      return a_left + a_right;
    }

    int sum(int* a_left, int* a_right){
      int res = 0;
      while(a_left != a_right){
        res += *a_left;
        ++a_left;
      }
      return res;
    }

    int sum(int* a_res, int* a_left, int* a_right){
      while(a_left != a_right){
        *a_res += *a_left;
        ++a_left;
      }
      return *a_res;
    }

  } // namespace BasisTest
} // namespace FcfTest

FCF_DECLARE_FUNCTION(
                     (fcftest,sum),
                     "engine_cpu",
                     FcfTest::BasisTest::sum,
                     int (*) (int, int),
                     (),
                    );

FCF_DECLARE_FUNCTION(
                     (fcftest,sum),
                     "engine_cpu",
                     FcfTest::BasisTest::sum,
                     int (*) (int*, int*),
                     (
                       (fcf::CallOptions, 1, fcf::CallArgumentOptions<fcf::CAO_PAIR_ITERATION_POINTER>),
                     ),
                    );

FCF_DECLARE_FUNCTION(
                     (fcftest,sum),
                     "engine_cpu",
                     FcfTest::BasisTest::sum,
                     int (*) (int*, int*, int*),
                     (
                       (fcf::CallOptions, 2, fcf::CallArgumentOptions<fcf::CAO_PAIR_ITERATION_POINTER | fcf::CAO_PAIR_SEGMENTATION  | fcf::CAO_RESOLVE_POINTER | fcf::CAO_CONVERT_POINTER >),
                     ),
                    );



namespace FcfTest {
  namespace BasisTest {


    void callResultTest(){
      std::cout << "Start callResultTest()..." << std::endl;

      {
        fcf::Variant res = fcf::rcall("fcftest::sum", 1, 2);
        FCF_TEST(res == 3, res);
      }
      {
        std::vector<int> v = {1,2,3,4};
        fcf::Variant res = fcf::rcall("fcftest::sum", v);
        FCF_TEST(res == 10, res);
      }
      {
        int buffer = 0;
        std::vector<fcf::Variant> v = {fcf::Variant(1), fcf::Variant(2), fcf::Variant(3), fcf::Variant(4)};
        fcf::Variant res = fcf::rcall("fcftest::sum", (int*)&buffer, v);
        FCF_TEST(res == 10, res);
      }
      {
        int buffer = 0;
        std::vector<fcf::Variant> v = {1, 2.1, "3", "4.1"};
        fcf::Variant res = fcf::rcall("fcftest::sum", (int*)&buffer, v);
        FCF_TEST(res == 10, res);
      }
      {
        int buffer = 0;
        std::list<fcf::Variant> v = {1, 2.1, "3", "4.1"};
        fcf::Variant res = fcf::rcall("fcftest::sum", (int*)&buffer, v);
        FCF_TEST(res == 10, res);
      }
      {
        int buffer = 0;
        fcf::Variant res = fcf::rcall("fcftest::sum", (int*)&buffer, std::list<fcf::Variant>{1, 2.1, "3", "4.1"});
        FCF_TEST(res == 10, res);
      }
      {
        int buffer = 0;
        std::list<fcf::Variant> v;
        fcf::Variant res = fcf::rcall("fcftest::sum", (int*)&buffer, v);
        FCF_TEST(res.empty());
      }
    }

  } // namespace BasisTest
} // namespace FcfTest

