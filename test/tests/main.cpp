#include <fcfTest/test.hpp>
#include "../../basis.hpp"
#include <vector>

void staticVectorTest();
void staticVectorCopyTest();
void staticVectorPushTest();
void staticVectorIteratorTest();
void staticVectorExceptionTest();
void deepIndexCallInner();
void deepIndexCall();
void variantTest();
void indexTypesTest();
void deepIndexCallCaller();
void deepIndexSimpleCaller();
void deepIndexNearestCaller();
void iteratorTest();
void dynamicIteratorTest();
void deepIndexContainerCaller();
void tupleTest();

int main(int a_argc, char* a_argv[]){
  staticVectorTest();
  staticVectorCopyTest();
  staticVectorPushTest();
  staticVectorIteratorTest();
  staticVectorExceptionTest();
  return 0;
  deepIndexCallCaller();
  deepIndexCallInner();
  deepIndexCall();
  deepIndexSimpleCaller();
  deepIndexNearestCaller();
  variantTest();
  indexTypesTest();
  iteratorTest();
  dynamicIteratorTest();
  deepIndexContainerCaller();
  tupleTest();
  return 0;
}
