#define FCF_BASIS_IMPLEMENTATION
#include <fcfBasis/basis.hpp>
#include <vector>
#include <map>
#include <tuple>

struct TupleViewer {
  template <typename ItemTy>
  void operator()(size_t a_index, const ItemTy& a_item) {
    std::cout << "  Key: " << a_index << ", Value: " << a_item << ", Type: " << fcf::Type<ItemTy>().getTypeInfo()->name << std::endl;
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
