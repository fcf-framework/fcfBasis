#include <fcfTest/test.hpp>
#include "../../basis.hpp"
#include <vector>

void deepIndexCallInner();
void deepIndexCall();
void variantTest();
void indexTypesTest();
void deepIndexCallCaller();
void deepIndexSimpleCaller();

int main(int a_argc, char* a_argv[]){
  deepIndexCallCaller();
  deepIndexCallInner();
  deepIndexCall();
  deepIndexSimpleCaller();
  variantTest();
  indexTypesTest();
  return 0;
}
