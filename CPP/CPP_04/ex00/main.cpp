#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
  Animal *meta = new Animal();
  Animal *j = new Dog();
  Animal *i = new Cat();
  std::cout << j->getType() << " " << std::endl;
  std::cout << i->getType() << " " << std::endl;
  i->makeSound();
  j->makeSound();
  meta->makeSound();
  delete meta;
  delete j;
  delete i;

  std::cout << "=============================" << std::endl;
  
  WrongAnimal *j2 = new WrongCat();
  j2->makeSound();
  delete j2;


  
  return 0;
}
