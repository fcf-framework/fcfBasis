#include "../../../ArgPlaceHolder.hpp"

#include <iostream>

#include "../../libraries/fcfTest/test.hpp"
#include "../../../Nop.hpp"
#include "../../../Type.hpp"
#include "../../../FunctionSignature.hpp"
#include "../../../bits/PartCallStorage/CallStorage.hpp"

#include "../../../bits/functions/fill.hpp"
#include "../../../convert.hpp"

void deepIndexCall(){
  std::cout << "Start deepIndexCall..." << std::endl;
  /*
  {
    DeepIndexCallTest::Array array(10, 1, 10);
    fcf::AdaptCall adaptCall = fcf::InvariantCallSeeker< DeepIndexCallTest::Array >()("random");
  }
  {
    fcf::AdaptCall adaptCall = fcf::InvariantCallSeeker< std::vector<float> , const float&, const float&>()("random");
    std::vector<float> vector(10);
    float a1 = 1;
    float a2 = 10;
    fcf::InvariantAdaptCaller().call<std::vector<float>, const float&, const float&>(adaptCall, vector, a1, a2);
    for(int i = 0; i < vector.size(); ++i) {
      FCF_TEST(vector[i] >= 1 && vector[i] <= 10, i, vector[i]);
    }
  }
  */
  
  /*
  {
    fcf::AdaptCall adaptCall = fcf::InvariantCallSeeker< std::vector<float> , float, float>()("random");
    std::vector<float> vector(10);
    fcf::InvariantAdaptCaller()(adaptCall, vector, (float)1, (float)10);
    for(int i = 0; i < vector.size(); ++i) {
      FCF_TEST(vector[i] >= 1 && vector[i] <= 10, i, vector[i]);
    }
  }
  {
    fcf::AdaptCall adaptCall = fcf::InvariantCallSeeker< std::list<float> , float, float>()("random");
    std::list<float> list(10);
    fcf::InvariantAdaptCaller()(adaptCall, list, (float)1, (float)10);
    for(float& item : list) {
      FCF_TEST(item >= 1 && item <= 10, item);
    }
  }
  {
    typedef std::vector< std::vector<float> > container_type;
    fcf::AdaptCall adaptCall = fcf::InvariantCallSeeker< container_type , float, float>()("random");
    container_type container(5);
    for(auto& citm : container){
      citm.resize(5);
    }
    fcf::InvariantAdaptCaller()(adaptCall, container, (float)1, (float)10);
    for(auto& citem : container){
      for(auto& item : citem){
        FCF_TEST(item >= 1 && item <= 10, item);
      }
    }
  }
  */

}
