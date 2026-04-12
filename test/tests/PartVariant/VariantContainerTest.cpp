#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace FcfTest {
  namespace BasisTest {

    FCF_TEST_DECLARE("fcfBasis", "Variant", "container variant"){
      {
        std::vector<int> vec = {1, 2, 3};
        fcf::Variant v(vec);
        FCF_TEST(v[0] == 1);
        FCF_TEST(v[1] == 2);
        FCF_TEST(v[2] == 3);
        FCF_TEST(!v[3].empty());

        vec[0] *= 10;
        FCF_TEST(v[0] == 1);
        FCF_TEST(vec[0] == 10);
      }
      {
        std::map<int, std::string> obj;
        obj[1] = "1-1";
        obj[2] = "2-1";
        fcf::Variant v(obj, fcf::Variant::REFERENCE);
        FCF_TEST(v[1] == "1-1", v[1]);
        FCF_TEST(v[2] == "2-1", v[2]);

        v[2] = "2-2";
        FCF_TEST(v[1] == "1-1", v[1]);
        FCF_TEST(obj[1] == "1-1", obj[1]);
        FCF_TEST(v[2] == "2-2", v[2]);
        FCF_TEST(obj[2] == "2-2", obj[2]);

        obj[2] = "2-3";
        FCF_TEST(v[1] == "1-1", v[1]);
        FCF_TEST(obj[1] == "1-1", obj[1]);
        FCF_TEST(v[2] == "2-3", v[2]);
        FCF_TEST(obj[2] == "2-3", obj[2]);

        v[3] = "3-1";
        FCF_TEST(v[1] == "1-1", v[1]);
        FCF_TEST(obj[1] == "1-1", obj[1]);
        FCF_TEST(v[2] == "2-3", v[2]);
        FCF_TEST(obj[2] == "2-3", obj[2]);
        FCF_TEST(v[3] == "3-1", v[3]);
        FCF_TEST(obj[3] == "3-1", obj[3]);

        {
          std::vector<std::string> list;
          for(auto value : v){
            list.push_back(value.cast<std::string>());
          }
          FCF_TEST(list.size() == 3, list.size());
          FCF_TEST(list[0] == "1-1", list[0]);
          FCF_TEST(list[1] == "2-3", list[1]);
          FCF_TEST(list[2] == "3-1", list[2]);
        }
        {
          std::vector< std::pair<int, std::string> > list;
          for(fcf::Variant::iterator it = v.begin(); it != v.end(); ++it){
            list.push_back({ it.key().cast<int>(), it.value().cast<std::string>() });
          }
          FCF_TEST(list.size() == 3, list.size());
          FCF_TEST(list[0].second == "1-1", list[0].second);
          FCF_TEST(list[0].first == 1, list[0].first);
          FCF_TEST(list[1].second == "2-3", list[1].second);
          FCF_TEST(list[1].first == 2, list[1].first);
          FCF_TEST(list[2].second == "3-1", list[2].second);
          FCF_TEST(list[2].first == 3, list[2].first);
        }
        {
          std::vector< std::pair<int, std::string> > list;
          for(fcf::Variant::const_iterator it = v.cbegin(); it != v.end(); ++it){
            list.push_back({ it.key().cast<int>(), it.value().cast<std::string>() });
          }
          FCF_TEST(list.size() == 3, list.size());
          FCF_TEST(list[0].second == "1-1", list[0].second);
          FCF_TEST(list[0].first == 1, list[0].first);
          FCF_TEST(list[1].second == "2-3", list[1].second);
          FCF_TEST(list[1].first == 2, list[1].first);
          FCF_TEST(list[2].second == "3-1", list[2].second);
          FCF_TEST(list[2].first == 3, list[2].first);
        }

        {
          std::vector< std::pair<int, std::string> > list;
          for(fcf::Variant::iterator it = v.begin(); it != v.end(); ++it){
            it.value() += "_";
            list.push_back({ it.key().cast<int>(), it.value().cast<std::string>() });
          }
          FCF_TEST(list.size() == 3, list.size());
          FCF_TEST(obj[1] == "1-1_", obj[1]);
          FCF_TEST(list[0].second == "1-1_", list[0].second);
          FCF_TEST(list[0].first == 1, list[0].first);
          FCF_TEST(obj[2] == "2-3_", obj[2]);
          FCF_TEST(list[1].second == "2-3_", list[1].second);
          FCF_TEST(list[1].first == 2, list[1].first);
          FCF_TEST(obj[3] == "3-1_", obj[3]);
          FCF_TEST(list[2].second == "3-1_", list[2].second);
          FCF_TEST(list[2].first == 3, list[2].first);
        }
        {
          auto it = v.cbegin();
          //it.value() = "123";
        }

      }

      {
        std::map<int, std::string> obj;
        obj[1] = "1-1";
        obj[2] = "2-1";
        fcf::Variant v(obj);
        FCF_TEST(v[1] == "1-1", v[1]);
        FCF_TEST(v[2] == "2-1", v[2]);

        v[2] = "2-2";

        FCF_TEST(v[1] == "1-1", v[1]);
        FCF_TEST(obj[1] == "1-1", obj[1]);
        FCF_TEST(v[2] == "2-2", v[2]);
        FCF_TEST(obj[2] == "2-1", obj[2]);

        v[3] = "3-1";
        FCF_TEST(obj.size() == 2, obj.size());
        FCF_TEST(v[1] == "1-1", v[1]);
        FCF_TEST(obj[1] == "1-1", obj[1]);
        FCF_TEST(v[2] == "2-2", v[2]);
        FCF_TEST(obj[2] == "2-1", obj[2]);
        FCF_TEST(v[3] == "3-1", v[3]);
      }

      {
        std::vector<int> vec = {1, 2, 3};
        fcf::Variant v(vec, fcf::Variant::REFERENCE);
        FCF_TEST(v[0] == 1);
        FCF_TEST(v[1] == 2);
        FCF_TEST(v[2] == 3);

        v[0] *= 10;
        FCF_TEST(v[0] == 10);
        FCF_TEST(vec[0] == 10);

        v[0] = 99;
        FCF_TEST(v[0] == 99, v[0]);
        FCF_TEST(vec[0] == 99, v[0]);

        v[1] *= 10;
        FCF_TEST(v[1] == 20);
        FCF_TEST(vec[1] == 20);
        v[2] *= 10;
        FCF_TEST(v[2] == 30);
        FCF_TEST(vec[2] == 30);

        vec.push_back(40);

        FCF_TEST(v[3] == 40);
        FCF_TEST(vec[3] == 40);

        FCF_TEST(!v[4].empty());
      }
      {
        fcf::Variant sourceVec       = std::vector<int>{1,2,3,4,5};
        fcf::Variant destinationList( fcf::Type< std::list<std::string> >{}  );
        FCF_TEST(destinationList.containerSize() == 0, destinationList.containerSize());
        for(size_t i = 0; i < sourceVec.containerSize(); ++i ){
          FCF_TEST(destinationList.containerSize() == i, i, destinationList.containerSize());
          destinationList[i] = sourceVec[i];
        }
        FCF_TEST(destinationList.containerSize() == 5, destinationList.containerSize());
        int counter = 1;
        for(fcf::Variant item : destinationList){
          std::string expected = std::to_string(counter);
          FCF_TEST(item == expected, item, expected);
          ++counter;
        }
      }
    }

  }
}


