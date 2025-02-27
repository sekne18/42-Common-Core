#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
{
  std::cout << "ClapTrap default constructor called" << std::endl;
  _name = "default";
  _hitPoints = 10;
  _energyPoints = 10;
  _attackDamage = 0;
}

ClapTrap::~ClapTrap()
{
  std::cout << "ClapTrap destructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name)
{
  std::cout << "ClapTrap parameterized constructor called" << std::endl;
  _name = name;
  _hitPoints = 10;
  _energyPoints = 10;
  _attackDamage = 0;
}

ClapTrap::ClapTrap(const ClapTrap &clapTrap)
{
  std::cout << "ClapTrap copy constructor called" << std::endl;
  _name = clapTrap._name;
  _hitPoints = clapTrap._hitPoints;
  _energyPoints = clapTrap._energyPoints;
  _attackDamage = clapTrap._attackDamage;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &clapTrap)
{
  std::cout << "ClapTrap assignation operator called" << std::endl;
  _name = clapTrap._name;
  _hitPoints = clapTrap._hitPoints;
  _energyPoints = clapTrap._energyPoints;
  _attackDamage = clapTrap._attackDamage;
  return *this;
}

void ClapTrap::attack(const std::string &target)
{
  if (_energyPoints == 0) {
    std::cout << "ClapTrap " << _name << " is out of energy and cannot attack!" << std::endl;
    return;
  } else if (_hitPoints == 0) {
    std::cout << "ClapTrap " << _name << " is dead and cannot attack!" << std::endl;
  } else {
    std::cout << "ClapTrap " << _name << " attacks " << target << " causing " << _attackDamage << " points of damage!" << std::endl;
    _energyPoints -= 1;
  }
}

void ClapTrap::takeDamage(unsigned int amount)
{
  if (_hitPoints == 0) {
    std::cout << "ClapTrap " << _name << " is already dead!" << std::endl;
    return;
  } else if (_hitPoints < (int)amount) {
    std::cout << "ClapTrap " << _name << " has died!" << std::endl;
    _hitPoints = 0;
  } else {
    std::cout << "ClapTrap " << _name << " takes " << amount << " points of damage!" << std::endl;
    _hitPoints -= amount;
  }
}

void ClapTrap::beRepaired(unsigned int amount)
{
  if (_energyPoints == 0) {
    std::cout << "ClapTrap " << _name << " is out of energy and cannot be repaired!" << std::endl;
    return;
  } else {
    std::cout << "ClapTrap " << _name << " is repaired for " << amount << " points of health!" << std::endl;
    _hitPoints += amount;
    _energyPoints -= 1;
  }
}
