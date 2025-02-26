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

FragTrap::FragTrap(const FragTrap &fragTrap) : ClapTrap(fragTrap)
{
  std::cout << "FragTrap copy constructor called" << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &fragTrap)
{
  std::cout << "FragTrap assignation operator called" << std::endl;
  _name = fragTrap._name;
  _hitPoints = fragTrap._hitPoints;
  _energyPoints = fragTrap._energyPoints;
  _attackDamage = fragTrap._attackDamage;
  return *this;
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


