#include <iostream>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"


namespace FcfTest { 
  namespace BasisTest { 
    namespace ForeachTest {

      template <typename TKey, typename TValue, typename TKeys, typename TValues>
      void tupleHandler(TKey a_key, TValue /*a_item*/, TKeys& a_keys, TValues& a_values) {
        a_keys.push_back(a_key);
        a_values.push_back( fcf::Type<TValue>().name() );
      }

      FCF_FOREACH_FUNCTION_WRAPPER(TupleHandlerForeachFunctionWrapper, tupleHandler);

      struct TupleHandler0 {
        template <typename TKey, typename TValue, typename TKeys, typename TValues>
        void operator()(TKey a_key, TValue /*a_item*/, TKeys& a_keys, TValues& a_values) {
          a_keys.push_back(a_key);
          a_values.push_back( fcf::Type<TValue>().name() );
        }
      };

      struct TupleHandler {
        template <typename TKey, typename TValue, typename TKeys, typename TValues>
        void iteration(TKey a_key, TValue /*a_item*/, TKeys& a_keys, TValues& a_values) {
          a_keys.push_back(a_key);
          a_values.push_back( fcf::Type<TValue>().name() );
        }
      };

      FCF_FOREACH_METHOD_WRAPPER(TupleHandlerForeachMethodWrapper, TupleHandler, iteration)
    }
  }
}



namespace FcfTest { 
  namespace BasisTest { 
    namespace ForeachTest {

      struct Container {

        std::string& operator[](size_t a_index){
          return vector[a_index];
        }

        size_t size(){
          return vector.size();
        }

        std::vector<std::string> vector;
      };
    } // ForeachTest namespace
  } // BasisTest namespace
} // FcfTest namespace

namespace fcf {

  template <>
  struct Cursor< FcfTest::BasisTest::ForeachTest::Container > : public FlatCursor<FcfTest::BasisTest::ForeachTest::Container> {
    typedef FlatCursor<FcfTest::BasisTest::ForeachTest::Container> BaseType;
    using BaseType::FlatCursor;
  };

} // fcf namespace


FCF_TYPEID_REGISTRY(FcfTest::BasisTest::ForeachTest::Container, "FcfTest::BasisTest::ForeachTest::Container", 0);
FCF_SPECIFICATOR_REGISTRY(FcfTest::BasisTest::ForeachTest::Container,  fcf::ContainerAccessSpecificator);


namespace FcfTest { 
  namespace BasisTest { 
    namespace ForeachTest {
      template <typename Ty>
      struct Vector : public std::vector<Ty> {
        using std::vector<Ty>::vector;
      };
    }
  }
}

namespace FcfTest {
  namespace BasisTest {

