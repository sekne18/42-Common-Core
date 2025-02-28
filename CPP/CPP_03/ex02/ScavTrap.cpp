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

ScavTrap::ScavTrap(const ScavTrap &scavTrap) : ClapTrap(scavTrap)
{
  std::cout << "ScavTrap copy constructor called" << std::endl;
  _name = scavTrap._name;
  _hitPoints = scavTrap._hitPoints;
  _energyPoints = scavTrap._energyPoints;
  _attackDamage = scavTrap._attackDamage;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &scavTrap)
{
  std::cout << "ScavTrap assignation operator called" << std::endl;
  if (this == &scavTrap)
    return *this;
  _name = scavTrap._name;
  _hitPoints = scavTrap._hitPoints;
  _energyPoints = scavTrap._energyPoints;
  _attackDamage = scavTrap._attackDamage;
  return *this;
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
