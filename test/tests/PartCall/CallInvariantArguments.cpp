#include <iostream>
#include <exception>
#include <chrono>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace fcf {
  template <typename ...TPackArg>
  void fill(TPackArg&&... a_packArg){
    static CallCache<TPackArg...> builder("fill", a_packArg...);
    builder(a_packArg...);
  }
} // fcf namespace

//void filling(int* a_begin, int* a_end, int a_value);

namespace FcfTest {
  namespace BasisTest {

    void callInvariantArgumentsTest (){
      std::cout << "Start callInvariantArgumentsTest()..." << std::endl;

      //unsigned long long iterations = 1000000;
      unsigned long long iterations = 10000;
      {
        std::vector<unsigned int> v = {1,2,3,4};
        fcf::fill(&v[0], &v[v.size()], 999.1);
        FCF_TEST(v.size() == 4, v.size());
        FCF_TEST(v[0] == 999, v[0]);
        FCF_TEST(v[1] == 999, v[1]);
        FCF_TEST(v[2] == 999, v[2]);
        FCF_TEST(v[3] == 999, v[3]);
      }
      {
        unsigned int value = 1;
        unsigned int* pvalue1 = &value;
        int* pvalue2 = 0;
        fcf::convertRuntimeByDestination(&pvalue2, &pvalue1, fcf::Type<unsigned int*>().index());
        FCF_TEST((void*)pvalue1 == (void*)pvalue2, pvalue1, pvalue2);
      }

      {
        std::vector<unsigned int> v = {1,2,3,4};
        fcf::fill(v, 999.1);
        FCF_TEST(v.size() == 4, v.size());
        FCF_TEST(v[0] == 999, v[0]);
        FCF_TEST(v[1] == 999, v[1]);
        FCF_TEST(v[2] == 999, v[2]);
        FCF_TEST(v[3] == 999, v[3]);
      }

      {
        std::vector<int> v = {1,2,3,4};
        fcf::fill(v, 999.1);
        FCF_TEST(v.size() == 4, v.size());
        FCF_TEST(v[0] == 999, v[0]);
        FCF_TEST(v[1] == 999, v[1]);
        FCF_TEST(v[2] == 999, v[2]);
        FCF_TEST(v[3] == 999, v[3]);
      }
      {
        std::vector<int> v = {1,2,3,4};
        fcf::Variant variant(v, fcf::Variant::REFERENCE);
        fcf::fill(variant, 999.1);
        FCF_TEST(v.size() == 4, v.size());
        FCF_TEST(v[0] == 999, v[0]);
        FCF_TEST(v[1] == 999, v[1]);
        FCF_TEST(v[2] == 999, v[2]);
        FCF_TEST(v[3] == 999, v[3]);
      }
      {
        std::vector<int> v = {1,2,3,4};
        fcf::NTest::Duration duration(iterations);
        duration.begin();
        for(size_t i = 0; i < duration.iterations(); ++i) {
          fcf::fill(v, 999);
        }
        duration.end();
        std::cout << "Duration: " << duration.duration().count() << "; total: " << duration.totalDuration().count() << "ns " << std::endl;
        FCF_TEST(v.size() == 4, v.size());
        FCF_TEST(v[0] == 999, v[0]);
        FCF_TEST(v[1] == 999, v[1]);
        FCF_TEST(v[2] == 999, v[2]);
        FCF_TEST(v[3] == 999, v[3]);
      }
      {
        std::vector<int> v = {1,2,3,4};
        fcf::Variant variant(v, fcf::Variant::REFERENCE);
        fcf::fill(variant, 999.1);

        fcf::NTest::Duration duration(iterations);
        duration([&variant](){
          fcf::fill(variant, 999.1);
        });
        std::cout << "Duration: " << duration.duration().count() << "; total: " << duration.totalDuration().count() << "ns " << std::endl;

        fcf::fill(variant, 999.1);
        FCF_TEST(v.size() == 4, v.size());
        FCF_TEST(v[0] == 999, v[0]);
        FCF_TEST(v[1] == 999, v[1]);
        FCF_TEST(v[2] == 999, v[2]);
        FCF_TEST(v[3] == 999, v[3]);
      }

      {
        std::vector<int> v = {1,2,3,4};
        fcf::Variant variant(v, fcf::Variant::REFERENCE);

        fcf::NTest::Duration duration(iterations);
        duration.begin();
          for(size_t i = 0; i < duration.iterations(); ++i) {
            fcf::fill(variant, 999.1);
          }
        duration.end();
        std::cout << "Duration: " << duration.duration().count() << "; total: " << duration.totalDuration().count() << "ns " << std::endl;

        fcf::fill(variant, 999.1);
        FCF_TEST(v.size() == 4, v.size());
        FCF_TEST(v[0] == 999, v[0]);
        FCF_TEST(v[1] == 999, v[1]);
        FCF_TEST(v[2] == 999, v[2]);
        FCF_TEST(v[3] == 999, v[3]);
      }

      {
        std::vector<fcf::Variant> vector = {(int)1,2,3,4};
        fcf::NTest::Duration duration(iterations);
        duration.begin();
          for(size_t i = 0; i < duration.iterations(); ++i) {
            fcf::call("fill",vector, (int)999);
            FCF_TEST(vector[0] == 999, vector[0]);
            FCF_TEST(vector[1] == 999, vector[1]);
            FCF_TEST(vector[2] == 999, vector[2]);
            FCF_TEST(vector[3] == 999, vector[3]);
          }
        duration.end();
        std::cout << "Duration: " << duration.duration().count() << "; total: " << duration.totalDuration().count() << "ns " << std::endl;
      }
      {
        std::vector<fcf::Variant> vector = {(int)1,2,3,4};
        fcf::NTest::Duration duration(iterations);
        duration.begin();
          for(size_t i = 0; i < duration.iterations(); ++i) {
            fcf::fill(vector, (int)999);
            FCF_TEST(vector[0] == 999, vector[0]);
            FCF_TEST(vector[1] == 999, vector[1]);
            FCF_TEST(vector[2] == 999, vector[2]);
            FCF_TEST(vector[3] == 999, vector[3]);
          }
        duration.end();
        std::cout << "Duration: " << duration.duration().count() << "; total: " << duration.totalDuration().count() << "ns std::vector<fcf::Variant>[4]" << std::endl;
      }
      {
        std::vector<fcf::Variant> vector = {(int)1,2,3,4};
        fcf::NTest::Duration duration(iterations);
        duration.begin();
          for(size_t i = 0; i < duration.iterations(); ++i) {
            fcf::fill(vector, (int)999);
            FCF_TEST(vector[0] == 999, vector[0]);
            FCF_TEST(vector[1] == 999, vector[1]);
            FCF_TEST(vector[2] == 999, vector[2]);
            FCF_TEST(vector[3] == 999, vector[3]);
          }
        duration.end();
        std::cout << "Duration: " << duration.duration().count() << "; total: " << duration.totalDuration().count() << "ns std::vector<fcf::Variant>[4]" << std::endl;
      }
      {
        std::vector<fcf::Variant> vector = {(int)1,2,3,4};
        fcf::NTest::Duration duration(iterations);
        duration.begin();
          for(size_t i = 0; i < duration.iterations(); ++i) {
            fcf::fill(vector, (int)999);
            FCF_TEST(vector[0] == 999, vector[0]);
            FCF_TEST(vector[1] == 999, vector[1]);
            FCF_TEST(vector[2] == 999, vector[2]);
            FCF_TEST(vector[3] == 999, vector[3]);
          }
        duration.end();
        std::cout << "Duration: " << duration.duration().count() << "; total: " << duration.totalDuration().count() << "ns std::vector<fcf::Variant>[4]" << std::endl;
      }
      {
        std::vector<fcf::Variant> vector = {(int)1,2,3,4};
        fcf::NTest::Duration duration(iterations);
        duration.begin();
          for(size_t i = 0; i < duration.iterations(); ++i) {
            fcf::fill(vector, (int)999);
            FCF_TEST(vector[0] == 999, vector[0]);
            FCF_TEST(vector[1] == 999, vector[1]);
            FCF_TEST(vector[2] == 999, vector[2]);
            FCF_TEST(vector[3] == 999, vector[3]);
          }
        duration.end();
        std::cout << "Duration: " << duration.duration().count() << "; total: " << duration.totalDuration().count() << "ns std::vector<fcf::Variant>[4]" << std::endl;
      }

      /*
      {
        unsigned int* begin = 0;
        unsigned int* end   = 0;
        fcf::call("fill",begin, end, 999.1);
      }
      */


      {
        std::vector<fcf::Variant> vector = {(int)1,2,3,4};
        fcf::NTest::Duration duration(iterations);
        duration.begin();
          for(size_t i = 0; i < duration.iterations(); ++i) {
            fcf::call("fill",vector, 999.1);
          }
        duration.end();
        std::cout << "Duration: " << duration.duration().count() << "; total: " << duration.totalDuration().count() << "ns " << std::endl;
      }

      {
        std::vector<int> values({1,2,3});
        fcf::call("fill", (unsigned int*)values.begin().operator->(), (unsigned int*)values.end().operator->(), 999);
        FCF_TEST(values.size() == 3, values.size());
        for(int& val : values){
          FCF_TEST(val == 999, val);
        }
      }
      {
        std::vector<int> values({1,2,3});
        fcf::fill((unsigned int*)values.begin().operator->(), (unsigned int*)values.end().operator->(), 999);
        FCF_TEST(values.size() == 3, values.size());
        for(int& val : values){
          FCF_TEST(val == 999, val);
        }
      }
      {
        std::vector<int> values({1,2,3});
        fcf::call("fill", values.begin().operator->(), values.end().operator->(), 999);
        FCF_TEST(values.size() == 3, values.size());
        for(int& val : values){
          FCF_TEST(val == 999, val);
        }
      }
      {
        std::vector<fcf::Variant> values({1,1,1});
        fcf::call("fill", values.begin().operator->(), values.end().operator->(), 999);
        FCF_TEST(values.size() == 3, values.size());
        for(fcf::Variant& val : values){
          FCF_TEST(val == 999, val);
        }
      }
      {
        std::vector<fcf::Variant> values({1,1,1});
        fcf::fill(values, 999);
        FCF_TEST(values.size() == 3, values.size());
        for(fcf::Variant& val : values){
          FCF_TEST(val == 999, val);
        }
      }
      {
        std::vector<fcf::Variant> values({1,1,1});
        fcf::fill(values, 999);
        FCF_TEST(values.size() == 3, values.size());
        for(fcf::Variant& val : values){
          FCF_TEST(val == 999, val);
        }
      }
    } // void callInvariantArgumentsTest() end

  }
}
