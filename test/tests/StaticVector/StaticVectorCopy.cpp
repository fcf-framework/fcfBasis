#include <iostream>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../StaticVector.hpp"


int g_staticVectorCopyTestItem_destructCounter = 0;
int g_staticVectorCopyTestItem_constructCounter = 0;

struct StaticVectorCopyTestItem {
  StaticVectorCopyTestItem()
    : value(9999){
    ++g_staticVectorCopyTestItem_constructCounter;
  }

  StaticVectorCopyTestItem(int a_value)
    : value(a_value) {
    ++g_staticVectorCopyTestItem_constructCounter;
  }

  StaticVectorCopyTestItem(const StaticVectorCopyTestItem& a_source)
    : value(a_source.value){
    ++g_staticVectorCopyTestItem_constructCounter;
  }

  ~StaticVectorCopyTestItem(){
    ++g_staticVectorCopyTestItem_destructCounter;
  }

  int value;
};

void staticVectorCopyTest(){
  std::cout << "Start staticVectorCopyTest()..." << std::endl;


  {
    typedef fcf::StaticVector<int, 2, 2, 1, 0, 0> static_vector_type;
    static_vector_type v1(3);
    v1[0] = 1;
    v1[1] = 2;
    v1[2] = 3;
    static_vector_type v2(v1);

    FCF_TEST(v2[0] == 1, v2[0]);
    FCF_TEST(v2[1] == 2, v2[1]);
    FCF_TEST(v2[2] == 3, v2[2]);
    FCF_TEST(v2.size() == 3, v2.size());
    FCF_TEST(v2.capacity() == 4, v2.capacity());
  }

  g_staticVectorCopyTestItem_destructCounter = 0;
  g_staticVectorCopyTestItem_constructCounter = 0;
  { // All data in internall buffer
    typedef fcf::StaticVector<StaticVectorCopyTestItem, 2, 2, 1, 0, 0> static_vector_type;
    static_vector_type v1(2);
    for(size_t i = 0; i < 2; ++i) {
      v1[i].value = i;
    }
    FCF_TEST(g_staticVectorCopyTestItem_constructCounter == 2, g_staticVectorCopyTestItem_constructCounter);
    static_vector_type v2;
    v2 = v1;
    for(size_t i = 0; i < 2; ++i){
      FCF_TEST(v1[i].value == i, i, v1[i].value);
      FCF_TEST(v2[i].value == i, i, v2[i].value);
    }
    FCF_TEST(v2.capacity() == 2, v2.capacity());
    FCF_TEST(v2.size() == 2, v2.size());
  }
  FCF_TEST(g_staticVectorCopyTestItem_destructCounter == 4, g_staticVectorCopyTestItem_destructCounter);
  FCF_TEST(g_staticVectorCopyTestItem_constructCounter == g_staticVectorCopyTestItem_destructCounter,
           g_staticVectorCopyTestItem_constructCounter,
           g_staticVectorCopyTestItem_destructCounter
           );



  g_staticVectorCopyTestItem_destructCounter = 0;
  g_staticVectorCopyTestItem_constructCounter = 0;
  { // All data in internall buffer (The receiving side had data in its internall buffer)
    typedef fcf::StaticVector<StaticVectorCopyTestItem, 2, 2, 1, 0, 0> static_vector_type;
    static_vector_type v1(2);
    for(size_t i = 0; i < 2; ++i) {
      v1[i].value = i;
    }
    FCF_TEST(g_staticVectorCopyTestItem_constructCounter == 2, g_staticVectorCopyTestItem_constructCounter);
    static_vector_type v2(2);
    v2 = v1;
    for(size_t i = 0; i < 2; ++i){
      FCF_TEST(v1[i].value == i, i, v1[i].value);
      FCF_TEST(v2[i].value == i, i, v2[i].value);
    }
    FCF_TEST(v2.capacity() == 2, v2.capacity());
    FCF_TEST(v2.size() == 2, v2.size());
  }
  FCF_TEST(g_staticVectorCopyTestItem_destructCounter == 6, g_staticVectorCopyTestItem_destructCounter);
  FCF_TEST(g_staticVectorCopyTestItem_constructCounter == g_staticVectorCopyTestItem_destructCounter,
           g_staticVectorCopyTestItem_constructCounter,
           g_staticVectorCopyTestItem_destructCounter
           );



  g_staticVectorCopyTestItem_destructCounter = 0;
  g_staticVectorCopyTestItem_constructCounter = 0;
  { // All data in internall buffer (The receiving size had data in the heap)
    typedef fcf::StaticVector<StaticVectorCopyTestItem, 2, 2, 1, 0, 0> static_vector_type;
    static_vector_type v1(2);
    for(size_t i = 0; i < 2; ++i) {
      v1[i].value = i;
    }
    FCF_TEST(g_staticVectorCopyTestItem_constructCounter == 2, g_staticVectorCopyTestItem_constructCounter);
    static_vector_type v2(3);
    v2 = v1;
    for(size_t i = 0; i < 2; ++i){
      FCF_TEST(v1[i].value == i, i, v1[i].value);
      FCF_TEST(v2[i].value == i, i, v2[i].value);
    }
    FCF_TEST(v2.capacity() == 2, v2.capacity());
    FCF_TEST(v2.size() == 2, v2.size());
  }
  FCF_TEST(g_staticVectorCopyTestItem_destructCounter == 7, g_staticVectorCopyTestItem_destructCounter);
  FCF_TEST(g_staticVectorCopyTestItem_constructCounter == g_staticVectorCopyTestItem_destructCounter,
           g_staticVectorCopyTestItem_constructCounter,
           g_staticVectorCopyTestItem_destructCounter
           );

  g_staticVectorCopyTestItem_destructCounter = 0;
  g_staticVectorCopyTestItem_constructCounter = 0;
  { // All data in heap
    typedef fcf::StaticVector<StaticVectorCopyTestItem, 2, 2, 1, 0, 0> static_vector_type;
    static_vector_type v1(3);
    for(size_t i = 0; i < 3; ++i) {
      v1[i].value = i;
    }
    FCF_TEST(g_staticVectorCopyTestItem_constructCounter == 3, g_staticVectorCopyTestItem_constructCounter);
    static_vector_type v2(v1);
    for(size_t i = 0; i < 3; ++i){
      FCF_TEST(v1[i].value == i, i, v1[i].value);
      FCF_TEST(v2[i].value == i, i, v2[i].value);
    }
    FCF_TEST(v2.capacity() == 4, v2.capacity());
    FCF_TEST(v2.size() == 3, v2.size());
  }
  FCF_TEST(g_staticVectorCopyTestItem_destructCounter == 6, g_staticVectorCopyTestItem_destructCounter);
  FCF_TEST(g_staticVectorCopyTestItem_constructCounter == g_staticVectorCopyTestItem_destructCounter,
           g_staticVectorCopyTestItem_constructCounter,
           g_staticVectorCopyTestItem_destructCounter
           );


  g_staticVectorCopyTestItem_destructCounter = 0;
  g_staticVectorCopyTestItem_constructCounter = 0;
  { // All data in heap (The receiving side had data in its internall buffer)
    typedef fcf::StaticVector<StaticVectorCopyTestItem, 2, 2, 1, 0, 0> static_vector_type;
    static_vector_type v1(3);
    for(size_t i = 0; i < 3; ++i) {
      v1[i].value = i;
    }
    FCF_TEST(g_staticVectorCopyTestItem_constructCounter == 3, g_staticVectorCopyTestItem_constructCounter);
    static_vector_type v2(2);
    v2 = v1;
    for(size_t i = 0; i < 3; ++i){
      FCF_TEST(v1[i].value == i, i, v1[i].value);
      FCF_TEST(v2[i].value == i, i, v2[i].value);
    }
    FCF_TEST(v2.capacity() == 4, v2.capacity());
    FCF_TEST(v2.size() == 3, v2.size());
  }
  FCF_TEST(g_staticVectorCopyTestItem_destructCounter == (3*2 + 2), g_staticVectorCopyTestItem_destructCounter);
  FCF_TEST(g_staticVectorCopyTestItem_constructCounter == g_staticVectorCopyTestItem_destructCounter,
           g_staticVectorCopyTestItem_constructCounter,
           g_staticVectorCopyTestItem_destructCounter
           );



  g_staticVectorCopyTestItem_destructCounter = 0;
  g_staticVectorCopyTestItem_constructCounter = 0;
  { // All data in heap (The receiving side had data in the heap)
    typedef fcf::StaticVector<StaticVectorCopyTestItem, 2, 2, 1, 0, 0> static_vector_type;
    static_vector_type v1(3);
    for(size_t i = 0; i < 3; ++i) {
      v1[i].value = i;
    }
    FCF_TEST(g_staticVectorCopyTestItem_constructCounter == 3, g_staticVectorCopyTestItem_constructCounter);
    static_vector_type v2(3);
    v2 = v1;
    for(size_t i = 0; i < 3; ++i){
      FCF_TEST(v1[i].value == i, i, v1[i].value);
      FCF_TEST(v2[i].value == i, i, v2[i].value);
    }
    FCF_TEST(v2.capacity() == 4, v2.capacity());
    FCF_TEST(v2.size() == 3, v2.size());
  }
  FCF_TEST(g_staticVectorCopyTestItem_destructCounter == (3*2 + 3), g_staticVectorCopyTestItem_destructCounter);
  FCF_TEST(g_staticVectorCopyTestItem_constructCounter == g_staticVectorCopyTestItem_destructCounter,
           g_staticVectorCopyTestItem_constructCounter,
           g_staticVectorCopyTestItem_destructCounter
           );



  g_staticVectorCopyTestItem_destructCounter = 0;
  g_staticVectorCopyTestItem_constructCounter = 0;
  {
    typedef fcf::StaticVector<StaticVectorCopyTestItem, 2, 2, 1, 0, 0> static_vector_type;
    static_vector_type v1 = {1, 2, 3};
    FCF_TEST(v1.capacity() == 4, v1.capacity());
    FCF_TEST(v1.size() == 3, v1.size());
    for(size_t i = 0; i < 3; ++i){
      FCF_TEST(v1[i].value == (i+1), (i+1), v1[i].value);
    }

    v1.resize(1);
    FCF_TEST(v1.capacity() == 2, v1.capacity());
    FCF_TEST(v1.size() == 1, v1.size());
  }



  g_staticVectorCopyTestItem_destructCounter = 0;
  g_staticVectorCopyTestItem_constructCounter = 0;
  {
    typedef fcf::StaticVector<StaticVectorCopyTestItem, 2, 2, 1, 0, 0> static_vector_type;
    static_vector_type v1(3, 9);
    FCF_TEST(v1.capacity() == 4, v1.capacity());
    FCF_TEST(v1.size() == 3, v1.size());
    for(size_t i = 0; i < 3; ++i){
      FCF_TEST(v1[i].value == 9, v1[i].value);
    }
    v1.resize(1);
    FCF_TEST(v1.capacity() == 2, v1.capacity());
    FCF_TEST(v1.size() == 1, v1.size());
  }

}
