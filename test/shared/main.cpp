#include <iostream>
#include "header.hpp"
int incCounter();

int main(int, char*[]){
  std::cout << "inc(): " << (Storage().inc())<< std::endl;
  std::cout << "inc(): " << (Storage().inc())<< std::endl;
  std::cout << "incCounter(): " << (incCounter())<< std::endl;
  return 0;
}
