#ifndef FRAG_TRAP_HPP
#define FRAG_TRAP_HPP

#include <iostream>
#include "ClapTrap.hpp"

class FragTrap : public ClapTrap
{
public:
  FragTrap();
  FragTrap(std::string name);
  ~FragTrap();
  FragTrap(const FragTrap &fragTrap);
  FragTrap &operator=(const FragTrap &fragTrap);
  void highFivesGuys(void);
  
};

#endif // FRAG_TRAP_HPP
