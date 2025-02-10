#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap()
{
  std::cout << "ScavTrap default constructor called" << std::endl;
  _hitPoints = 100;
  _energyPoints = 50;
  _attackDamage = 20;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
  std::cout << "ScavTrap name constructor called" << std::endl;
  _hitPoints = 100;
  _energyPoints = 50;
  _attackDamage = 20;
}

ScavTrap::~ScavTrap()
{
  std::cout << "ScavTrap destructor called" << std::endl;
}

void ScavTrap::attack(const std::string &target)
{
  std::cout << "ScavTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" << std::endl;
}

void ScavTrap::guardGate()
{
  std::cout << "ScavTrap " << _name << " has entered in Gate keeper mode" << std::endl;
}
