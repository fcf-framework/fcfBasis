#include <iostream>
#include <tuple>
#include <vector>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../bits/PartMetaType/MetaTypeSequence.hpp"
#include "../../../foreach.hpp"

namespace FcfTest {
  namespace BasisTest {

    namespace SequenceTest {

      template <int Index>
      struct Item {
        enum {index_value = Index};
      };

      template <int Start, int End>
      struct Filler{

        typedef std::vector<int> vector_type;

        void operator()(vector_type& a_container){
          container = &a_container;
          typedef typename fcf::MetaTypeSequence<Start, End>::type sequence_type;
          _call(sequence_type());
        }

        template <int ... SequencePack>
        void _call(fcf::MetaTypeSequence<SequencePack...> a_sequence){
          typedef std::tuple< Item<SequencePack>...  > tuple_type;
          tuple_type tuple;
          fcf::foreach(tuple, *this);
        }

        template <typename TTuple, typename TItem>
        void operator()(TTuple& a_container, size_t a_index, TItem a_item){
          container->push_back(TItem::index_value);
        }

        vector_type* container;
      };



    };

    void sequenceTest(){
      std::cout << "Start sequenceTest()..." << std::endl;

      {
        FcfTest::BasisTest::SequenceTest::Filler<0, 3> filler;
        std::vector<int> v;
        filler(v);
        size_t expsize = 3;
        FCF_TEST(v.size() == expsize, v.size(), expsize);
        for(size_t i = 0; i < expsize; ++i){
          FCF_TEST(v[i] == i, v[i], i);
        }
      }
      {
        FcfTest::BasisTest::SequenceTest::Filler<0, 2> filler;
        std::vector<int> v;
        filler(v);
        size_t expsize = 2;
        FCF_TEST(v.size() == expsize, v.size(), expsize);
        for(size_t i = 0; i < expsize; ++i){
          FCF_TEST(v[i] == i, v[i], i);
        }
      }
      {
        FcfTest::BasisTest::SequenceTest::Filler<0, 1> filler;
        std::vector<int> v;
        filler(v);
        size_t expsize = 1;
        FCF_TEST(v.size() == expsize, v.size(), expsize);
        for(size_t i = 0; i < expsize; ++i){
          FCF_TEST(v[i] == i, v[i], i);
        }
      }
      {
        FcfTest::BasisTest::SequenceTest::Filler<0, 0> filler;
        std::vector<int> v;
        filler(v);
        size_t expsize = 0;
        FCF_TEST(v.size() == expsize, v.size(), expsize);
      }


      {
        FcfTest::BasisTest::SequenceTest::Filler<1, 4> filler;
        std::vector<int> v;
        filler(v);
        size_t expsize = 3;
        FCF_TEST(v.size() == expsize, v.size(), expsize);
        for(size_t i = 0; i < expsize; ++i){
          FCF_TEST(v[i] == i+1, v[i], i+1);
        }
      }
      {
        FcfTest::BasisTest::SequenceTest::Filler<1, 3> filler;
        std::vector<int> v;
        filler(v);
        size_t expsize = 2;
        FCF_TEST(v.size() == expsize, v.size(), expsize);
        for(size_t i = 0; i < expsize; ++i){
          FCF_TEST(v[i] == i+1, v[i], i+1);
        }
      }
      {
        FcfTest::BasisTest::SequenceTest::Filler<1, 2> filler;
        std::vector<int> v;
        filler(v);
        size_t expsize = 1;
        FCF_TEST(v.size() == expsize, v.size(), expsize);
        for(size_t i = 0; i < expsize; ++i){
          FCF_TEST(v[i] == i+1, v[i], i+1);
        }
      }
      {
        FcfTest::BasisTest::SequenceTest::Filler<1, 1> filler;
        std::vector<int> v;
        filler(v);
        size_t expsize = 0;
        FCF_TEST(v.size() == expsize, v.size(), expsize);
      }

    }
  }
}


