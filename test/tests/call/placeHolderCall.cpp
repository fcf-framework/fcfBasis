#include <iostream>
#include "../../libraries/fcfTest/test.hpp"
#include "../../../call.hpp"
#include "../../../functions.hpp"
#include "../../../Type.hpp"
#include "../../../specificators.hpp"
#include "../../../basis.hpp"

#include "../../../bits/Call/Details/CallWrapper.hpp"

namespace FcfTest {
  namespace BasisTest {

    /*
    #define _FCF_DECLARE_FUNCTION__SELECTOR_NOP_FCF_DECLARE_FUNCTION__REM_PARENTHESIS_NOP__EMPTY_SELECTOR ::fcf::Nop
    #define _FCF_DECLARE_FUNCTION__SELECTOR_NOP_ON_FCF_DECLARE_FUNCTION__REM_PARENTHESIS_NOP__EMPTY_SELECTOR
    #define _FCF_DECLARE_FUNCTION__REM_PARENTHESIS_NOP__EMPTY_SELECTOR(...) _ON_FCF_DECLARE_FUNCTION__REM_PARENTHESIS_NOP__EMPTY_SELECTOR __VA_ARGS__
    #define _FCF_DECLARE_FUNCTION__REM_PARENTHESIS_NOP_0(...) _FCF_DECLARE_FUNCTION__SELECTOR_NOP##__VA_ARGS__
    #define _FCF_DECLARE_FUNCTION__REM_PARENTHESIS_NOP(...) _FCF_DECLARE_FUNCTION__REM_PARENTHESIS_NOP_0(__VA_ARGS__)

    #define _FCF_DECLARE_FUNCTION__SELECTOR_FCF_DECLARE_FUNCTION__REM_PARENTHESIS__EMPTY_SELECTOR
    #define _FCF_DECLARE_FUNCTION__REM_PARENTHESIS__EMPTY_SELECTOR(...) _FCF_DECLARE_FUNCTION__REM_PARENTHESIS__EMPTY_SELECTOR __VA_ARGS__
    #define _FCF_DECLARE_FUNCTION__REM_PARENTHESIS_0(...) _FCF_DECLARE_FUNCTION__SELECTOR##__VA_ARGS__
    #define _FCF_DECLARE_FUNCTION__REM_PARENTHESIS(...) _FCF_DECLARE_FUNCTION__REM_PARENTHESIS_0(__VA_ARGS__)

    #define _FCF_DECLARE_FUNCTION__SIGNATURE(a_arg) \
      typename ::fcf::ArgPlaceHolder::Signature< \
                                                a_signature, \
                                                ::fcf::Details::CallResultTypeGetter<a_signature>::type, \
                                                _FCF_DECLARE_FUNCTION__REM_PARENTHESIS_NOP(_FCF_DECLARE_FUNCTION__REM_PARENTHESIS_NOP__EMPTY_SELECTOR a_arg)\
                                                >::active_type

    #define _FCF_DECLARE_FUNCTION__RESOLVE_SIGNATURES_1(a_arg1, a_arg2, a_arg3, ...) \
      _FCF_DECLARE_FUNCTION__SIGNATURE(a_arg1),\
      _FCF_DECLARE_FUNCTION__SIGNATURE(a_arg2),\
      _FCF_DECLARE_FUNCTION__SIGNATURE(a_arg3)
    #define _FCF_DECLARE_FUNCTION__RESOLVE_SIGNATURES_0(...)\
              _FCF_DECLARE_FUNCTION__RESOLVE_SIGNATURES_1(__VA_ARGS__, , , )

    #define _FCF_DECLARE_FUNCTION__RESOLVE_SIGNATURES(a_placeHolder) \
      _FCF_DECLARE_FUNCTION__RESOLVE_SIGNATURES_0( _FCF_DECLARE_FUNCTION__REM_PARENTHESIS(_FCF_DECLARE_FUNCTION__REM_PARENTHESIS__EMPTY_SELECTOR a_placeHolder) )

    #define FCFTEST_STRINGIFY_2(...) #__VA_ARGS__
    #define FCFTEST_STRINGIFY_1(...) FCFTEST_STRINGIFY_2(__VA_ARGS__)
    #define FCFTEST_STRINGIFY_0(...) FCFTEST_STRINGIFY_1(__VA_ARGS__)
    #define FCFTEST_STRINGIFY(...) FCFTEST_STRINGIFY_0(__VA_ARGS__)
*/

