#include "Animal.hpp"

AAnimal::AAnimal()
{
  std::cout << "Animal constructor called" << std::endl;
  _type = "Dinaosaur";
  _sound = "Rawr";
}

AAnimal::~AAnimal()
{
  std::cout << "Animal destructor called" << std::endl;
}
