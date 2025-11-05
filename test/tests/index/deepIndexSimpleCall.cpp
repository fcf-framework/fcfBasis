#include <iostream>
#include <chrono>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../call.hpp"
#include "../../../functions.hpp"
#include "../../../foreach.hpp"
#include "../../../bits/PartMetaType/MetaTypeTupleReplace.hpp"
#include "../../../bits/PartMetaType/MetaTypeTupleInsert.hpp"


bool enable_log = false;

void deepIndexContainerCaller(){
  std::cout << "Start deepIndexContainerCaller..." << std::endl;
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
}

void deepIndexNearestCaller(){
  std::cout << "Start deepIndexNearestCaller..." << std::endl;

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

void deepIndexSimpleCaller(){
  std::cout << "Start deepIndexSimpleCaller..." << std::endl;
  
  {
    bool except = false;
    try {
      fcf::Call dc;
      fcf::CallSeeker<void, int*, int*, int, bool>()("random", &dc);
    } catch(...) {
      except = true;
    }
    FCF_TEST(except == true);
  }
  {
    fcf::Call dc;
    fcf::CallSeeker<void, int*, int*, int, int>()("random", &dc);
    int arr[10];
    std::fill(std::begin(arr), std::end(arr), 99);
    fcf::call(&dc, &arr[0], &arr[10], 0, 10);
    for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
      FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
    }
  }
  {
    fcf::Variant variant((int)10);
    fcf::Call dc;
    fcf::CallSeeker<void, int*, int*, int, const fcf::Variant>()("random", &dc, (int*)0, (int*)0, (int)0, variant);
    int arr[10];
    std::fill(std::begin(arr), std::end(arr), 99);
    fcf::call(&dc, &arr[0], &arr[10], 0, variant);
    for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
      FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
    }
  }
  {
    fcf::Variant variant((int)10);
    fcf::Call dc;
    fcf::CallSeeker<void, int*, int*, int, const fcf::Variant&>()("random", &dc, (int*)0, (int*)0, (int)0, variant);
    int arr[10];
    std::fill(std::begin(arr), std::end(arr), 99);
    fcf::call(&dc, &arr[0], &arr[10], 0, variant);
    for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
      FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
    }
  }
  {
    int arr[10];
    std::fill(std::begin(arr), std::end(arr), 99);
    fcf::call("random", &arr[0], &arr[10], 0, 10);
    for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
      FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
    }
  }
  enable_log = true;
  std::cout <<  "Start test" << std::endl;
  {
    int arr[10];
    std::fill(std::begin(arr), std::end(arr), 99);
    fcf::Variant v((int)10);
    fcf::call("random", &arr[0], &arr[10], 0, v);
    for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
      FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
    }
  }
  enable_log = false;
  std::cout <<  "End test" << std::endl;

  //duration test
  {
    unsigned long long defaultSize = 16*1024;
    unsigned long long defaultSizeForDetect = defaultSize * 100;
    unsigned long long defaultDuration = 0;
    {
      int arr[10];
      std::fill(std::begin(arr), std::end(arr), 99);
      size_t size = defaultSizeForDetect;
      auto start = std::chrono::high_resolution_clock::now();
      for(size_t i = 0; i < size; ++i) {
        fcf::random(&arr[0], &arr[10], 0, 10);
      }
      auto end = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
      defaultDuration = duration / size;
      for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
        FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
      }
    }
    {
      int arr[10];
      std::fill(std::begin(arr), std::end(arr), 99);
      fcf::Variant v((int)10);

      size_t size = defaultSize;
      auto start = std::chrono::high_resolution_clock::now();
      for(size_t i = 0; i < size; ++i) {
        fcf::call("random", &arr[0], &arr[10], 0, 10);
      }
      auto end = std::chrono::high_resolution_clock::now();
      unsigned long long duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
      unsigned long long rduration = duration / size;
      rduration = rduration < defaultDuration ? 0 : rduration - defaultDuration;
      std::cout << "(int*, int*, int, int)     [Find, Call] : " << rduration << "nsec" << std::endl;

      for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
        FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
      }
    }
    {
      int arr[10];
      std::fill(std::begin(arr), std::end(arr), 99);
      fcf::Variant v((int)10);

      size_t size = defaultSize;
      auto start = std::chrono::high_resolution_clock::now();
      for(size_t i = 0; i < size; ++i) {
        fcf::call("random", &arr[0], &arr[10], 0, v);
      }
      auto end = std::chrono::high_resolution_clock::now();
      unsigned long long duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
      unsigned long long rduration = duration / size;
      rduration = rduration < defaultDuration ? 0 : rduration - defaultDuration;
      std::cout << "(int*, int*, int, variant) [Find, Call] : " << rduration << "nsec" << std::endl;

      for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
        FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
      }
    }

    {
      int arr[10];
      std::fill(std::begin(arr), std::end(arr), 99);
      fcf::Variant v((int)10);

      fcf::Call dc;
      fcf::CallSeeker<void, int*, int*, int, const fcf::Variant>()("random", &dc, (int*)0, (int*)0, (int)0, v);

      size_t size = defaultSize;
      auto start = std::chrono::high_resolution_clock::now();
      for(size_t i = 0; i < size; ++i) {
        fcf::call(&dc, &arr[0], &arr[10], 0, v);
      }
      auto end = std::chrono::high_resolution_clock::now();
      unsigned long long duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
      unsigned long long rduration = duration / size;
      rduration = rduration < defaultDuration ? 0 : rduration - defaultDuration;
      std::cout << "(int*, int*, int, variant) [Call]       : " << rduration << "nsec" << std::endl;
      for(size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
        FCF_TEST(arr[i] >= 0 && arr[i] <= 9, i, arr[i]);
      }
    }
  }


}


