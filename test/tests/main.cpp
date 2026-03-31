#include <iostream>
#include <fcfTest/test.hpp>
#include "../../basis.hpp"
#include <fcfBasis/PartTypes.hpp>


FCF_TEST_GROUP_ORDER("Type", -12)
FCF_TEST_GROUP_ORDER("Exception", -11)
FCF_TEST_GROUP_ORDER("Foreach", -10)
FCF_TEST_GROUP_ORDER("MetaType", -9)
FCF_TEST_GROUP_ORDER("Specificator", -8)
FCF_TEST_GROUP_ORDER("Variant", -7)

int main(int a_argc, char* a_argv[]) {
  bool error = false;
  fcf::NTest::cmdRun(a_argc, (const char**)a_argv, fcf::NTest::CRM_RUN, &error); 
  return error ? 1 : 0;
}

