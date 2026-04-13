#define FCF_BASIS_IMPLEMENTATION
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <tuple>
#include <string>
#include <fcfBasis/basis.hpp>

struct TuplePrinter{
  template<typename TTuple, typename TItem>
  void operator()(const TTuple& /*a_tuple*/, size_t a_index, TItem& a_item){
    std::cout << "Tuple index [" << a_index << "]: " << a_item << std::endl;
  }
};

struct TuplePrinterSpec {
  template<typename TTuple, typename TItem>
  void handler(const TTuple& /*a_tuple*/, size_t a_index, TItem& a_item){
    std::cout << "Tuple index [" << a_index << "]: " << a_item << std::endl;
  }
};

FCF_FOREACH_METHOD_WRAPPER(TuplePrinterSpecWrapper, TuplePrinterSpec, handler);

/**
 * @brief Демонстрационное приложение для изучения работы fcf::foreach.
 *
 * Основная идея: fcf::foreach предоставляет унифицированный способ обхода
 * различных структур данных, передавая в функцию-обработчик:
 * 1. Ссылку на контейнер.
 * 2. Текущий индекс (или ключ).
 * 3. Текущее значение.
 */

int main() {
    std::cout << "=== [1] Работа с последовательными контейнерами (Vector, List) ===" << std::endl;

    std::vector<int> vec = {10, 20, 30, 40, 50};
    std::list<std::string> lst = {"Apple", "Banana", "Cherry"};

    // Обход вектора: получаем индекс и значение
    fcf::foreach(vec, [](const std::vector<int>& /*container*/, size_t index, const int& value) {
        std::cout << "Vector element [" << index << "]: " << value << std::endl;
    });

    std::cout << "\n---" << std::endl;

    // Обход списка: индекс здесь также инкрементируется
    fcf::foreach(lst, [](const std::list<std::string>& /*container*/, size_t index, const std::string& value) {
        std::cout << "List element [" << index << "]: " << value << std::endl;
    });


    std::cout << "\n=== [2] Работа с ассоциативными контейнерами (Map) ===" << std::endl;

    std::map<std::string, double> prices = {
        {"Coffee", 2.5},
        {"Tea", 1.5},
        {"Cake", 5.0}
    };

    // В map 'index' фактически является ключом (key)
    fcf::foreach(prices, [](const std::map<std::string, double>& /*container*/, const std::string& key, const double& value) {
        std::cout << "Product: " << key << " | Price: $" << value << std::endl;
    });


    std::cout << "\n=== [3] Работа с множествами (Set) ===" << std::endl;

    std::set<int> unique_numbers = {1, 5, 2, 8, 5}; // 5 повторится один раз

    // В set 'index' и 'value' будут указывать на один и тот же элемент
    fcf::foreach(unique_numbers, [](const std::set<int>& /*container*/, int index, int value) {
        std::cout << "Set element: " << value << " (index/key: " << index << ")" << std::endl;
    });


    std::cout << "\n=== [4] Работа с кортежами (Tuple) ===" << std::endl;
    auto my_tuple = std::make_tuple(1, "Hello", 3.14, 'A');
    TuplePrinter printer;
    // foreach для tuple использует метапрограммирование для развертки элементов
    fcf::foreach(my_tuple, printer);


    std::cout << "\n=== [5] Работа с кортежами (Tuple) ===" << std::endl;
    std::tuple<int, std::string, int, char> spec_tuple = std::make_tuple(1, "Hello", 3.14, 'A');
    TuplePrinterSpec spec_printer;
    TuplePrinterSpecWrapper spec_printer_wrapper(spec_printer);
    // foreach для tuple использует метапрограммирование для развертки элементов
    fcf::foreach(spec_tuple, spec_printer_wrapper);

    std::cout << "\n=== [6] Модификация данных через foreach ===" << std::endl;

    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Если передать не const контейнер, можно изменять элементы
    fcf::foreach(numbers, [](std::vector<int>& /*container*/, size_t /*index*/, int& value) {
        value *= 10; // Умножаем каждое число на 10
    });

    std::cout << "Modified vector: ";
    for(int n : numbers) std::cout << n << " ";
    std::cout << std::endl;

    return 0;
}


