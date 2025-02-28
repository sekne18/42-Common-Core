#ifndef ICE_HPP
#define ICE_HPP

#include "AMateria.hpp"

class Ice : public AMateria
{
private:
  std::string _type;
public:
  Ice();
  Ice(const Ice &copy);
  ~Ice();
  Ice &operator=(const Ice &assign);

  Ice *clone() const;
  void use(ICharacter &target);
  std::string const &getType() const;
};

#endif // ICE_HPP
