#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
  AAnimal a;
  AAnimal* dog = new Dog(); 
  dog->makeSound();

  delete dog;
  return 0;
}
