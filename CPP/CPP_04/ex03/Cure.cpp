#include "Cure.hpp"

Cure::Cure() : AMateria("cure")
{
  std::cout << "Cure default constructor" << "\n";
  _type = "cure";
}

Cure::Cure(const Cure &copy) : AMateria("cure")
{
  std::cout << "Cure copy constructor" << "\n";
  _type = copy._type;
  *this = copy;
}

Cure::~Cure() {}

Cure &Cure::operator=(const Cure &copy) {
  if (this == &copy)
    return *this;
  this->_type = copy._type;
  return *this;
}

Cure *Cure::clone() const {
  return new Cure(*this);
}

std::string const &Cure::getType() const {
  return _type;
}

void Cure::use(ICharacter &target) {
  std::cout << " heals " << target.getName() << "’s wounds" << "\n";
}