struct TupleTestFunc{
  std::string result;
  template <typename Tuple, typename TIndex, typename TValue>
  void operator()(Tuple& a_tuple, TIndex a_index, TValue& a_value){
    if (!result.empty()){
      result += "|";
    }
    result += fcf::Type<TValue>().name();
  }
};


void tupleTest() {
  std::cout << "Start tupleTest..." << std::endl;

  // insert test
  {
    typedef std::tuple<> ttype;
    typedef typename fcf::MetaTypeTupleInsert<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float", ttf.result);
  }
  {
    typedef std::tuple<char> ttype;
    typedef typename fcf::MetaTypeTupleInsert<ttype, float, 1>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|float", ttf.result);
  }
  {
    typedef std::tuple<char> ttype;
    typedef typename fcf::MetaTypeTupleInsert<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float|char", ttf.result);
  }
  {
    typedef std::tuple<char, short> ttype;
    typedef typename fcf::MetaTypeTupleInsert<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float|char|short", ttf.result);
  }
  {
    typedef std::tuple<char, short> ttype;
    typedef typename fcf::MetaTypeTupleInsert<ttype, float, 1>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|float|short", ttf.result);
  }
  {
    typedef std::tuple<char, short> ttype;
    typedef typename fcf::MetaTypeTupleInsert<ttype, float, 2>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|short|float", ttf.result);
  }

  // replace test
  {
    typedef std::tuple<char> ttype;
    typedef typename fcf::MetaTypeTupleReplace<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float", ttf.result)
  }
  {
    typedef std::tuple<char, short> ttype;
    typedef typename fcf::MetaTypeTupleReplace<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float|short", ttf.result)
  }
  {
    typedef std::tuple<char, short> ttype;
    typedef typename fcf::MetaTypeTupleReplace<ttype, float, 1>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|float", ttf.result)
  }

  {
    typedef std::tuple<char, short, int> ttype;
    typedef typename fcf::MetaTypeTupleReplace<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float|short|int", ttf.result)
  }
  {
    typedef std::tuple<char, short, int> ttype;
    typedef typename fcf::MetaTypeTupleReplace<ttype, float, 1>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|float|int", ttf.result)
  }
  {
    typedef std::tuple<char, short, int> ttype;
    typedef typename fcf::MetaTypeTupleReplace<ttype, float, 2>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|short|float", ttf.result)
  }
  {
    typedef std::tuple<char, short> ttype;
    typedef typename fcf::MetaTypeTupleReplace<ttype, float, 1>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|float", ttf.result)
  }
  {
    typedef std::tuple<char, short> ttype;
    typedef typename fcf::MetaTypeTupleReplace<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float|short", ttf.result)
  }
  {
    typedef std::tuple<char> ttype;
    typedef typename fcf::MetaTypeTupleReplace<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float", ttf.result)
  }
  
}


