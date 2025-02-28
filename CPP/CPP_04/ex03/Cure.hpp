#ifndef CURE_HPP
#define CURE_HPP

#include "AMateria.hpp"

class Cure : public AMateria
{
private:
  std::string _type;
public:
  Cure();
  Cure(const Cure &copy);
  ~Cure();
  Cure &operator=(const Cure &assign);
  std::string const &getType() const;
  Cure *clone() const;
  void use(ICharacter &target);
};

#endif // CURE_HPP
