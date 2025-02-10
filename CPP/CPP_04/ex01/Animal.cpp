#include "Animal.hpp"

Animal::Animal()
{
  std::cout << "Animal constructor called" << std::endl;
  _type = "Dinaosaur";
  _sound = "Rawr";
}

Animal::~Animal()
{
  std::cout << "Animal destructor called" << std::endl;
}

void Animal::makeSound() const
{
  std::cout << _sound << std::endl;
}

std::string Animal::getType() const
{
  return _type;
}
