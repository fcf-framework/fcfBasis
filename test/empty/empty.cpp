#include <iostream>
#include <map>

int main(int /*a_argc*/, char* a_argv[]){
  
  std::map<std::string, std::string> m;
  std::cout << "!!!!!!!!1" << std::endl;
  m["1"] = "1";
  m["2"] = "2";
  for(auto itm : m){
    std::cout << itm.first << ":" << itm.second << std::endl;
  }
  return 0;
}
