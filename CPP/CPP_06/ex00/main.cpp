#include "ScalarConverter.hpp"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Error: Invalid number of arguments" << std::endl;
    return 1;
  }
  ScalarConverter sc(argv[1]);
  sc.convert();
  return 0;
}
