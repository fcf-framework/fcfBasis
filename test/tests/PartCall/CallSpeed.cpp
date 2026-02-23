#include <iostream>
#include <exception>
#include <chrono>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace fcf {
  template <typename ...TPackArg>
  void fill(TPackArg&&... a_packArg){
    static CallCache<TPackArg...> builder("fill", a_packArg...);
    builder.call(a_packArg...);
  }
} // fcf namespace

namespace FcfTest {
  namespace BasisTest {

    void callSpeedTest(){
      std::cout << "Start callSpeedTest()..." << std::endl;

      const size_t iterationCount = 10*1024*1024;


      // OLD DURTION: 120ns
      // 
      // REMOVE SKIP CONVERIONS: 100ns-109ns
      {
        int arr[10];
        std::fill(std::begin(arr), std::end(arr), 99);
        fcf::Variant v((int)10);

        fcf::Call dc;
        fcf::CallSeeker<void, int*, int*, int, const fcf::Variant>()("fill", &dc, (int*)0, (int*)0, v);

        fcf::NTest::Duration duration(iterationCount);
        duration.begin();
        for(size_t i = 0; i < duration.iterations(); ++i) {
          fcf::call(&dc, &arr[0], &arr[10], v);
        }
        duration.end();
        std::cout << "Duration: " << duration.duration().count() << "; total: " << duration.totalDuration().count() << "ns " << std::endl;
      }


      {
        std::vector<int> v = {1,2,3,4};
        fcf::NTest::Duration duration(iterationCount);
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
    }

  } // namespace BasisTest
} // namespace FcfTest

