#include "Cat.hpp"

Cat::Cat()
{
  std::cout << "Cat constructor called" << std::endl;
  _type = "Cat";
  _sound = "Meow";
}

Cat::~Cat()
{
  std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound() const
{
  std::cout << _sound << std::endl;
}
