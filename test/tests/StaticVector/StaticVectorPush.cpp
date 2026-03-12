#include <iostream>
#include <exception>
#include <set>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../StaticVector.hpp"


namespace FcfTest {
  namespace BasisTest {

    int g_staticVectorPushTestItem_destructCounter = 0;
    int g_staticVectorPushTestItem_constructCounter = 0;
    std::set<void*> g_staticVectorPushTestItem_set;

    struct StaticVectorPushTestItem {
      StaticVectorPushTestItem()
        : value(9999){
        ++g_staticVectorPushTestItem_constructCounter;
        if (g_staticVectorPushTestItem_set.find(this) != g_staticVectorPushTestItem_set.end()){
          throw std::runtime_error("Invalid test");
        }
        g_staticVectorPushTestItem_set.insert(this);
      }

      StaticVectorPushTestItem(int a_value)
        : value(a_value) {
        ++g_staticVectorPushTestItem_constructCounter;
        if (g_staticVectorPushTestItem_set.find(this) != g_staticVectorPushTestItem_set.end()){
          throw std::runtime_error("Invalid test");
        }
        g_staticVectorPushTestItem_set.insert(this);
      }

      StaticVectorPushTestItem(const StaticVectorPushTestItem& a_source)
        : value(a_source.value){
        ++g_staticVectorPushTestItem_constructCounter;
        if (g_staticVectorPushTestItem_set.find(this) != g_staticVectorPushTestItem_set.end()){
          throw std::runtime_error("Invalid test");
        }
        g_staticVectorPushTestItem_set.insert(this);
      }

      ~StaticVectorPushTestItem(){
        ++g_staticVectorPushTestItem_destructCounter;
        g_staticVectorPushTestItem_set.erase(this);
      }

      int value;
    };

