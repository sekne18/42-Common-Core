#ifndef ClapTrap_HPP
#define ClapTrap_HPP

#include <iostream>

class ClapTrap
{
protected:
  std::string _name;
  int _hitPoints;
  int _energyPoints;
  int _attackDamage;

public:
  ClapTrap();
  ClapTrap(std::string name);
  ClapTrap(const ClapTrap &clapTrap);
  ClapTrap &operator=(const ClapTrap &clapTrap);
  virtual ~ClapTrap();
  virtual void attack(const std::string &target);
  void takeDamage(unsigned int amount);
  void beRepaired(unsigned int amount);

};

#endif // ClapTrap_HPP
