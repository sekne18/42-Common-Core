#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
  int i = -1;

  Animal *animals[10];
  while (++i < 10)
  {
    if (i % 2 == 0)
      animals[i] = new Dog();
    else
      animals[i] = new Cat();
  }
  
  while (--i >= 0)
    animals[i]->makeSound();

  while (++i < 10)
    delete animals[i];
  return 0;
}
