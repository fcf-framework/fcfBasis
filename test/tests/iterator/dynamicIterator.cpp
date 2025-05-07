#include <iostream>
#include "../../libraries/fcfTest/test.hpp"
#include "../../basis.hpp"

void dynamicIteratorTest(){
  std::cout << "Start dynamicIteratorTest()..." << std::endl;
  {
    typedef std::vector<int> container_type;
    container_type                             c;
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);
    fcf::VectorDynamicIterator<container_type> vdi1(c);
    ++vdi1;
    fcf::VectorDynamicIterator<container_type> vdi2(c, fcf::DIP_BEGIN);
    fcf::VectorDynamicIterator<container_type> vdi3;
    FCF_TEST(vdi1 != vdi2);
    FCF_TEST(vdi1.key() == 1);
    FCF_TEST(vdi1.value() == 2);
    vdi3 = vdi1--;
    FCF_TEST(vdi3.key() == 1);
    FCF_TEST(vdi3.value() == 2);
    FCF_TEST(vdi1.key() == 0);
    FCF_TEST(vdi1.value() == 1);
    FCF_TEST(vdi1 == vdi2);

    vdi1 = fcf::VectorDynamicIterator<container_type>(c, 1);
    FCF_TEST(vdi1.key() == 1);
    FCF_TEST(vdi1.value() == 2);
  }
  {
    typedef std::list<int> container_type;
    container_type                             c;
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);
    fcf::ListDynamicIterator<container_type> vdi1(c);
    ++vdi1;
    fcf::ListDynamicIterator<container_type> vdi2(c, fcf::DIP_BEGIN);
    fcf::ListDynamicIterator<container_type> vdi3;
    FCF_TEST(vdi1 != vdi2);
    FCF_TEST(vdi1.key() == 1);
    FCF_TEST(vdi1.value() == 2);
    vdi3 = vdi1--;
    FCF_TEST(vdi3.key() == 1);
    FCF_TEST(vdi3.value() == 2);
    FCF_TEST(vdi1.key() == 0);
    FCF_TEST(vdi1.value() == 1);
    FCF_TEST(vdi1 == vdi2);

    vdi1 = fcf::ListDynamicIterator<container_type>(c, 1);
    FCF_TEST(vdi1.key() == 1, vdi1.key());
    FCF_TEST(vdi1.value() == 2, vdi1.value());
  }

  {
    typedef std::map<int, int> container_type;
    container_type                             c;
    c[0] = 1;
    c[1] = 2;
    c[2] = 3;
    fcf::MapDynamicIterator<container_type> vdi1(c);
    ++vdi1;
    fcf::MapDynamicIterator<container_type> vdi2(c, fcf::DIP_BEGIN);
    fcf::MapDynamicIterator<container_type> vdi3;
    FCF_TEST(vdi1 != vdi2);
    FCF_TEST(vdi1.key() == 1);
    FCF_TEST(vdi1.value() == 2);
    vdi3 = vdi1--;
    FCF_TEST(vdi3.key() == 1);
    FCF_TEST(vdi3.value() == 2);
    FCF_TEST(vdi1.key() == 0);
    FCF_TEST(vdi1.value() == 1);
    FCF_TEST(vdi1 == vdi2);

    vdi1 = fcf::MapDynamicIterator<container_type>(c, 1);
    FCF_TEST(vdi1.key() == 1, vdi1.key());
    FCF_TEST(vdi1.value() == 2, vdi1.value());
  }

  {
    typedef std::set<std::string> container_type;
    container_type        c;
    c.insert("0");
    c.insert("1");
    c.insert("2");
    fcf::SetDynamicIterator<container_type> vdi1(c);
    ++vdi1;
    fcf::SetDynamicIterator<container_type> vdi2(c, fcf::DIP_BEGIN);
    fcf::SetDynamicIterator<container_type> vdi3;
    FCF_TEST(vdi1 != vdi2);
    FCF_TEST(vdi1.key() == "1");
    FCF_TEST(vdi1.value() == "1");
    vdi3 = vdi1--;
    FCF_TEST(vdi3.key() == "1");
    FCF_TEST(vdi3.value() == "1");
    FCF_TEST(vdi1.key() == "0");
    FCF_TEST(vdi1.value() == "0");
    FCF_TEST(vdi1 == vdi2);

    vdi1 = fcf::SetDynamicIterator<container_type>(c, "1");
    FCF_TEST(vdi1.key() == "1", vdi1.key());
    FCF_TEST(vdi1.value() == "1", vdi1.value());
  }

}

