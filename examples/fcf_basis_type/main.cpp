#define FCF_BASIS_IMPLEMENTATION
#include <iostream>
#include <string>
#include <vector>
#include <fcfBasis/basis.hpp>

/**
 * @brief Demonstration example of using the fcf::Type metadata system.
 *
 * The core idea of fcf::Type is that it provides access to type information
 * at runtime, which is typically only available at compile time.
 */

// 1. Prepare a custom type for demonstration
struct MyCustomStruct {
    int id;
    std::string name;
};

// To allow fcf::Type to work with our type in the context of specificators (e.g., comparison),
// it must be registered. In this example, we just show basic registration.
// In a real project, this is done via macros or specialized registrars.

int main() {
    std::cout << "=== [1] Basic information about built-in types ===" << std::endl;
    {
        // Get the type descriptor for int
        fcf::Type<int> intType;
        std::cout << "Type Name: " << intType.name() << std::endl;
        std::cout << "Type Index: " << intType.index() << std::endl;
        std::cout << "Type Size: " << intType.getTypeInfo()->size << " bytes" << std::endl;

        // Get the type descriptor for std::string
        fcf::Type<std::string> stringType;
        std::cout << "\nType Name: " << stringType.name() << std::endl;
        std::cout << "Type Index: " << stringType.index() << std::endl;
        std::cout << "Type Size: " << stringType.getTypeInfo()->size << " bytes" << std::endl;
    }

    std::cout << "\n=== [2] Working with pointers and constness ===" << std::endl;
    {
        // The fcf::Type system can distinguish types considering qualifiers.
        // We can get the index for 'const int' or 'int*'
        fcf::Type<const int> constIntType;
        fcf::Type<int*> intPtrType;

        std::cout << "const int name: " << constIntType.name() << " (Index: 0x" << std::hex << constIntType.index() << std::dec << ")" << std::endl;
        std::cout << "int* name:      " << intPtrType.name() << " (Index: 0x" << std::hex << intPtrType.index() << std::dec << ")" << std::endl;

        // Check that indices are different (as they are different types in the fcf system)
        if (constIntType.index() != intPtrType.index()) {
            std::cout << "-> Indices differ, as expected." << std::endl;
        }
    }

    std::cout << "\n=== [3] Using specificators (Runtime Behavior) ===" << std::endl;
    {
        // Specificators allow performing operations on types using their metadata.
        // For example, LessSpecificator (the < operator).

        int a = 10;
        int b = 20;

        // Get the comparison specificator for the int type
        // getSpecificator() returns a universal function pointer (UniversalCall)
        fcf::UniversalCall lessFunc = fcf::Type<int>().getSpecificator<fcf::LessSpecificator>();

        if (lessFunc) {
            // Create a Variant object and bind a reference to variable b to it
            fcf::Variant varB(b, fcf::Variant::REFERENCE);
            // Call the specificator function.
            // The first argument is a pointer to the reference, the second is an array of Variant elements
            // and its size.
            fcf::Variant result = lessFunc(&a, &varB, 1);
            if (result.cast<bool>()) {
                std::cout << "Result " << a << "<" << b << ": " << result << " (via LessSpecificator logic)" << std::endl;
            }
        }
    }

    return 0;
}
