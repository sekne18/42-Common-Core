#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
  Dog *j = new Dog();
  Cat *i = new Cat();

  j->makeSound();
  std::cout << j->getType() << std::endl;
  i->makeSound();
  std::cout << i->getType() << std::endl;

  Dog *deepCopyDog = new Dog(*j);
  AAnimal *deepCopyCat = new Cat();

  deepCopyDog->makeSound();
  deepCopyCat->makeSound();

  delete j;
  delete i;
  delete deepCopyDog;
  delete deepCopyCat;

  return 0;
}
