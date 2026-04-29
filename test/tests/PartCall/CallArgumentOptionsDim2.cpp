#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"
#include "../bits/functions.hpp"


namespace FcfTest {
  namespace CallArgumentOptionsDim2 {
    template <typename Ty, typename TyExpected>
    void test_fill(Ty& a_data, const TyExpected& a_expectedData){
      fcf::CallOptions co;
      fcf::CallArgument argumentOptions[1];

      argumentOptions[0].specificator   = fcf::Type<fcf::ValueSpecificator>().index();
      argumentOptions[0].argumentNumber = 1;
      argumentOptions[0].values         = 999;

      co.argumentOptions = argumentOptions;
      co.argumentOptionsCount = sizeof(argumentOptions) / sizeof(argumentOptions[0]);

      fcf::call(co, "fill", a_data);

      fcf::Variant                 evar(a_expectedData, fcf::Variant::REFERENCE);
      fcf::Variant::const_iterator eit(evar.cbegin());

      FCF_TEST(a_data.size() == a_expectedData.size(), a_data.size(), a_expectedData.size());

      for(const auto& item : a_expectedData){
        FCF_TEST(item.size() == eit.value().containerSize(), item.size(), eit.value().containerSize(), fcf::Type<Ty>().name());
        ++eit;
      }

    }
  }
}

FCF_TEST_DECLARE("fcfBasis", "Call", "argument options call (dim:2)"){

  {
    typedef std::vector<int>     VecType;
    typedef std::vector<VecType> MatType;
    MatType m = {
      {1,2,3},
      {4,5,6},
      {7,8,9}
    };
    MatType em = {
      {999,999,999},
      {999,999,999},
      {999,999,999}
    };
    FcfTest::CallArgumentOptionsDim2::test_fill(m, em);
  }
}
