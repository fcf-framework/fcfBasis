#define FCF_BASIS_IMPLEMENTATION
#include <fcfBasis/basis.hpp>

namespace math {
  int add(int a, int b) {
    return a + b;
  }
}

// Registering a function
// Macro Arguments:
//  function,                   - Source function pointer
//  function_name,              - Registred function name
//  space,                      - Engine (cpu - default CPU mode)
//  signature,                  - Function signature
//  placeholders,               - Options
//  includeSourceCode           - Add sourceCode to current cpp file
//  sourceCode                  - Only for other engines
FCF_FUNCTION_REGISTRATION(
   math::add,
  "math::add",
  "cpu",
  int(*)(int, int),
  (),
  false,
  ()
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
