#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
  // Create and fill an array of Animal objects. Half dogs, half cats.
  int i = -1;

  Animal *animals[10];
  while (++i < 10)
  {
    if (i % 2 == 0)
      animals[i] = new Dog();
    else
      animals[i] = new Cat();
  }
  
  i = -1;
  while (++i < 10)
    delete animals[i];

  return 0;
}
