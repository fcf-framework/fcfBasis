#define FCF_BASIS_IMPLEMENTATION
#include <fcfBasis/basis.hpp>

namespace math {
  int add(int a, int b) {
    return a + b;
  }
}

// Registering a function
// Macro Arguments:
//  (namespace1, namespace2, name), - Function name for storing
//  space,
//  function_pointer,               - Source function name
//  signature,
//  placeholders,
//  a_sourceCode                    - only for other engines
FCF_DECLARE_FUNCTION(
  (math, add),
  "engine_cpu",
  math::add,
  int(*)(int, int),
  (),
);

int main() {
  // Call by name, arguments can be of different types (will be converted)
  fcf::Variant result = fcf::rcall("math::add", 10, 20);
  std::cout << "Result:  " << result << std::endl; // 30

  // Call with conversion from string
  fcf::Variant result2 = fcf::rcall("math::add", (const char*)"5", (const char*)"5");
  std::cout << "Result2: " << result2 << std::endl; // 10

  return 0;
}
