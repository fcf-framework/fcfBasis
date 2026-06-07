#define FCF_BASIS_IMPLEMENTATION
#include <fcfBasis/basis.hpp>

// Declaring an exception with 2 arguments
FCF_EXCEPTION_DECLARE(MyError, "MY_ERROR", "Error in ${{1}}$ with value ${{2}}$", 2);

int main() {
  try {
    throw MyError(__FILE__, __LINE__, "FunctionX", 42);
  } catch (const fcf::Exception& e) {
    std::cout << e.full() << std::endl;
    // Output:
    // Error:    MY_ERROR
    // Message:  Error in FunctionX with value 42
    // Position: main.cpp:9
  }

  return 0;
}
