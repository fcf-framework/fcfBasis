#include <iostream>
#include <vector>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace FcfTest {
  namespace BasisTest {

    FCF_TEST_DECLARE("fcfBasis", "Variant", "erase variant"){
      {
        std::vector<int> vector = {1,2,3,4};
        fcf::Variant variant(vector);
        FCF_TEST(variant.containerSize() == 4, variant.containerSize());
        variant.erase(1);
        FCF_TEST(variant.containerSize() == 3, variant.containerSize());
        FCF_TEST(variant[0] == 1, variant[0]);
        FCF_TEST(variant[1] == 3, variant[1]);
        FCF_TEST(variant[2] == 4, variant[2]);

        fcf::Variant::iterator it =  ++variant.begin();
        fcf::Variant::iterator itEnd = variant.end();
        variant.erase(it, itEnd);
        FCF_TEST(variant.containerSize() == 1, variant.containerSize());
        FCF_TEST(variant[0] == 1, variant[0]);

        variant[variant.containerSize()] = 22;
        FCF_TEST(variant.containerSize() == 2, variant.containerSize());
        FCF_TEST(variant[0] == 1, variant[0]);
        FCF_TEST(variant[1] == 22, variant[1]);

        variant.erase(--variant.end(), variant.end());
        FCF_TEST(variant.containerSize() == 1, variant.containerSize());
        FCF_TEST(variant[0] == 1, variant[0]);

        variant[variant.containerSize()] = 33;
        FCF_TEST(variant.containerSize() == 2, variant.containerSize());
        FCF_TEST(variant[0] == 1, variant[0]);
        FCF_TEST(variant[1] == 33, variant[1]);

        variant.erase(--variant.end());
        FCF_TEST(variant.containerSize() == 1, variant.containerSize());
        FCF_TEST(variant[0] == 1, variant[0]);

        variant.erase(variant.begin());
        FCF_TEST(variant.containerSize() == 0, variant.containerSize());
      }
      {
        std::vector<int> vector = {1,2,3,4};
        fcf::Variant variant(vector, fcf::Variant::REFERENCE);
        FCF_TEST(variant.containerSize() == 4, variant.containerSize());
        variant.erase(1);
        FCF_TEST(vector.size() == 3, vector.size());
        FCF_TEST(variant.containerSize() == 3, variant.containerSize());
        FCF_TEST(variant[0] == 1, variant[0]);
        FCF_TEST(variant[1] == 3, variant[1]);
        FCF_TEST(variant[2] == 4, variant[2]);
        FCF_TEST(vector[0] == 1, vector[0]);
        FCF_TEST(vector[1] == 3, vector[1]);
        FCF_TEST(vector[2] == 4, vector[2]);


        fcf::Variant::iterator it =  ++variant.begin();
        fcf::Variant::iterator itEnd = variant.end();
        variant.erase(it, itEnd);
        FCF_TEST(variant.containerSize() == 1, variant.containerSize());
        FCF_TEST(variant[0] == 1, variant[0]);
        FCF_TEST(vector.size() == 1, vector.size());
        FCF_TEST(vector[0] == 1, vector[0]);

        variant[variant.containerSize()] = 22;
        FCF_TEST(variant.containerSize() == 2, variant.containerSize());
        FCF_TEST(variant[0] == 1, variant[0]);
        FCF_TEST(variant[1] == 22, variant[1]);
        FCF_TEST(vector.size() == 2, vector.size());
        FCF_TEST(vector[0] == 1, vector[0]);
        FCF_TEST(vector[1] == 22, vector[1]);

        variant.erase(--variant.end(), variant.end());
        FCF_TEST(variant.containerSize() == 1, variant.containerSize());
        FCF_TEST(variant[0] == 1, variant[0]);
        FCF_TEST(vector.size() == 1, vector.size());
        FCF_TEST(vector[0] == 1, vector[0]);

        variant[variant.containerSize()] = 33;
        FCF_TEST(variant.containerSize() == 2, variant.containerSize());
        FCF_TEST(vector.size() == 2, vector.size());
        FCF_TEST(variant[0] == 1, variant[0]);
        FCF_TEST(variant[1] == 33, variant[1]);
        FCF_TEST(vector[0] == 1, vector[0]);
        FCF_TEST(vector[1] == 33, vector[1]);

        variant.erase(--variant.end());
        FCF_TEST(variant.containerSize() == 1, variant.containerSize());
        FCF_TEST(vector.size() == 1, vector.size());
        FCF_TEST(variant[0] == 1, variant[0]);
        FCF_TEST(vector[0] == 1, vector[0]);

        variant.erase(variant.begin());
        FCF_TEST(variant.containerSize() == 0, variant.containerSize());
        FCF_TEST(vector.size() == 0, vector.size());

      }
    }

  }
}

