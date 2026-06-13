#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"
#include "../bits/functions.hpp"

FCF_TEST_DECLARE("fcfBasis", "Call", "argument options call (dim:1)"){

  //
  //  Simple options tests for loop (dim: 1)
  //

  {
    fcf::CallOptions co;
    fcf::CallArgument argumentOptions[1];

    argumentOptions[0].specificator   = fcf::Type<fcf::ValueSpecificator>().index();
    argumentOptions[0].argumentNumber = 1;
    argumentOptions[0].values         = 999;

    co.argumentOptions = argumentOptions;
    co.argumentOptionsCount = sizeof(argumentOptions) / sizeof(argumentOptions[0]);

    std::vector<int> vec = {1,2,3,4,5};
    fcf::call(co, "fill", vec);
    for(size_t i = 0; i < vec.size(); ++i){
      FCF_TEST(vec[i] == 999, vec[i], i);
    }
  }

  {
    fcf::CallOptions co;
    fcf::CallArgument argumentOptions[1];

    argumentOptions[0].specificator   = fcf::Type<fcf::ValueSpecificator>().index();
    argumentOptions[0].argumentNumber = 1;
    argumentOptions[0].values         = 999;

    co.argumentOptions = argumentOptions;
    co.argumentOptionsCount = sizeof(argumentOptions) / sizeof(argumentOptions[0]);

    std::vector<fcf::Variant> vec = {1,2,3,4,5};
    fcf::call(co, "fill", vec);
    for(size_t i = 0; i < vec.size(); ++i){
      FCF_TEST(vec[i] == 999, vec[i], i);
    }
  }


  {
    fcf::CallOptions co;
    fcf::CallArgument argumentOptions[1];

    argumentOptions[0].specificator   = fcf::Type<fcf::ValueSpecificator>().index();
    argumentOptions[0].argumentNumber = 1;
    argumentOptions[0].values         = 999;

    co.argumentOptions = argumentOptions;
    co.argumentOptionsCount = sizeof(argumentOptions) / sizeof(argumentOptions[0]);

    fcf::Variant var;
    std::vector<fcf::Variant> vec = {1,2,3,4,5};
    var = vec;
    fcf::call(co, "fill", var);
    size_t c = 0;
    for(const fcf::Variant& item: var){
      FCF_TEST(item == 999, item);
      ++c;
    }
    FCF_TEST(c == 5, c);
  }

  {
    fcf::CallOptions co;
    fcf::CallArgument argumentOptions[1];

    argumentOptions[0].specificator   = fcf::Type<fcf::ValueSpecificator>().index();
    argumentOptions[0].argumentNumber = 1;
    argumentOptions[0].values         = 999;

    co.argumentOptions = argumentOptions;
    co.argumentOptionsCount = sizeof(argumentOptions) / sizeof(argumentOptions[0]);

    std::vector<fcf::Variant> vec = {1,2,3,4,5};
    fcf::Variant var(vec, fcf::Variant::REFERENCE);
    fcf::NTest::Duration duration(1000);
    duration([&var, &co](){
        fcf::call(co, "fill", var);
    });
    fcf::NTest::inf() << "  call fill(Variant(std::vector<Variant> = {1,2,3,4,5}))() [no cache]: " << duration.duration().count() << "ns"<< std::endl;
    for(size_t i = 0; i < vec.size(); ++i){
      FCF_TEST(vec[i] == 999, vec[i], i);
    }
    size_t c = 0;
    for(const fcf::Variant& item: var){
      FCF_TEST(item == 999, item);
      ++c;
    }
    FCF_TEST(c == 5, c);
  }
}
