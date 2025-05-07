#include <iostream>
#include "../../libraries/fcfTest/test.hpp"
#include "../../basis.hpp"

void iteratorTest(){
  std::cout << "Start iteratorTest()..." << std::endl;

  {
    typedef std::vector<char> type;
    type vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    fcf::DynamicIteratorSpecificator::function_type resolver = fcf::Type<type>().dynamicIteratorResolver();
    fcf::DynamicIteratorInfo dii;
    dii.flags = fcf::DIF_ITERATION | fcf::DIF_GET_KEY | fcf::DIF_GET_VALUE | fcf::DIF_GET_TYPE | fcf::DIF_GET_SIZE;
    FCF_TEST((void*)resolver != 0, (void*)resolver);

    size_t i = 0;
    bool res;
    res = resolver(&vec, &dii);
    FCF_TEST(res == true);
    FCF_TEST(dii.key.as<int>() == 0, dii.key.as<int>());
    FCF_TEST(*(char*)dii.value == 1, *(char*)dii.value);
    FCF_TEST(dii.type == fcf::Type<char>().index(), dii.type, fcf::Type<char>().index());
    FCF_TEST(dii.size == 3, dii.size);

    res = resolver(&vec, &dii);
    FCF_TEST(res == true);
    FCF_TEST(dii.key.as<int>() == 1, dii.key.as<int>());
    FCF_TEST(*(char*)dii.value == 2, *(char*)dii.value);
    FCF_TEST(dii.type == fcf::Type<char>().index(), dii.type, fcf::Type<char>().index());
    FCF_TEST(dii.size == 3, dii.size);

    res = resolver(&vec, &dii);
    FCF_TEST(res == true);
    FCF_TEST(dii.key.as<int>() == 2, dii.key.as<int>());
    FCF_TEST(*(char*)dii.value == 3, *(char*)dii.value);
    FCF_TEST(dii.type == fcf::Type<char>().index(), dii.type, fcf::Type<char>().index());
    FCF_TEST(dii.size == 3, dii.size);

    res = resolver(&vec, &dii);
    FCF_TEST(res == false);
  }

  {
    typedef std::vector<int> container_type;
    container_type c;
    c.push_back(1);
    c.push_back(2);
    c.push_back(3);
    unsigned int typeIndex = fcf::Type<container_type>().index();
    const fcf::Details::TypeInfo* ti = fcf::Details::typeStorage.get(typeIndex);
    fcf::DynamicIteratorSpecificator::function_type resolver = ti->dynamicIteratorResolver;
    FCF_TEST((void*)resolver != 0, (void*)resolver)
    fcf::DynamicIteratorInfo dii;
    dii.flags = fcf::DIF_ITERATION | fcf::DIF_GET_KEY | fcf::DIF_GET_VALUE | fcf::DIF_GET_TYPE | fcf::DIF_GET_SIZE;
    size_t i = 0;
    int arr[3];
    while(resolver(&c, &dii)){
      arr[i] = *(int*)dii.value;
      ++i;
    }
    FCF_TEST(i, 3);
    FCF_TEST(arr[0], 1);
    FCF_TEST(arr[1], 2);
    FCF_TEST(arr[2], 3);

  }
}
