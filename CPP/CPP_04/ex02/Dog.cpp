#include "Dog.hpp"

Dog::Dog()
{
  std::cout << "Dog constructor called" << std::endl;
  _type = "Dog";
  _sound = "Woof woof";
  _brain = new Brain();
}

Dog &Dog::operator=(Dog const &rhs)
{
  if (this != &rhs)
  {
    _type = rhs._type;
    _sound = rhs._sound;
    _brain = new Brain();
  }
  return *this;
}

Dog::Dog(Dog const &src) : AAnimal(src)
{
  std::cout << "Dog copy constructor called" << std::endl;
  _type = src.getType();
  _sound = src._sound;
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
