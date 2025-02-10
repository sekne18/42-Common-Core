#ifndef FRAG_TRAP_HPP
#define FRAG_TRAP_HPP

#include <iostream>
#include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap
{
public:
  FragTrap();
  FragTrap(std::string name);
  ~FragTrap();
  void highFivesGuys(void);
  
};

#endif // FRAG_TRAP_HPP
