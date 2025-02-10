#include "Dog.hpp"

Dog::Dog()
{
  std::cout << "Dog constructor called" << std::endl;
  _type = "Dog";
  _sound = "Woof";
  _brain = new Brain();
}

Dog::~Dog()
{
  std::cout << "Dog destructor called" << std::endl;
  delete _brain;
}

void Dog::makeSound() const
{
  std::cout << _sound << std::endl;
}

