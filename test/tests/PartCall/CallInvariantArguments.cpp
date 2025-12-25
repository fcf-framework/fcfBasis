#include <iostream>
#include <exception>
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
          fcf::call(&dc, a_packArg...);
        }
      private:
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

} // fcf namespace

namespace FcfTest {
  namespace BasisTest {

    void callInvariantArgumentsTest (){
      std::cout << "Start callInvariantArgumentsTest()..." << std::endl;
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

    } // void callInvariantArgumentsTest() end

  }
}
