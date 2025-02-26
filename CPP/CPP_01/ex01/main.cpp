#include "Zombie.hpp"

int main()
{
  int i = -1;
  Zombie* horde = zombieHorde(5, "Zombie");
  if (horde)
  {
    while (++i < 5)
      horde[i].announce();
    delete[] horde;
  }
  return 0;
}
