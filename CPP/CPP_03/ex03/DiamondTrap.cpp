#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
{
  std::cout << "DiamondTrap default constructor called" << std::endl;
  _name = "default";
  _hitPoints = FragTrap::_hitPoints;
  _energyPoints = ScavTrap::_energyPoints; 
  _attackDamage = FragTrap::_attackDamage;
}

DiamondTrap::DiamondTrap(const std::string &name) : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name)
{
  std::cout << "DiamondTrap constructor called" << std::endl;
  _name = name;
  _hitPoints = FragTrap::_hitPoints;
  _energyPoints = ScavTrap::_energyPoints;
  _attackDamage = FragTrap::_attackDamage;
}

DiamondTrap::DiamondTrap(const DiamondTrap &diamondTrap) : ClapTrap(diamondTrap), ScavTrap(diamondTrap), FragTrap(diamondTrap)
{
  std::cout << "DiamondTrap copy constructor called" << std::endl;
  _name = diamondTrap._name;
  _hitPoints = diamondTrap._hitPoints;
  _energyPoints = diamondTrap._energyPoints;
  _attackDamage = diamondTrap._attackDamage;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &diamondTrap)
{
  std::cout << "DiamondTrap assignation operator called" << std::endl;
  if (this == &diamondTrap)
    return *this;
  _name = diamondTrap._name;
  _hitPoints = diamondTrap._hitPoints;
  _energyPoints = diamondTrap._energyPoints;
  _attackDamage = diamondTrap._attackDamage;
  return *this;
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
