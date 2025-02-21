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
  _type = other._type;
  return *this;
}

WrongCat::WrongCat(const WrongCat &other) : WrongAnimal()
{
  *this = other;
}
