#include <iostream>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../call.hpp"
#include "../../../functions.hpp"

namespace FcfTest {
  namespace BasisTest {

    void placeHolderCall(){
      std::cout << "Start placeHolderCall()..." << std::endl;

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

    }

  } // BasisTest namespace
} // FcfTest namespace

