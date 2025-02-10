#include "FragTrap.hpp" 

FragTrap::FragTrap() : ClapTrap()
{
  std::cout << "FragTrap default constructor called" << std::endl;
  _hitPoints = 100;
  _energyPoints = 100;
  _attackDamage = 30;
}

FragTrap::~FragTrap()
{
  std::cout << "FragTrap destructor called" << std::endl;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
  std::cout << "FragTrap parameter constructor called" << std::endl;
  _hitPoints = 100;
  _energyPoints = 100;
  _attackDamage = 30;
}

void FragTrap::highFivesGuys(void)
{
  std::cout << "FragTrap " << _name << " requests a high five" << std::endl;
}


