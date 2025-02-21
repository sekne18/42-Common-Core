#include "Animal.hpp"

AAnimal::AAnimal()
{
  std::cout << "Animal constructor called" << std::endl;
  _type = "Dinaosaur";
  _sound = "Rawr";
}

AAnimal::AAnimal(AAnimal const &src)
{
  std::cout << "Animal copy constructor called" << std::endl;
  _type = src.getType();
  _sound = src._sound;
}

AAnimal &AAnimal::operator=(AAnimal const &rhs)
{
  std::cout << "Animal assignation operator called" << std::endl;
  if (this != &rhs)
  {
    _type = rhs.getType();
    _sound = rhs._sound;
  }
  return *this;
}

std::string AAnimal::getType() const
{
  return _type;
}

AAnimal::~AAnimal()
{
  std::cout << "Animal destructor called" << std::endl;
}
