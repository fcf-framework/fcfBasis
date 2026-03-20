#include <iostream>
#include "../../libraries/fcfTest/test.hpp"
#include "../../basis.hpp"
#include "../../bits/PartSpecificator/ContainerAccessSpecificator.hpp"
#include <array>

 
FCF_TEST_DECLARE("fcfBasis", "ContainerAccess", "dynamic container access"){
  {
    typedef std::vector<char> type;
    type vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    fcf::Variant vit = fcf::Type<type>().getSpecificator<fcf::ContainerAccessSpecificator>()(&vec, 0, 0);
    fcf::DynamicContainerAccessBase* it = (fcf::DynamicContainerAccessBase*)vit.ptr();
    FCF_TEST((void*)vit.ptr() != 0, (void*)vit.ptr());

    FCF_TEST(it->isEnd() == false);
    FCF_TEST(it->getKey().cast<int>() == 0, it->getKey().cast<int>());
    FCF_TEST(it->getValue().cast<int>() == 1, it->getValue().cast<int>());
    FCF_TEST(it->getValueTypeIndex() == fcf::Type<char>().index(), it->getValueTypeIndex(), fcf::Type<char>().index());
    FCF_TEST(it->getContainerSize() == 3, it->getContainerSize());

    it->inc();
    FCF_TEST(it->isEnd() == false);
    FCF_TEST(it->getKey().cast<int>() == 1, it->getKey().cast<int>());
    FCF_TEST(it->getValue().cast<int>() == 2, it->getValue().cast<int>());
    FCF_TEST(it->getValueTypeIndex() == fcf::Type<char>().index(), it->getValueTypeIndex(), fcf::Type<char>().index());
    FCF_TEST(it->getContainerSize() == 3, it->getContainerSize());

    it->inc();
    FCF_TEST(it->isEnd() == false);
    FCF_TEST(it->getKey().cast<int>() == 2, it->getKey().cast<int>());
    FCF_TEST(it->getValue().cast<int>() == 3, it->getValue().cast<int>());
    FCF_TEST(it->getValueTypeIndex() == fcf::Type<char>().index(), it->getValueTypeIndex(), fcf::Type<char>().index());
    FCF_TEST(it->getContainerSize() == 3, it->getContainerSize());

    it->inc();
    FCF_TEST(it->isEnd() == true);
  }

  {
    typedef std::vector<int> container_type;
    container_type c;
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);

    fcf::Variant vit = fcf::Type<container_type>().getSpecificator<fcf::ContainerAccessSpecificator>()(&c, 0, 0);
    fcf::DynamicContainerAccessBase& it = *(fcf::DynamicContainerAccessBase*)vit.ptr();

    size_t i = 0;
    int arr[3] = {0,0,0};
    while(it){
      arr[i] = it.getValue().cast<int>();
      ++i;
      ++it;
    }
    FCF_TEST(i, 3);
    FCF_TEST(arr[0], 1);
    FCF_TEST(arr[1], 2);
    FCF_TEST(arr[2], 3);
  }
  {
    typedef std::vector<int> container_type;
    container_type c;
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);

    fcf::Variant vit = fcf::Type<container_type>().getSpecificator<fcf::ContainerAccessSpecificator>()(&c, 0, 0);
    fcf::DynamicContainerAccessBase& it = *(fcf::DynamicContainerAccessBase*)vit.ptr();

    FCF_TEST(it == true);
    it.setPosition(1);

    FCF_TEST(it == true);
    FCF_TEST(it.getKey().cast<int>() == 1, it.getKey().cast<int>());
    FCF_TEST(it.getValue().cast<int>() == 2, it.getValue().cast<int>());
    FCF_TEST(it.getValueTypeIndex() == fcf::Type<int>().index(), it.getValueTypeIndex());
    FCF_TEST(it.getContainerSize() == 3, it.getContainerSize());
  }

  {
    typedef std::vector<int> container_type;
    container_type c;
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);
    fcf::Variant vit = fcf::Type<container_type>().getSpecificator<fcf::ContainerAccessSpecificator>()(&c, 0, 0);
    fcf::DynamicContainerAccessBase& it = *(fcf::DynamicContainerAccessBase*)vit.ptr();

    FCF_TEST(it);
    it.setPosition(10);
    FCF_TEST(!it);
    ++it;
    FCF_TEST(!it);
  }

}

