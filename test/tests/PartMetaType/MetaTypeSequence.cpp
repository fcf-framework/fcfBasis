#include <iostream>
#include <vector>
#include <exception>
#include "../../libraries/fcfTest/test.hpp"
//#include "../../../basis.hpp"
#include "../../bits/PartMetaType/MetaTypeSequence.hpp"

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
        void _call(fcf::MetaTypeSequence<SequencePack...> /*a_sequence*/){
          iteration((const Item<SequencePack>*)((void*)(long)0xffffffff)...);
          /*
          typedef std::tuple< Item<SequencePack>...  > tuple_type;
          tuple_type tuple;
          fcf::foreach(tuple, *this);
          */
        }

        template <typename TItem, typename ...TArgPack>
        void iteration(const TItem*, const TArgPack*... a_packArg){
          container->push_back(TItem::index_value);
          iteration(a_packArg...);
        }

        template <typename TItem>
        void iteration(const TItem*){
          container->push_back(TItem::index_value);
        }

        void iteration(){
        }

        template <typename TTuple, typename TItem>
        void operator()(TTuple& /*a_container*/, size_t /*a_index*/, TItem /*a_item*/){
          container->push_back(TItem::index_value);
        }

        vector_type* container;
      };



    };

    FCF_TEST_DECLARE("fcfBasis", "MetaType", "sequence metatype"){
      {
        FcfTest::BasisTest::SequenceTest::Filler<0, 3> filler;
        std::vector<int> v;
        filler(v);
        int expsize = 3;
        for(size_t i = 0; i < v.size(); ++i){
          FCF_TEST(v[i] == (int)i, v[i], i);
        }
        FCF_TEST((int)v.size() == expsize, v.size(), expsize);
      }
      {
        FcfTest::BasisTest::SequenceTest::Filler<0, 2> filler;
        std::vector<int> v;
        filler(v);
        size_t expsize = 2;
        FCF_TEST(v.size() == expsize, v.size(), expsize);
        for(size_t i = 0; i < expsize; ++i){
          FCF_TEST((size_t)v[i] == i, v[i], i);
        }
      }
      {
        FcfTest::BasisTest::SequenceTest::Filler<0, 1> filler;
        std::vector<int> v;
        filler(v);
        size_t expsize = 1;
        FCF_TEST(v.size() == expsize, v.size(), expsize);
        for(size_t i = 0; i < expsize; ++i){
          FCF_TEST((size_t)v[i] == i, v[i], i);
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
          FCF_TEST((size_t)v[i] == i+1, v[i], i+1);
        }
      }
      {
        FcfTest::BasisTest::SequenceTest::Filler<1, 3> filler;
        std::vector<int> v;
        filler(v);
        size_t expsize = 2;
        FCF_TEST(v.size() == expsize, v.size(), expsize);
        for(size_t i = 0; i < expsize; ++i){
          FCF_TEST((size_t)v[i] == i+1, v[i], i+1);
        }
      }
      {
        FcfTest::BasisTest::SequenceTest::Filler<1, 2> filler;
        std::vector<int> v;
        filler(v);
        size_t expsize = 1;
        FCF_TEST(v.size() == expsize, v.size(), expsize);
        for(size_t i = 0; i < expsize; ++i){
          FCF_TEST((size_t)v[i] == i+1, v[i], i+1);
        }
      }
      {
        FcfTest::BasisTest::SequenceTest::Filler<1, 1> filler;
        std::vector<int> v;
        filler(v);
        size_t expsize = 0;
        FCF_TEST(v.size() == expsize, v.size(), expsize);
      }

      {
        FcfTest::BasisTest::SequenceTest::Filler<1, 0> filler;
        std::vector<int> v;
        filler(v);
        size_t expsize = 0;
        FCF_TEST(v.size() == expsize, v.size(), expsize);
      }

    }

  }
}

