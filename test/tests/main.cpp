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

    void callInvariantArgumentsTest();
    void callQuietTest();
    void callResultTest();
    void callSpeedTest();
    void callIterationsTest();
    void callZeroIterationsTest();

    void exceptionTest();

    void arithmeticSpecificatorsTest();
    void minMaxSpecificatorTest();
    void foreachTest();
    void variantCmpTest();
    void variantAssignmentTest();
    void variantConstructorTest();
    void variantArithmeticTest();
    void variantPtrTest();
    void variantRefTest();
    void variantContainerTest();
    void variantConstTest();
    void variantEraseTest();

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



template <typename TClass, typename Ty, void (TClass::*Method)(Ty)>
struct Test{
};

int main(int /*a_argc*/, char* /*a_argv*/[]) {


  variantTest();

  FcfTest::BasisTest::callInvariantArgumentsTest();
  FcfTest::BasisTest::callQuietTest();
  FcfTest::BasisTest::callResultTest();
  FcfTest::BasisTest::callSpeedTest();
  FcfTest::BasisTest::callIterationsTest();
  FcfTest::BasisTest::callZeroIterationsTest();

  FcfTest::BasisTest::exceptionTest();

  FcfTest::BasisTest::foreachTest();
  FcfTest::BasisTest::variantConstTest();
  FcfTest::BasisTest::variantPtrTest();
  FcfTest::BasisTest::variantRefTest();
  FcfTest::BasisTest::variantConstructorTest();
  FcfTest::BasisTest::variantAssignmentTest();
  FcfTest::BasisTest::variantCmpTest();
  FcfTest::BasisTest::variantContainerTest();
  FcfTest::BasisTest::variantArithmeticTest();
  FcfTest::BasisTest::variantEraseTest();
  FcfTest::BasisTest::sequenceTest();

  FcfTest::BasisTest::arithmeticSpecificatorsTest();
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
