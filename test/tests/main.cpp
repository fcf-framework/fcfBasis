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


namespace NTest{
namespace {
  namespace {
    struct S{
    };
  }
}
}




#define SRINGIFY_3(a_var) #a_var
#define SRINGIFY_2(a_var) SRINGIFY_3(a_var)
#define SRINGIFY_1(a_var) SRINGIFY_2(a_var)
#define SRINGIFY_0(a_var) SRINGIFY_1(a_var)
#define SRINGIFY(a_var) SRINGIFY_0(a_var)

int main(int /*a_argc*/, char* /*a_argv*/[]) {
  {
    std::string s = SRINGIFY(FCF_TEMPLATE_TYPEID_DECLARE__DECLNAMESPACES((std,vector)) );
    std::cout << s << std::endl;

    s = SRINGIFY(FCF_TEMPLATE_TYPEID_DECLARE__DECLENDNAMESPACES((std,vector)) );
    std::cout << s << std::endl;

    s = SRINGIFY(FCF_TEMPLATE_TYPEID_DECLARE__NAMESPACES((std,vector)) );
    std::cout << s << std::endl;

    //return 0;
  }
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
  FcfTest::BasisTest::variantConstructorTest();
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
