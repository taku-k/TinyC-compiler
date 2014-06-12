#include <iostream>
#include <cstdlib>

#include "tc_driver.hpp"

int main(const int argc, const char **argv)
{
  if (argc != 2) {
    std::cerr << "入力ファイルを指定してください\n";
    return 1;
  }

   TC::TC_Driver driver;
   
   driver.parse(argv[1]);

   return 0;
}