    struct PHCTestDataItem{
      int value;
      int defaultValue;
      PHCTestDataItem()
        : value(0)
        , defaultValue(999){
      }
      PHCTestDataItem& operator=(int a_value){
        value = a_value;
        return *this;
      }
    };
  }
}

    namespace fcf {
      template <>
      struct Type<FcfTest::BasisTest::PHCTestDataItem, ValueSpecificator> {
        enum { enable = true };
        static void resolve(FcfTest::BasisTest::PHCTestDataItem& a_container, fcf::StaticVector<fcf::Variant, 4>& a_dst){
          a_dst.resize(1);
          a_dst[0] = a_container.defaultValue;
        }
      };
    }


    FCF_SPECIFICATOR_REGISTRY_FORCE(FcfTest::BasisTest::PHCTestDataItem, fcf::ValueSpecificator);

    FCF_TYPEID_REGISTRY_FORCE(FcfTest::BasisTest::PHCTestDataItem, "FcfTest::BasisTest::PHCTestDataItem",                           0);
    FCF_TYPEID_REGISTRY_FORCE(std::vector<FcfTest::BasisTest::PHCTestDataItem>, "std::vector<FcfTest::BasisTest::PHCTestDataItem>", 0);

    FCF_DECLARE_FUNCTION(fill, 
                       "engine_cpu", 
                       fcf::fill, 
                       void(*) (FcfTest::BasisTest::PHCTestDataItem*, FcfTest::BasisTest::PHCTestDataItem*, int),
                       ((fcf::ValueSpecificator, 1, FcfTest::BasisTest::PHCTestDataItem*, FcfTest::BasisTest::PHCTestDataItem*, fcf::Arg1)),
                      );

namespace FcfTest {
  namespace BasisTest {

    
    void function_test_1(int* a_a1, int a_a2, short a_a3){
      *a_a1 = a_a2;
    }
    void function_test_2(int* a_a1, int a_a2, short a_a3){
      *a_a1 = (int)a_a3;
    }
    
    void placeHolderCall(){
      std::cout << "Start placeHolderCall()..." << std::endl;
      
      {
        typedef void (function_type)(int*, int, short);
        fcf::Details::CallWrapper<function_type> c;
        void* cpa[4];
        int   a1data = 0;
        int*  a1 = &a1data;
        int   a2 = 2;
        short a3 = 3;
        cpa[0] = &a1;
        cpa[1] = &a2;
        cpa[2] = &a3;
        c.call(function_test_1, &cpa[0]);
        FCF_TEST(a1data == a2, a1data, a2);
        c.call(function_test_2, &cpa[0]);
        FCF_TEST(a1data == a3, a1data, a3);
          
        
      }
      /*
      {
        size_t val  = 999;
        size_t size = 10;
        std::vector<int> v(size);
        fcf::call("fill", v, val);
        FCF_TEST(v.size() == size, size, v.size());
        for(size_t i = 0; i < size; ++i){
          FCF_TEST(v[i] == val, i, val, v[i]);
        }
      }
    */
      /*
      {
        int val  = 999;
        size_t size = 10;
        std::vector<PHCTestDataItem> v(size);
        fcf::call("fill", v, val);
        for(auto itm : v){
          FCF_TEST(itm.value == val, itm.value, val);
        }
      }
      */
      
      {
        size_t size = 10;
        std::vector<PHCTestDataItem> v(size);
        std::cout << "v[0] ptr: " << (void*)&v[0] << std::endl;
        std::cout << "v[0] : " << v[0].value << std::endl;
        std::cout << "v[0] : " << v[0].defaultValue << std::endl;
        fcf::call("fill", v);
        for(auto itm : v){
          FCF_TEST(itm.value == itm.defaultValue, itm.value, itm.defaultValue);
        }
      }
      

    }

  } // BasisTest namespace
} // FcfTest namespace

