#include "Dog.hpp"

Dog::Dog()
{
  std::cout << "Dog constructor called" << std::endl;
  _type = "Dog";
  _sound = "Woof";
  _brain = new Brain();
}

Dog::Dog(const Dog &other) : Animal(other)
{
  std::cout << "Dog copy constructor called" << std::endl;
  _type = other._type;
  _sound = other._sound;
  _brain = new Brain(*other._brain);
}

Dog &Dog::operator=(const Dog &other)
{
  std::cout << "Dog assignment operator called" << std::endl;
  if (this != &other)
  {
    _type = other._type;
    _sound = other._sound;
    delete _brain;
    _brain = new Brain(*other._brain);
  }
  return *this;
}

Dog::~Dog()
{
  std::cout << "Dog destructor called" << std::endl;
  delete _brain;
}

void Dog::makeSound()
{
  std::cout << _sound << std::endl;
}

