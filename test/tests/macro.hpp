#ifndef ___FCF_BASIS_TESTS__MACRO_HPP___
#define ___FCF_BASIS_TESTS__MACRO_HPP___

#include <sstream>

namespace fcfBasisTest {

  template <typename... TPack>
  struct PrintPack {
    template <typename TArg, typename... TPack2>
    std::string operator()(const TArg& a_arg, TPack2... a_pack){
      std::stringstream ss;
      ss << "    arg: " << a_arg << std::endl;
      return ss.str() + PrintPack<TPack2...>()(a_pack...);
    }
  };

  template <>
  struct PrintPack<> {
    std::string operator()(){
      return std::string();
    }
  };

  namespace {
    template <typename... TArgPack>
    std::string printTestArgs(TArgPack... a_pack){
      return PrintPack<TArgPack...>()(a_pack...);
    }
  }
}

#define FCF_BASIS_TEST_STRINGIZE2(x) #x
#define FCF_BASIS_TEST_STRINGIZE(x) FCF_BASIS_TEST_STRINGIZE2(x)
#define FCF_BASIS_TEST_LINE_STRING FCF_BASIS_TEST_STRINGIZE(__LINE__)
#define FCF_BASIS_TEST(exp, ...) \
  if (!(exp)){ \
    std::string messge = std::string() + \
                         "Test error: " + #exp + "  [FILE: " + __FILE__ + ":" + FCF_BASIS_TEST_LINE_STRING + "]\n" + \
                         fcfBasisTest::printTestArgs(__VA_ARGS__);\
    throw std::runtime_error(messge);\
  }

#endif // #ifndef ___FCF_BASIS_TESTS__MACRO_HPP___
