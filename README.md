**fcfBasis** is a C++ library (C++11) providing a meta-type system, dynamic function call dispatching, a universal data container (`Variant`), and generic iteration tools.

The library is designed for creating systems where data types, functions, and their interactions are defined or modified at runtime, while maintaining performance through caching and compile-time optimizations.


### Attention! The library is currently being refactored. Variable names may change.

## Core Concepts

### 1. Meta-Type System (`fcf::Type`)

Unlike the standard `typeid`, `fcf::Type` provides rich runtime information about a type: name, size, index, as well as access to specifiers (operations on the type) and converters.

Each type must be registered in the system. For built-in types, this is done automatically. For user-defined types, use the `FCF_TYPEID_REGISTRY` macro.

**Example of registering a custom type:**

```cpp
#define FCF_BASIS_IMPLEMENTATION
#include <fcfBasis/basis.hpp>

struct MyStruct {
    int id;
    std::string name;
};

// Registering a type with the name "MyStruct" and base index 0
FCF_TYPEID_REGISTRY(MyStruct, "MyStruct", 0);

int main() {
    // Getting metadata
    fcf::Type<MyStruct> type;
    std::cout << "Name:  " << type.typeInfo()->name << std::endl;
    std::cout << "Index: " << type.typeInfo()->index
              << "; hex: 0x" << std::hex << type.typeInfo()->index << std::dec << std::endl;
    std::cout << "Size:  " << type.typeInfo()->size << std::endl;
    return 0;
}
```

### 2. Universal Variant (`fcf::Variant`)

`fcf::Variant` is a type-safe container capable of storing values of any registered type. It supports Small Object Optimization (SOO) for small objects to avoid heap allocation.

**Key Features:**
* Storage for any type.
* Automatic type conversion during assignment and extraction.
* Working with references (`REFERENCE`).
* Arithmetic and comparison operations.
* Access to containers (vectors, lists, maps) via the `[]` operator and iterators.

**Usage Example:**

```cpp
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
```

### 3. Dynamic Function Call (`fcf::call` / `fcf::rcall`)

The library allows registering functions and calling them by string name at runtime. The system automatically selects the appropriate function overload, performs necessary argument conversions, and returns the result as an `fcf::Variant`.

**Registering a function:**

```cpp
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
//  a_sourceCode                    - Only for other engines
FCF_DECLARE_FUNCTION(
  (math, add),
  "cpu",
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
```

### 4. Specifiers

Specifiers are a way to bind behavior (operations) to a data type. For example, `LessSpecificator` defines how objects are compared using the `<` operator, and `AddSpecificator` defines how they are added.

This allows `fcf::Variant` and the call system to perform operations on custom types if corresponding specifiers are registered for them.

**Example of implementing comparison for a custom type:**

```cpp
#define FCF_BASIS_IMPLEMENTATION
#include <fcfBasis/basis.hpp>

struct Person {
    int age;
    std::string name;
};

FCF_TYPEID_REGISTRY(Person, "Person", 0);

// Type specialization for LessSpecificator
namespace fcf {
    template<>
    struct Type<Person, LessSpecificator> : public TypeImpl<Person, LessSpecificator> {
        inline bool call(const Person* a_left, const Person* a_right) const {
            return a_left->age < a_right->age;
        }
    };
}

// Specifier Registration
FCF_SPECIFICATOR_REGISTRY(Person, fcf::LessSpecificator);

int main() {
    Person p1{25, "Alice"};
    Person p2{30, "Bob"};

    fcf::Variant vp1(p1);
    fcf::Variant vp2(p2);

    // Variant comparison uses LessSpecificator
    if (vp1 < vp2) {
        std::cout << "Alice is younger than Bob" << std::endl;
    }
    return 0;
}
```

### 5. Generic Iteration (`fcf::foreach`)

The `fcf::foreach` macro provides a unified interface for iterating over elements of various containers (`std::vector`, `std::list`, `std::map`, `std::tuple`, etc.).

**Examples:**

```cpp
#define FCF_BASIS_IMPLEMENTATION
#include <fcfBasis/basis.hpp>
#include <vector>
#include <map>
#include <tuple>

struct TupleViewer {
  template <typename ItemTy>
  void operator()(size_t a_index, const ItemTy& a_item) {
    std::cout << "  Key: " << a_index << ", Value: " << a_item << ", Type: " << fcf::Type<ItemTy>().typeInfo()->name << std::endl;
  }
};

int main() {
    // Iterate over the vector
    std::vector<int> vec = {1, 2, 3};
    std::cout << "Vector items:" << std::endl;
    fcf::foreach(vec, [](size_t index, int& value) {
        std::cout << "  Index: " << index << ", Value: " << value << std::endl;
    });

    // Iterate over the map
    std::cout << "Map items:" << std::endl;
    std::map<std::string, int> map = {{"A", 1}, {"B", 2}};
    fcf::foreach(map, [](const std::string& key, int& value) {
        std::cout << "  Key: " << key << ", Value: " << value << std::endl;
    });

    // Iterate over the tuple
    std::cout << "Tuple items:" << std::endl;
    auto tuple = std::make_tuple(1, "Hello", 3.14);
    fcf::foreach(tuple, TupleViewer());

    return 0;
}
```

### 6. Static Vector (`fcf::StaticVector`)

`fcf::StaticVector` is an analogue to `std::vector` that stores data on the stack (in an internal buffer) if the number of elements does not exceed a specified limit. This avoids heap allocation for small collections, improving performance.

**Example:**

```cpp
#define FCF_BASIS_IMPLEMENTATION
#include <fcfBasis/basis.hpp>

int main() {
    // Vector with an internal buffer of 4 elements
    fcf::StaticVector<int, 4> vec;

    vec.push_back(1);
    vec.push_back(2);
    // Data is stored in the stack

    vec.push_back(3);
    vec.push_back(4);
    // The buffer is full

    vec.push_back(5);
    // Heap memory allocation because size exceeded 4

    return 0;
}
```

### 7. Exception System (`fcf::Exception`)

An extended exception system that supports error chaining (sub-exceptions) and message formatting with argument substitution.

**Example:**

```cpp
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
```

## Build and Usage

The examples above use CMake for building.
To use the library in your project:

1.  Specify the path to the `fcfBasis` header files.
2.  Define the `FCF_BASIS_IMPLEMENTATION` macro in one `.cpp` file of your project before including the headers.
    This is necessary to deploy template implementations and register built-in types.


**CMakeLists.txt Example:**

```cmake
add_executable(my_app main.cpp)
target_include_directories(my_app PRIVATE /path/to/libraries/directory/with/fcfBasis)
```

**main.cpp Example:**

```cpp
#define FCF_BASIS_IMPLEMENTATION
#include <fcfBasis/basis.hpp>

int main() {
    // Your code
    return 0;
}
```

## License

MIT License. Copyright (c) 2026 Vladimir Markin
