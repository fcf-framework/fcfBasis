#include <iostream>
#include <exception>
#include <set>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../PartStaticVector.hpp"


namespace FcfTest {
  namespace BasisTest {

    int g_staticVectorTestInitCounter = 0;
    std::set<void*> g_staticVectorTestItem_set;

    struct StaticVectorTestItem {
      StaticVectorTestItem()
      : ptr(0)
      , state(9999){
        ++g_staticVectorTestInitCounter;
        if (g_staticVectorTestItem_set.find(this) != g_staticVectorTestItem_set.end()){
          throw std::runtime_error("Invalid test");
        }
        g_staticVectorTestItem_set.insert(this);
      }

      StaticVectorTestItem(const StaticVectorTestItem& a_source)
      : ptr(a_source.ptr)
      , state(a_source.state){
        ++g_staticVectorTestInitCounter;
        if (g_staticVectorTestItem_set.find(this) != g_staticVectorTestItem_set.end()){
          throw std::runtime_error("Invalid test");
        }
        g_staticVectorTestItem_set.insert(this);
      }

      ~StaticVectorTestItem(){
        if (ptr) {
          ++(*ptr);
        }
        g_staticVectorTestItem_set.erase(this);
      }
      int* ptr;
      int  state;
    };

    void staticVectorTest();

    FCF_TEST_DECLARE("fcfBasis", "StaticVector", "StaticVector"){
      staticVectorTest();
    }

