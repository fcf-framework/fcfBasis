#include <iostream>
#include <exception>
#include <set>
#include <vector>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../StaticVector.hpp"

namespace FcfTest {
  namespace BasisTest {

    struct EraseTestItem {
      EraseTestItem(int a_value)
        : value(a_value) {
        ++activeCounter;
      }
      EraseTestItem()
        : value(999999) {
        ++activeCounter;
      }
      EraseTestItem(const EraseTestItem& a_source)
        : value(a_source.value)
      {
        ++activeCounter;
      }
      ~EraseTestItem(){
        --activeCounter;
      }
      int        value;
      static int activeCounter;
    };

    int EraseTestItem::activeCounter = 0;

    FCF_TEST_DECLARE("fcfBasis", "StaticVector", "erase StaticVector"){
      {
        fcf::StaticVector<EraseTestItem, 2> v = {0,1,2,3};
        v.erase( ++(++v.begin()));
        FCF_TEST(v.size() == 3, v.size());
        FCF_TEST(v.capacity() == 4, v.capacity());
        FCF_TEST(v[0].value == 0, v[0].value);
        FCF_TEST(v[1].value == 1, v[1].value);
        FCF_TEST(v[2].value == 3, v[2].value);

        v.erase(v.begin());
        FCF_TEST(v.size() == 2, v.size());
        FCF_TEST(v.capacity() == 2, v.capacity());
        FCF_TEST(v[0].value == 1, v[0].value);
        FCF_TEST(v[1].value == 3, v[1].value);

        v.erase(--v.end());
        FCF_TEST(v.size() == 1, v.size());
        FCF_TEST(v.capacity() == 2, v.capacity());
        FCF_TEST(v[0].value == 1, v[0].value);
      }
      {
        fcf::StaticVector<EraseTestItem, 2> v = {0,1,2,3};
        v.erase( ++(++v.begin()), true);
        FCF_TEST(v.size() == 3, v.size());
        FCF_TEST(v.capacity() == 4, v.capacity());
        FCF_TEST(v[0].value == 0, v[0].value);
        FCF_TEST(v[1].value == 1, v[1].value);
        FCF_TEST(v[2].value == 3, v[2].value);

        v.erase(v.begin(), true);
        FCF_TEST(v.size() == 2, v.size());
        FCF_TEST(v.capacity() == 4, v.capacity());
        FCF_TEST(v[0].value == 1, v[0].value);
        FCF_TEST(v[1].value == 3, v[1].value);

        v.erase(--v.end(), true);
        FCF_TEST(v.size() == 1, v.size());
        FCF_TEST(v.capacity() == 4, v.capacity());
        FCF_TEST(v[0].value == 1, v[0].value);
      }
      {
        fcf::StaticVector<EraseTestItem, 2> v = {0,1,2,3,4,5,6,7};
        fcf::StaticVector<EraseTestItem, 2>::iterator beg = v.begin() + 2;
        fcf::StaticVector<EraseTestItem, 2>::iterator end = beg + 2;
        v.erase(beg, end);
        FCF_TEST(v.size() == 6, v.size());
        FCF_TEST(v.capacity() == 8, v.capacity());
        FCF_TEST(v[0].value == 0, v[0].value);
        FCF_TEST(v[1].value == 1, v[1].value);
        FCF_TEST(v[2].value == 4, v[2].value);
        FCF_TEST(v[3].value == 5, v[3].value);
        FCF_TEST(v[4].value == 6, v[4].value);
        FCF_TEST(v[5].value == 7, v[5].value);

        beg = v.end() - 2;
        end = v.end();
        v.erase(beg, end);
        FCF_TEST(v.size() == 4, v.size());
        FCF_TEST(v.capacity() == 4, v.capacity());
        FCF_TEST(v[0].value == 0, v[0].value);
        FCF_TEST(v[1].value == 1, v[1].value);
        FCF_TEST(v[2].value == 4, v[2].value);
        FCF_TEST(v[3].value == 5, v[3].value);

        beg = v.begin();
        end = v.begin()+2;
        v.erase(beg, end);
        FCF_TEST(v.size() == 2, v.size());
        FCF_TEST(v.capacity() == 2, v.capacity());
        FCF_TEST(v[0].value == 4, v[0].value);
        FCF_TEST(v[1].value == 5, v[1].value);

        beg = v.begin();
        end = v.end();
        v.erase(beg, end);
        FCF_TEST(v.size() == 0, v.size());
        FCF_TEST(v.capacity() == 2, v.capacity());
      }

      FCF_TEST(EraseTestItem::activeCounter == 0, EraseTestItem::activeCounter);
    }

  } // BasisTest namespace
} // FcfTest namespace
