#define FCF_BASIS_IMPLEMENTATION
#include <iostream>
#include <string>
#include <fcfBasis/basis.hpp>

/**
 * @brief Application to demonstrate the functionality of fcf::StaticVector.
 *
 * Main concepts:
 * 1. Small Object Optimization (SOO): Data is stored on the stack if it fits within StaticSize.
 * 2. Dynamic expansion: When StaticSize is exceeded, the vector switches to using the heap.
 * 3. Iteration: Support for standard iteration interfaces.
 */

int main() {
    std::cout << "=== [1] Initialization and Small Object Optimization (SOO) ===" << std::endl;
    {
        // Create a vector with a small static size (e.g., 4 elements)
        // Parameters: Ty, StaticSize, OffsetSize, StepSize, StepModuleInt, StepModuleFrac, MaxPow
        fcf::StaticVector<int, 4> smallVec;

        std::cout << "Initial size: " << smallVec.size() << ", Capacity: " << smallVec.capacity() << std::endl;

        // Fill the vector with elements that fit in the static buffer
        for (int i = 1; i <= 4; ++i) {
            smallVec.push_back(i * 10);
        }

        std::cout << "Size after 4 push_back: " << smallVec.size() << std::endl;
        std::cout << "Capacity (should be 4): " << smallVec.capacity() << std::endl;

        // Check if memory is in the static buffer
        // In StaticVector implementation, this is checked by comparing the data address with the _adata address
        // But we can simply print the values
        std::cout << "Elements: ";
        for (size_t i = 0; i < smallVec.size(); ++i) {
            std::cout << smallVec[i] << " ";
        }
        std::cout << "\n" << std::endl;
    }

    std::cout << "=== [2] Dynamic Expansion (Heap Allocation) ===" << std::endl;
    {
        // Same vector, but add more elements than StaticSize (4) allows
        fcf::StaticVector<int, 4> growingVec;

        for (int i = 1; i <= 10; ++i) {
            growingVec.push_back(i);
        }

        std::cout << "Size after 10 push_back: " << growingVec.size() << std::endl;
        std::cout << "New capacity (should be > 4): " << growingVec.capacity() << std::endl;

        std::cout << "Elements: ";
        for (size_t i = 0; i < growingVec.size(); ++i) {
            std::cout << growingVec[i] << " ";
        }
        std::cout << "\n" << std::endl;
    }

    std::cout << "=== [3] Working with Iterators and ContainerAccess ===" << std::endl;
    {
        fcf::StaticVector<std::string, 5> strVec;
        strVec.push_back("Hello");
        strVec.push_back("fcf");
        strVec.push_back("Static");
        strVec.push_back("Vector");

        std::cout << "Iteration via begin/end:" << std::endl;
        for (auto it = strVec.begin(); it != strVec.end(); ++it) {
            std::cout << "  [" << *it << "]" << std::endl;
        }

        std::cout << "\nIteration via range-based for:" << std::endl;
        for (const auto& str : strVec) {
            std::cout << "  " << str << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "=== [4] Deletion and Modification Operations ===" << std::endl;
    {
        fcf::StaticVector<int, 10> modVec;
        modVec.push_back(1);
        modVec.push_back(2);
        modVec.push_back(3);
        modVec.push_back(4);
        modVec.push_back(5);

        std::cout << "Before deletion (index 2): ";
        for(size_t i=0; i<modVec.size(); ++i) std::cout << modVec[i] << " ";
        std::cout << std::endl;

        // Remove element at index 2 (value 3)
        modVec.erase(modVec.begin() + 2);

        std::cout << "After deletion (index 2): ";
        for(size_t i=0; i<modVec.size(); ++i) std::cout << modVec[i] << " ";
        std::cout << "\n" << std::endl;
    }

    std::cout << "=== [5] Using initializer_list ===" << std::endl;
    {
        fcf::StaticVector<double, 10> doubleVec = {1.1, 2.2, 3.3, 4.4, 5.5};

        std::cout << "Elements: ";
        for (size_t i = 0; i < doubleVec.size(); ++i) {
            std::cout << doubleVec[i] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}