    void staticVectorTest(){
      {
        typedef fcf::StaticVector<int, 2, 0, 1, 1, 0, 0> static_vector_type;
        static_vector_type v = {1};
        FCF_TEST(v.capacity() == 2);
        FCF_TEST(v.size() == 1);
        v.push_back(2);
        FCF_TEST(v.capacity() == 2);
        FCF_TEST(v.size() == 2);
        v.push_back(3);
        FCF_TEST(v.capacity() == 3);
        FCF_TEST(v.size() == 3);
        v.push_back(4);
        FCF_TEST(v.capacity() == 4);
        FCF_TEST(v.size() == 4);
        v.pop_back();
        FCF_TEST(v.capacity() == 3);
        FCF_TEST(v.size() == 3);
      }

      {
        typedef fcf::StaticVector<int, 2> static_vector_type;
        static_vector_type v = {1};
        FCF_TEST(v.capacity() == 2);
        FCF_TEST(v.size() == 1);
        v.push_back(2);
        FCF_TEST(v.capacity() == 2);
        FCF_TEST(v.size() == 2);
        v.push_back(3);
        FCF_TEST(v.capacity() == 4, v.capacity());
        FCF_TEST(v.size() == 3, v.size());
        v.push_back(4);
        FCF_TEST(v.capacity() == 4);
        FCF_TEST(v.size() == 4);
        v.pop_back();
        FCF_TEST(v.capacity() == 4, v.capacity());
        FCF_TEST(v.size() == 3);
      }

      {
        typedef fcf::StaticVector<int, 8> static_vector_type;

        {
          size_t size = static_vector_type::_getBufferSize(0);
          FCF_TEST(size == 8, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(5);
          FCF_TEST(size == 8, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(8);
          FCF_TEST(size == 8, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(9);
          FCF_TEST(size == 16, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(10);
          FCF_TEST(size == 16, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(11);
          FCF_TEST(size == 16, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(1023);
          FCF_TEST(size == 1024, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(1024);
          FCF_TEST(size == 1024, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(1025);
          FCF_TEST(size == 2048, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(1026);
          FCF_TEST(size == 2048, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(1027);
          FCF_TEST(size == 2048, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(2000);
          FCF_TEST(size == 2048, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(2048);
          FCF_TEST(size == 2048, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(2049);
          FCF_TEST(size == 4096, size);
        }

      }


      {
        typedef fcf::StaticVector<int, 8, 0, 2, 1, 0, 1024> static_vector_type;

        {
          size_t size = static_vector_type::_getBufferSize(0);
          FCF_TEST(size == 8, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(5);
          FCF_TEST(size == 8, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(8);
          FCF_TEST(size == 8, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(9);
          FCF_TEST(size == 10, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(10);
          FCF_TEST(size == 10, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(11);
          FCF_TEST(size == 12, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(1023);
          FCF_TEST(size == 1024, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(1024);
          FCF_TEST(size == 1024, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(1025);
          FCF_TEST(size == 1026, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(1026);
          FCF_TEST(size == 1026, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(1027);
          FCF_TEST(size == 1028, size);
        }

      }

      {
        typedef fcf::StaticVector<int, 8, 0, 8, 2, 0, 56> static_vector_type;

        {
          size_t size = static_vector_type::_getBufferSize(0);
          FCF_TEST(size == 8, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(5);
          FCF_TEST(size == 8, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(8);
          FCF_TEST(size == 8, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(9);
          FCF_TEST(size == 24, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(24);
          FCF_TEST(size == 24, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(25);
          FCF_TEST(size == 56, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(56);
          FCF_TEST(size == 56, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(57);
          FCF_TEST(size == 88, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(58);
          FCF_TEST(size == 88, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(88);
          FCF_TEST(size == 88, size);
        }
        {
          size_t size = static_vector_type::_getBufferSize(89);
          FCF_TEST(size == 120, size);
        }

      }

      {
        typedef fcf::StaticVector<StaticVectorTestItem, 2, 0, 2, 1, 0, 0> static_vector_type;
        int counter = 0;
        g_staticVectorTestInitCounter = 0;
        {
          static_vector_type sv(1);
          FCF_TEST(sv.size() == 1, sv.size());
          FCF_TEST(sv[0].state == 9999, sv[0].state);
          sv[0].ptr = &counter;
        }
        FCF_TEST(counter == 1, counter);
        FCF_TEST(g_staticVectorTestInitCounter == 1, g_staticVectorTestInitCounter);

        counter = 0;
        g_staticVectorTestInitCounter = 0;
        {
          static_vector_type sv(1);
          FCF_TEST(sv.size() == 1, sv.size());
          FCF_TEST(sv[0].state == 9999, sv[0].state);
          sv[0].ptr = &counter;
          sv.resize(2);
          sv[1].ptr = &counter;
        }
        FCF_TEST(counter == 2, counter);
        FCF_TEST(g_staticVectorTestInitCounter == 2, g_staticVectorTestInitCounter);

        counter = 0;
        g_staticVectorTestInitCounter = 0;
        {
          static_vector_type sv(1);
          FCF_TEST(sv.size() == 1, sv.size());
          FCF_TEST(sv[0].state == 9999, sv[0].state);
          sv[0].ptr = &counter;

          sv.resize(2);
          FCF_TEST(sv.size() == 2, sv.size());
          FCF_TEST(sv[0].state == 9999, sv[0].state);

          sv[1].ptr = &counter;
          sv.resize(3);
          FCF_TEST(sv.size() == 3, sv.size());
          FCF_TEST(sv.capacity() == 4, sv.capacity());
          FCF_TEST(sv[0].state == 9999, sv[0].state);
        }
        FCF_TEST(counter == 4, counter);
        FCF_TEST(g_staticVectorTestInitCounter == 5, g_staticVectorTestInitCounter);

        counter = 0;
        g_staticVectorTestInitCounter = 0;
        {
          static_vector_type sv(1);
          FCF_TEST(sv.size() == 1, sv.size());
          FCF_TEST(sv[0].state == 9999, sv[0].state);
          sv[0].ptr = &counter;

          sv.resize(2);
          FCF_TEST(sv.size() == 2, sv.size());
          FCF_TEST(sv[0].state == 9999, sv[0].state);

          sv[1].ptr = &counter;
          sv.resize(3);
          FCF_TEST(sv.size() == 3, sv.size());
          FCF_TEST(sv.capacity() == 4, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }

          sv.resize(4);
          FCF_TEST(sv.size() == 4, sv.size());
          FCF_TEST(sv.capacity() == 4, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
        }
        FCF_TEST(counter == 4, counter);
        FCF_TEST(g_staticVectorTestInitCounter == 6, g_staticVectorTestInitCounter);


        counter = 0;
        g_staticVectorTestInitCounter = 0;
        {
          static_vector_type sv(1);
          FCF_TEST(sv.size() == 1, sv.size());
          FCF_TEST(sv[0].state == 9999, sv[0].state);
          sv[0].ptr = &counter;

          sv.resize(2);
          FCF_TEST(sv.size() == 2, sv.size());
          FCF_TEST(sv[0].state == 9999, sv[0].state);

          sv[1].ptr = &counter;
          sv.resize(3);
          FCF_TEST(sv.size() == 3, sv.size());
          FCF_TEST(sv.capacity() == 4, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }

          sv.resize(4);
          FCF_TEST(sv.size() == 4, sv.size());
          FCF_TEST(sv.capacity() == 4, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }

          sv.resize(5);
          FCF_TEST(sv.size() == 5, sv.size());
          FCF_TEST(sv.capacity() == 6, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }

        }
        FCF_TEST(counter == 6, counter);
        FCF_TEST(g_staticVectorTestInitCounter == 11, g_staticVectorTestInitCounter);



        counter = 0;
        g_staticVectorTestInitCounter = 0;
        {
          static_vector_type sv(1);
          FCF_TEST(sv.size() == 1, sv.size());
          FCF_TEST(sv[0].state == 9999, sv[0].state);
          sv[0].ptr = &counter;

          sv.resize(2);
          FCF_TEST(sv.size() == 2, sv.size());
          FCF_TEST(sv[0].state == 9999, sv[0].state);

          sv[1].ptr = &counter;
          sv.resize(3);
          FCF_TEST(sv.size() == 3, sv.size());
          FCF_TEST(sv.capacity() == 4, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }

          sv.resize(4);
          FCF_TEST(sv.size() == 4, sv.size());
          FCF_TEST(sv.capacity() == 4, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }

          sv.resize(5);
          FCF_TEST(sv.size() == 5, sv.size());
          FCF_TEST(sv.capacity() == 6, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }

          sv.resize(6);
          FCF_TEST(sv.size() == 6, sv.size());
          FCF_TEST(sv.capacity() == 6, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }

        }
        FCF_TEST(counter == 6, counter);
        FCF_TEST(g_staticVectorTestInitCounter == 12, g_staticVectorTestInitCounter);

        // Reduction

        counter = 0;
        g_staticVectorTestInitCounter = 0;
        {
          static_vector_type sv(6);
          for (size_t i = 0; i < sv.size(); ++i) {
            sv[i].ptr = &counter;
          }
          FCF_TEST(sv.size() == 6, sv.size());
          FCF_TEST(sv.capacity() == 6, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
        }
        FCF_TEST(counter == 6, counter);
        FCF_TEST(g_staticVectorTestInitCounter == 6, g_staticVectorTestInitCounter);

        counter = 0;
        g_staticVectorTestInitCounter = 0;
        {
          static_vector_type sv(6);
          for (size_t i = 0; i < sv.size(); ++i) {
            sv[i].ptr = &counter;
          }
          FCF_TEST(sv.size() == 6, sv.size());
          FCF_TEST(sv.capacity() == 6, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(5);
          FCF_TEST(sv.size() == 5, sv.size());
          FCF_TEST(sv.capacity() == 6, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
        }
        FCF_TEST(counter == 6, counter);
        FCF_TEST(g_staticVectorTestInitCounter == 6, g_staticVectorTestInitCounter);


        counter = 0;
        g_staticVectorTestInitCounter = 0;
        {
          static_vector_type sv(6);
          for (size_t i = 0; i < sv.size(); ++i) {
            sv[i].ptr = &counter;
          }
          FCF_TEST(sv.size() == 6, sv.size());
          FCF_TEST(sv.capacity() == 6, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(5);
          FCF_TEST(sv.size() == 5, sv.size());
          FCF_TEST(sv.capacity() == 6, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(4);
          FCF_TEST(sv.size() == 4, sv.size());
          FCF_TEST(sv.capacity() == 4, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
        }
        FCF_TEST(counter == 10, counter);
        FCF_TEST(g_staticVectorTestInitCounter == 10, g_staticVectorTestInitCounter);

        counter = 0;
        g_staticVectorTestInitCounter = 0;
        {
          static_vector_type sv(6);
          FCF_TEST(sv.size() == 6, sv.size());
          FCF_TEST(sv.capacity() == 6, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            sv[i].ptr = &counter;
          }
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(5);
          FCF_TEST(sv.size() == 5, sv.size());
          FCF_TEST(sv.capacity() == 6, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(4);
          FCF_TEST(sv.size() == 4, sv.size());
          FCF_TEST(sv.capacity() == 4, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(3);
          FCF_TEST(sv.size() == 3, sv.size());
          FCF_TEST(sv.capacity() == 4, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
        }
        FCF_TEST(counter == 10, counter);
        FCF_TEST(g_staticVectorTestInitCounter == 10, g_staticVectorTestInitCounter);

        counter = 0;
        g_staticVectorTestInitCounter = 0;
        {
          static_vector_type sv(6);
          FCF_TEST(sv.size() == 6, sv.size());
          FCF_TEST(sv.capacity() == 6, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            sv[i].ptr = &counter;
          }
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(5);
          FCF_TEST(sv.size() == 5, sv.size());
          FCF_TEST(sv.capacity() == 6, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(4);
          FCF_TEST(sv.size() == 4, sv.size());
          FCF_TEST(sv.capacity() == 4, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(3);
          FCF_TEST(sv.size() == 3, sv.size());
          FCF_TEST(sv.capacity() == 4, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(2);
          FCF_TEST(sv.size() == 2, sv.size());
          FCF_TEST(sv.capacity() == 2, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
        }
        FCF_TEST(counter == 12, counter);
        FCF_TEST(g_staticVectorTestInitCounter == 12, g_staticVectorTestInitCounter);

        counter = 0;
        g_staticVectorTestInitCounter = 0;
        {
          static_vector_type sv(6);
          FCF_TEST(sv.size() == 6, sv.size());
          FCF_TEST(sv.capacity() == 6, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            sv[i].ptr = &counter;
          }
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(5);
          FCF_TEST(sv.size() == 5, sv.size());
          FCF_TEST(sv.capacity() == 6, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(4);
          FCF_TEST(sv.size() == 4, sv.size());
          FCF_TEST(sv.capacity() == 4, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(3);
          FCF_TEST(sv.size() == 3, sv.size());
          FCF_TEST(sv.capacity() == 4, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(2);
          FCF_TEST(sv.size() == 2, sv.size());
          FCF_TEST(sv.capacity() == 2, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(1);
          FCF_TEST(sv.size() == 1, sv.size());
          FCF_TEST(sv.capacity() == 2, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
        }
        FCF_TEST(counter == 12, counter);
        FCF_TEST(g_staticVectorTestInitCounter == 12, g_staticVectorTestInitCounter);

        counter = 0;
        g_staticVectorTestInitCounter = 0;
        {
          static_vector_type sv(6);
          FCF_TEST(sv.size() == 6, sv.size());
          FCF_TEST(sv.capacity() == 6, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            sv[i].ptr = &counter;
          }
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(5);
          FCF_TEST(sv.size() == 5, sv.size());
          FCF_TEST(sv.capacity() == 6, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(4);
          FCF_TEST(sv.size() == 4, sv.size());
          FCF_TEST(sv.capacity() == 4, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(3);
          FCF_TEST(sv.size() == 3, sv.size());
          FCF_TEST(sv.capacity() == 4, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(2);
          FCF_TEST(sv.size() == 2, sv.size());
          FCF_TEST(sv.capacity() == 2, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(1);
          FCF_TEST(sv.size() == 1, sv.size());
          FCF_TEST(sv.capacity() == 2, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
          sv.resize(0);
          FCF_TEST(sv.size() == 0, sv.size());
          FCF_TEST(sv.capacity() == 2, sv.capacity());
          for (size_t i = 0; i < sv.size(); ++i) {
            FCF_TEST(sv[i].state == 9999, sv[i].state);
          }
        }
        FCF_TEST(counter == 12, counter);
        FCF_TEST(g_staticVectorTestInitCounter == 12, g_staticVectorTestInitCounter);

      }
      FCF_TEST(g_staticVectorTestItem_set.size() == 0, g_staticVectorTestItem_set.size());
    }

  } // BasisTest namespace
} // FcfTest namespace

