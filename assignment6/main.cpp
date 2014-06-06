#include <iostream>
#include <cstdlib>

#include "tc_driver.hpp"

int main(const int argc, const char **argv)
{
   TC::TC_Driver driver;
   
   driver.parse();

   driver.print();

   // driver.debug();

   return( EXIT_SUCCESS );
}
