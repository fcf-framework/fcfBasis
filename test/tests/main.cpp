#include <fcfTest/test.hpp>
#include "../../basis.hpp"
#include <vector>

void deepIndexCallInner();
void deepIndexCall();
void variantTest();
void indexTypesTest();

int main(int a_argc, char* a_argv[]){
  deepIndexCallInner();
  deepIndexCall();
  variantTest();
  indexTypesTest();
  return 0;
}
