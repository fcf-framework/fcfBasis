#define FCF_BASIS_IMPLEMENTATION
#include <iostream>
#include <fcfBasis/basis.hpp>

int main() {
    // 1. Initialization in different ways
    fcf::Variant v1 = 10;                // int
    fcf::Variant v2 = 20.5;              // double
    fcf::Variant v3 = "100.1";           // string
    fcf::Variant v4 = "Hello, FCF!";     // const char*
    fcf::Variant v5 = true;              // bool

    // 2. Automatic type conversion in arithmetic
    fcf::Variant sum1 = v1 + v2;         // int + double -> int
    std::cout << "Sum (int + double) -> int    : " << sum1.cast<int>() << std::endl;

    fcf::Variant sum2 = v2 + v3;         // double + string(double) -> double
    std::cout << "Sum (int + string) -> double : " << sum2.cast<double>() << std::endl;

    // 3. Comparison
    fcf::Variant a = 100;
    fcf::Variant b = 200;
    if (a < b) {
        std::cout << "a is less than b" << std::endl;
    }

    // 4. Type check
    if (v1.is<int>()) {
        std::cout << "v1 is an integer             : " << v1.get<int>() << std::endl;
    }

    // 5. Working with strings
    fcf::Variant str = std::string("Dynamic");
    str += " String";
    std::cout << "String value                 : " << str.cast<std::string>() << std::endl;

    return 0;
}
