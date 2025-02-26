#include "Harl.hpp"

/*
* Program expects a single argument, the log level and prints the corresponding message
* It should print level above the given level as well
* for example, if the log level is info, it should print info, warning, error and debug
 * */
int main(int ac, char **av)
{
  if (ac != 2)
  {
    std::cout << "Usage: ./harl <log level>" << std::endl;
    return 1;
  }
  Harl harl;
  harl.complain(av[1]);
  return 0;
}
