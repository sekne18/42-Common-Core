#include "Replace.hpp"

int main(int ac, char **av)
{
  if (ac != 4)
  {
    std::cerr << "Error: Usage: " << av[0] << " <filename> <word to replace> <new word>" << std::endl;
    return 1;
  }
  Replace r;
  r.replace(av[1], av[2], av[3]);
  return 0;
}
