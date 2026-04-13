#include <iostream>
#include <vector>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

struct TupleTestFunc{
  std::string result;
  template <typename TIndex, typename TValue>
  void operator()(TIndex /*a_index*/, TValue& /*a_value*/){
    if (!result.empty()){
      result += "|";
    }
    result += fcf::Type<TValue>().name();
  }
};

FCF_TEST_DECLARE("fcfBasis", "MetaType", "modify typle metatype"){
  // insert test
  {
    typedef std::tuple<> ttype;
    typedef typename fcf::MetaTypeTupleInsert<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float", ttf.result);
  }
  {
    typedef std::tuple<char> ttype;
    typedef typename fcf::MetaTypeTupleInsert<ttype, float, 1>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|float", ttf.result);
  }
  {
    typedef std::tuple<char> ttype;
    typedef typename fcf::MetaTypeTupleInsert<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float|char", ttf.result);
  }
  {
    typedef std::tuple<char, short> ttype;
    typedef typename fcf::MetaTypeTupleInsert<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float|char|short", ttf.result);
  }
  {
    typedef std::tuple<char, short> ttype;
    typedef typename fcf::MetaTypeTupleInsert<ttype, float, 1>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|float|short", ttf.result);
  }
  {
    typedef std::tuple<char, short> ttype;
    typedef typename fcf::MetaTypeTupleInsert<ttype, float, 2>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|short|float", ttf.result);
  }

  // replace test
  {
    typedef std::tuple<char> ttype;
    typedef typename fcf::MetaTypeTupleReplace<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float", ttf.result)
  }
  {
    typedef std::tuple<char, short> ttype;
    typedef typename fcf::MetaTypeTupleReplace<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float|short", ttf.result)
  }
  {
    typedef std::tuple<char, short> ttype;
    typedef typename fcf::MetaTypeTupleReplace<ttype, float, 1>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|float", ttf.result)
  }

  {
    typedef std::tuple<char, short, int> ttype;
    typedef typename fcf::MetaTypeTupleReplace<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float|short|int", ttf.result)
  }
  {
    typedef std::tuple<char, short, int> ttype;
    typedef typename fcf::MetaTypeTupleReplace<ttype, float, 1>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|float|int", ttf.result)
  }
  {
    typedef std::tuple<char, short, int> ttype;
    typedef typename fcf::MetaTypeTupleReplace<ttype, float, 2>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|short|float", ttf.result)
  }
  {
    typedef std::tuple<char, short> ttype;
    typedef typename fcf::MetaTypeTupleReplace<ttype, float, 1>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "char|float", ttf.result)
  }
  {
    typedef std::tuple<char, short> ttype;
    typedef typename fcf::MetaTypeTupleReplace<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float|short", ttf.result)
  }
  {
    typedef std::tuple<char> ttype;
    typedef typename fcf::MetaTypeTupleReplace<ttype, float, 0>::type rtype;
    TupleTestFunc ttf;
    rtype tuple;
    fcf::foreach(tuple, ttf);
    FCF_TEST(ttf.result == "float", ttf.result)
  }
}
