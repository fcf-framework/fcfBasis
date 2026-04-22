#include <iostream>
#include <fcfTest/test.hpp>
#include <fcfBasis/basis.hpp>
#include "../bits/functions.hpp"

FCF_TEST_DECLARE("fcfBasis", "Call", "deep call"){
  {
    typedef std::vector<int>   VecType;
    typedef std::list<VecType> MatType;

    MatType m = {
      {9,9,9},
      {9,9,9},
      {9,9,9}
    };

    fcf::call("fill", m, 0);
    size_t row = 0;
    for(auto& item : m){
      size_t col = 0;
      for(auto& subIitem : item){
        FCF_TEST(subIitem == 0, subIitem, col, row);
        ++col;
      }
      ++row;
    }
  }
  {
    typedef std::vector<int>     VecType;
    typedef std::vector<VecType> MatType;

    MatType m = {
      {9,9,9},
      {9,9,9},
      {9,9,9}
    };

    fcf::call("fill", m, 0);
    size_t row = 0;
    for(auto& item : m){
      size_t col = 0;
      for(auto& subIitem : item){
        FCF_TEST(subIitem == 0, subIitem);
        ++col;
      }
      ++row;
    }
  }
  {
    typedef std::list<int>       VecType;
    typedef std::vector<VecType> MatType;

    MatType m = {
      {9,9,9},
      {9,9,9},
      {9,9,9}
    };

    fcf::call("fill", m, 0);
    size_t row = 0;
    for(auto& item : m){
      size_t col = 0;
      for(auto& subIitem : item){
        FCF_TEST(subIitem == 0, subIitem);
        ++col;
      }
      ++row;
    }
  }

}
