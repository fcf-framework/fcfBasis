#include <fcfTest/test.hpp>
#include "../../basis.hpp"
#include <vector>

void deepIndexCallInner();
void deepIndexCall();
void variantTest();

int main(int a_argc, char* a_argv[]){
  deepIndexCallInner();
  deepIndexCall();
  variantTest();
  return 0;
}
