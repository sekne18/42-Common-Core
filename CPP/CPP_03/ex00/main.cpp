#include "ClapTrap.hpp"

int main()
{
  ClapTrap clapTrap("ClapTrap");
  clapTrap.attack("enemy");
  clapTrap.takeDamage(5);
  clapTrap.beRepaired(5);
  return 0;
}
