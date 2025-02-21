#include "Cat.hpp"

Cat::Cat()
{
  std::cout << "Cat constructor called" << std::endl;
  _type = "Cat";
  _sound = "Meow meow";
  _brain = new Brain();
}

Cat::Cat(Cat const &src) : AAnimal(src)
{
  std::cout << "Cat copy constructor called" << std::endl;
  _type = src.getType();
  _sound = src._sound;
  _brain = new Brain();
}

Cat &Cat::operator=(Cat const &rhs)
{
  std::cout << "Cat assignation operator called" << std::endl;
  if (this != &rhs)
  {
    _type = rhs.getType();
    _sound = rhs._sound;
    _brain = new Brain();
  }
  return *this;
}

Cat::~Cat()
{
  std::cout << "Cat destructor called" << std::endl;
  delete _brain;
}

void Cat::makeSound() const
{
  std::cout << _sound << std::endl;
}
