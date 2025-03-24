#include <iostream>

#include "../../libraries/fcfTest/test.hpp"

#include "../../../ArgPlaceHolder.hpp"

#include "../../../bits/functions/fill.hpp"

void deepIndexCallInner(){
  std::cout << "Start deepIndexCallInner..." << std::endl;
  {
    {
      typedef typename fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<0, int, float, double>::type type;
      FCF_TEST(fcf::Type<type>().name() == "int", fcf::Type<type>().name());
    }
    {
      typedef typename fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<0, fcf::Arg1, int, float>::type type;
      FCF_TEST(fcf::Type<type>().name() == "int", fcf::Type<type>().name());
    }
    {
      typedef typename fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<1, fcf::Arg1, int, float>::type type;
      FCF_TEST(fcf::Type<type>().name() == "float", fcf::Type<type>().name());
    }
    {
      typedef typename fcf::Details::Basis::ArgPlaceHolder::RemovePlaceHolderByIndex<2, fcf::Arg1, int, float>::type type;
      FCF_TEST(fcf::Type<type>().name() == "fcf::Nop", fcf::Type<type>().name());
    }
  }
  {
    ::fcf::ArgPlaceHolder::Arguments<void (int, std::string)>::type2 value1 = "test1";
    FCF_TEST(value1 == "test1", value1);
  }
  {
    typedef typename fcf::ArgPlaceHolder::RemovePlaceHolder<void (int, fcf::Arg1)> phtype;
    FCF_TEST(fcf::Type<phtype::type1>().name() == "int", fcf::Type<phtype::type1>().name());
    FCF_TEST(fcf::Type<phtype::type2>().name() == "fcf::Nop", fcf::Type<phtype::type2>().name());
    typedef void (*test_function_type)(int);
    FCF_TEST((std::is_same<test_function_type, phtype::function_type>::value));
  }
  {
    typedef typename fcf::ArgPlaceHolder::RemovePlaceHolder<void (fcf::Arg1, int)> phtype;
    FCF_TEST(fcf::Type<phtype::type1>().name() == "int", fcf::Type<phtype::type1>().name());
    FCF_TEST(fcf::Type<phtype::type2>().name() == "fcf::Nop", fcf::Type<phtype::type2>().name());
    typedef void (*test_function_type)(int);
    FCF_TEST((std::is_same<test_function_type, phtype::function_type>::value));
  }
  {
    typedef typename fcf::ArgPlaceHolder::RemovePlaceHolder<void (int)> phtype;
    FCF_TEST(fcf::Type<phtype::type1>().name() == "int", fcf::Type<phtype::type1>().name());
    FCF_TEST(fcf::Type<phtype::type2>().name() == "fcf::Nop", fcf::Type<phtype::type2>().name());
    typedef void (*test_function_type)(int);
    FCF_TEST((std::is_same<test_function_type, phtype::function_type>::value));
  }
  {
    typedef typename fcf::ArgPlaceHolder::RemovePlaceHolder<void (int, fcf::Arg1, int)> phtype;
    FCF_TEST(fcf::Type<phtype::type1>().name() == "int", fcf::Type<phtype::type1>().name());
    FCF_TEST(fcf::Type<phtype::type2>().name() == "int", fcf::Type<phtype::type2>().name());
    FCF_TEST(fcf::Type<phtype::type3>().name() == "fcf::Nop", fcf::Type<phtype::type3>().name());
    typedef void (*test_function_type)(int, int);
    FCF_TEST((std::is_same<test_function_type, phtype::function_type>::value));
  }
  {
    typedef typename fcf::ArgPlaceHolder::RemovePlaceHolder<void (fcf::Arg1)> phtype;
    FCF_TEST(fcf::Type<phtype::type1>().name() == "fcf::Nop", fcf::Type<phtype::type1>().name());
    typedef void (*test_function_type)();
    FCF_TEST((std::is_same<test_function_type, phtype::function_type>::value));
  }
  {
    typedef fcf::Variant VariantArray[3];
    VariantArray variant;
    variant[0] = 1001;
    variant[1] = 1002;
    variant[2] = 1003;
    int a1 = 1;
    int a2 = 2;

    {
      typedef ::fcf::ArgPlaceHolder::Arguments<void(int, fcf::Arg1)>                      template_args_type;
      typedef fcf::Details::Basis::ArgPlaceHolder::ArgResolver<0, template_args_type, int, int>  getter1_type;
      FCF_TEST(getter1_type::call(variant, a1) == 1, getter1_type::call(variant, a1));
    }
    {
      typedef ::fcf::ArgPlaceHolder::Arguments<void(int, fcf::Arg1)>                      template_args_type;
      typedef fcf::Details::Basis::ArgPlaceHolder::ArgResolver<1, template_args_type, int, int>  getter2_type;
      FCF_TEST(getter2_type::call(variant, a1) == 1001, getter2_type::call(variant, a1));
    }
    {
      typedef ::fcf::ArgPlaceHolder::Arguments<void(int, fcf::Arg2)>                      template_args_type;
      typedef fcf::Details::Basis::ArgPlaceHolder::ArgResolver<1, template_args_type, int, int>  getter2_type;
      FCF_TEST(getter2_type::call(variant, a1) == 1002, getter2_type::call(variant, a1));
    }

  }

  {
    typedef fcf::Variant VariantArray[3];
    VariantArray variant;
    variant[0] = 1001;
    variant[1] = 1002;
    variant[2] = 1003;
    int a1 = 1;
    int a2 = 2;
    {
      typedef ::fcf::ArgPlaceHolder::Arguments<void(int, fcf::Arg1, int)>                             template_args_type;
      typedef fcf::Details::Basis::ArgPlaceHolder::ArgResolver<0, template_args_type, int, int, int>  getter_type;
      FCF_TEST(getter_type::call(variant, a1, a2) == 1, getter_type::call(variant, a1, a2));
    }
    {
      typedef ::fcf::ArgPlaceHolder::Arguments<void(int, fcf::Arg1, int)>                             template_args_type;
      typedef fcf::Details::Basis::ArgPlaceHolder::ArgResolver<1, template_args_type, int, int, int>  getter_type;
      FCF_TEST(getter_type::call(variant, a1, a2) == 1001, getter_type::call(variant, a1, a2));
    }
    {
      typedef ::fcf::ArgPlaceHolder::Arguments<void(int, fcf::Arg1, int)>                             template_args_type;
      typedef fcf::Details::Basis::ArgPlaceHolder::ArgResolver<2, template_args_type, int, int, int>  getter_type;
      FCF_TEST(getter_type::call(variant, a1, a2) == 2, getter_type::call(variant, a1, a2));
    }
    {
      typedef ::fcf::ArgPlaceHolder::Arguments<void(int, fcf::Arg1, int)>                             template_args_type;
      typedef fcf::Details::Basis::ArgPlaceHolder::ArgResolver<2, template_args_type, int, int, int>  getter_type;
      FCF_TEST(getter_type::call(variant, a1, a2) == 2, getter_type::call(variant, a1, a2));
    }
    {
      typedef ::fcf::ArgPlaceHolder::Arguments<void(int, fcf::Arg3, int)>                      template_args_type;
      typedef fcf::Details::Basis::ArgPlaceHolder::ArgResolver<1, template_args_type, int, int, int>  getter_type;
      FCF_TEST(getter_type::call(variant, a1, a2) == 1003, getter_type::call(variant, a1, a2));
    }
  }

  {
    typedef fcf::Variant VariantArray[3];
    VariantArray variant;
    variant[0] = 1001;
    variant[1] = 1002;
    variant[2] = 1003;
    int a1 = 1;
    int a2 = 2;



    {
      std::vector<int> vec(10, 0);
      typedef void (*function_type)(std::vector<int>&, const int&);
      function_type func = (function_type)fcf::fill;

      typedef ::fcf::ArgPlaceHolder::Arguments<void(std::vector<int>&, fcf::Arg2)>                   template_args_type;
      typedef fcf::ArgPlaceHolder::Caller<template_args_type, void (std::vector<int>&, const int&)>  caller_type;

      caller_type::call(func, variant, vec);
      for(auto itm : vec) {
        FCF_TEST(itm == 1002, itm);
      }
    }

    {
      std::vector<int> vec(10, 0);
      typedef void (*function_type)(std::vector<int>&, const int&);
      function_type func = (function_type)fcf::fill;

      typedef ::fcf::ArgPlaceHolder::Arguments<void(std::vector<int>&, const int&)>                    template_args_type;
      typedef fcf::ArgPlaceHolder::Caller<template_args_type, void (std::vector<int>&, const int&)>  caller_type;

      caller_type::call(func, variant, vec, 999);
      for(auto itm : vec) {
        FCF_TEST(itm == 999, itm);
      }
    }

  }

}
