#include <iostream>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace fcf {

  template <unsigned int ...ValuesPack>
  class UniversalCallSignatureResultIndexes{
  };

  template <typename TResult, typename ...TArgPack>
  class UniversalCallSignature;

  template <typename TResult, typename ...TArgPack>
  class UniversalCallSignature<TResult(*)(TArgPack...)> {
  };
}


void universalCallTestCall(int){
}

FCF_TEST_DECLARE("fcfBasis", "Types", "UniversalCall"){
  //typedef decltype(&universalCallTestCall) UniversalCallTestCallType;

  //fcf::UniversalCallSignature<UniversalCallTestCallType> ucs;
}
