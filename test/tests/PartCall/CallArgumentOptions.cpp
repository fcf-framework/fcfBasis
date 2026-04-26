#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"
#include "../bits/functions.hpp"

FCF_TEST_DECLARE("fcfBasis", "Call", "argument options call"){
  {
    fcf::CallOptions co;
    fcf::CallArgument argumentOptions[1];

    argumentOptions[0].specificator   = fcf::Type<fcf::ValueSpecificator>().index();
    argumentOptions[0].argumentNumber = 1;
    argumentOptions[0].value          = 999;

    co.argumentOptions = argumentOptions;
    co.argumentOptionsCount = sizeof(argumentOptions) / sizeof(argumentOptions[0]);

    std::vector<int> vec = {1,2,3,4,5};
    fcf::call(co, "fill", vec);

  }
}
