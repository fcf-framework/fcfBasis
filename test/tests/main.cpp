#include <fcfTest/test.hpp>
#include "../../basis.hpp"
#include <vector>

void deepIndexCallInner();
void deepIndexCall();
void variantTest();
void indexTypesTest();
void deepIndexCallCaller();
void deepIndexSimpleCaller();
void deepIndexNearestCaller();
void iteratorTest();
void dynamicIteratorTest();

int main(int a_argc, char* a_argv[]){
  deepIndexCallCaller();
  deepIndexCallInner();
  deepIndexCall();
  deepIndexSimpleCaller();
  deepIndexNearestCaller();
  variantTest();
  indexTypesTest();
  iteratorTest();
  dynamicIteratorTest();
  return 0;
}
