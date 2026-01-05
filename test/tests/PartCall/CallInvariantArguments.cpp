#include <iostream>
#include <exception>
#include <chrono>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../basis.hpp"

namespace fcf {

  namespace NDetails {

    template <typename Ty, typename = void>
    struct CallBuildBufferIsInvariantItem {
      enum { value = false };
    };

    template <typename Ty>
    struct CallBuildBufferIsInvariantItem<Ty, decltype((void)::fcf::Type<Ty, ::fcf::ResolveSpecificator>::invariant_value )> {
      enum { value = ::fcf::Type<Ty, ::fcf::ResolveSpecificator>::invariant_value };
    };


    template <typename ...TPackArg>
    struct CallBuildBufferIsInvariant {
      enum { invariant_value = false };
    };

    template <typename TArg, typename ...TPackArg>
    struct CallBuildBufferIsInvariant<TArg, TPackArg...> {
      typedef typename std::remove_const< typename std::remove_reference< TArg>::type >::type type;
      enum { invariant_value = CallBuildBufferIsInvariantItem<type>::value | CallBuildBufferIsInvariant<TPackArg...>::invariant_value  };
    };

    template <bool IsInvariant, typename ...TPackArg>
    class CallBuildBufferHandler{
      public:
        template <typename ...TInputPackArg>
        CallBuildBufferHandler(const char* a_functionName, TInputPackArg&&... a_packArg) {
          fcf::CallSeeker<void, TPackArg...>()(a_functionName, &_call, a_packArg...);
        }

        template <typename ...TInputPackArg>
        inline void operator()(TInputPackArg&&... a_packArg){
          fcf::call(&_call, a_packArg...);
        }

      private:
        fcf::Call _call;
    };

    template <typename ...TPackArg>
    struct CallBuildBufferHandler<true, TPackArg...>{
      public:
        template <typename ...TInputPackArg>
        CallBuildBufferHandler(const char* a_functionName, TInputPackArg&&... /*a_packArg*/)
          : _functionName(a_functionName){
        }

        template <typename ...TInputPackArg>
        inline void operator()(TInputPackArg&&... a_packArg){
          fcf::Call dc;
          fcf::CallSeeker<void, TPackArg...>()(_functionName.c_str(), &dc, a_packArg...);
          _addToGraph(dc, _graph);
          
          //bool complete = false;
          //Caller().call(complete, _graph, a_packArg...);
          
          fcf::call(&dc, a_packArg...);
        }
      private:

        void _addToGraph(const Call& a_call, Caller::CallGraph& a_graph){
          Caller::ConversionsNode* node = &a_graph.conversions;
          Call* lastDstCall  = &a_graph.conversions.call;
          for(const CallConversion& conversion : a_call.conversions){
            Caller::KeyNode ca{conversion.index, conversion.sourceIndex, conversion.mode};
            auto insertIt = node->conversions.insert({ca, Caller::TypeNode()});
            Caller::TypeNode* typesConversion = &insertIt.first->second;
            auto insertTypeIt = typesConversion->types.insert({conversion.type, Caller::ConversionsNode()});
            lastDstCall = &insertTypeIt.first->second.call;
            node = &insertTypeIt.first->second;
          }
          *lastDstCall = a_call;
        }
        Caller::CallGraph _graph;
        std::string _functionName;
    };

  } // NDetails namespace


  template <typename ...TPackArg>
  class CallBuildBuffer {
    public:
      enum { invariant_value = NDetails::CallBuildBufferIsInvariant<TPackArg...>::invariant_value };

      template <typename ...TInputPackArg>
      CallBuildBuffer(const char* a_functionName, TInputPackArg&&... a_packArg)
        : _handler(a_functionName, a_packArg...) {
      }

      template <typename ...TInputPackArg>
      inline void operator()(TInputPackArg&&... a_packArg){
        _handler(a_packArg...);
      }
    private:
      NDetails::CallBuildBufferHandler< invariant_value, TPackArg... > _handler;
  };

  template <typename ...TPackArg>
  void fill(TPackArg&&... a_packArg){
    static CallBuildBuffer<TPackArg...> builder("fill", a_packArg...);
    builder(a_packArg...);
  }

  namespace Test {

    class Duration {
      public:
        Duration(unsigned long long a_iterations)
          : _iterations(a_iterations){
        }

        Duration()
          : _iterations(1){
        }

        unsigned long long iterations(){
          return _iterations;
        }

        void begin(){
          _start = std::chrono::high_resolution_clock::now();
        }

        void end(){
          _end = std::chrono::high_resolution_clock::now();
        }

        template <typename TFunctor>
        void operator()(TFunctor&& a_functor){
          begin();
          for(unsigned long long i = 0; i < _iterations; ++i) {
            a_functor();
          }
          end();
        }

        std::chrono::nanoseconds totalDuration(){
          return std::chrono::duration_cast<std::chrono::nanoseconds>(_end - _start);
        }

