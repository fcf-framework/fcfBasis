#include <iostream>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../StaticVector.hpp"

namespace FcfTest {
  namespace BasisTest {

    FCF_TEST_DECLARE("fcfBasis", "StaticVector", "not reduce StaticVector"){
      {
        fcf::StaticVector<int, 16> v(24);
        FCF_TEST(v.size() == 24, v.size());
        FCF_TEST(v.capacity() == 32, v.capacity());
        v.clear(true);
        FCF_TEST(v.size() == 0, v.size());
        FCF_TEST(v.capacity() == 32, v.capacity());
      }
      {
        fcf::StaticVector<int, 8> v(24);
        FCF_TEST(v.size() == 24, v.size());
        FCF_TEST(v.capacity() == 32, v.capacity());
        v.clear(true);
        FCF_TEST(v.size() == 0, v.size());
        FCF_TEST(v.capacity() == 32, v.capacity());
        v.clear();
        FCF_TEST(v.size() == 0, v.size());
        FCF_TEST(v.capacity() == 8, v.capacity());
      }
      {
        fcf::StaticVector<int, 16> v(256);
        FCF_TEST(v.size() == 256, v.size());
        FCF_TEST(v.capacity() == 256, v.capacity());
        v.resize(64, true);
        FCF_TEST(v.size() == 64, v.size());
        FCF_TEST(v.capacity() == 256, v.capacity());
        v.resize(64);
        FCF_TEST(v.size() == 64, v.size());
        FCF_TEST(v.capacity() == 64, v.capacity());
        v.push_back(1);
        FCF_TEST(v.size() == 65, v.size());
        FCF_TEST(v.capacity() == 128, v.capacity());
      }
      {
        fcf::StaticVector<int, 16> v(256);
        FCF_TEST(v.size() == 256, v.size());
        FCF_TEST(v.capacity() == 256, v.capacity());
        v.resize(64, true);
        FCF_TEST(v.size() == 64, v.size());
        FCF_TEST(v.capacity() == 256, v.capacity());
        v.push_back(1);
        FCF_TEST(v.size() == 65, v.size());
        FCF_TEST(v.capacity() == 256, v.capacity());
      }
      {
        fcf::StaticVector<int, 16> v(1);
        v.resize(31, true);
        FCF_TEST(v.size() == 31, v.size());
        FCF_TEST(v.capacity() == 32, v.capacity());
        v.resize(16, true);
        FCF_TEST(v.size() == 16, v.size());
        FCF_TEST(v.capacity() == 32, v.capacity());
        v.resize(64, true);
        FCF_TEST(v.size() == 64, v.size());
        FCF_TEST(v.capacity() == 64, v.capacity());
      }
      {
        fcf::StaticVector<int, 16> v(65);
        FCF_TEST(v.size() == 65, v.size());
        FCF_TEST(v.capacity() == 128, v.capacity());
        v.pop_back();
        FCF_TEST(v.size() == 64, v.size());
        FCF_TEST(v.capacity() == 64, v.capacity());
      }
      {
        fcf::StaticVector<int, 16> v(65);
        FCF_TEST(v.size() == 65, v.size());
        FCF_TEST(v.capacity() == 128, v.capacity());
        v.pop_back(true);
        FCF_TEST(v.size() == 64, v.size());
        FCF_TEST(v.capacity() == 128, v.capacity());
      }

    }

  } // BasisTest namespace
} // FcfTest namespace

