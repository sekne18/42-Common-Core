#include "Cat.hpp"

Cat::Cat()
{
  std::cout << "Cat constructor called" << std::endl;
  _type = "Cat";
  _sound = "Meow";
}

Cat::Cat(const Cat &other) : Animal()
{
  std::cout << "Cat copy constructor called" << std::endl;
  _type = other._type;
  _sound = other._sound;
}

Cat &Cat::operator=(const Cat &other)
{
  std::cout << "Cat assignment operator called" << std::endl;
  if (this != &other)
  {
    _type = other._type;
    _sound = other._sound;
  }
  return *this;
}

Cat::~Cat()
{
  std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound()
{
  std::cout << _sound << std::endl;
}