        std::chrono::nanoseconds duration(){
          return std::chrono::duration_cast<std::chrono::nanoseconds>(_end - _start) / _iterations;
        }

      private:
        unsigned long long                              _iterations;
        std::chrono::high_resolution_clock::time_point _start;
        std::chrono::high_resolution_clock::time_point _end;
    };

  }

} // fcf namespace

//void filling(int* a_begin, int* a_end, int a_value);

namespace FcfTest {
  namespace BasisTest {

    void callInvariantArgumentsTest (){
      std::cout << "Start callInvariantArgumentsTest()..." << std::endl;

      //unsigned long long iterations = 1000000;
      unsigned long long iterations = 10000;
      {
        std::vector<unsigned int> v = {1,2,3,4};
        fcf::fill(&v[0], &v[v.size()], 999.1);
        FCF_TEST(v.size() == 4, v.size());
        FCF_TEST(v[0] == 999, v[0]);
        FCF_TEST(v[1] == 999, v[1]);
        FCF_TEST(v[2] == 999, v[2]);
        FCF_TEST(v[3] == 999, v[3]);
      }
      {
        unsigned int value = 1;
        unsigned int* pvalue1 = &value;
        int* pvalue2 = 0;
        fcf::convertRuntimeByDestination(&pvalue2, &pvalue1, fcf::Type<unsigned int*>().index());
        FCF_TEST((void*)pvalue1 == (void*)pvalue2, pvalue1, pvalue2);
      }
      /*
      {
        std::vector<unsigned int> v = {1,2,3,4};
        fcf::fill(v, 999.1);
        FCF_TEST(v.size() == 4, v.size());
        FCF_TEST(v[0] == 999, v[0]);
        FCF_TEST(v[1] == 999, v[1]);
        FCF_TEST(v[2] == 999, v[2]);
        FCF_TEST(v[3] == 999, v[3]);
      }
      */
      {
        std::vector<int> v = {1,2,3,4};
        fcf::fill(v, 999.1);
        FCF_TEST(v.size() == 4, v.size());
        FCF_TEST(v[0] == 999, v[0]);
        FCF_TEST(v[1] == 999, v[1]);
        FCF_TEST(v[2] == 999, v[2]);
        FCF_TEST(v[3] == 999, v[3]);
      }
      {
        std::vector<int> v = {1,2,3,4};
        fcf::Variant variant(v, fcf::Variant::REFERENCE);
        fcf::fill(variant, 999.1);
        FCF_TEST(v.size() == 4, v.size());
        FCF_TEST(v[0] == 999, v[0]);
        FCF_TEST(v[1] == 999, v[1]);
        FCF_TEST(v[2] == 999, v[2]);
        FCF_TEST(v[3] == 999, v[3]);
      }

      {
        std::vector<int> v = {1,2,3,4};
        fcf::Test::Duration duration(iterations);
        duration.begin();
        for(size_t i = 0; i < duration.iterations(); ++i) {
          fcf::fill(v, 999);
        }
        duration.end();
        std::cout << "Duration: " << duration.duration().count() << "; total: " << duration.totalDuration().count() << "ns " << std::endl;
        FCF_TEST(v.size() == 4, v.size());
        FCF_TEST(v[0] == 999, v[0]);
        FCF_TEST(v[1] == 999, v[1]);
        FCF_TEST(v[2] == 999, v[2]);
        FCF_TEST(v[3] == 999, v[3]);
      }
      {
        std::vector<int> v = {1,2,3,4};
        fcf::Variant variant(v, fcf::Variant::REFERENCE);

        fcf::Test::Duration duration(iterations);
        duration([&variant](){
          fcf::fill(variant, 999.1);
        });
        std::cout << "Duration: " << duration.duration().count() << "; total: " << duration.totalDuration().count() << "ns " << std::endl;

        fcf::fill(variant, 999.1);
        FCF_TEST(v.size() == 4, v.size());
        FCF_TEST(v[0] == 999, v[0]);
        FCF_TEST(v[1] == 999, v[1]);
        FCF_TEST(v[2] == 999, v[2]);
        FCF_TEST(v[3] == 999, v[3]);
      }

      {
        std::vector<int> v = {1,2,3,4};
        fcf::Variant variant(v, fcf::Variant::REFERENCE);

        fcf::Test::Duration duration(iterations);
        duration.begin();
          for(size_t i = 0; i < duration.iterations(); ++i) {
            fcf::fill(variant, 999.1);
          }
        duration.end();
        std::cout << "Duration: " << duration.duration().count() << "; total: " << duration.totalDuration().count() << "ns " << std::endl;

        fcf::fill(variant, 999.1);
        FCF_TEST(v.size() == 4, v.size());
        FCF_TEST(v[0] == 999, v[0]);
        FCF_TEST(v[1] == 999, v[1]);
        FCF_TEST(v[2] == 999, v[2]);
        FCF_TEST(v[3] == 999, v[3]);
      }

    } // void callInvariantArgumentsTest() end

  }
}
