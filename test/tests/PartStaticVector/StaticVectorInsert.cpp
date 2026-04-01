#include <iostream>
#include <exception>
#include <set>
#include <vector>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../PartStaticVector.hpp"

namespace FcfTest {
  namespace BasisTest {

    struct InsertTestItem {
      InsertTestItem(int a_value)
        : value(a_value) {
        ++activeCounter;
      }
      InsertTestItem()
        : value(999999) {
        ++activeCounter;
      }
      InsertTestItem(const InsertTestItem& a_source)
        : value(a_source.value)
      {
        ++activeCounter;
      }
      ~InsertTestItem(){
        --activeCounter;
      }
      int        value;
      static int activeCounter;
    };

    int InsertTestItem::activeCounter = 0;

    FCF_TEST_DECLARE("fcfBasis", "StaticVector", "insert StaticVector"){
      {
        fcf::StaticVector<InsertTestItem, 4> v;
        v.insert(v.begin(), InsertTestItem(1));
        FCF_TEST(v.size() == 1, v.size());
        FCF_TEST(v.capacity() == 4, v.capacity());
        FCF_TEST(v[0].value == 1, v[0].value);
        v.insert(v.begin(), InsertTestItem(0));
        FCF_TEST(v.size() == 2, v.size());
        FCF_TEST(v.capacity() == 4, v.capacity());
        FCF_TEST(v[0].value == 0, v[0].value);
        FCF_TEST(v[1].value == 1, v[1].value);
        v.insert(v.end(), InsertTestItem(2));
        FCF_TEST(v.size() == 3, v.size());
        FCF_TEST(v.capacity() == 4, v.capacity());
        FCF_TEST(v[0].value == 0, v[0].value);
        FCF_TEST(v[1].value == 1, v[1].value);
        FCF_TEST(v[2].value == 2, v[2].value);
        v.insert(--v.end(), InsertTestItem(3));
        FCF_TEST(v.size() == 4, v.size());
        FCF_TEST(v.capacity() == 4, v.capacity());
        FCF_TEST(v[0].value == 0, v[0].value);
        FCF_TEST(v[1].value == 1, v[1].value);
        FCF_TEST(v[2].value == 3, v[2].value);
        FCF_TEST(v[3].value == 2, v[3].value);
      }
      FCF_TEST(InsertTestItem::activeCounter == 0, InsertTestItem::activeCounter);
      {
        fcf::StaticVector<InsertTestItem, 2> v;
        v.insert(v.begin(), InsertTestItem(1));
        FCF_TEST(v.size() == 1, v.size());
        FCF_TEST(v.capacity() == 2, v.capacity());
        FCF_TEST(v[0].value == 1, v[0].value);
        v.insert(v.begin(), InsertTestItem(0));
        FCF_TEST(v.size() == 2, v.size());
        FCF_TEST(v.capacity() == 2, v.capacity());
        FCF_TEST(v[0].value == 0, v[0].value);
        FCF_TEST(v[1].value == 1, v[1].value);
        v.insert(v.end(), InsertTestItem(2));
        FCF_TEST(v.size() == 3, v.size());
        FCF_TEST(v.capacity() == 4, v.capacity());
        FCF_TEST(v[0].value == 0, v[0].value);
        FCF_TEST(v[1].value == 1, v[1].value);
        FCF_TEST(v[2].value == 2, v[2].value);
        v.insert(--v.end(), InsertTestItem(3));
        FCF_TEST(v.size() == 4, v.size());
        FCF_TEST(v.capacity() == 4, v.capacity());
        FCF_TEST(v[0].value == 0, v[0].value);
        FCF_TEST(v[1].value == 1, v[1].value);
        FCF_TEST(v[2].value == 3, v[2].value);
        FCF_TEST(v[3].value == 2, v[3].value);
      }
      FCF_TEST(InsertTestItem::activeCounter == 0, InsertTestItem::activeCounter);
      {
        fcf::StaticVector<InsertTestItem, 2> stvec;
        {
          std::vector<InsertTestItem> vec = { InsertTestItem(1), InsertTestItem(2)};
          stvec.insert(stvec.begin(), vec.begin(), vec.end());
          FCF_TEST(stvec.size() == 2, stvec.size());
          FCF_TEST(stvec.capacity() == 2, stvec.capacity());
          FCF_TEST(stvec[0].value == 1, stvec[0].value);
          FCF_TEST(stvec[1].value == 2, stvec[1].value);
        }
        {
          std::vector<InsertTestItem> vec = { InsertTestItem(3), InsertTestItem(4)};
          stvec.insert(++stvec.begin(), vec.begin(), vec.end());
          FCF_TEST(stvec.size() == 4, stvec.size());
          FCF_TEST(stvec.capacity() == 4, stvec.capacity());
          FCF_TEST(stvec[0].value == 1, stvec[0].value);
          FCF_TEST(stvec[1].value == 3, stvec[1].value);
          FCF_TEST(stvec[2].value == 4, stvec[2].value);
          FCF_TEST(stvec[3].value == 2, stvec[3].value);
        }
        {
          std::vector<InsertTestItem> vec = { InsertTestItem(5), InsertTestItem(6)};
          stvec.insert(stvec.begin(), vec.begin(), vec.end());
          FCF_TEST(stvec.size() == 6, stvec.size());
          FCF_TEST(stvec.capacity() == 8, stvec.capacity());
          FCF_TEST(stvec[0].value == 5, stvec[0].value);
          FCF_TEST(stvec[1].value == 6, stvec[1].value);
          FCF_TEST(stvec[2].value == 1, stvec[2].value);
          FCF_TEST(stvec[3].value == 3, stvec[3].value);
          FCF_TEST(stvec[4].value == 4, stvec[4].value);
          FCF_TEST(stvec[5].value == 2, stvec[5].value);
        }
        {
          std::vector<InsertTestItem> vec = { InsertTestItem(7), InsertTestItem(8)};
          stvec.insert(stvec.end(), vec.begin(), vec.end());
          FCF_TEST(stvec.size() == 8, stvec.size());
          FCF_TEST(stvec.capacity() == 8, stvec.capacity());
          FCF_TEST(stvec[0].value == 5, stvec[0].value);
          FCF_TEST(stvec[1].value == 6, stvec[1].value);
          FCF_TEST(stvec[2].value == 1, stvec[2].value);
          FCF_TEST(stvec[3].value == 3, stvec[3].value);
          FCF_TEST(stvec[4].value == 4, stvec[4].value);
          FCF_TEST(stvec[5].value == 2, stvec[5].value);
          FCF_TEST(stvec[6].value == 7, stvec[6].value);
          FCF_TEST(stvec[7].value == 8, stvec[7].value);
        }
        {
          std::vector<InsertTestItem> vec = { InsertTestItem(9), InsertTestItem(10)};
          stvec.insert(stvec.end(), vec.begin(), vec.end());
          FCF_TEST(stvec.size() == 10, stvec.size());
          FCF_TEST(stvec.capacity() == 16, stvec.capacity());
          FCF_TEST(stvec[0].value == 5, stvec[0].value);
          FCF_TEST(stvec[1].value == 6, stvec[1].value);
          FCF_TEST(stvec[2].value == 1, stvec[2].value);
          FCF_TEST(stvec[3].value == 3, stvec[3].value);
          FCF_TEST(stvec[4].value == 4, stvec[4].value);
          FCF_TEST(stvec[5].value == 2, stvec[5].value);
          FCF_TEST(stvec[6].value == 7, stvec[6].value);
          FCF_TEST(stvec[7].value == 8, stvec[7].value);
          FCF_TEST(stvec[8].value == 9, stvec[8].value);
          FCF_TEST(stvec[9].value == 10, stvec[9].value);
        }
      }
      FCF_TEST(InsertTestItem::activeCounter == 0, InsertTestItem::activeCounter);
    }

  } // BasisTest namespace
} // FcfTest namespace
