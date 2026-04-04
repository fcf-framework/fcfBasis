#include <fcfBasis/basis.hpp>
#include <fcfTest/test.hpp>

std::string external_storage_concat2(std::string a_left, std::string a_right){
  return a_left + a_right;
}

FCF_TEST_DECLARE("fcfBasis", "Call", "external storage call"){
  fcf::CallStorage storage;
  storage.add("external_storage_concat", external_storage_concat2);
  fcf::Variant result = rcall(fcf::CallOptions(0, storage),  (const char*)"external_storage_concat", (const char*)"1", (const char*)"2");
  FCF_TEST(result == "12", result);
}
