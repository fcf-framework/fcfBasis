#define FCF_BASIS_IMPLEMENTATION
#include <fcfBasis/basis.hpp>
#include <iostream>

int main() {
    // Initialization with different types
    fcf::Variant v1 = 10;
    fcf::Variant v2 = 20.5;
    fcf::Variant v3 = "Hello";

    // Arithmetic (automatic type casting)
    fcf::Variant sum = v1 + v2;
    std::cout << "Sum: " << sum.cast<double>() << std::endl; // 30.5

    // Extracting the value
    if (v1.is<int>()) {
        std::cout << "v1 is int: " << v1.get<int>() << std::endl;
    }

    // Working with Strings
    fcf::Variant str = std::string("Dynamic");
    str += " String";
    std::cout << "String: " << str << std::endl;

    return 0;
}
