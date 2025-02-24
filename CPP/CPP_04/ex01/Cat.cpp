#include "Cat.hpp"

Cat::Cat()
{
  std::cout << "Cat constructor called" << std::endl;
  _type = "Cat";
  _sound = "Meow";
  _brain = new Brain();
}

Cat::Cat(const Cat &other) : Animal(other)
{
  std::cout << "Cat copy constructor called" << std::endl;
  _type = other._type;
  _sound = other._sound;
  _brain = new Brain(*other._brain);
}

Cat &Cat::operator=(const Cat &other)
{
  std::cout << "Cat assignment operator called" << std::endl;
  if (this != &other)
  {
    _type = other._type;
    _sound = other._sound;
    delete _brain;
    _brain = new Brain(*other._brain);
  }
  return *this;
}

Cat::~Cat()
{
  std::cout << "Cat destructor called" << std::endl;
  delete _brain;
}

void Cat::makeSound()
{
  std::cout << _sound << std::endl;
}
