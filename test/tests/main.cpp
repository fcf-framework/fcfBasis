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
    void variantConstructorTest();
    void variantArithmeticTest();
    void variantPtrTest();
    void variantRefTest();
    void variantContainerTest();

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
  /*
  {
    std::map<int, int> m;
    m[1] = 1;
    std::cout << m[1] << std::endl;
    auto res = m.insert(std::pair<int, int>(1,2));
    std::cout << m[1] << "|"<< res.second << std::endl;
    res = m.insert(std::pair<int, int>(2,2));
    std::cout << m[2] << "|"<< res.second << std::endl;
    return 0;
  }
  */
  variantTest();
  FcfTest::BasisTest::foreachTest();
  FcfTest::BasisTest::variantPtrTest();
  FcfTest::BasisTest::variantRefTest();
  FcfTest::BasisTest::variantConstructorTest();
  FcfTest::BasisTest::variantCmpTest();
  FcfTest::BasisTest::variantContainerTest();
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
