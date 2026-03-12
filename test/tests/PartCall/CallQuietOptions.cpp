#include <iostream>
#include <exception>
#include <chrono>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace FcfTest {
  namespace BasisTest {
    namespace QuietTest {

      int sum(int* a_res, int* a_left, int* a_right){
        while(a_left != a_right){
          *a_res += *a_left;
          ++a_left;
        }
        return *a_res;
      }

      template <typename ... TPack>
      fcf::Variant sum(fcf::CallOptions& a_options, TPack&& ... a_pack){
        fcf::CallCache<TPack...> cc("QuietTest::sum", a_pack...);
        return cc.rcall(a_options, a_pack...);
      }

      template <typename ... TPack>
      fcf::Variant sum(TPack&& ... a_pack){
        fcf::CallCache<TPack...> cc("QuietTest::sum", a_pack...);
        return cc.rcall(a_pack...);
      }

    } // namespace QuietTest
  } // namespace BasisTest
} // namespace FcfTest

FCF_DECLARE_FUNCTION(
                     (QuietTest,sum),
                     "engine_cpu",
                     FcfTest::BasisTest::QuietTest::sum,
                     int (*) (int*, int*, int*),
                     (
                       (fcf::CallOptions, 2, fcf::CallArgumentOptions<fcf::CAO_PAIR_ITERATION_POINTER | fcf::CAO_PAIR_SEGMENTATION  | fcf::CAO_RESOLVE_POINTER | fcf::CAO_CONVERT_POINTER >),
                     ),
                    );


namespace FcfTest {
  namespace BasisTest {

    void callQuietTest(){
      std::cout << "Start callQuietTest()..." << std::endl;

      {
        bool error = false;
        try {
          int buffer = 0;
          fcf::Variant res = fcf::rcall("QuietTest::sum", (int*)&buffer, std::list<fcf::Variant>{1, 2.1, fcf::Nop(), "3", "4.1"});
        } catch(const std::exception&){
          error = true;
        }
        FCF_TEST(error);
      }
      for(size_t i= 0; i < 2; ++i) {
        bool error = false;
        try {
          int buffer = 0;
          fcf::Variant res = QuietTest::sum((int*)&buffer, std::list<fcf::Variant>{1, 2.1, fcf::Nop(), "3", "4.1"});
        } catch(const std::exception&){
          error = true;
        }
        FCF_TEST(error);
      }
      {
        bool error = false;
        try {
          int buffer = 0;
          fcf::CallOptions co;
          fcf::Variant res = fcf::rcall(co, "QuietTest::sum", (int*)&buffer, std::list<fcf::Variant>{1, 2.1, fcf::Nop(), "3", "4.1"});
        } catch(const std::exception&){
          error = true;
        }
        FCF_TEST(error);
      }
      for(size_t i= 0; i < 2; ++i){
        bool error = false;
        try {
          int buffer = 0;
          fcf::CallOptions co;
          fcf::Variant res = QuietTest::sum(co, (int*)&buffer, std::list<fcf::Variant>{1, 2.1, fcf::Nop(), "3", "4.1"});
        } catch(const std::exception&){
          error = true;
        }
        FCF_TEST(error);
      }
      {
        int buffer = 0;
        fcf::CallOptions co(fcf::CO_ITERATION_SELECT_QUIET);
        fcf::Variant res = fcf::rcall(co, "QuietTest::sum", (int*)&buffer, std::list<fcf::Variant>{fcf::Nop(), 1, 2.1, "3", "4.1"});
        FCF_TEST(buffer == 10, buffer);
        FCF_TEST(res == 10, res);
      }
      for(size_t i= 0; i < 2; ++i){
        int buffer = 0;
        fcf::CallOptions co(fcf::CO_ITERATION_SELECT_QUIET);
        fcf::Variant res = QuietTest::sum(co, (int*)&buffer, std::list<fcf::Variant>{fcf::Nop(), 1, 2.1, "3", "4.1"});
        FCF_TEST(buffer == 10, buffer);
        FCF_TEST(res == 10, res);
      }
      {
        int buffer = 0;
        fcf::Variant res = fcf::rcall(fcf::CallOptions(fcf::CO_ITERATION_SELECT_QUIET), "QuietTest::sum", (int*)&buffer, std::list<fcf::Variant>{1,fcf::Nop(), 2.1, "3", "4.1"});
        FCF_TEST(buffer == 10, buffer);
        FCF_TEST(res == 10, res);
      }
      for(size_t i= 0; i < 2; ++i){
        int buffer = 0;
        fcf::Variant res = QuietTest::sum(fcf::CallOptions(fcf::CO_ITERATION_SELECT_QUIET), (int*)&buffer, std::list<fcf::Variant>{1,fcf::Nop(), 2.1, "3", "4.1"});
        FCF_TEST(buffer == 10, buffer);
        FCF_TEST(res == 10, res);
      }
      {
        int buffer = 0;
        fcf::Variant res = fcf::rcall(fcf::CallOptions(fcf::CO_ITERATION_SELECT_QUIET), "QuietTest::sum", (int*)&buffer, std::list<fcf::Variant>{1, 2.1, "3", "4.1",fcf::Nop()});
        FCF_TEST(buffer == 10, buffer);
        FCF_TEST(res == 10, res);
      }
      for(size_t i= 0; i < 2; ++i){
        int buffer = 0;
        fcf::Variant res = QuietTest::sum(fcf::CallOptions(fcf::CO_ITERATION_SELECT_QUIET), (int*)&buffer, std::list<fcf::Variant>{1, 2.1, "3", "4.1",fcf::Nop()});
        FCF_TEST(buffer == 10, buffer);
        FCF_TEST(res == 10, res);
      }
      {
        bool error = false;
        try {
          int buffer = 0;
          fcf::CallOptions co(fcf::CO_ITERATION_SELECT_QUIET);
          fcf::Variant res = fcf::rcall(co, "QuietTest::sum", (int*)&buffer, 1, 1);
        } catch(const std::exception&){
          error = true;
        }
        FCF_TEST(error == true);
      }
      for(size_t i= 0; i < 2; ++i){
        bool error = false;
        try {
          int buffer = 0;
          fcf::CallOptions co(fcf::CO_ITERATION_SELECT_QUIET);
          fcf::Variant res = QuietTest::sum(co, (int*)&buffer, 1, 1);
        } catch(const std::exception&){
          error = true;
        }
        FCF_TEST(error == true);
      }


    }

  } // namespace BasisTest
} // namespace FcfTest

