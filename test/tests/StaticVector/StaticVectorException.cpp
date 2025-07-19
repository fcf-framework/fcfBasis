#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../StaticVector.hpp"


namespace FcfTest {
  namespace BasisTest {

    namespace StaticVectorExceptionTest{
      int g_initCounter = 0;
      int g_exceptValue = 0;

      class Item{
        public:
          Item()
            : value(9999) {
            ++g_initCounter;
            if (g_initCounter == g_exceptValue){
              throw std::runtime_error("Test Error");
            }
          }

          Item(int a_value, bool a_ignoreExcept = false)
            : value(9999) {
            ++g_initCounter;
            if (!a_ignoreExcept && g_initCounter == g_exceptValue){
              throw std::runtime_error("Test Error");
            }
          }

          Item(const Item& a_source)
            : value(a_source.value) {
            ++g_initCounter;
            if (g_initCounter == g_exceptValue){
              throw std::runtime_error("Test Error");
            }
          }

          ~Item(){
          }

          int value;
      };
    } // StaticVectorExceptionTest namespace

    void staticVectorExceptionTest(){
      std::cout << "Start staticVectorExceptionTest()..." << std::endl;
      {
        typedef fcf::StaticVector<StaticVectorExceptionTest::Item, 2, 0, 2, 2, 0, 0> static_vector_type;
        StaticVectorExceptionTest::g_exceptValue = 2;
        StaticVectorExceptionTest::g_initCounter = 0;
        try {
          static_vector_type v(3);
        } catch(std::runtime_error&){
        }
      }
      {
        typedef fcf::StaticVector<StaticVectorExceptionTest::Item, 8, 0, 2, 1, 0, 0> static_vector_type;
        StaticVectorExceptionTest::g_exceptValue = 0;
        StaticVectorExceptionTest::g_initCounter = 0;
        static_vector_type v1(4);
        v1[0].value = 1;
        v1[1].value = 2;
        v1[2].value = 3;
        v1[3].value = 4;
        static_vector_type v2(4);
        v2[0].value = 10;
        v2[1].value = 20;
        v2[2].value = 30;
        v2[3].value = 40;
        StaticVectorExceptionTest::g_exceptValue = 3;
        StaticVectorExceptionTest::g_initCounter = 0;
        try {
          v2 = v1;
        } catch(std::runtime_error&){
        }
        FCF_TEST(v2.size() == 2, v2.size());
        FCF_TEST(v2.capacity() == 8, v2.capacity());
        FCF_TEST(v2[0].value == 1, v2[0].value);
        FCF_TEST(v2[1].value == 2, v2[1].value);
      }

      {
        typedef fcf::StaticVector<StaticVectorExceptionTest::Item, 2, 0, 2, 1, 0, 0> static_vector_type;
        StaticVectorExceptionTest::g_exceptValue = 0;
        StaticVectorExceptionTest::g_initCounter = 0;
        static_vector_type v1(4);
        v1[0].value = 1;
        v1[1].value = 2;
        v1[2].value = 3;
        v1[3].value = 4;
        static_vector_type v2(4);
        v2[0].value = 10;
        v2[1].value = 20;
        v2[2].value = 30;
        v2[3].value = 40;
        FCF_TEST(v2.capacity() == 4, v2.capacity());
        StaticVectorExceptionTest::g_exceptValue = 3;
        StaticVectorExceptionTest::g_initCounter = 0;
        try {
          v2 = v1;
        } catch(std::runtime_error&){
        }
        FCF_TEST(v2.size() == 2, v2.size());
        FCF_TEST(v2.capacity() == 4, v2.capacity());
        FCF_TEST(v2[0].value == 1, v2[0].value);
        FCF_TEST(v2[1].value == 2, v2[1].value);
      }

      {
        typedef fcf::StaticVector<StaticVectorExceptionTest::Item, 2, 0, 2, 1, 0, 0> static_vector_type;
        StaticVectorExceptionTest::g_exceptValue = 0;
        StaticVectorExceptionTest::g_initCounter = 0;
        static_vector_type v1(4);
        v1[0].value = 1;
        v1[1].value = 2;
        v1[2].value = 3;
        v1[3].value = 4;
        StaticVectorExceptionTest::g_exceptValue = 4;
        StaticVectorExceptionTest::g_initCounter = 0;
        try {
          v1.push_back({5, true});
        } catch(std::runtime_error&){
        }
        FCF_TEST(v1.size() == 4, v1.size());
        FCF_TEST(v1.capacity() == 4, v1.capacity());
        FCF_TEST(v1[0].value == 1, v1[0].value);
        FCF_TEST(v1[1].value == 2, v1[1].value);
      }
      {
        typedef fcf::StaticVector<StaticVectorExceptionTest::Item, 2, 0, 2, 1, 0, 0> static_vector_type;
        StaticVectorExceptionTest::g_exceptValue = 0;
        StaticVectorExceptionTest::g_initCounter = 0;
        static_vector_type v1(4);
        v1[0].value = 1;
        v1[1].value = 2;
        v1[2].value = 3;
        v1[3].value = 4;
        StaticVectorExceptionTest::g_exceptValue = 5;
        StaticVectorExceptionTest::g_initCounter = 0;
        try {
          v1.resize(10);
        } catch(std::runtime_error&){
        }
        FCF_TEST(v1.size() == 4, v1.size());
        FCF_TEST(v1.capacity() == 4, v1.capacity());
        FCF_TEST(v1[0].value == 1, v1[0].value);
        FCF_TEST(v1[1].value == 2, v1[1].value);
        FCF_TEST(v1[2].value == 3, v1[2].value);
        FCF_TEST(v1[3].value == 4, v1[3].value);
      }


      {
        typedef fcf::StaticVector<StaticVectorExceptionTest::Item, 2, 0, 2, 1, 0, 0> static_vector_type;
        StaticVectorExceptionTest::g_exceptValue = 0;
        StaticVectorExceptionTest::g_initCounter = 0;
        static_vector_type v1(6);
        v1[0].value = 1;
        v1[1].value = 2;
        v1[2].value = 3;
        v1[3].value = 4;
        v1[4].value = 5;
        v1[5].value = 6;
        StaticVectorExceptionTest::g_exceptValue = 3;
        StaticVectorExceptionTest::g_initCounter = 0;
        try {
          v1.resize(4);
        } catch(std::runtime_error&){
        }
        FCF_TEST(v1.size() == 6, v1.size());
        FCF_TEST(v1.capacity() == 6, v1.capacity());
        FCF_TEST(v1[0].value == 1, v1[0].value);
        FCF_TEST(v1[1].value == 2, v1[1].value);
        FCF_TEST(v1[2].value == 3, v1[2].value);
        FCF_TEST(v1[3].value == 4, v1[3].value);
        FCF_TEST(v1[4].value == 5, v1[4].value);
        FCF_TEST(v1[5].value == 6, v1[5].value);
      }

    }

  } // BasisTest namespace
} // FcfTest namespace


