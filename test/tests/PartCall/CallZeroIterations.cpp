#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace FcfTest {
  namespace BasisTest {
    void callZeroIterationsTest(){
      std::cout << "Start callZeroIterationsTest()..." << std::endl;

      {
        std::vector<fcf::Variant> vector;
        fcf::call("fill",vector, 999.1);
      }
      {
        int* begin = 0;
        int* end   = 0;
        fcf::call("fill",begin, end, 999.1);
      }
      {
        int* begin = (int*)0xffffffff;
        int* end   = (int*)0xffffffff;
        fcf::call("fill",begin, end, 999.1);
      }
      {
        unsigned int* begin = 0;
        unsigned int* end   = 0;
        fcf::call("fill", begin, end, 999.1);
      }
      {
        std::vector<fcf::Variant> values;
        fcf::call("fill", values.begin().operator->(), values.end().operator->(), 999);
        FCF_TEST(values.size() == 0, values.size());
      }

    }
  }
}
