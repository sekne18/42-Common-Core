#include "Animal.hpp"

Animal::Animal()
{
  std::cout << "Animal constructor called" << std::endl;
  _type = "Dinaosaur";
  _sound = "Rawr";
}

Animal::Animal(const Animal &other)
{
  std::cout << "Animal copy constructor called" << std::endl;
  _type = other._type;
  _sound = other._sound;
}

Animal &Animal::operator=(const Animal &other)
{
  std::cout << "Animal assignment operator called" << std::endl;
  if (this != &other)
  {
    _type = other._type;
    _sound = other._sound;
  }
  return *this;
}

Animal::~Animal()
{
  std::cout << "Animal destructor called" << std::endl;
}

void Animal::makeSound()
{
  std::cout << _sound << std::endl;
}

std::string Animal::getType() const
{
  return _type;
}
