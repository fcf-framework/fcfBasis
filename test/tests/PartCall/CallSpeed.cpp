#include <iostream>
#include <exception>
#include <chrono>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace FcfTest {
  namespace BasisTest {

    void callSpeedTest(){
      std::cout << "Start callSpeedTest()..." << std::endl;
      std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;

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

        for(size_t i = 0; i < dc.conversions.size(); ++i){
          std::cout << "ITM: " << (int)dc.conversions[i].mode << std::endl;
        }

        fcf::NTest::Duration duration(iterationCount);
        duration.begin();
        for(size_t i = 0; i < duration.iterations(); ++i) {
          fcf::call(&dc, &arr[0], &arr[10], v);
        }
        duration.end();
        std::cout << "Duration: " << duration.duration().count() << "; total: " << duration.totalDuration().count() << "ns " << std::endl;
      }
    }

  } // namespace BasisTest
} // namespace FcfTest

