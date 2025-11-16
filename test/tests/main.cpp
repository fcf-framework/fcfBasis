#include <fcfTest/test.hpp>
#include "../../basis.hpp"
#include <vector>
#include <iostream>
namespace FcfTest {
  namespace BasisTest {

    void sequenceTest();

    void staticVectorTest();
    void staticVectorCopyTest();
    void staticVectorExceptionTest();
    void staticVectorIteratorTest();
    void staticVectorPushTest();
    void staticVectorNotReduce();
    void staticVectorInsertTest();
    void staticVectorEraseTest();

    void declareCall();
    void placeHolderCall();

    void minMaxSpecificatorTest();
    void foreachTest();
    void variantCmpTest();
    void variantArithmeticTest();

  } // BasisTest namespace
} // FcfTest namespace

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



int main(int /*a_argc*/, char* /*a_argv*/[]) {
  variantTest();
  FcfTest::BasisTest::foreachTest();
  FcfTest::BasisTest::variantCmpTest();
  FcfTest::BasisTest::variantArithmeticTest();
  FcfTest::BasisTest::sequenceTest();

  FcfTest::BasisTest::minMaxSpecificatorTest();

  FcfTest::BasisTest::staticVectorTest();
  FcfTest::BasisTest::staticVectorCopyTest();
  FcfTest::BasisTest::staticVectorExceptionTest();
  FcfTest::BasisTest::staticVectorIteratorTest();
  FcfTest::BasisTest::staticVectorPushTest();
  FcfTest::BasisTest::staticVectorNotReduce();
  FcfTest::BasisTest::staticVectorInsertTest();
  FcfTest::BasisTest::staticVectorEraseTest();

  FcfTest::BasisTest::declareCall();

  FcfTest::BasisTest::placeHolderCall();

  deepIndexCallCaller();
  deepIndexCallInner();
  deepIndexCall();
  deepIndexSimpleCaller();
  deepIndexNearestCaller();
  indexTypesTest();
  iteratorTest();
  dynamicIteratorTest();
  deepIndexContainerCaller();
  tupleTest();

  return 0;
}
