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

/**
 * @brief Registers the type in the global fcf::TypeStorage.
 *
 * This macro:
 * 1. Generates a unique TypeId for MyCustomStruct.
 * 2. Creates a TypeInfo object containing the type's name and metadata.
 * 3. Stores this information in the global registry so it can be retrieved via fcf::Type<MyCustomStruct>().
 *
 * @param MyCustomStruct The type to register.
 * @param "MyCustomStruct" The human-readable name for the type.
 * @param 0 The base type index (0 for a new root type).
 */
FCF_TYPEID_REGISTRY(MyCustomStruct, "MyCustomStruct",  0);


namespace fcf {
  /**
   * @brief Specialization of fcf::Type to provide runtime behavior for a specificator.
   *
   * Here we define how MyCustomStruct should behave when used with fcf::LessSpecificator.
   * This allows the generic fcf::Type system to perform comparisons on this custom type at runtime.
   */
  template<> struct Type<MyCustomStruct, LessSpecificator> : public TypeImpl<MyCustomStruct, LessSpecificator> {
    inline bool call(const MyCustomStruct* a_left, const MyCustomStruct* a_right) const {
      return a_left->name < a_right->name;
    }
  };
}

/**
 * @brief Links the specificator logic to the registered type.
 *
 * This macro tells the fcf system that for the type MyCustomStruct,
 * the fcf::LessSpecificator operation is implemented by the specialization
 * defined above. This is essential for the runtime dispatch mechanism.
 *
 * @param MyCustomStruct The type that supports the specificator.
 * @param fcf::LessSpecificator The specificator being registered.
 */
FCF_SPECIFICATOR_REGISTRY(MyCustomStruct,  fcf::LessSpecificator);

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

    std::cout << "\n=== [4] Working with Custom Types (MyCustomStruct) ===" << std::endl;
    {
        MyCustomStruct obj1{1, "Alice"};
        MyCustomStruct obj2{2, "Bob"};
        MyCustomStruct obj3{3, "Charlie"};

        // 1. Metadata access
        fcf::Type<MyCustomStruct> customType;
        std::cout << "Custom Type Name: " << customType.name() << std::endl;
        std::cout << "Custom Type Index: 0x" << std::hex << customType.index() << std::dec << std::endl;

        // 2. Runtime comparison via Variant and Specificator
        // We wrap objects in Variants to simulate runtime dispatch
        fcf::Variant var1(obj1);
        fcf::Variant var2(obj2);
        fcf::Variant var3(obj3);

        fcf::UniversalCall lessFunc = fcf::Type<MyCustomStruct>().getSpecificator<fcf::LessSpecificator>();

        if (lessFunc) {
            // Compare Alice < Bob
            fcf::Variant res1 = lessFunc(&obj1, &var2, 1);
            std::cout << "Is 'Alice' < 'Bob'?   [lessFunc comparison] " << (res1.cast<bool>() ? "Yes" : "No") << std::endl;
            // When comparing (<) Variant objects, fcf::LessSpecificator is also used.
            std::cout << "Is 'Alice' < 'Bob'?   [Variant comparison]  " << (( var1 < var2 ) ? "Yes" : "No") << std::endl;

            // Compare Bob < Alice (should be false)
            fcf::Variant res2 = lessFunc(&obj2, &var1, 1);
            std::cout << "Is 'Bob' < 'Alice'?   [lessFunc comparison] " << (res2.cast<bool>() ? "Yes" : "No") << std::endl;
            // When comparing (<) Variant objects, fcf::LessSpecificator is also used.
            std::cout << "Is 'Bob' < 'Alice'?   [Variant comparison]  " << (( var2 < var1 ) ? "Yes" : "No") << std::endl;

            // Compare Bob < Charlie
            fcf::Variant res3 = lessFunc(&obj2, &var3, 1);
            std::cout << "Is 'Bob' < 'Charlie'? [lessFunc comparison] " << (res3.cast<bool>() ? "Yes" : "No") << std::endl;
            // When comparing (<) Variant objects, fcf::LessSpecificator is also used.
            std::cout << "Is 'Bob' < 'Charlie'? [Variant comparison]  " << (( var2 < var3 ) ? "Yes" : "No") << std::endl;
        }
    }

    return 0;
}
