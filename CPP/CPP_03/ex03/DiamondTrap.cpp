#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
{
  std::cout << "DiamondTrap default constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const std::string &name) : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name)
{
  std::cout << "DiamondTrap constructor called" << std::endl;
  _name = name;
  _hitPoints = FragTrap::_hitPoints;
  _energyPoints = ScavTrap::_energyPoints;
  _attackDamage = FragTrap::_attackDamage;
}

DiamondTrap::~DiamondTrap()
{
  std::cout << "DiamondTrap destructor called" << std::endl;
}

void DiamondTrap::attack(const std::string &target)
{
  ScavTrap::attack(target);
}

void DiamondTrap::whoAmI()
{
  std::cout << "My name is " << _name << std::endl;
}
