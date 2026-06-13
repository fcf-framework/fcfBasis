#define FCF_BASIS_IMPLEMENTATION
#include <fcfBasis/basis.hpp>

struct MyStruct {
    int id;
    std::string name;
};

// Registering a type with name "MyStruct" and base index 0
FCF_TYPEID_REGISTRY(MyStruct, "MyStruct", 0);

int main() {
    // Retrieving metadata
    fcf::Type<MyStruct> type;
    std::cout << "Name:  " << type.typeInfo()->name << std::endl;
    std::cout << "Index: " << type.typeInfo()->index 
              << "; hex: 0x" << std::hex << type.typeInfo()->index << std::dec << std::endl;
    std::cout << "Size:  " << type.typeInfo()->size << std::endl;
    return 0;
}
