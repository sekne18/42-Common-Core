#include "FragTrap.hpp"

int main()
{
  FragTrap fragTrap("FragTrap");
  //ScavTrap scavTrap("ScavTrap");

  fragTrap.attack("enemy");
  fragTrap.takeDamage(10);
  fragTrap.beRepaired(10);
  fragTrap.beRepaired(1);
  fragTrap.highFivesGuys();
  return 0;
}
