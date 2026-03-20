#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace FcfTest {
  namespace BasisTest {

    FCF_TEST_DECLARE("fcfBasis", "Variant", "pointer variant"){
      {
        int i = 1;
        fcf::Variant v;
        v = &i;
        FCF_TEST(v.get<int*>() == &i);
        FCF_TEST(*v.get<int*>() == i);
      }
    }

  }
}

