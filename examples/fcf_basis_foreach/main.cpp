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
 * @brief Простой функтор для печати элементов кортежа.
 *
 * Демонстрирует базовый синтаксис: оператор () принимает индекс и ссылку на элемент.
 */
struct TuplePrinter{
  template<typename TItem>
  void operator()(size_t a_index, TItem& a_item){
    std::cout << "Tuple index [" << a_index << "]: " << a_item << std::endl;
  }
};

/**
 * @brief Специализированный функтор, использующий макрос FCF_FOREACH_METHOD_WRAPPER.
 *
 * Это необходимо, если метод-обработчик называется не operator(), а, например, handler().
 * Макрос создает обертку, совместимую с механизмом foreach.
 */
struct TuplePrinterSpec {
  template<typename TItem>
  void handler(size_t a_index, TItem& a_item){
    std::cout << "Tuple index [" << a_index << "]: " << a_item << std::endl;
  }
};

// Создаем обертку для TuplePrinterSpec, чтобы foreach мог вызвать метод 'handler'
FCF_FOREACH_METHOD_WRAPPER(TuplePrinterSpecWrapper, TuplePrinterSpec, handler);

/**
 * @brief Функтор для подсчета количества числовых типов в кортеже.
 *
 * Демонстрирует возможность передачи дополнительного аргумента (счетчика)
 * в обработчик через foreach.
 */
struct TupleNumTypeCouner {
  template<typename TItem>
  void handler(size_t /*a_index*/, TItem& /*a_item*/, size_t& a_counter){
    // Используем систему типов fcf для проверки имени типа во время выполнения
    if (fcf::Type<TItem>().name() == "int" ||
        fcf::Type<TItem>().name() == "float" ||
        fcf::Type<TItem>().name() == "double"){
      ++a_counter;
    }
  }
};

// Создаем обертку для TupleNumTypeCouner
FCF_FOREACH_METHOD_WRAPPER(TupleNumTypeCounerWrapper, TupleNumTypeCouner, handler);

/**
 * @brief Демонстрационное приложение для изучения работы fcf::foreach.
 *
 * Основная идея: fcf::foreach предоставляет унифицированный способ обхода
 * различных структур данных, передавая в функцию-обработчик:
 * 1.   Текущий индекс (для последовательных) или ключ (для ассоциативных).
 * 2.   Текущее значение.
 * 3.   Дополнительные пользовательские аргументы.
 */

int main() {
    std::cout << "=== [1] Работа с последовательными контейнерами (Vector, List) ===" << std::endl;
    {
      std::vector<int> vec = {10, 20, 30, 40, 50};
      std::list<std::string> lst = {"Apple", "Banana", "Cherry"};

      // Обход вектора: лямбда-выражение получает индекс и значение
      fcf::foreach(vec, [](size_t index, const int& value) {
          std::cout << "Vector element [" << index << "]: " << value << std::endl;
      });

      std::cout << "\n---" << std::endl;

      // Обход списка: foreach автоматически адаптируется под итераторы контейнера
      fcf::foreach(lst, [](size_t index, const std::string& value) {
          std::cout << "List element [" << index << "]: " << value << std::endl;
      });
    }


    std::cout << "\n=== [2] Работа с ассоциативными контейнерами (Map) ===" << std::endl;
    {
      std::map<std::string, double> prices = {
          {"Coffee", 2.5},
          {"Tea", 1.5},
          {"Cake", 5.0}
      };

      // В map 'index' фактически является ключом (key) контейнера
      fcf::foreach(prices, [](const std::string& key, const double& value) {
          std::cout << "Product: " << key << "    \t| Price: $" << value << std::endl;
      });
    }


    std::cout << "\n=== [3] Работа с множествами (Set) ===" << std::endl;
    {
      std::set<int> unique_numbers = {1, 5, 2, 8, 5}; // 5 повторится один раз

      // В set 'index' и 'value' указывают на один и тот же элемент
      fcf::foreach(unique_numbers, [](int index, int value) {
          std::cout << "Set element: " << value << " (index/key: " << index << ")" << std::endl;
      });
    }


    std::cout << "\n=== [4] Работа с кортежами (Tuple) ===" << std::endl;
    std::cout <<   "===     Обработка в operator()     ===" << std::endl;
    {
      auto tuple = std::make_tuple(1, "Hello", 3.14, 'A');
      TuplePrinter handler;
      // foreach для tuple использует метапрограммирование для развертки элементов кортежа
      fcf::foreach(tuple, handler);
    }


    std::cout << "\n=== [5] Работа с кортежами (Tuple) ===" << std::endl;
    std::cout <<   "===  Обработка в отдельном методе  ===" << std::endl;
    {
      std::tuple<int, std::string, int, char> tuple = std::make_tuple(1, "Hello", 3.14, 'A');
      TuplePrinterSpec handler;
      TuplePrinterSpecWrapper wrapper(handler);
      // Использование обертки для вызова метода 'handler' вместо operator()
      fcf::foreach(tuple, wrapper);
    }

    std::cout << "\n=== [6] Работа с кортежами (Tuple) ===" << std::endl;
    std::cout <<   "===    Передача доп. параметра     ===" << std::endl;
    {
      std::tuple<int, std::string, float, char> tuple = std::make_tuple(1, "Hello", 3.14, 'A');
      TupleNumTypeCouner handler;
      TupleNumTypeCounerWrapper wrapper(handler);
      size_t numCounter = 0;

      // Демонстрация передачи внешнего состояния (numCounter) в обработчик
      fcf::foreach(tuple, wrapper, numCounter);
      std::cout << "Количество числовых элементов в кортеже:" << numCounter << std::endl;
    }


    std::cout << "\n=== [7] Модификация данных через foreach ===" << std::endl;
    {
      std::vector<int> numbers = {1, 2, 3, 4, 5};

      // Если передать не const контейнер, можно изменять элементы напрямую через ссылку
      fcf::foreach(numbers, [](size_t /*index*/, int& value) {
          value *= 10; // Умножаем каждое число на 10
      });

      std::cout << "Modified vector: ";
      for(int n : numbers) std::cout << n << " ";
      std::cout << std::endl;
    }

    return 0;
}
