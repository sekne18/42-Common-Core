#include "WrongCat.hpp"

WrongCat::WrongCat()
{
  _type = "WrongCat";
  std::cout << "WrongCat constructor called" << std::endl;
}

WrongCat::~WrongCat()
{
  std::cout << "WrongCat destructor called" << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &other)
{
  std::cout << "WrongCat assignment operator called" << std::endl;
  _type = other._type;
  return *this;
}

WrongCat::WrongCat(const WrongCat &other) : WrongAnimal()
{
  std::cout << "WrongCat copy constructor called" << std::endl;
  *this = other;
}

void WrongCat::makeSound() const
{
  std::cout << "WrongCat Meow Meow" << std::endl;
}
