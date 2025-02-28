#include "Ice.hpp"

Ice::Ice() : AMateria("ice")
{
  std::cout << "Ice default constructor" << std::endl;
  _type = "ice";
}

Ice::Ice(const Ice &copy) : AMateria("ice")
{
  std::cout << "Ice copy constructor" << std::endl;
  _type = copy._type;
  *this = copy;
}

Ice::~Ice() {}

Ice &Ice::operator=(const Ice &copy)
{
  if (this == &copy)
    return *this;
  this->_type = copy._type;
  return *this;
}

Ice *Ice::clone() const
{
  return new Ice(*this);
}

std::string const &Ice::getType() const
{
  return _type;
}

void Ice::use(ICharacter &target) {
  std::cout << " shoots an ice bolt at " << target.getName() << std::endl;
}
