#define FCF_BASIS_IMPLEMENTATION
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <fcfBasis/basis.hpp>

/**
 * @brief Demonstration class showing the capabilities of fcf::Variant
 * when working with various container types.
 */
class VariantContainerShowcase {
public:
    /**
     * @brief Generic function to print the contents of any container
     * wrapped in a Variant.
     *
     * @param container Variant containing a container (std::vector, std::list, std::map, etc.)
     */
    void printAnyContainer(const fcf::Variant& container) {
        std::cout << "[Showcase] Attempting to print container of type: "
                  << (container.isContainer() ? "Container" : "Non-container") << std::endl;

        if (!container.isContainer()) {
            std::cout << "  -> Error: Provided Variant is not a container!" << std::endl;
            return;
        }

        std::cout << "  -> Size: " << container.containerSize() << std::endl;

        // 1. Demonstration of iteration via Variant::iterator
        // This works identically for std::vector, std::list, and even std::set
        std::cout << "  -> Elements: ";
        for (fcf::Variant::const_iterator it = container.begin(); it != container.end(); ++it) {
            // For simplicity of the example, we print the value
            std::cout << *it << " ";
        }
        std::cout << "\n" << std::endl;
    }

    /**
     * @brief Demonstration of working with associative containers (std::map)
     */
    void demonstrateMap() {
        std::cout << "--- Map Demonstration ---" << std::endl;

        // Create a Variant containing std::map
        fcf::Variant mapVar = std::map<std::string, int>{
            {"Alpha", 1},
            {"Beta", 2},
            {"Gamma", 3}
        };

        // Access by key via [] operator
        // Variant will automatically return a new Variant containing the value
        fcf::Variant val = mapVar["Beta"];
        std::cout << "Value for 'Beta': " << val.as<int>() << std::endl;

        // Adding a new element
        mapVar["Delta"] = 42;
        std::cout << "New map size: " << mapVar.containerSize() << std::endl;

        // Iterating through pairs (Key/Value)
        for (fcf::Variant::iterator it = mapVar.begin(); it != mapVar.end(); ++it) {
            // In fcf::Variant for map, the iterator provides key() and value() methods
            std::cout << "  Key: " << it.key().as<std::string>()
                      << "\t| Value: " << it.value().as<int>() << std::endl;
        }
        std::cout << std::endl;
    }

    /**
     * @brief Demonstration of type conversion within containers
     */
    void demonstrateConversion() {
        std::cout << "--- Conversion Demonstration ---" << std::endl;

        // Source container: vector of integers
        fcf::Variant intVec = std::vector<int>{1, 2, 3, 4, 5};

        // Target container: list of strings (std::list<std::string>)
        // We explicitly specify the type via fcf::Type
        fcf::Variant stringList(fcf::Type<std::list<std::string>>{});

        // Transferring data with automatic conversion int -> std::string
        for (size_t i = 0; i < intVec.containerSize(); ++i) {
            stringList[i] = intVec[i];
        }

        std::cout << "Converted list elements: ";
        for (fcf::Variant item : stringList) {
            std::cout << "[" << item.as<std::string>() << "] ";
        }
        std::cout << "\n" << std::endl;
    }
};

int main() {
    VariantContainerShowcase showcase;

    // Test 1: Different container types
    std::cout << "=== Test 1: Universal Iteration ===" << std::endl;
    showcase.printAnyContainer(std::vector<double>{1.1, 2.2, 3.3});
    showcase.printAnyContainer(std::list<int>{10, 20, 30, 40});
    showcase.printAnyContainer(std::set<std::string>{"Apple", "Banana", "Cherry"});

    // Test 2: Working with Map
    showcase.demonstrateMap();

    // Test 3: Conversion
    showcase.demonstrateConversion();

    return 0;
}