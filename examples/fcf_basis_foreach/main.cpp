#define FCF_BASIS_IMPLEMENTATION
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <tuple>
#include <string>
#include <fcfBasis/basis.hpp>

/**
 * @brief Simple functor for printing tuple elements.
 *
 * Demonstrates basic syntax: operator() accepts an index and a reference to an item.
 */
struct TuplePrinter{
  template<typename TItem>
  void operator()(size_t a_index, TItem& a_item){
    std::cout << "Tuple index [" << a_index << "]: " << a_item << std::endl;
  }
};

/**
 * @brief Specialized functor using the FCF_FOREACH_METHOD_WRAPPER macro.
 *
 * This is necessary if the handler method is named something other than operator(), 
 * such as handler(). The macro creates a wrapper compatible with the foreach mechanism.
 */
struct TuplePrinterSpec {
  template<typename TItem>
  void handler(size_t a_index, TItem& a_item){
    std::cout << "Tuple index [" << a_index << "]: " << a_item << std::endl;
  }
};

// Create a wrapper for TuplePrinterSpec so foreach can call the 'handler' method
FCF_FOREACH_METHOD_WRAPPER(TuplePrinterSpecWrapper, TuplePrinterSpec, handler);

/**
 * @brief Functor for counting the number of numeric types in a tuple.
 *
 * Demonstrates the ability to pass an additional argument (counter) 
 * to the handler via foreach.
 */
struct TupleNumTypeCouner {
  template<typename TItem>
  void handler(size_t /*a_index*/, TItem& /*a_item*/, size_t& a_counter){
    // Use the fcf type system to check the type name at runtime
    if (fcf::Type<TItem>().name() == "int" ||
        fcf::Type<TItem>().name() == "float" ||
        fcf::Type<TItem>().name() == "double"){
      ++a_counter;
    }
  }
};

// Create a wrapper for TupleNumTypeCouner
FCF_FOREACH_METHOD_WRAPPER(TupleNumTypeCounerWrapper, TupleNumTypeCouner, handler);

/**
 * @brief Demonstration application for studying fcf::foreach.
 *
 * The main idea is that fcf::foreach provides a unified way to iterate over
 * various data structures, passing to the handler function:
 * 1.   The current index (for sequential) or key (for associative).
 * 2.   The current value.
 * 3.   Additional user-defined arguments.
 */

int main() {
    std::cout << "=== [1] Working with sequential containers (Vector, List) ===" << std::endl;
    {
      std::vector<int> vec = {10, 20, 30, 40, 50};
      std::list<std::string> lst = {"Apple", "Banana", "Cherry"};

      // Iterating over a vector: lambda expression receives index and value
      fcf::foreach(vec, [](size_t index, const int& value) {
          std::cout << "Vector element [" << index << "]: " << value << std::endl;
      });

      std::cout << "\n---" << std::endl;

      // Iterating over a list: foreach automatically adapts to the container's iterators
      fcf::foreach(lst, [](size_t index, const std::string& value) {
          std::cout << "List element [" << index << "]: " << value << std::endl;
      });
    }


    std::cout << "\n=== [2] Working with associative containers (Map) ===" << std::endl;
    {
      std::map<std::string, double> prices = {
          {"Coffee", 2.5},
          {"Tea", 1.5},
          {"Cake", 5.0}
      };

      // In a map, 'index' is effectively the container's key
      fcf::foreach(prices, [](const std::string& key, const double& value) {
          std::cout << "Product: " << key << "    \t| Price: $" << value << std::endl;
      });
    }


    std::cout << "\n=== [3] Working with sets (Set) ===" << std::endl;
    {
      std::set<int> unique_numbers = {1, 5, 2, 8, 5}; // 5 will appear only once

      // In a set, 'index' and 'value' point to the same element
      fcf::foreach(unique_numbers, [](int index, int value) {
          std::cout << "Set element: " << value << " (index/key: " << index << ")" << std::endl;
      });
    }


    std::cout << "\n=== [4] Working with tuples (Tuple) ===" << std::endl;
    std::cout <<   "===    Processing in operator()     ===" << std::endl;
    {
      auto tuple = std::make_tuple(1, "Hello", 3.14, 'A');
      TuplePrinter handler;
      // foreach for tuple uses metaprogramming to unpack tuple elements
      fcf::foreach(tuple, handler);
    }


    std::cout << "\n=== [5] Working with tuples (Tuple) ===" << std::endl;
    std::cout <<   "=== Processing in a separate method ===" << std::endl;
    {
      std::tuple<int, std::string, int, char> tuple = std::make_tuple(1, "Hello", 3.14, 'A');
      TuplePrinterSpec handler;
      TuplePrinterSpecWrapper wrapper(handler);
      // Using a wrapper to call the 'handler' method instead of operator()
      fcf::foreach(tuple, wrapper);
    }

    std::cout << "\n=== [6] Working with tuples (Tuple) ===" << std::endl;
    std::cout <<   "===  Passing additional parameter   ===" << std::endl;
    {
      std::tuple<int, std::string, float, char> tuple = std::make_tuple(1, "Hello", 3.14, 'A');
      TupleNumTypeCouner handler;
      TupleNumTypeCounerWrapper wrapper(handler);
      size_t numCounter = 0;

      // Demonstration of passing external state (numCounter) to the handler
      fcf::foreach(tuple, wrapper, numCounter);
      std::cout << "Number of numeric elements in tuple: " << numCounter << std::endl;
    }


    std::cout << "\n=== [7] Modifying data via foreach ===" << std::endl;
    {
      std::vector<int> numbers = {1, 2, 3, 4, 5};

      // If a non-const container is passed, elements can be modified directly via reference
      fcf::foreach(numbers, [](size_t /*index*/, int& value) {
          value *= 10; // Multiply each number by 10
      });

      std::cout << "Modified vector: ";
      for(int n : numbers) std::cout << n << " ";
      std::cout << std::endl;
    }

    return 0;
}
