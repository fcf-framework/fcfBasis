#include <iostream>
#include <fcfTest/test.hpp>
#include <fcfBasis/basis.hpp>
#include "../bits/functions.hpp"

namespace fcf {
  template <typename ...TPackArg>
  void fill(TPackArg&&... a_packArg){
    static CallCache<TPackArg...> builder("fill", a_packArg...);
    builder.call(a_packArg...);
  }
} // fcf namespace

namespace FcfTest {
  namespace Call {
    template <typename TType>
    void fill2LevelDeepCallTest(){
      TType m = {
        {9,9,9},
        {9,9,9},
        {9,9,9}
      };

      fcf::call("fill", m, 13579);
      size_t row = 0;
      for(auto& item : m){
        size_t col = 0;
        for(auto& subIitem : item){
          FCF_TEST(subIitem == 13579, subIitem);
          ++col;
        }
        ++row;
      }
    }
    template <typename TType>
    void fill2LevelCachedDeepCallTest(){
      TType m = {
        {9,9,9},
        {9,9,9},
        {9,9,9}
      };

      fcf::fill(m, 13579);
      size_t row = 0;
      for(auto& item : m){
        size_t col = 0;
        for(auto& subIitem : item){
          FCF_TEST(subIitem == 13579, subIitem);
          ++col;
        }
        ++row;
      }
    }
    template <typename TType>
    void fill2LevelCachedForDataDeepCallTest(TType& a_data){
      fcf::fill(a_data, 13579);
      size_t row = 0;
      for(auto& item : a_data){
        size_t col = 0;
        for(auto& subIitem : item){
          FCF_TEST(subIitem == 13579, subIitem);
          ++col;
        }
        ++row;
      }
    }

  }
}

FCF_TEST_DECLARE("fcfBasis", "Call", "deep call"){
  {
    typedef std::vector<int>   VecType;
    typedef std::list<VecType> MatType;
    FcfTest::Call::fill2LevelDeepCallTest<MatType>();
  }
  {
    typedef std::vector<int>     VecType;
    typedef std::vector<VecType> MatType;
    FcfTest::Call::fill2LevelDeepCallTest<MatType>();
  }
  {
    typedef std::list<int>       VecType;
    typedef std::vector<VecType> MatType;
    FcfTest::Call::fill2LevelDeepCallTest<MatType>();
  }
  {
    typedef std::list<int>       VecType;
    typedef std::list<VecType> MatType;
    FcfTest::Call::fill2LevelDeepCallTest<MatType>();
  }

  {
    typedef std::list<fcf::Variant> VecType;
    typedef std::list<VecType>      MatType;
    FcfTest::Call::fill2LevelDeepCallTest<MatType>();
  }

  {
    typedef std::list<fcf::Variant> VecType;
    typedef std::vector<VecType>    MatType;
    FcfTest::Call::fill2LevelDeepCallTest<MatType>();
  }

  {
    typedef std::vector<fcf::Variant> VecType;
    typedef std::vector<VecType>    MatType;
    FcfTest::Call::fill2LevelDeepCallTest<MatType>();
  }

  {
    typedef std::vector<fcf::Variant> VecType;
    typedef std::list<VecType>        MatType;
    FcfTest::Call::fill2LevelDeepCallTest<MatType>();
    FcfTest::Call::fill2LevelCachedDeepCallTest<MatType>();
    MatType m = {
      {9,9,9},
      {9,9,9},
      {9,9,9}
    };
    FcfTest::Call::fill2LevelCachedForDataDeepCallTest<MatType>(m);
    fcf::NTest::Duration banch(1000);
    banch([&m](){
      FcfTest::Call::fill2LevelCachedForDataDeepCallTest<MatType>(m);
    });
    fcf::NTest::inf() << "  Duration for " << fcf::Type<MatType>().name() << " 3x3: "<< banch.duration().count() << std::endl;
  }

  {
    typedef std::vector<int> VecType;
    typedef std::list<VecType>        MatType;
    MatType m = {
      {9,9,9},
      {9,9,9},
      {9,9,9}
    };
    FcfTest::Call::fill2LevelCachedForDataDeepCallTest<MatType>(m);
    fcf::NTest::Duration banch(1000);
    banch([&m](){
      FcfTest::Call::fill2LevelCachedForDataDeepCallTest<MatType>(m);
    });
    fcf::NTest::inf() << "  Duration for " << fcf::Type<MatType>().name() << " 3x3: " << banch.duration().count() << std::endl;
  }

}
