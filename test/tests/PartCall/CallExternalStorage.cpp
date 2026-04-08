#include <fcfBasis/basis.hpp>
#include <fcfTest/test.hpp>

std::string external_storage_concat2(std::string a_left, std::string a_right){
  return a_left + a_right;
}

std::string external_storage_concat2(std::string* a_begin, std::string* a_end){
  std::string result;
  for(; a_begin != a_end; ++a_begin){
    result += *a_begin;
  }
  return result;
}


FCF_TEST_DECLARE("fcfBasis", "Call", "external storage call"){
  {
    fcf::CallStorage storage;
    storage.add("external_storage_concat", static_cast< std::string(*)(std::string, std::string) >(external_storage_concat2));
    fcf::Variant result = rcall(fcf::CallOptions(0, storage),  (const char*)"external_storage_concat", (const char*)"1", (const char*)"2");
    FCF_TEST(result == "12", result);
  }
}
