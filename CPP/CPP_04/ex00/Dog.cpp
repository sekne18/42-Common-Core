#include "Dog.hpp"

Dog::Dog()
{
  std::cout << "Dog constructor called" << std::endl;
  _type = "Dog";
  _sound = "Woof";
}

Dog::Dog(const Dog &other) : Animal()
{
  std::cout << "Dog copy constructor called" << std::endl;
  _type = other._type;
  _sound = other._sound;
}

Dog &Dog::operator=(const Dog &other)
{
  std::cout << "Dog assignment operator called" << std::endl;
  if (this != &other)
  {
    _type = other._type;
    _sound = other._sound;
  }
  return *this;
}

Dog::~Dog()
{
  std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound()
{
  std::cout << _sound << std::endl;
}