    FCF_TEST_DECLARE("fcfBasis", "Foreach", "foreach"){
      {
        std::vector<size_t>                                   keys;
        std::vector<std::string>                              values;
        FcfTest::BasisTest::ForeachTest::Vector<std::string>  container;
        container.push_back("001");
        container.push_back("002");
        fcf::foreach(
          container,
          [](size_t a_key, std::string& a_value, std::vector<size_t>& a_keys, std::vector<std::string>& a_values){
            a_keys.push_back(a_key);
            a_values.push_back(a_value);
            a_value += "-";
            a_value += fcf::convert<std::string>(a_key);
          }, 
          keys, values);
        FCF_TEST(keys.size() == 2, keys.size());
        FCF_TEST(keys[0] == 0 && keys[1] == 1, keys[0], keys[1]);
        FCF_TEST(values[0] == "001" && values[1] == "002", values[0], values[1]);
        FCF_TEST(container[0] == "001-0" && container[1] == "002-1", container[0], container[1]);
      }
      {
        std::vector<size_t>                           keys;
        std::vector<std::string>                      values;
        std::tuple<int, char, short>                  tuple;
        fcf::foreach(tuple, FcfTest::BasisTest::ForeachTest::TupleHandlerForeachFunctionWrapper(), keys, values);
        FCF_TEST(keys.size() == 3, keys.size());
        FCF_TEST(keys[0] == 0 && keys[1] == 1 && keys[2] == 2, keys[0], keys[1], keys[1]);
        FCF_TEST(values[0] == "int" && values[1] == "char" && values[2] == "short", values[0], values[1], values[2]);
      }
      {
        std::vector<size_t>                           keys;
        std::vector<std::string>                      values;
        FcfTest::BasisTest::ForeachTest::TupleHandler ft;
        std::tuple<int, char, short>                  tuple;
        fcf::foreach(tuple, FcfTest::BasisTest::ForeachTest::TupleHandlerForeachMethodWrapper(ft), keys, values);
        FCF_TEST(keys.size() == 3, keys.size());
        FCF_TEST(keys[0] == 0 && keys[1] == 1 && keys[2] == 2, keys[0], keys[1], keys[1]);
        FCF_TEST(values[0] == "int" && values[1] == "char" && values[2] == "short", values[0], values[1], values[2]);
      }
      {
        std::vector<size_t>                           keys;
        std::vector<std::string>                      values;
        std::tuple<int, char, short>                  tuple;
        fcf::foreach(tuple, FcfTest::BasisTest::ForeachTest::TupleHandlerForeachMethodWrapper(FcfTest::BasisTest::ForeachTest::TupleHandler()), keys, values);
        FCF_TEST(keys.size() == 3, keys.size());
        FCF_TEST(keys[0] == 0 && keys[1] == 1 && keys[2] == 2, keys[0], keys[1], keys[1]);
        FCF_TEST(values[0] == "int" && values[1] == "char" && values[2] == "short", values[0], values[1], values[2]);
      }
      {
        std::vector<size_t>                           keys;
        std::vector<std::string>                      values;
        std::tuple<int, char, short>                  tuple;
        fcf::foreach(tuple, FcfTest::BasisTest::ForeachTest::TupleHandler0(), keys, values);
        FCF_TEST(keys.size() == 3, keys.size());
        FCF_TEST(keys[0] == 0 && keys[1] == 1 && keys[2] == 2, keys[0], keys[1], keys[1]);
        FCF_TEST(values[0] == "int" && values[1] == "char" && values[2] == "short", values[0], values[1], values[2]);
      }
      {
        std::vector<size_t>       keys;
        std::vector<std::string>  values;
        ForeachTest::Container    container;
        container.vector.push_back("001");
        container.vector.push_back("002");
        fcf::foreach(container, [](size_t a_key, std::string& a_value, std::vector<size_t>& a_keys, std::vector<std::string>& a_values){
          a_keys.push_back(a_key);
          a_values.push_back(a_value);
          a_value += "-";
          a_value += fcf::convert<std::string>(a_key);
        }, keys, values);
        FCF_TEST(keys.size() == 2, keys.size());
        FCF_TEST(keys[0] == 0 && keys[1] == 1, keys[0], keys[1]);
        FCF_TEST(values[0] == "001" && values[1] == "002", values[0], values[1]);
        FCF_TEST(container.vector[0] == "001-0" && container.vector[1] == "002-1", container.vector[0], container.vector[1]);
      }
      {
        typedef std::list<std::string> container_type;
        std::vector<size_t>       keys;
        std::vector<std::string>  values;
        container_type    container;
        container.push_back("001");
        container.push_back("002");
        fcf::foreach(container, [](size_t a_key, std::string& a_value, std::vector<size_t>& a_keys, std::vector<std::string>& a_values){
          a_keys.push_back(a_key);
          a_values.push_back(a_value);
          a_value += "-";
          a_value += fcf::convert<std::string>(a_key);
        }, keys, values);
        FCF_TEST(keys.size() == 2, keys.size());
        FCF_TEST(keys[0] == 0 && keys[1] == 1, keys[0], keys[1]);
        FCF_TEST(values[0] == "001" && values[1] == "002", values[0], values[1]);
        FCF_TEST(*container.begin() == "001-0" && *(++container.begin()) == "002-1", *(container.begin()), *(++container.begin()));
      }
      {
        typedef std::set<std::string> container_type;
        std::vector<std::string>  keys;
        std::vector<std::string>  values;
        container_type    container;
        container.insert("001");
        container.insert("002");
        fcf::foreach(container, [](const std::string& a_key, const std::string& a_value, std::vector<std::string>& a_keys, std::vector<std::string>& a_values){
          a_keys.push_back(a_key);
          a_values.push_back(a_value);
        }, keys, values);
        FCF_TEST(keys.size() == 2, keys.size());
        FCF_TEST(keys[0] == "001" && keys[1] == "002", keys[0], keys[1]);
        FCF_TEST(values[0] == "001" && values[1] == "002", values[0], values[1]);
        FCF_TEST(*container.begin() == "001" && *(++container.begin()) == "002", *(container.begin()), *(++container.begin()));
      }
      {
        std::vector<size_t>       keys;
        std::vector<std::string>  values;
        std::vector<std::string>  vec = { "001", "002" };
        fcf::foreach(vec, [](size_t a_key, std::string& a_value, std::vector<size_t>& a_keys, std::vector<std::string>& a_values){
          a_keys.push_back(a_key);
          a_values.push_back(a_value);
          a_value += "-";
          a_value += fcf::convert<std::string>(a_key);
        }, keys, values);
        FCF_TEST(keys.size() == 2, keys.size());
        FCF_TEST(keys[0] == 0 && keys[1] == 1, keys[0], keys[1]);
        FCF_TEST(values[0] == "001" && values[1] == "002", values[0], values[1]);
        FCF_TEST(vec[0] == "001-0" && vec[1] == "002-1", vec[0], vec[1]);
      }
      {
        std::vector<std::string> keys;
        std::vector<int>         values;
        std::map<std::string, int> map = { {"001", 1}, {"002", 2} };
        fcf::foreach(map, [&keys, &values](std::string a_key, int& a_value){
          keys.push_back(a_key);
          values.push_back(a_value);
          a_value += 3;
        });
        FCF_TEST(keys.size() == 2, keys.size());
        FCF_TEST(keys[0] == "001" && keys[1] == "002", keys[0], keys[1]);
        FCF_TEST(values[0] == 1 && values[1] == 2, values[0], values[1]);
        FCF_TEST(map["001"] == 4 && map["002"] == 5, map["001"], map["002"]);
      }
      {
        std::vector<std::string> keys;
        std::vector<int>         values;
        std::map<std::string, int> map = { {"001", 1}, {"002", 2} };
        fcf::foreach(map, [](std::string a_key, int& a_value, std::vector<std::string>* a_keys, std::vector<int>* a_values){
          a_keys->push_back(a_key);
          a_values->push_back(a_value);
          a_value += 3;
        }, &keys, &values);
        FCF_TEST(keys.size() == 2, keys.size());
        FCF_TEST(keys[0] == "001" && keys[1] == "002", keys[0], keys[1]);
        FCF_TEST(values[0] == 1 && values[1] == 2, values[0], values[1]);
        FCF_TEST(map["001"] == 4 && map["002"] == 5, map["001"], map["002"]);
      }
      {
        std::vector<std::string> keys;
        std::vector<int>         values;
        std::map<std::string, int> map = { {"001", 1}, {"002", 2} };
        fcf::foreach(map, [](std::string a_key, int& a_value, std::vector<std::string>& a_keys, std::vector<int>& a_values){
          a_keys.push_back(a_key);
          a_values.push_back(a_value);
          a_value += 3;
        }, keys, values);
        FCF_TEST(keys.size() == 2, keys.size());
        FCF_TEST(values.size() == 2, values.size());
        FCF_TEST(keys[0] == "001" && keys[1] == "002", keys[0], keys[1]);
        FCF_TEST(values[0] == 1 && values[1] == 2, values[0], values[1]);
        FCF_TEST(map["001"] == 4 && map["002"] == 5, map["001"], map["002"]);
      }
      {
        std::vector<std::string> keys;
        std::vector<int>         values;
        fcf::foreach(std::map<std::string, int>{ {"001", 1}, {"002", 2} }, [](std::string a_key, int& a_value, std::vector<std::string>& a_keys, std::vector<int>& a_values){
          a_keys.push_back(a_key);
          a_values.push_back(a_value);
          a_value += 3;
        }, keys, values);
        FCF_TEST(keys.size() == 2, keys.size());
        FCF_TEST(values.size() == 2, values.size());
        FCF_TEST(keys[0] == "001" && keys[1] == "002", keys[0], keys[1]);
        FCF_TEST(values[0] == 1 && values[1] == 2, values[0], values[1]);
      }

    }
  } // BasisTest namespace
} // FcfTest namespace