    void staticVectorPushTest(){
      std::cout << "Start staticVectorPushTest()..." << std::endl;
      g_staticVectorPushTestItem_set.clear();

      {
        typedef fcf::StaticVector<StaticVectorPushTestItem, 8, 0, 8, 2, 0, 55> static_vector_type;
        {
          size_t size = static_vector_type::_getPreviousSize(56);
          FCF_TEST(size == 24, size) ;
          size = static_vector_type::_getNextSize(24);
          FCF_TEST(size == 56, size) ;
          size = static_vector_type::_getNextSize(56);
          FCF_TEST(size == 88, size) ;
        }
        {
          size_t size = static_vector_type::_getPreviousSize(57);
          FCF_TEST(size == 56, size) ;
          size = static_vector_type::_getNextSize(56);
          FCF_TEST(size == 88, size) ;
          size = static_vector_type::_getNextSize(86);
          FCF_TEST(size == 88, size) ;
          size = static_vector_type::_getNextSize(88);
          FCF_TEST(size == 120, size) ;
          size = static_vector_type::_getNextSize(89);
          FCF_TEST(size == 120, size) ;
        }
        {
          size_t size = static_vector_type::_getPreviousSize(58);
          FCF_TEST(size == 56, size) ;
          size = static_vector_type::_getNextSize(58);
          FCF_TEST(size == 88, size) ;
        }
      }

      {
        typedef fcf::StaticVector<StaticVectorPushTestItem, 8, 0, 8, 2, 0, 56> static_vector_type;
        {
          size_t size = static_vector_type::_getPreviousSize(24);
          FCF_TEST(size == 8, size) ;
        }
        {
          size_t size = static_vector_type::_getPreviousSize(55);
          FCF_TEST(size == 23, size) ;
        }
        {
          size_t size = static_vector_type::_getPreviousSize(56);
          FCF_TEST(size == 24, size) ;
          size = static_vector_type::_getNextSize(24);
          FCF_TEST(size == 56, size) ;
          size = static_vector_type::_getNextSize(56);
          FCF_TEST(size == 88, size) ;
        }
        {
          size_t size = static_vector_type::_getPreviousSize(57);
          FCF_TEST(size == 56, size) ;
          size = static_vector_type::_getNextSize(57);
          FCF_TEST(size == 88, size) ;
          size = static_vector_type::_getNextSize(87);
          FCF_TEST(size == 88, size) ;
          size = static_vector_type::_getNextSize(88);
          FCF_TEST(size == 120, size) ;
          size = static_vector_type::_getNextSize(89);
          FCF_TEST(size == 120, size) ;
        }
        {
          size_t size = static_vector_type::_getPreviousSize(58);
          FCF_TEST(size == 56, size) ;
          size = static_vector_type::_getNextSize(58);
          FCF_TEST(size == 88, size) ;
        }
      }



      {
        typedef fcf::StaticVector<StaticVectorPushTestItem, 8, 0, 8, 2, 0, 56> static_vector_type;

        {
          size_t size = static_vector_type::_getPreviousSize(0);
          FCF_TEST(size == 8, size) ;
        }
        {
          size_t size = static_vector_type::_getPreviousSize(1);
          FCF_TEST(size == 8, size) ;
        }
        {
          size_t size = static_vector_type::_getPreviousSize(7);
          FCF_TEST(size == 8, size) ;
        }
        {
          size_t size = static_vector_type::_getPreviousSize(8);
          FCF_TEST(size == 8, size) ;
        }
        {
          size_t size = static_vector_type::_getPreviousSize(9);
          FCF_TEST(size == 8, size) ;
        }
        {
          size_t size = static_vector_type::_getPreviousSize(10);
          FCF_TEST(size == 8, size) ;
        }
        {
          size_t size = static_vector_type::_getPreviousSize(24);
          FCF_TEST(size == 8, size) ;
        }
        {
          size_t size = static_vector_type::_getPreviousSize(56);
          FCF_TEST(size == 24, size) ;
        }
        {
          size_t size = static_vector_type::_getPreviousSize(57);
          FCF_TEST(size == 56, size) ;
        }
        {
          size_t size = static_vector_type::_getPreviousSize(87);
          FCF_TEST(size == 56, size) ;
        }
        {
          size_t size = static_vector_type::_getPreviousSize(88);
          FCF_TEST(size == 56, size) ;
        }
        {
          size_t size = static_vector_type::_getPreviousSize(87);
          FCF_TEST(size == 56, size) ;
        }
        {
          size_t size = static_vector_type::_getPreviousSize(89);
          FCF_TEST(size == 88, size) ;
        }

      }
      {
        typedef fcf::StaticVector<StaticVectorPushTestItem, 8, 0, 8, 2, 0, 56> static_vector_type;
        {
          size_t size = static_vector_type::_getNextSize(8);
          FCF_TEST(size == 24, size) ;
        }
        {
          size_t size = static_vector_type::_getNextSize(24);
          FCF_TEST(size == 56, size) ;
        }
        {
          size_t size = static_vector_type::_getNextSize(56);
          FCF_TEST(size == 88, size) ;
        }
        {
          size_t size = static_vector_type::_getNextSize(88);
          FCF_TEST(size == 120, size) ;
        }
      }
      {
        typedef fcf::StaticVector<StaticVectorPushTestItem, 2, 0, 2, 1, 0, 8> static_vector_type;

        g_staticVectorPushTestItem_constructCounter = 0;
        g_staticVectorPushTestItem_destructCounter = 0;
        {
          static_vector_type v;
          v.push_back(1);
          FCF_TEST(v.size() == 1, v.size());
          FCF_TEST(v.capacity() == 2, v.capacity());
        }
        FCF_TEST(g_staticVectorPushTestItem_constructCounter > 1, g_staticVectorPushTestItem_constructCounter);
        FCF_TEST(g_staticVectorPushTestItem_constructCounter == g_staticVectorPushTestItem_destructCounter,
                 g_staticVectorPushTestItem_constructCounter,
                 g_staticVectorPushTestItem_destructCounter);


        g_staticVectorPushTestItem_constructCounter = 0;
        g_staticVectorPushTestItem_destructCounter = 0;
        {
          static_vector_type v;
          for(size_t i = 0; i < 10; ++i) {
            v.push_back((int)i);
            size_t c = (size_t)std::ceil((double)(i+1) / 2);
            c *= 2;
            if (c < 2){
              c = 2;
            }
            FCF_TEST(v.size() == (i+1), v.size(), (i+1));
            FCF_TEST(v.capacity() == c, v.capacity(), c, i);
          }
        }
        FCF_TEST(g_staticVectorPushTestItem_constructCounter == g_staticVectorPushTestItem_destructCounter,
                 g_staticVectorPushTestItem_constructCounter,
                 g_staticVectorPushTestItem_destructCounter);




        g_staticVectorPushTestItem_constructCounter = 0;
        g_staticVectorPushTestItem_destructCounter = 0;
        {
          static_vector_type v;
          for(size_t i = 0; i < 10; ++i) {
            v.push_back((int)i);
            size_t c = (size_t)std::ceil((double)(i+1) / 2);
            c *= 2;
            if (c < 2){
              c = 2;
            }
            FCF_TEST(v.size() == (i+1), v.size(), (i+1));
            FCF_TEST(v.capacity() == c, v.capacity(), c, i);
          }
          for(size_t i = 0; i < 10; ++i) {
            v.pop_back();
            size_t c = (size_t)std::ceil((double)(10 - i - 1) / 2);
            c *= 2;
            if (c < 2){
              c = 2;
            }
            FCF_TEST(v.size() == (10 - i - 1), v.size(), (10 - i - 1));
            FCF_TEST(v.capacity() == c, v.capacity(), c, i);
          }
        }
        FCF_TEST(g_staticVectorPushTestItem_constructCounter == g_staticVectorPushTestItem_destructCounter,
                 g_staticVectorPushTestItem_constructCounter,
                 g_staticVectorPushTestItem_destructCounter);

      }

      FCF_TEST(g_staticVectorPushTestItem_set.size() == 0, g_staticVectorPushTestItem_set.size());
    }

  } // BasisTest namespace
} // FcfTest namespace


