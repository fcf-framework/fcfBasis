#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

FCF_TEST_DECLARE("fcfBasis", "Call", "call"){
  {
    std::vector<int> vec(10);
    std::fill(std::begin(vec), std::end(vec), 99);
    fcf::Call dc;
    fcf::CallSeeker<void, std::vector<int>, int, int>()("random", &dc, vec, (int)0, (int)0);
    fcf::call(&dc, vec, (int)0, (int)10);
    for(size_t i = 0; i < vec.size(); ++i){
      FCF_TEST((vec[i] >= 0 && vec[i] <= 9), i, vec[i]);
    }
  }
  {
    int arr[10];
    std::fill(std::begin(arr), std::end(arr), 99);
    fcf::Variant v((short)10);
    fcf::call("random", &arr[0], &arr[10], 0, v);
    for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
      FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
    }
  }
  {
    int arr[10];
    std::fill(std::begin(arr), std::end(arr), 99);
    fcf::Variant v((long long)10);
    fcf::call("random", &arr[0], &arr[10], 0, v);
    for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
      FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
    }
  }
  {
    int arr[10];
    std::fill(std::begin(arr), std::end(arr), 99);
    fcf::Variant v(std::string("10"));
    fcf::call("random", &arr[0], &arr[10], 0, v);
    for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
      FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
    }
  }
  {
    int arr[10];
    std::fill(std::begin(arr), std::end(arr), 99);
    fcf::Variant v(std::string("10"));
    fcf::Call dc;
    fcf::CallSeeker<void, int*, int*, int, fcf::Variant>()("random", &dc);
    fcf::call(&dc, &arr[0], &arr[10], 0, v);
    for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
      FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
    }
  }

}

