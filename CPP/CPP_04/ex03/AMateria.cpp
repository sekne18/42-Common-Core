#include "AMateria.hpp"

AMateria::AMateria() : _type("default")
{
  std::cout << "AMateria constructor called" << std::endl;
}

AMateria::AMateria(std::string const & type) : _type(type)
{
  std::cout << "AMateriaconstructor called" << std::endl;
}

AMateria::AMateria(AMateria const &src) : _type(src._type)
{
  std::cout << "AMateria copy constructor called" << std::endl;
}

AMateria::~AMateria()
{
  std::cout << "AMateria destructor called" << std::endl;
}

std::string const & AMateria::getType() const
{
  return this->_type;
}

void AMateria::use(ICharacter& target)
{
  std::cout << "* uses some materia on " << target.getName() << " *" << std::endl;
}
