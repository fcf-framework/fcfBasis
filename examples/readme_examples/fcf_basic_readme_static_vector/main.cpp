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
